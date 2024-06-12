#include "../include/RedisManager.h"

#include <cstring>

extern STATUS status;

RM RedisManager::instance = nullptr;

RM RedisManager::getInstance() {
    if(instance == nullptr) {
        instance = new RedisManager();
    }
    return instance;
}

RedisManager::RedisManager() {
    logger = LogManager::getInstance();
    logger->info("Redis Manager onCreate");
}
RedisManager::~RedisManager() {
    redisFree(conn);
}

void RedisManager::init(std::string host, int port) {
    conn = redisConnect(host.c_str(), port);
    if(conn != NULL && conn->err) {
        status = ERROR;
        logger->info("Redis connect failed");
        return;
    }
    logger->info("Redis connect success");
}

void RedisManager::putToken(int userId, std::string token) {
    redisReply* reply = (redisReply*)redisCommand(conn, "SET %d %s", userId, token.c_str());
    if(reply->type == REDIS_REPLY_STATUS && strcasecmp(reply->str, "OK") == 0) {}
    else {
        logger->info("Redis set failed");
    }
    freeReplyObject(reply);
}
bool RedisManager::checkToken(int userId, std::string token) {
    redisReply* reply = (redisReply*)redisCommand(conn, "GET %d", userId);
    if(reply->type == REDIS_REPLY_ERROR) {
        logger->info("Redis get failed");
        freeReplyObject(reply);
        return 0;
    }
    bool result = false;
    if(reply->type == REDIS_REPLY_STRING) {
        result = (token == reply->str);
    }
    freeReplyObject(reply);
    return result;
}
void RedisManager::removeToken(int userId) {
    redisReply* reply = (redisReply*)redisCommand(conn, "DEL %d", userId);
    if(reply->type == REDIS_REPLY_INTEGER) {}
    else {
        logger->info("Redis del failed");
    }
    freeReplyObject(reply);
}