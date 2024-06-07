#pragma once

#include <sqlpp11/mysql/mysql.h>
#include <string>

typedef class DatabaseManager {
    //----------------
    private :

    static DBM instance; // 单例模式
    DatabaseManager();

    sqlpp::mysql::connection_config conf; // 数据库连接配置
    sqlpp::mysql::connection conn; // 数据库连接

    // ---------------
    public :

    void init(const std::string host, const std::string user, const std::string password, const std::string database, const bool debug);
    DBM getInstance();

    bool signUp(const std::string username, const std::string password);
    bool signIn(const std::string username, const std::string password);

} *DBM;

DBM DatabaseManager::instance = nullptr;