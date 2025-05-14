#include"head.h"

int create_product_database() {
    sqlite3* db;
    char* errMsg;
    int exit;

    // �����ݿ�
    exit = sqlite3_open("products.db", &db);
    if (exit) {
        std::cerr << "�޷������ݿ�: " << sqlite3_errmsg(db) << std::endl;
        return exit;
    }

    // ��������������ڣ�
    const char* createTableSQL = "CREATE TABLE IF NOT EXISTS Products (ID INTEGER PRIMARY KEY AUTOINCREMENT, Name TEXT NOT NULL, Price INTEGER NOT NULL, Owner INTEGER NOT NULL, Description TEXT, Category TEXT NOT NULL ,isPurchased TEXT,Buyer TEXT);";
    exit = sqlite3_exec(db, createTableSQL, nullptr, nullptr, &errMsg);
    if (exit != SQLITE_OK) {
        std::cerr << "���������: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
    // �ر����ݿ�
    sqlite3_close(db);
    return 0;
}
