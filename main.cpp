#include "include/DatabaseManager.h"
#include "include/RedisManager.h"
#include "include/LogManager.h"
#include "include/status.h"

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

void init() {
    loadConfig();
    initLogger();
    initDB();
    initRedis();

    if(status != ERROR) status = REDAY;

    LogManager::getInstance()->info("system closed");
}

int main() {
    init();
    return 0;
}