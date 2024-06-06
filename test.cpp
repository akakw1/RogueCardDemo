#include "include/demo.h"
#include <sqlpp11/mysql/mysql.h>
#include <sqlpp11/sqlpp11.h>

int main() {
    sqlpp::mysql::connection_config myconfig;
    myconfig.host = "localhost";
    myconfig.user = "DBServer";
    myconfig.password = "DBServer@123";
    myconfig.database = "demo";
    myconfig.debug = true;

    sqlpp::mysql::connection db(myconfig);
    demo::Accounts tmp;
    tmp.userName = "wzx";
    tmp.passWord = "psd";
    db(insert_into(tmp));

    return 0;
}