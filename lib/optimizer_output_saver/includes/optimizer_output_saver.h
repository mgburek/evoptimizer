//
// Created by mateusz on 7/18/25.
//

#ifndef OPTIMIZER_OUTPUT_SAVER_H
#define OPTIMIZER_OUTPUT_SAVER_H

#include <fstream>
#include <map>

namespace Evo {
    class OptimizerOutputSaver {
        std::fstream _file;
        inline static std::map<std::string, std::unique_ptr<OptimizerOutputSaver> > _output_savers;


        template<typename T>
        void write(const T &value) {
            _file.write(reinterpret_cast<const char *>(&value), sizeof(value));
        }

    public:
        explicit OptimizerOutputSaver(const std::string &filename)
            : _file{std::fstream(filename, std::ios::out | std::ios::trunc)} {
        }

        ~OptimizerOutputSaver() {
            if (_file.is_open())
                _file.close();
        }

        template<typename SaveAsType, typename Generation>
        void saveGeneration(Generation generation,
                            const int32_t gen_num, const int32_t optimizer_iteration) {
            if (!_file.is_open()) {
                throw std::runtime_error("Failed to write: file stream is not open.");
            }

            const size_t population_size = generation.size();
            const size_t genes_num = population_size > 0 ? generation[0].size() : 0;

            write(optimizer_iteration);
            write(gen_num);
            write(static_cast<int32_t>(population_size));
            write(static_cast<int32_t>(genes_num));

            for (int32_t i = 0; i < population_size; i++)
                for (int32_t j = 0; j < genes_num; j++)
                    write(static_cast<SaveAsType>(generation[i][j]));

            if (_file.fail()) {
                throw std::runtime_error("Failed to write obstacle data to file.");
            }
        }

        static std::unique_ptr<OptimizerOutputSaver> &getForFile(const std::string &file_name) {
            if (_output_savers.find(file_name) == _output_savers.end())
                _output_savers.emplace(file_name, std::make_unique<OptimizerOutputSaver>(file_name));

            return _output_savers[file_name];
        }
    };
}

#ifdef ENABLE_SAVE_OPTIMIZER_OUTPUT
#define SAVE_GENERATION(file_name, saveType, generation, gen_num, optimizer_iteration) \
    Evo::OptimizerOutputSaver::getForFile(file_name)->saveGeneration<saveType>(         \
            generation,gen_num, optimizer_iteration);
#else
#define SAVE_GENERATION(file_name, saveType, generation, gen_num, optimizer_iteration) ;
#endif


#endif //OPTIMIZER_OUTPUT_SAVER_H
