#pragma once

#include <hiredis/hiredis.h>
#include <string>

typedef class RedisManager {
// -----------------
    private :

    static RedisManager* instance;
    RedisManager();

    redisContext conn;

// -----------------
    public :

    static RedisManager* getInstance();
    void init(std::string host, int port);

    void putToken(int userId, std::string token);
    bool checkToken(int userId, std::string token);
    void removeToken(int userId);

} *RM;

RM RedisManager::instance = nullptr;