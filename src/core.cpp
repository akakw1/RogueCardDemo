#include "../include/core.h"

Core::Core() {
    ready = false;
}
Core::~Core() {}

void Core::init() {
    logger = LogManager::getInstance();
    db = DatabaseManager::getInstance();
    redis = RedisManager::getInstance();

    ready = true;

    if(logger == NULL) {}
    if(db == NULL) {}
    if(redis == NULL) {}

    if(ready) logger->info("Core is ready");
}

void Core::loop() {
    if(! requestQueue.empty()) {
        solve(requestQueue.front().first, requestQueue.front().second);
        requestQueue.pop();
    }
}

void Core::add(Json::Value* request, Json::Value* reply) {
    requestQueue.push(std::make_pair(request, reply));
    loop();
}