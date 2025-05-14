#include"head.h"

void login(char* buffer, SOCKET clientSocket) {
    sqlite3* db;
    if (sqlite3_open("users.db", &db) != SQLITE_OK) {
        std::cerr << "无法打开数据库" << std::endl;
    }
    //std::cout << "open database";
    std::string username, password;
    int i=1;
    while (buffer[i] != '@') {
        username = username + buffer[i];
        i++;
    }
    i++;
    while (buffer[i] != '@') {
        password = password + buffer[i];
        i++;
    }
    //std::cout << name << std::endl;
    //std::cout << id << std::endl;
    sqlite3_stmt* stmt;
    std::string sql = "SELECT Password FROM Users WHERE Account = '"+ username +"'";
    //std::cout << sql;

    // 准备SQL语句
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
    }

    // 绑定参数
    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    const char* _password_c;
    std::string _password;
    //SELECT COALESCE((SELECT ID FROM your_table WHERE Name = 'your_name'), '0') AS Result;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            _password_c = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
            _password = std::string(_password_c);// 获取学号
        }
        sqlite3_finalize(stmt);
    }
    //std::cout << std::endl;
    //std::cout << "id:" << id << std::endl;
    //std::cout << "_id:" << _id << std::endl;
    
    if (password == _password) {
        std::string response = "1";
        std::cout << "yes";
        send(clientSocket, response.c_str(), response.length(), 0);
    }
    else {
        std::string response = "0";
        std::cout << "no";
        send(clientSocket, response.c_str(), response.length(), 0);
    }

}

void check_personal_info(char* buffer, SOCKET clientSocket) {
    sqlite3* db;
    if (sqlite3_open("students.db", &db) != SQLITE_OK) {
        std::cerr << "无法打开数据库" << std::endl;
    }
    //std::cout << "open database";
    std::string name, id;
    int i = 1;
    while (buffer[i] != '@') {
        name = name + buffer[i];
        i++;
    }
    i++;
    while (buffer[i] != '@') {
        id = id + buffer[i];
        i++;
    }
    //std::cout << name << std::endl;
    //std::cout << id << std::endl;
    sqlite3_stmt* stmt;
    std::string sql = "SELECT ID FROM Students WHERE Name = '" + name + "'";
    //std::cout << sql;

    // 准备SQL语句
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
    }

    // 绑定参数
    sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);
    const char* _id_c;
    std::string _id;
    //SELECT COALESCE((SELECT ID FROM your_table WHERE Name = 'your_name'), '0') AS Result;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            _id_c = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
            _id = std::string(_id_c);// 获取学号
        }
        sqlite3_finalize(stmt);
    }
    //std::cout << std::endl;
    //std::cout << "id:" << id << std::endl;
    //std::cout << "_id:" << _id << std::endl;

    if (id == _id) {
        std::string response = "1";
        std::cout << "yes";
        send(clientSocket, response.c_str(), response.length(), 0);
    }
    else {
        std::string response = "0";
        std::cout << "no";
        send(clientSocket, response.c_str(), response.length(), 0);
    }
}

void sign_up(char* buffer) {
    sqlite3* db;
    if (sqlite3_open("users.db", &db) != SQLITE_OK) {
        std::cerr << "无法打开数据库" << std::endl;
    }
    //std::cout << "open database";
    std::string name, id, username, password;
    int i = 1;
    while (buffer[i] != '@') {
        name = name + buffer[i];
        i++;
    }
    i++;
    while (buffer[i] != '@') {
        id = id + buffer[i];
        i++;
    }
    i++;
    while (buffer[i] != '@') {
        username = username + buffer[i];
        i++;
    }
    i++;
    while (buffer[i] != '@') {
        password = password + buffer[i];
        i++;
    }
    //std::cout << name << id << username << password << std::endl;
    std::string money = "1000";
    std::string sql = "INSERT INTO Users (name, school_id, account, password, money) VALUES ('" + name + "', '" + id + "', '" + username + "', '" + password + "', '" + money + "');";
    char* errorMessage;
    if (sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errorMessage) != SQLITE_OK) {
        std::cerr << "添加学生失败: " << errorMessage << std::endl;
        sqlite3_free(errorMessage);
    }
    else {
        std::cout << "成功添加学生: " << name << "，学号: " << id << std::endl;
    }
}

