#include"head.h"

void init_socket() {
    // 初始化 Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Failed to initialize Winsock." << std::endl;
        return;
    }

    // 创建套接字
    clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Failed to create socket." << std::endl;
        WSACleanup();
        return;
    }

    // 设置服务器地址
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(12345);
    //inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr); // 使用本地地址
    inet_pton(AF_INET, "183.173.202.105", &serverAddr.sin_addr); 
    // 连接到服务器
    if (connect(clientSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Connection failed: " << WSAGetLastError() << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return;
    }

    //std::cout << "Connected to server." << std::endl;
}

bool receive_message() {
    
    //std::cout << sizeof(buffer) << std::endl;
    int bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
    //bytesReceived = strlen(buffer);
    //std::cout << bytesReceived << std::endl;
    if (bytesReceived > 0) {
        buffer[bytesReceived] = '\0'; // 添加字符串结束符
        //std::cout << "Received response: " << buffer << std::endl;
        return true;
    }
    else {
        std::cerr << "Receive failed." << std::endl;
        return false;
    }

}

/*
bool receive_message(char* buffer) {
    std::string message;
    int bytes_received;
    while ((bytes_received = recv(clientSocket, buffer, sizeof(buffer), 0)) > 0) {
        message.append(buffer, bytes_received);
        // 如果检测到结束符号，可以退出循环    
    }
    buffer = (char*)message.data();
    return true;
}
*/
bool check_person_info(std::string message) {
    // 发送消息
    send_message(message);

    // 接收响应
    if (receive_message()) {
        //std::cout << buffer;
        switch (buffer[0]) {
        case '1':memset(buffer, '\0', sizeof(buffer));return true;  break;
        case '0':memset(buffer, '\0', sizeof(buffer));return false;  break;
        default: std::cout << "error receive data from server" << std::endl; memset(buffer, '\0', sizeof(buffer)); return false;
        }
    }
    else return false;
}

bool check_password(std::string message) {
    // 发送消息
    send_message(message);

    // 接收响应
    if (receive_message()) {
        switch (buffer[0]) {
        case '1':memset(buffer, '\0', sizeof(buffer)); return true; break;
        case '0':memset(buffer, '\0', sizeof(buffer)); return false; break;
        default: std::cout << "error receive data from server" << std::endl; return false;
        }
    }
    else return false;
}

void send_message(std::string message) {
    message = caesar_encrypt(message);
    send(clientSocket, message.c_str(), message.length(), 0);
    //std::cout << "Sent message: " << message << std::endl;
}

std::vector<std::string> get_goods(std::string account, std::string way, std::string input) {
    std::string msg = "E" + account + "@" + way + "@" + input + "@";
    send_message(msg);
    if (receive_message()) {
        std::vector<std::string> goods(find_char_in_msg('#', buffer));
        //std::cout << find_char_in_msg('#', buffer);
        int bytesReceived = strlen(buffer);
        //std::cout << bytesReceived;
        for (int i = 0, j = 0; i < bytesReceived; i++) {
            if (buffer[i] != '#') {
                goods[j] = goods[j] + buffer[i];
            }
            else {
                goods[j] = goods[j] + "#\0";
                j++;
            }
        }
        //std::cout << goods[0];
        //system("pause");
        memset(buffer, '\0', sizeof(buffer));
        return goods;
    }
    //else return;
}

std::vector<std::string> get_history_chat(std::string counter_account) {
    std::string msg = "J" + counter_account;

    send_message(msg);
    if (receive_message()) {
        int len = strlen(buffer);

        std::vector<std::string> message(find_char_in_msg('#', buffer));

        for (int i = 0, j = 0; i < len; i++) {
            if (buffer[i] != '#') {
                message[j] = message[j] + buffer[i];
            }
            else {
                message[j] = message[j] + '\0';
                j++;
            }
        }
        memset(buffer, '\0', sizeof(buffer));
        return message;
    }
    //else return;
    
}

std::vector<std::string>get_discussion_title() {
    send_message("H");

    if (receive_message()) {
        std::vector<std::string> strings(find_char_in_msg('#', buffer));
        char c;
        int i = 0;
        int j = 0;
        while (buffer[j] != '\0') {
            strings[i] = strings[i] + buffer[j];
            j++;
            if (buffer[j] == '#') {
                strings[i] = strings[i] + '#';
                i++; j++;
            }
        }
        memset(buffer, '\0', sizeof(buffer));
        return strings;
    }
    else {
        std::vector<std::string> strings(0);
        return strings;
    }
}

//std::vector<std::string> get_self_goods();

int find_char_in_msg(char c,char* buffer) {
    int num = 0;
    for (int i = 0; i < strlen(buffer); i++) {
        if (buffer[i] == c) num++;
    }
    return num;
}

void init_window() {
    // 设置终端背景色为白色，前景色为黑色
    system("color F0"); // F = 白色背景，0 = 黑色字符

    // 设置终端大小为 50 列，100 行
    system("mode con: cols=50 lines=100");

}


int get_price(std::string goods) {
    std::string name, price, description, owner, category;
    int j, k;
    for (j = 0; goods[j] != '@'; j++) {
        name = name + goods[j];
    }
    for (k = j + 1; goods[k] != '@'; k++) {
        category = category + goods[k];
    }
    for (j = k + 1; goods[j] != '@'; j++) {
        price = price + goods[j];
    }
    for (k = j + 1; goods[k] != '@'; k++) {
        description = description + goods[k];
    }
    for (j = k + 1; goods[j] != '#'; j++) {
        owner = owner + goods[j];
    }
    return std::stoi(price);
}

std::string get_name(std::string goods) {
    std::string name, price, description, owner, category;
    int j, k;
    for (j = 0; goods[j] != '@'; j++) {
        name = name + goods[j];
    }
    for (k = j + 1; goods[k] != '@'; k++) {
        category = category + goods[k];
    }
    for (j = k + 1; goods[j] != '@'; j++) {
        price = price + goods[j];
    }
    for (k = j + 1; goods[k] != '@'; k++) {
        description = description + goods[k];
    }
    for (j = k + 1; goods[j] != '#'; j++) {
        owner = owner + goods[j];
    }
    return name;
}

std::string get_owner(std::string goods) {
    std::string name, price, description, owner, category;
    int j, k;
    for (j = 0; goods[j] != '@'; j++) {
        name = name + goods[j];
    }
    for (k = j + 1; goods[k] != '@'; k++) {
        category = category + goods[k];
    }
    for (j = k + 1; goods[j] != '@'; j++) {
        price = price + goods[j];
    }
    for (k = j + 1; goods[k] != '@'; k++) {
        description = description + goods[k];
    }
    for (j = k + 1; goods[j] != '#'; j++) {
        owner = owner + goods[j];
    }
    return owner;
}

std::string caesar_encrypt(std::string msg) {
    for (int i = 0; i<msg.length(); i++) {
        if (msg[i] >= 'A' && msg[i] <= 'Z')
        {
            msg[i] = ((msg[i] - 'A') + 16) % 26 + 'A';
        }
        else if (msg[i] >= 'a' && msg[i] <= 'z')
        {
            msg[i] = ((msg[i] - 'a') + 16) % 26 + 'a';
        }
    }
    return msg;   
}
