#pragma once

#include "DatabaseManager.h"
#include "LogManager.h"
#include "RedisManager.h"
#include "status.h"

#include <queue>
#include <string>
#include <utility>
#include <json/json.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

class Core {
    private :

    std::queue<std::pair<Json::Value*, Json::Value*> > requestQueue;
    LM logger;
    DBM db;
    RM redis;
    bool ready;
    int serverSocket;
    sockaddr_in addr;

    void solve(Json::Value* request, Json::Value* reply);

    public :

    Core();
    ~Core();
    void init(const std::string &host, int port);
    int getSocket();

    void loop();
    void start();

    void add(Json::Value* request, Json::Value* reply);

    bool signIn(const int &id, const std::string &password, std::string &token);
    void getData(Json::Value &res);

} ;
extern Core core;
extern STATUS status;