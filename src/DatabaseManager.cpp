#include "../include/DatabaseManager.h"

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

    conn(conf);
}

bool DatabaseManager::signUp(const std::string username, const std::string password) {
    demo::Accounts tmp;
    conn(insert_into(tmp).set(tmp.userName = username, tmp.passWord = password));
    return 1;
}
bool DatabaseManager::signIn(const std::string username, const std::string password) {
    demo::Accounts tmp;
    auto result = conn(select(tmp.userId).from(tmp).where(tmp.userName == username && tmp.passWord = password));
    return ! result.empty();
}

DatabaseManager::DatabaseManager() {
    printf("Database Manager onCreate\n");
}