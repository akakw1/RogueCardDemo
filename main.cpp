#include "include/DatabaseManager.h"
#include "include/RedisManager.h"
#include "include/LogManager.h"
#include "include/status.h"
#include "include/core.h"
#include "include/Connection.h"

#include <json/json.h>
#include <fstream>
#include <string>

Json::Value config;
STATUS status = START;

void loadConfig() {
    std::ifstream in("config.json");
    in >> config;
    in.close();
}
void initLogger() {
    LM logger = LogManager::getInstance();
    Json::Value loggerConfig = config["logger"];
    std::string configFile = loggerConfig["configFile"].asString();
    logger->init(configFile);
}
void initDB() {
    DBM db = DatabaseManager::getInstance();
    Json::Value dbConfig = config["database"];
    std::string host = dbConfig["host"].asString();
    std::string user = dbConfig["user"].asString();
    std::string password = dbConfig["password"].asString();
    std::string database = dbConfig["database"].asString();
    bool debug = dbConfig["debug"].asBool();
    db->init(host, user, password, database, debug);
}
void initRedis() {
    RM rm = RedisManager::getInstance();
    Json::Value redisConfig = config["redis"];
    std::string host = redisConfig["host"].asString();
    int port = redisConfig["port"].asInt();
    rm->init(host, port);
}
void initCore() {
    Json::Value serverConfig = config["server"];
    std::string host = serverConfig["host"].asString();
    int port = serverConfig["port"].asInt();
    core.init(host, port);
}

void init() {
    loadConfig();
    initLogger();
    initDB();
    initRedis();
    initCore();

    if(status != ERROR) status = REDAY;

    core.start();
    Connection conn;
    conn.accept(core.getSocket());
    conn.loop();

    LogManager::getInstance()->info("system closed");
}

int main() {
    init();
    return 0;
}