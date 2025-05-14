#include"head.h"

int create_product_database() {
    sqlite3* db;
    char* errMsg;
    int exit;

    // 打开数据库
    exit = sqlite3_open("products.db", &db);
    if (exit) {
        std::cerr << "无法打开数据库: " << sqlite3_errmsg(db) << std::endl;
        return exit;
    }

    // 创建表（如果不存在）
    const char* createTableSQL = "CREATE TABLE IF NOT EXISTS Products (ID INTEGER PRIMARY KEY AUTOINCREMENT, Name TEXT NOT NULL, Price INTEGER NOT NULL, Owner INTEGER NOT NULL, Description TEXT, Category TEXT NOT NULL ,isPurchased TEXT,Buyer TEXT);";
    exit = sqlite3_exec(db, createTableSQL, nullptr, nullptr, &errMsg);
    if (exit != SQLITE_OK) {
        std::cerr << "创建表错误: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
    // 关闭数据库
    sqlite3_close(db);
    return 0;
}
