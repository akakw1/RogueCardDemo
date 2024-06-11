#include "include/DatabaseManager.h"
#include "include/RedisManager.h"
#include <json/json.h>
#include <fstream>
#include <string>

Json::Value config;
DBM db;

void loadConfig() {
    std::ifstream in("config.json");
    in >> config;
    in.close();
}
void initDB() {
    db = DatabaseManager::getInstance();
    Json::Value dbConfig = config["database"];
    std::string host = dbConfig["host"].asString();
    std::string user = dbConfig["user"].asString();
    std::string password = dbConfig["password"].asString();
    std::string database = dbConfig["database"].asString();
    bool debug = dbConfig["debug"].asBool();
    db->init(host, user, password, database, debug);
}

int main() {
    loadConfig();
    initDB();
    return 0;
}