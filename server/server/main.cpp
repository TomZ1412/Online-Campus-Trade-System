#include"head.h"

void handleClient(SOCKET clientSocket) {
    char buffer[512];
    int bytesReceived;
   
    while (1) {
        // 接收账号信息
        bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
        if (bytesReceived > 0) {
            buffer[bytesReceived] = '\0'; // 添加字符串结束符
            caesar_decrypt(buffer);
            std::string accountInfo(buffer);

            std::cout << "Received account info: " << accountInfo << std::endl;
            switch (buffer[0]) {
            case'A':check_personal_info(buffer, clientSocket); break;
            case 'B':login(buffer, clientSocket); break;
            case 'C':sign_up(buffer); break;
            case 'D':upload_goods(buffer); break;
            case 'E':get_goods_list(buffer, clientSocket); break;
            case 'F':launch_discussion(buffer); break;
            case 'G':joinin_discussion(buffer); break;
            case 'H':get_discussion(buffer, clientSocket); break;
            case 'I':send_chat(buffer); break;
            case 'J':get_chat(buffer, clientSocket); break;
            case 'K':    break;
            case 'L':get_discussion_body(buffer, clientSocket); break;
            case 'M':get_personal_info(buffer, clientSocket); break;
            case 'N':purchase(buffer); break;
            }

            /*
            // 查询数据库
            sqlite3* db;
            sqlite3_stmt* stmt;

            // 打开数据库
            if (sqlite3_open("users.db", &db) != SQLITE_OK) {
                std::cerr << "Cannot open database." << std::endl;
                return;
            }

            // 准备 SQL 查询
            std::string sql = "SELECT name, school_id FROM users WHERE account = ?;";
            if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
                std::cerr << "Failed to prepare statement." << std::endl;
                sqlite3_close(db);
                return;
            }

            // 绑定参数
            sqlite3_bind_text(stmt, 1, accountInfo.c_str(), -1, SQLITE_STATIC);

            // 执行查询并获取结果
            std::string name, student_id;
            if (sqlite3_step(stmt) == SQLITE_ROW) {
                name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
                student_id = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            }
            else {
                std::cerr << "Account not found." << std::endl;
            }

            // 清理
            sqlite3_finalize(stmt);
            sqlite3_close(db);

            // 发送结果回客户端
            std::string response;
            if (!name.empty() && !student_id.empty()) {
                response = "Name: " + name + ", Student ID: " + student_id;
            }
            else {
                response = "Account not found.";
            }

            send(clientSocket, response.c_str(), response.length(), 0);*/
        }
        memset(buffer, '\0', sizeof(buffer));
    }
    

    // 关闭客户端套接字
    closesocket(clientSocket);
}

int main() {
    
    WSADATA wsaData;
    SOCKET listenSocket = INVALID_SOCKET;
    sockaddr_in serverAddr, clientAddr;
    int clientAddrSize = sizeof(clientAddr);
    std::vector<std::thread> threads;

    // 初始化 Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Failed to initialize Winsock." << std::endl;
        return 1;
    }

    // 创建监听套接字
    listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listenSocket == INVALID_SOCKET) {
        std::cerr << "Failed to create socket." << std::endl;
        WSACleanup();
        return 1;
    }

    // 设置服务器地址
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(12345);

    // 绑定套接字
    if (bind(listenSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Bind failed." << std::endl;
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }

    // 开始监听
    if (listen(listenSocket, SOMAXCONN) == SOCKET_ERROR) {
        std::cerr << "Listen failed." << std::endl;
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }

    std::cout << "Server started on port 12345." << std::endl;

    while (true) {
        // 接受客户端连接
        SOCKET clientSocket = accept(listenSocket, (sockaddr*)&clientAddr, &clientAddrSize);
        if (clientSocket == INVALID_SOCKET) {
            std::cerr << "Accept failed." << std::endl;
            continue; // 如果失败，继续接受下一个连接
        }

        std::cout << "Client connected." << std::endl;

        // 创建新线程处理客户端
        threads.emplace_back(handleClient, clientSocket);
    }

    // 等待所有线程完成
    for (auto& th : threads) {
        if (th.joinable()) {
            th.join();
        }
    }

    // 清理资源
    closesocket(listenSocket);
    WSACleanup();

    return 0;
}

/*
int main() {
    char buffer[1024] = "Maccount@";
    SOCKET listenSocket = INVALID_SOCKET;
    get_personal_info(buffer, listenSocket);
}*/

void caesar_decrypt(char buffer[512]) {
    for (int i = 0; i < strlen(buffer); i++)
    {
        if (buffer[i] >= 'A' && buffer[i] <= 'Z')

        {
            buffer[i] = ((buffer[i] - 'A') + 10) % 26 + 'A';
        }
        else if (buffer[i] >= 'a' && buffer[i] <= 'z')
        {
            buffer[i] = ((buffer[i] - 'a') + 10) % 26 + 'a';
        }
    }
}