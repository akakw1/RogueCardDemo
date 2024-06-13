#include "DatabaseManager.h"
#include "LogManager.h"
#include "RedisManager.h"

#include <queue>
#include <utility>
#include <json/json.h>

class Core {
    private :

    std::queue<std::pair<Json::Value*, Json::Value*> > requestQueue;
    LM logger;
    DBM db;
    RM redis;
    bool ready;

    void solve(Json::Value* request, Json::Value* reply);

    public :

    Core();
    ~Core();
    void init();

    void loop();

    void add(Json::Value* request, Json::Value* reply);

    bool signIn(const int &id, const std::string &password, std::string &token);
    void getData(Json::Value &res);

} core;