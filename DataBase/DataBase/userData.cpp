#include "head.h"

int create_user_database() {
    sqlite3* db;
    char* errMsg;
    int exit;

    // 打开数据库
    exit = sqlite3_open("users.db", &db);
    if (exit) {
        std::cerr << "无法打开数据库: " << sqlite3_errmsg(db) << std::endl;
        return exit;
    }

    // 创建表（如果不存在）
    const char* createTableSQL = "CREATE TABLE IF NOT EXISTS Users (ID INTEGER PRIMARY KEY AUTOINCREMENT, Name TEXT NOT NULL, School_ID TEXT NOT NULL, Account TEXT NOT NULL, Password TEXT NOT NULL, Money TEXT);";
    exit = sqlite3_exec(db, createTableSQL, nullptr, nullptr, &errMsg);
    if (exit != SQLITE_OK) {
        std::cerr << "创建表错误: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
    // 关闭数据库
    sqlite3_close(db);
    return 0;
}