void upload_goods(char* buffer) {
    sqlite3* db;
    if (sqlite3_open("products.db", &db) != SQLITE_OK) {
        std::cerr << "无法打开数据库" << std::endl;
    }
    //std::cout << "open database";
    std::string name, category, price, description, owner, isPurchased;
    int i = 1;
    while (buffer[i] != '@') {
        name = name + buffer[i];
        i++;
    }
    i++;
    while (buffer[i] != '@') {
        category = category + buffer[i];
        i++;
    }
    i++;
    while (buffer[i] != '@') {
        price = price + buffer[i];
        i++;
    }
    i++;
    while (buffer[i] != '@') {
        description = description + buffer[i];
        i++;
    }
    i++;
    while (buffer[i] != '@') {
        owner = owner + buffer[i];
        i++;
    }
    isPurchased = "undeal";
    //std::cout << name << id << username << password << std::endl;
    std::string sql = "INSERT INTO Products (name, category, price, description, owner, isPurchased, buyer) VALUES ('" + name + "', '" + category + "', '" + price + "', '" + description + "', '" + owner + "', '" + isPurchased + "','None');";
    std::cout << sql;
    char* errorMessage;
    if (sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errorMessage) != SQLITE_OK) {
        std::cerr << "添加学生失败: " << errorMessage << std::endl;
        sqlite3_free(errorMessage);
    }
    else {
        std::cout << "成功添加商品: " << name << "，描述: " << description << std::endl;
    }
}

void get_goods_list(char* buffer, SOCKET clientSocket) {
    sqlite3* db;
    if (sqlite3_open("products.db", &db) != SQLITE_OK) {
        std::cerr << "无法打开数据库" << std::endl;
    }
    //std::cout << "open database";
    std::string account, method, input;
    int i = 1;
    while (buffer[i] != '@') {
        account = account + buffer[i];
        i++;
    }
    i++;
    while (buffer[i] != '@') {
        method = method + buffer[i];
        i++;
    }
    i++;
    while (buffer[i] != '@') {
        input = input + buffer[i];
        i++;
    }
    i++;
    //std::cout << account << method << input;
    std::string name, category, price, description, owner, isPurchased;
    std::string msg;
    if (method == "category") {
        const char* sql = "SELECT NAME,CATEGORY,PRICE,DESCRIPTION,OWNER,ISPURCHASED FROM products WHERE category = ?;";
        sqlite3_stmt* stmt;
        
        //char* name_c, category_c, price_c, description_c, owner_c;

        if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
            std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
            return;
        }

        sqlite3_bind_text(stmt, 1, input.c_str(), -1, SQLITE_STATIC);

        while (sqlite3_step(stmt) == SQLITE_ROW) {
            name = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));
            category = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
            price= std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
            description = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
            owner = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)));
            isPurchased = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5)));
            if(isPurchased=="undeal") msg = msg + name + "@" + category + "@" + price + "@" + description + "@" + owner + "#";
            //std::cout << msg;
        }
    }
    else if (method == "name") {
        const char* sql = "SELECT NAME,CATEGORY,PRICE,DESCRIPTION,OWNER FROM products WHERE name = ?;";
        sqlite3_stmt* stmt;

        if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
            std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
            return;
        }

        sqlite3_bind_text(stmt, 1, input.c_str(), -1, SQLITE_STATIC);

        while (sqlite3_step(stmt) == SQLITE_ROW) {
            name = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));
            category = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
            price = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
            description = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
            owner = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)));
            msg = msg + name + "@" + category + "@" + price + "@" + description + "@" + owner + "#";
        }
    }
    send(clientSocket, msg.c_str(), msg.length(), 0);
    std::cout << "send message:" << msg;
    //std::cout << msg.length();
}

void launch_discussion(char* buffer) {
    sqlite3* db;
    if (sqlite3_open("discussions.db", &db) != SQLITE_OK) {
        std::cerr << "无法打开数据库" << std::endl;
    }
    //std::cout << "open database";
    std::string account, title, body;
    int i = 1;
    while (buffer[i] != '@') {
        account = account + buffer[i];
        i++;
    }
    i++;
    while (buffer[i] != '@') {
        title = title + buffer[i];
        i++;
    }
    i++;
    while (buffer[i] != '@') {
        body = body + buffer[i];
        i++;
    }
    i++;

    std::string isComment = "launch";
    std::string sql = "INSERT INTO discussions (account, title, body, isjudge) VALUES ('" + account + "', '" + title + "', '" + body + "', '" + isComment + "');";
    char* errorMessage;
    if (sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errorMessage) != SQLITE_OK) {
        std::cerr << "添加校园圈失败: " << errorMessage << std::endl;
        sqlite3_free(errorMessage);
    }
    else {
        std::cout << "成功添加校园圈: " << title << "，账号: " << account << std::endl;
    }
}

