#include "../include/Connection.h"

#include <arpa/inet.h>
#include <unistd.h>

Connection::Connection() {
    logger = LogManager::getInstance();
    addrSize = sizeof(addr);
}

void Connection::accept(int serverSocket) {
    conn = ::accept(serverSocket, (sockaddr*) &addr, &addrSize);
    logger->info("new connection accepted from " + addrToString());
}
bool Connection::recv() {
    ssize_t len = ::recv(conn, buffer, bufferSize, 0);
    if(len <= 0) return false;
    io.clear();
    io.str(buffer);
    io >> request;
    return true;
}
void Connection::send() {
    io.clear();
    io.str(std::string());
    io << reply;
    std::strcpy(buffer, io.str().c_str());
    ::send(conn, buffer, io.str().size(), 0);
}
void Connection::work() {
    core.add(&request, &reply);
}

void Connection::loop() {
    while(recv()) {
        work();
        send();
    }
    close(conn);
}

std::string Connection::addrToString() {
    char ipstr[INET_ADDRSTRLEN];
    std::string res = "";
    inet_ntop(AF_INET, &(addr.sin_addr), ipstr, INET_ADDRSTRLEN);
    res += ipstr;
    res += " : ";
    res += std::to_string(ntohs(addr.sin_port));
    return res;
}