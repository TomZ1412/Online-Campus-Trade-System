#include "head.h"

int create_user_database() {
    sqlite3* db;
    char* errMsg;
    int exit;

    // �����ݿ�
    exit = sqlite3_open("users.db", &db);
    if (exit) {
        std::cerr << "�޷������ݿ�: " << sqlite3_errmsg(db) << std::endl;
        return exit;
    }

    // ��������������ڣ�
    const char* createTableSQL = "CREATE TABLE IF NOT EXISTS Users (ID INTEGER PRIMARY KEY AUTOINCREMENT, Name TEXT NOT NULL, School_ID TEXT NOT NULL, Account TEXT NOT NULL, Password TEXT NOT NULL, Money TEXT);";
    exit = sqlite3_exec(db, createTableSQL, nullptr, nullptr, &errMsg);
    if (exit != SQLITE_OK) {
        std::cerr << "���������: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
    // �ر����ݿ�
    sqlite3_close(db);
    return 0;
}
