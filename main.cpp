#include "include/DatabaseManager.h"
#include "include/RedisManager.h"
#include <json/json.h>
#include <fstream>
#include <string>

Json::Value config;
DBM db;

void loadConfig() {
    ifstream in("config.json");
    in >> config;
    in.close();
}
void initDB() {
    db = DatabaseManager::getInstance();
    Json::Value dbConfig = config["database"];
    std::string host = dbConfig["host"];
    std::string user = dbConfig["user"];
    std::string password = dbConfig["password"];
    std::string database = dbconfig["database"];
    std::string debug = dbconfig["debug"];
    db.init(host, user, password, database, debug);
}

int main() {
    loadConfig();
    initDB();
    return 0;
}