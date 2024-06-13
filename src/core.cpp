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

void Core::solve(Json::Value* request, Json::Value* reply) {
    Json::Value &req = *request;
    Json::Value &rep = *reply;
    std::string op = req["operation"].asString();
    if(op == "SignIn") {
        int id = req["id"].asInt();
        std::string password = req["password"].asString();
        std::string token;
        bool flag = signIn(id, password, token);
        rep["operation"] = "SignInResult";
        rep["result"] = flag ? "success" : "fail";
        if(flag) {
            rep["token"] = token;
        }
    }
    else if(op == "getData") {
        Json::Value res;
        getData(res);
        rep["operation"] = "GetDataResult";
        rep["monsterList"] = res;
    }
}

bool Core::signIn(const int &id, const std::string &password, std::string &token) {
    bool result = db->signIn(id, password);
    if(! result) return 0;
    token = "aaa";
    redis->putToken(id, token);
    return 1;
}
void Core::getData(Json::Value &res) {
    db->getData(res);
}