#include "LogManager.h"
#include "core.h"

#include <string>
#include <sstream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <json/json.h>

class Connection {
    // ---------------
    private :

    const static size_t bufferSize = 2048;

    socklen_t addrSize;
    sockaddr_in addr;
    int conn;

    LM logger;

    char buffer[bufferSize];
    Json::Value request;
    Json::Value reply;
    std::stringstream io;

    bool recv();
    void send();
    void work();

    // ---------------
    public :

    Connection();

    void accept(int serverSocket);

    void loop();

    std::string addrToString();
};