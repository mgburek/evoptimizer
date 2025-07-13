//
// Created by mateusz on 7/13/25.
//

#ifndef LOGGER_INTERFACE_H
#define LOGGER_INTERFACE_H

#include <memory>
#include <string>
#include <iostream>
#include <sstream>

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

    class StdLogger final : public Logger {
    public:
        void printInfo(const std::string &text) override {
            std::cout << text << "\n";
        }
    };

    class LoggerInstance {
        inline static std::unique_ptr<Logger> _logger = std::make_unique<DummyLogger>();

    public:
        static void useLogger(std::unique_ptr<Logger> logger) {
            if (logger)
                _logger = std::move(logger);
        }

        template<typename... Args>
        static void logInfo(Args &&... args) {
            if (!_logger)
                return;

            std::ostringstream oss;
            (oss << ... << std::forward<Args>(args));
            _logger->printInfo(oss.str());
        }
    };
}

#ifdef LOGGER_ENABLED
#define LOG_INFO(...) Evo::LoggerInstance::logInfo(__VA_ARGS__);
#else
#define LOG_INFO(text) ;
#endif

#ifdef LOGGER_ENABLED
#define USE_LOGGER(logger_class, ...) \
Evo::LoggerInstance::useLogger(std::make_unique<logger_class>(__VA_ARGS__));
#else
#define USE_LOGGER(logger_class, ...) ;
#endif
#endif //LOGGER_INTERFACE_H
