#pragma once

#include <sqlpp11/mysql/mysql.h>
#include <sqlpp11/sqlpp11.h>
#include <string>

#include "demo.h"
#include "LogManager.h"

typedef class DatabaseManager {
    //----------------
    private :

    static DatabaseManager* instance; // 单例模式
    DatabaseManager();

    sqlpp::mysql::connection_config conf; // 数据库连接配置
    sqlpp::mysql::connection conn; // 数据库连接

    LM logger;

    // ---------------
    public :

    void init(const std::string host, const std::string user, const std::string password, const std::string database, const bool debug);
    static DatabaseManager* getInstance();

    bool signUp(const std::string username, const std::string password);
    bool signIn(const std::string username, const std::string password);

} *DBM;