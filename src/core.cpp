#include "../include/core.h"

Core core;

Core::Core() {
    ready = false;
}
Core::~Core() {
}

void Core::init(const std::string &host, int port) {
    logger = LogManager::getInstance();
    db = DatabaseManager::getInstance();
    redis = RedisManager::getInstance();

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(host.c_str());
    addr.sin_port = htons(port);

    ready = true;

    if(logger == NULL) {}
    if(db == NULL) {}
    if(redis == NULL) {}

    if(ready) logger->info("Core is ready");
}
int Core::getSocket() { return serverSocket;}

void Core::loop() {
    if(! requestQueue.empty()) {
        solve(requestQueue.front().first, requestQueue.front().second);
        requestQueue.pop();
    }
}
void Core::start() {
    logger->info("core is running");
    status = RUNNING;
    bind(serverSocket, (sockaddr*) &addr, sizeof(addr));
    listen(serverSocket, 1);
    logger->info("server listening");
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