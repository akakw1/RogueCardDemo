#pragma once

#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>
#include <log4cplus/configurator.h>
#include <string>

typedef class LogManager {
    private :
        static LogManager* instance;
        log4cplus::Logger logger;
        log4cplus::BasicConfigurator config;

        LogManager();

    public :
        static LogManager* getInstance();
        void init(std::string conf);
        void info(std::string msg);
} *LM;

//#define INFO(s) (LogManager::getInstance()->info(s))
