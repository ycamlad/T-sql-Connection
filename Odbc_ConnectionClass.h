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
    bool InsertStudent(const std::wstring &theFirstname, const std::wstring&theLastname,const std::wstring&theCity,std::vector<std::vector<std::string>>& result);
    bool SelectAllOrByID( const SQLINTEGER &ID, std::vector<std::vector<std::string>>& reuslt);
    bool UpdateStudent(const SQLINTEGER *ID,std::wstring &Firstname,std::wstring &Lastname,std::wstring &City, std::vector<std::vector<std::string>>& result);
    SQLWCHAR deleteWhiteSpace(SQLWCHAR word);
    bool DeleteByID( const SQLINTEGER* ID, std::vector<std::vector<std::string>>& result);
    void Disconnect();



private:
    SQLHANDLE sqlConnHandle;
    SQLHANDLE sqlStmtHandle;
    SQLHANDLE sqlEnvHandle;
    SQLWCHAR retconstring[SQL_RETURN_CODE_LEN];
    

};