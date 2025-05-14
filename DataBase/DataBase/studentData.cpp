#include"head.h"

int create_student_database(){
    sqlite3* db;
    char* errMsg;
    int exit;

    // �����ݿ�
    exit = sqlite3_open("students.db", &db);
    if (exit) {
        std::cerr << "�޷������ݿ�: " << sqlite3_errmsg(db) << std::endl;
        return exit;
    }

    // ��������������ڣ�
    const char* createTableSQL = "CREATE TABLE IF NOT EXISTS Students (Name TEXT PRIMARY KEY, ID TEXT NOT NULL);";
    exit = sqlite3_exec(db, createTableSQL, nullptr, nullptr, &errMsg);
    if (exit != SQLITE_OK) {
        std::cerr << "���������: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
    // �ر����ݿ�
    sqlite3_close(db);
    return 0;
}

void addStudent(const std::string& name, const std::string& id) {
    sqlite3* db;
    if (sqlite3_open("students.db", &db) != SQLITE_OK) {
        std::cerr << "�޷������ݿ�" << std::endl;
    }
    
    std::string sql = "INSERT INTO students (name, id) VALUES ('" + name + "', '" + id + "');";
    char* errorMessage;
    if (sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errorMessage) != SQLITE_OK) {
        std::cerr << "���ѧ��ʧ��: " << errorMessage << std::endl;
        sqlite3_free(errorMessage);
    }
    else {
        std::cout << "�ɹ����ѧ��: " << name << "��ѧ��: " << id << std::endl;
    }
}