void joinin_discussion(char* buffer) {
    sqlite3* db;
    if (sqlite3_open("discussions.db", &db) != SQLITE_OK) {
        std::cerr << "无法打开数据库" << std::endl;
    }
    //std::cout << "open database";
    std::string account, title, body;
    int i = 1;
    while (buffer[i] != '@') {
        account = account + buffer[i];
        i++;
    }
    i++;
    while (buffer[i] != '@') {
        title = title + buffer[i];
        i++;
    }
    i++;
    while (buffer[i] != '@') {
        body = body + buffer[i];
        i++;
    }
    i++;

    std::string isComment = "comment";
    std::string sql = "INSERT INTO discussions (account, title, body, isjudge) VALUES ('" + account + "', '" + title + "', '" + body + "', '" + isComment + "');";
    char* errorMessage;
    if (sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errorMessage) != SQLITE_OK) {
        std::cerr << "评论校园圈失败: " << errorMessage << std::endl;
        sqlite3_free(errorMessage);
    }
    else {
        std::cout << "成功评论校园圈: " << title << "，账号: " << account << std::endl;
    }
}

void get_discussion(char* buffer, SOCKET clientSocket) {
    sqlite3* db;
    if (sqlite3_open("discussions.db", &db) != SQLITE_OK) {
        std::cerr << "无法打开数据库" << std::endl;
        return; // 如果数据库无法打开，直接返回
    }

    std::string account, title;
    std::string msg;

    sqlite3_stmt* stmt;
    std::string sql = "SELECT Account, Title FROM discussions WHERE isJudge = ?;";

    // 准备 SQL 语句
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db); // 关闭数据库连接
        return;
    }

    // 绑定参数
    if (sqlite3_bind_text(stmt, 1, "launch", -1, SQLITE_STATIC) != SQLITE_OK) {
        std::cerr << "Failed to bind parameter: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt); // 清理语句
        sqlite3_close(db);      // 关闭数据库连接
        return;
    }

    // 执行查询并处理结果
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        // 从第一列获取 account
        account = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));
        // 从第二列获取 title
        title = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        // 拼接 msg 字符串
        msg += account + "@" + title + "#";
    }

    // 检查查询状态
    if (sqlite3_finalize(stmt) != SQLITE_OK) {
        std::cerr << "Failed to finalize statement: " << sqlite3_errmsg(db) << std::endl;
    }

    // 发送消息到客户端
    send(clientSocket, msg.c_str(), msg.length(), 0);
    std::cout << "send message:" << msg << std::endl;

    // 关闭数据库连接
    sqlite3_close(db);
}

void get_discussion_body(char* buffer, SOCKET clientSocket) {
    sqlite3* db;
    if (sqlite3_open("discussions.db", &db) != SQLITE_OK) {
        std::cerr << "无法打开数据库" << std::endl;
    }
    //std::cout << "open database";
    std::string account, title, body, isJudge;
    int i = 1;
    while (buffer[i] != '@') {
        title = title + buffer[i];
        i++;
    }
    i++;
    std::string launcher, commentor;

    std::string sql = "SELECT ACCOUNT,TITLE,BODY,ISJUDGE FROM discussions WHERE title = '" + title +"';";
    sqlite3_stmt* stmt;

    //char* name_c, category_c, price_c, description_c, owner_c;

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    sqlite3_bind_text(stmt, 1, title.c_str(), -1, SQLITE_STATIC);
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        account = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));
        title = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        body = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
        isJudge = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
        if (isJudge == "launch") {
            launcher = launcher + account + "@" + title + "@" + body + "#";
        }
        else if (isJudge == "comment") {
            commentor = commentor + account + "@" + body + "#";
        }
        //std::cout << msg;
    }
    std::string msg = launcher + commentor;
    send(clientSocket, msg.c_str(), msg.length(), 0);
    std::cout << msg;
}

