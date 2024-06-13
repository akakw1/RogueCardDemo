#include "../include/DatabaseManager.h"

DBM DatabaseManager::instance = nullptr;

DBM DatabaseManager::getInstance() {
    if(instance == nullptr) {
        instance = new DatabaseManager();
    }
    return instance;
}

void DatabaseManager::init(const std::string host, const std::string user, const std::string password, const std::string database, const bool debug) {
    conf.host = host;
    conf.user = user;
    conf.password = password; 
    conf.database = database;
    conf.debug = debug;

    conn = sqlpp::mysql::connection(conf);

    logger->info("Database connect success");
}

bool DatabaseManager::signUp(const std::string username, const std::string password) {
    return 1;
}
bool DatabaseManager::signIn(const int id, const std::string password) {
    CardGame::Account tmp;
    auto result = conn(select(tmp.id).from(tmp).where(tmp.id == id and tmp.password == password.c_str()));
    return ! result.empty();
}
void DatabaseManager::getData(Json::Value &res) {
    res = Json::Value(Json::arrayValue);
    CardGame::Enemy tmp;
    Json::Value e;
    for(const auto &row : conn.run(select(tmp.id, tmp.name, tmp.MaxHp).from(tmp).where(tmp.id >= 0))) {
        e["id"] = (int)row.id;
        e["name"] = (std::string)row.name;
        e["MaxHp"] = (int)row.MaxHp;
        res.append(e);
    }
}

DatabaseManager::DatabaseManager() {
    logger = LogManager::getInstance();
    logger->info("Database Manager onCreate");
}