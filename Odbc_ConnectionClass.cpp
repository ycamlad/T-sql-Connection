#include "Odbc_ConnectionClass.h"

Odbc_ConnectionClass::Odbc_ConnectionClass() : sqlConnHandle(NULL),sqlStmtHandle(NULL),sqlEnvHandle(NULL),retconstring(L"") {}
//
Odbc_ConnectionClass::~Odbc_ConnectionClass() {
	Odbc_ConnectionClass::Disconnect();
}


bool Odbc_ConnectionClass::Connect(const char* server, const char* database) {
	// Allocate environment handle
	if (!SQL_SUCCEEDED(SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &sqlEnvHandle)))
		return false;
	// Set the ODBC version environement attribute
	if (!SQL_SUCCEEDED(SQLSetEnvAttr(sqlEnvHandle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0))) {
		SQLFreeHandle(SQL_HANDLE_ENV, sqlEnvHandle);
		return false;
	}
	// Allocate connection handle
	if (!SQL_SUCCEEDED(SQLAllocHandle(SQL_HANDLE_DBC, sqlEnvHandle, &sqlConnHandle))){
		SQLFreeHandle(SQL_HANDLE_ENV, sqlEnvHandle);
		return false;
	}

	// Connect to SQL Server using Windows Authentication 
	std::cout << "Attempting connection to SQL Server...";
	std::cout << "\n";

	switch (SQLDriverConnect(sqlConnHandle,
		NULL,
		
		(SQLWCHAR*)L"DRIVER={SQL Server};SERVER=DESKTOP-53IN7K4\\MSSQLSERVER02;DATABASE=StudentManagement;Trusted_Connection=yes;",
		SQL_NTS,
		retconstring,
		1024,
		NULL,
		SQL_DRIVER_NOPROMPT)) {
	case SQL_SUCCESS:
		std::wcout << L"Successfully connected to SQL Server: " << retconstring;
		std::wcout << L"\n";
		break;
	case SQL_SUCCESS_WITH_INFO:
		std::wcout << L"Successfully connected to SQL Server with info: " << retconstring;
		std::wcout << L"\n";
		break;
	case SQL_INVALID_HANDLE:
		std::wcout << L"Could not connect to SQL Server: " << retconstring;
		std::wcout << L"\n";
		Disconnect();
		break;
	case SQL_ERROR:
		std::wcout << L"Could not connect to SQL Server: " << retconstring;
		std::wcout << L"\n";
		Disconnect();
		break;
	default:
		break;
	}

	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT, sqlConnHandle, &sqlStmtHandle)) {
		std::cout << "Connection problem";
		Disconnect();
	}
		 

	return true;
}


bool Odbc_ConnectionClass::ExecuteQuery(const SQLWCHAR* query, std::vector<std::vector<std::string>>& result) {
	SQLRETURN ret;
	const size_t bufferSize = 1000;
	ret = SQLAllocHandle(SQL_HANDLE_STMT, sqlConnHandle, &sqlStmtHandle);
	ret = SQLExecDirect(sqlStmtHandle,(SQLWCHAR*)query, SQL_NTS);

	if (ret == SQL_ERROR) {
		return false;
	}

	// Fetch results
	SQLSMALLINT numCols = 0;
	SQLNumResultCols(sqlStmtHandle, &numCols);

	for (SQLSMALLINT i = 1; i <= numCols; i++) {
		SQLCHAR colName[1024];
		SQLSMALLINT colNameLen;
		SQLColAttribute(sqlStmtHandle,i,SQL_DESC_NAME,colName,sizeof(colName),&colNameLen,NULL);

		wprintf(L"Column %d: %s\n",i,(wchar_t*)colName);
	}
	std::wcout << std::endl;

	while (ret != SQL_NO_DATA) {
		std::vector<std::string> row;
		for (int i = 1; i <= numCols; ++i) {
			SQLCHAR buffer[512];
			SQLINTEGER indPtr;
			ret = SQLGetData(sqlStmtHandle, i, SQL_C_CHAR, buffer, sizeof(buffer), &indPtr);
			if (indPtr == SQL_NULL_DATA) {
				row.push_back("NULL");
			}
			else if(indPtr>0 && indPtr< sizeof(buffer)/sizeof(buffer[0])) {
				buffer[indPtr / sizeof(buffer[0])] = L'\0';
				row.push_back(reinterpret_cast<const char*>(buffer));
				
			}
		}

		result.push_back(row);
		ret = SQLFetch(sqlStmtHandle);
	}

	SQLFreeStmt(sqlStmtHandle, SQL_DROP);

	return true;
}

void Odbc_ConnectionClass::Disconnect() {
	SQLFreeHandle(SQL_HANDLE_STMT, sqlStmtHandle);
	SQLDisconnect(sqlConnHandle);
	SQLFreeHandle(SQL_HANDLE_DBC, sqlConnHandle);
	SQLFreeHandle(SQL_HANDLE_ENV, sqlEnvHandle);

	std::cout << "\nDisconnected!\n";
}