void purchase(char* buffer) {
    sqlite3* db_p;
    if (sqlite3_open("products.db", &db_p) != SQLITE_OK) {
        std::cerr << "无法打开数据库" << std::endl;
    }
    sqlite3* db_u;
    if (sqlite3_open("users.db", &db_u) != SQLITE_OK) {
        std::cerr << "无法打开数据库" << std::endl;
    }
    //std::cout << "open database";
    std::string name, account, price, counter_account;
    int i = 1;
    while (buffer[i] != '@') {
        name = name + buffer[i];
        i++;
    }
    i++;
    while (buffer[i] != '@') {
        account = account + buffer[i];
        i++;
    }
    i++;
    while (buffer[i] != '@') {
        price = price + buffer[i];
        i++;
    }
    i++;
    while (buffer[i] != '@') {
        counter_account = counter_account + buffer[i];
        i++;
    }
    i++;
    std::string sql = "UPDATE products SET isPurchased = 'dealed' WHERE name = '" + name + "';";
    std::string sql1 = "UPDATE products SET buyer = '"+account+"' WHERE name = '" + name + "';";
    std::string sql2 = "UPDATE users SET money = CAST(money AS REAL) + "+price+" WHERE account = '" + counter_account + "'; ";
    std::string sql3 = "UPDATE users SET money = CAST(money AS REAL) - " + price + " WHERE account = '" + account + "'; ";

    char* errMessage = nullptr;
    int rc = sqlite3_exec(db_p, sql.c_str(), nullptr, nullptr, &errMessage);

    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMessage << std::endl;
        sqlite3_free(errMessage);
    }

    rc = sqlite3_exec(db_p, sql1.c_str(), nullptr, nullptr, &errMessage);

    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMessage << std::endl;
        sqlite3_free(errMessage);
    }
    rc = sqlite3_exec(db_u, sql2.c_str(), nullptr, nullptr, &errMessage);

    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMessage << std::endl;
        sqlite3_free(errMessage);
    }
    rc = sqlite3_exec(db_u, sql3.c_str(), nullptr, nullptr, &errMessage);

    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMessage << std::endl;
        sqlite3_free(errMessage);
    }
}

void send_chat(char* buffer) {
    sqlite3* db;
    if (sqlite3_open("chats.db", &db) != SQLITE_OK) {
        std::cerr << "无法打开数据库" << std::endl;
    }
    //std::cout << "open database";
    std::string account, body, counter_account;
    int i = 1;
    while (buffer[i] != '@') {
        account = account + buffer[i];
        i++;
    }
    i++;
    while (buffer[i] != '@') {
        body = body + buffer[i];
        i++;
    }
    i++;
    while (buffer[i] != '@') {
        counter_account = counter_account + buffer[i];
        i++;
    }
    i++;

    std::string sql = "INSERT INTO Chats (account, body, counter_account) VALUES ('" + account + "', '" + body + "', '" + counter_account + "');";
    char* errorMessage;
    if (sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errorMessage) != SQLITE_OK) {
        std::cerr << "添加学生失败: " << errorMessage << std::endl;
        sqlite3_free(errorMessage);
    }
    else {
        std::cout << "成功留言: " << body << std::endl;
    }
}

void get_chat(char* buffer, SOCKET clientSocket) {
    sqlite3* db;
    if (sqlite3_open("chats.db", &db) != SQLITE_OK) {
        std::cerr << "无法打开数据库" << std::endl;
    }
    //std::cout << "open database";
    std::string account, counter_account, body;
    int i = 1;
    while (buffer[i] != '@') {
        account = account + buffer[i];
        i++;
    }

    sqlite3_stmt* stmt;
    std::string sql = "SELECT Account, Body FROM chats WHERE counter_account = ?;";

    // 准备 SQL 语句
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db); // 关闭数据库连接
        return;
    }

    // 绑定参数
    if (sqlite3_bind_text(stmt, 1, account.c_str(), -1, SQLITE_STATIC) != SQLITE_OK) {
        std::cerr << "Failed to bind parameter: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt); // 清理语句
        sqlite3_close(db);      // 关闭数据库连接
        return;
    }
    std::string msg;
    // 执行查询并处理结果
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        // 从第一列获取 account
        counter_account = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));
        // 从第二列获取 title
        body = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        // 拼接 msg 字符串
        msg += counter_account + "@" + body + "#";
    }

    // 检查查询状态
    if (sqlite3_finalize(stmt) != SQLITE_OK) {
        std::cerr << "Failed to finalize statement: " << sqlite3_errmsg(db) << std::endl;
    }

    // 发送消息到客户端
    send(clientSocket, msg.c_str(), msg.length(), 0);
    std::cout << "send message:" << msg << std::endl;
}

