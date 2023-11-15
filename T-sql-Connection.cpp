
#include "Odbc_ConnectionClass.h"

int main() {

    Odbc_ConnectionClass db;

    if (db.Connect("DESKTOP-53IN7K4\\MSSQLSERVER02", "StudentManagement")) {
        SQLWCHAR* query = (SQLWCHAR*)L"SELECT * FROM StudentInformation";

        SQLWCHAR* query2 = (SQLWCHAR*)L"SELECT @@VERSION";
        std::vector<std::vector<std::string>> result;
        std::vector<std::vector<SQLWCHAR>> result2;

        if (db.ExecuteQuery(query, result)) {

            for (const auto& row : result) {
                for (const auto& col : row) {
                    std::cout << col << "\t";
                }
                std::cout << std::endl;
            }
        }
        else {
            std::cerr << "Error executing the query." << std::endl;
        }
        //db.Disconnect();
        return 0;
    }
    else {

        std::cerr << "Error connecting to the database." << std::endl;
        return -1;
    }


    return 0;
}