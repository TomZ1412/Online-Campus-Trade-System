#include"head.h"

int create_chat_database() {
    sqlite3* db;
    char* errMsg;
    int exit;

    // �����ݿ�
    exit = sqlite3_open("chats.db", &db);
    if (exit) {
        std::cerr << "�޷������ݿ�: " << sqlite3_errmsg(db) << std::endl;
        return exit;
    }

    // ��������������ڣ�
    const char* createTableSQL = "CREATE TABLE IF NOT EXISTS chats (Account TEXT , Body TEXT NOT NULL, Counter_Account TEXT NOT NULL);";
    exit = sqlite3_exec(db, createTableSQL, nullptr, nullptr, &errMsg);
    if (exit != SQLITE_OK) {
        std::cerr << "���������: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
    // �ر����ݿ�
    sqlite3_close(db);
    return 0;
}