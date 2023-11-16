
#include "Odbc_ConnectionClass.h"

int main() {

    Odbc_ConnectionClass db;

    if (db.Connect("DESKTOP-53IN7K4\\MSSQLSERVER02", "StudentManagement")) {
        SQLWCHAR* query = (SQLWCHAR*)L"SELECT * FROM StudentInformation";
        SQLWCHAR* query2 = (SQLWCHAR*)L"SELECT @@VERSION";
        SQLWCHAR* query3 = (SQLWCHAR*)L"INSERT INTO StudentInformation (StudentID) VALUES('857')";
        SQLWCHAR* query4 = (SQLWCHAR*)L"856";


       
        std::vector<std::vector<std::string>> result;
        std::vector<std::vector<SQLWCHAR>> result2;

        //if (db.SelectQuery(query, result)) {

        //    for (const auto& row : result) {
        //        for (const auto& col : row) {
        //            std::cout << col << "\t";
        //        }
        //        std::cout << std::endl;
        //    }
        //}
        //else {
        //    std::cerr << "Error executing the query." << std::endl;
        //}
        ////db.Disconnect();
        //return 0;


        if (db.DeleteQuery(query4, result)) {

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





    //std::string word = "Science!";

    //for (int i = 1; i <= 3; i++) {
    //    if (i % 2 == 1) {
    //        for (int j = 0; j < 30; j++) {
    //            std::cout << "=";
    //        }
    //       // std::cout << "\n";
    //    }

    //        if (i%2 == 0) {
    //            std::cout << "|";
    //            for (int k = 0; k<=10; k++) {
    //                
    //                std::cout << " ";
    //                if (k == 8) {
    //                    std::cout << word;
    //                }
    //            }
    //            for (int l = 0; l < 9; l++) {
    //                std::cout << " ";
    //            }
    //            std::cout << "|";

    //        }
    //       
    //        std::cout << "\n";
    //       
    //    
    //}

    return 0;
}