#include"head.h"

int create_student_database(){
    sqlite3* db;
    char* errMsg;
    int exit;

    // 打开数据库
    exit = sqlite3_open("students.db", &db);
    if (exit) {
        std::cerr << "无法打开数据库: " << sqlite3_errmsg(db) << std::endl;
        return exit;
    }

    // 创建表（如果不存在）
    const char* createTableSQL = "CREATE TABLE IF NOT EXISTS Students (Name TEXT PRIMARY KEY, ID TEXT NOT NULL);";
    exit = sqlite3_exec(db, createTableSQL, nullptr, nullptr, &errMsg);
    if (exit != SQLITE_OK) {
        std::cerr << "创建表错误: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
    // 关闭数据库
    sqlite3_close(db);
    return 0;
}

void addStudent(const std::string& name, const std::string& id) {
    sqlite3* db;
    if (sqlite3_open("students.db", &db) != SQLITE_OK) {
        std::cerr << "无法打开数据库" << std::endl;
    }
    
    std::string sql = "INSERT INTO students (name, id) VALUES ('" + name + "', '" + id + "');";
    char* errorMessage;
    if (sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errorMessage) != SQLITE_OK) {
        std::cerr << "添加学生失败: " << errorMessage << std::endl;
        sqlite3_free(errorMessage);
    }
    else {
        std::cout << "成功添加学生: " << name << "，学号: " << id << std::endl;
    }
}