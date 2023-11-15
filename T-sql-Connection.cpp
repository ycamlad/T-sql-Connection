
#include "Odbc_ConnectionClass.h"

int main() {

    //Odbc_ConnectionClass db;

    //if (db.Connect("DESKTOP-53IN7K4\\MSSQLSERVER02", "StudentManagement")) {
    //    SQLWCHAR* query = (SQLWCHAR*)L"SELECT * FROM StudentInformation";

    //    SQLWCHAR* query2 = (SQLWCHAR*)L"SELECT @@VERSION";
    //    std::vector<std::vector<std::string>> result;
    //    std::vector<std::vector<SQLWCHAR>> result2;

    //    if (db.ExecuteQuery(query, result)) {

    //        for (const auto& row : result) {
    //            for (const auto& col : row) {
    //                std::cout << col << "\t";
    //            }
    //            std::cout << std::endl;
    //        }
    //    }
    //    else {
    //        std::cerr << "Error executing the query." << std::endl;
    //    }
    //    //db.Disconnect();
    //    return 0;
    //}
    //else {

    //    std::cerr << "Error connecting to the database." << std::endl;
    //    return -1;
    //}


    for (int m = 1; m <= 10; m++) {
        if (m % 2 == 1) {
            for (int i = 1; i <= 7; i++) {
                if (i % 2 == 1) {
                    for (int j = 0; j < 10; j++) {
                        std::cout << " /";
                    }
                }
            }
             if (m % 2 == 0) {
                for (int k = 0; k < 10; k++) {
                    if (k == 0 || k == 9) {
                        std::cout << " /";
                    }
                    else {
                        std::cout << "  ";
                    }
                }
            }
            std::cout << std::endl;
        }
    }


    return 0;
}