#include <iostream>
#include <windows.h>
#include <sql.h>
#include <sqltypes.h>
#include <sqlext.h>
#include <string>
#include <vector>
#include <cwchar>
class Odbc_ConnectionClass {
#define SQL_RESULT_LEN 240
#define SQL_RETURN_CODE_LEN 2000
public:
    Odbc_ConnectionClass();
    ~Odbc_ConnectionClass();

    bool Connect(const char* server, const char* database);
    bool SelectQuery(const SQLWCHAR* query, std::vector<std::vector<std::string>>& reuslt);
    bool DeleteQuery( SQLWCHAR* ID, std::vector<std::vector<std::string>>& result);
    void Disconnect();



private:
    SQLHANDLE sqlConnHandle;
    SQLHANDLE sqlStmtHandle;
    SQLHANDLE sqlEnvHandle;
    SQLWCHAR retconstring[SQL_RETURN_CODE_LEN];
    

};