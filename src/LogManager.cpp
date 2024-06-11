#include "../include/LogManager.h"

LM LogManager::instance = nullptr;

LM LogManager::getInstance() {
    if(instance == nullptr) {
        instance = new LogManager();
    }
    return instance;
}

void LogManager::init(std::string conf) {
    log4cplus::PropertyConfigurator::doConfigure(LOG4CPLUS_TEXT(conf));
    logger = log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("logmain"));
    info("log manager init success");
}

void LogManager::info(std::string msg) {
    LOG4CPLUS_INFO(logger, LOG4CPLUS_TEXT(msg));
}

LogManager::LogManager() {}