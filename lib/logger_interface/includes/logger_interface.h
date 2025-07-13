//
// Created by mateusz on 7/13/25.
//

#ifndef LOGGER_INTERFACE_H
#define LOGGER_INTERFACE_H

#include <memory>
#include <string>

namespace Evo {
    class Logger {
    public:
        virtual ~Logger() = default;

        virtual void printInfo(const std::string &text) = 0;
    };

    class DummyLogger final : public Logger {
    public:
        void printInfo(const std::string &text) override {
            /*do nothing*/
        }
    };

    inline static std::unique_ptr<Logger> logger = std::make_unique<DummyLogger>();
}

#ifdef LOGGER_ENABLED
#define LOG_INFO(text) Evo::logger->printInfo(text);
#else
#define LOG_INFO(text) ;
#endif

#endif //LOGGER_INTERFACE_H