void get_personal_info(char* buffer, SOCKET clientSocket) {
    sqlite3* db_p;
    if (sqlite3_open("products.db", &db_p) != SQLITE_OK) {
        std::cerr << "无法打开数据库" << std::endl;
    }

    sqlite3* db_u;
    if (sqlite3_open("users.db", &db_u) != SQLITE_OK) {
        std::cerr << "无法打开数据库" << std::endl;
    }

    sqlite3* db_c;
    if (sqlite3_open("chats.db", &db_c) != SQLITE_OK) {
        std::cerr << "无法打开数据库" << std::endl;
    }

    std::string account;
    int i = 1;
    while (buffer[i] != '@') {
        account = account + buffer[i];
        i++;
    }

    sqlite3_stmt* stmt;
    std::string sql = "SELECT Name,School_id,Money FROM users WHERE account = ?;";


    std::string _name,school_id,money;
    if (sqlite3_prepare_v2(db_u, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db_u) << std::endl;
        sqlite3_close(db_u); // 关闭数据库连接
        return;
    }

    // 绑定参数
    if (sqlite3_bind_text(stmt, 1, account.c_str(), -1, SQLITE_STATIC) != SQLITE_OK) {
        std::cerr << "Failed to bind parameter: " << sqlite3_errmsg(db_u) << std::endl;
        sqlite3_finalize(stmt); // 清理语句
        sqlite3_close(db_u);      // 关闭数据库连接
        return;
    }
    std::string msg;
    // 执行查询并处理结果

    //个人基本信息
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        _name = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));
        school_id = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        money = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
        msg += _name+'@'+school_id+'@'+money + "%";
    }


    //已发布商品
    std::string name, category,price, description, isPurchased, buyer,owner;
    sql= "SELECT name,category,price, description,isPurchased FROM products WHERE owner = ?;";
    if (sqlite3_prepare_v2(db_p, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db_p) << std::endl;
        sqlite3_close(db_p); // 关闭数据库连接
        return;
    }

    // 绑定参数
    if (sqlite3_bind_text(stmt, 1, account.c_str(), -1, SQLITE_STATIC) != SQLITE_OK) {
        std::cerr << "Failed to bind parameter: " << sqlite3_errmsg(db_p) << std::endl;
        sqlite3_finalize(stmt); // 清理语句
        sqlite3_close(db_p);      // 关闭数据库连接
        return;
    }
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        name = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));
        category = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        price = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
        description = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
        isPurchased = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)));
        msg += name + '@' + category+'@'+price+'@'+ description + '@' + isPurchased + '#';
    }
    msg += '%';



    //已卖出的
    sql = "SELECT name,buyer FROM products WHERE owner = ?;";
    if (sqlite3_prepare_v2(db_p, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db_p) << std::endl;
        sqlite3_close(db_p); // 关闭数据库连接
        return;
    }

    // 绑定参数
    if (sqlite3_bind_text(stmt, 1, account.c_str(), -1, SQLITE_STATIC) != SQLITE_OK) {
        std::cerr << "Failed to bind parameter: " << sqlite3_errmsg(db_p) << std::endl;
        sqlite3_finalize(stmt); // 清理语句
        sqlite3_close(db_p);      // 关闭数据库连接
        return;
    }
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        name = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));
        buyer = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        if(buyer!="None")  msg += name + '@' + buyer+ '#';
    }
    msg += '%';

    //已买入的

    sql = "SELECT name,owner FROM products WHERE buyer = ?;";
    if (sqlite3_prepare_v2(db_p, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db_p) << std::endl;
        sqlite3_close(db_p); // 关闭数据库连接
        return;
    }

    // 绑定参数
    if (sqlite3_bind_text(stmt, 1, account.c_str(), -1, SQLITE_STATIC) != SQLITE_OK) {
        std::cerr << "Failed to bind parameter: " << sqlite3_errmsg(db_p) << std::endl;
        sqlite3_finalize(stmt); // 清理语句
        sqlite3_close(db_p);      // 关闭数据库连接
        return;
    }
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        name = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));
        owner = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        msg += name + '@' + owner + '#';
    }
    msg += '%';


    //接受的留言
    std::string counter_account, body;
    sql = "SELECT account,body FROM chats WHERE counter_account = ?;";
    if (sqlite3_prepare_v2(db_c, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db_c) << std::endl;
        sqlite3_close(db_c); // 关闭数据库连接
        return;
    }

    // 绑定参数
    if (sqlite3_bind_text(stmt, 1, account.c_str(), -1, SQLITE_STATIC) != SQLITE_OK) {
        std::cerr << "Failed to bind parameter: " << sqlite3_errmsg(db_c) << std::endl;
        sqlite3_finalize(stmt); // 清理语句
        sqlite3_close(db_c);      // 关闭数据库连接
        return;
    }
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        counter_account = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));
        body = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        msg += counter_account + '@' + body + '#';
    }
    msg += '%';

    send(clientSocket, msg.c_str(), msg.length(), 0);
    std::cout << "send message:" << msg << std::endl;
}
