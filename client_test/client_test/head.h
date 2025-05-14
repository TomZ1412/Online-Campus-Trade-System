#pragma once

#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iomanip>
#include <string.h>
#include <conio.h>
#include <vector>
#include <string>
#include <limits>

#undef max

#pragma comment(lib, "Ws2_32.lib")

#define SLEEP_TIME  200
#define WAIT_TIME 2000

/*
A:确认个人信息 name@school_id
B:确认账号密码 account@password
C:注册账号密码 name@school_id@account@password
D:添加商品 name@actegory@price@description@owner
E:获取商品列表 account@method@input  n*[name@category@price@description@owner#]
F:发布校园圈 [account@title@body@]
G:评论校园圈 [account@title@message@]
H:获取校园圈标题 n*[counter_account@title#]
L:获取校园圈内容 title->body
N:购买商品 [account@price@counter_account]
I:发送私聊消息 [counter_account@message]
J:获取私聊消息 n*[message+y/h@]

K:评价他人 [score@counter_account]
M:获取个人信息 [money%n*[name@category@description@isPurchased#]%n*[name@buyer#]%n*[name@solder]n*[counter_account@body]%]




1:发布商品
2:查找商品
3:打开校园圈
4:查看个人账户

*/

void init_socket();
bool check_person_info(std::string msg);
bool check_password(std::string msg);
void send_message(std::string msg);
std::vector<std::string> get_goods(std::string account,std::string way,std::string input);
std::vector<std::string> get_history_chat(std::string counter_account);
std::vector<std::string> get_discussion_title();
int find_char_in_msg(char c, char* buffer);
void init_window();
bool receive_message();
std::string get_owner(std::string goods);
int get_price(std::string goods);
std::string get_name(std::string goods);
std::string caesar_encrypt(std::string msg);

struct message {
	std::string owner;
	std::string body;
};
struct goods {
	std::string name;
	std::string categpry;
	std::string price;
	std::string description;
	std::string owner;
	std::string isPurchased;
	std::string buyer;
};
class User {
public:
	bool setup();

	void upload_goods();
	void search_goods();

	void judge(std::string counter_account);

	void launch_discussion();
	void joinin_discussion(std::string counter_account);

	void chat(std::string counter_account);

	void discuss();
	void check_self();

	void purchase(std::string name, std::string counter_account,int price);
	void init();

	User();
	~User() {};	
//private:
	std::string name;
	std::string school_id;
	std::string account;
	std::string password;
	int money;

	goods my_goods[64];
	goods sold_goods[32];
	goods buy_goods[32];
	message leave_message[32];
	//message purchase_message[32];

	void sign_up();
	void login();

};

class UI {
public:
	void print_line(char c, int length);
	void print_space(int num);
	void print_title(std::string title, int width);
	void print_c(char c, int length);

	void print_start_menu();
	void print_setup_menu(std::string l_or_s,std::string string1,std::string string2);
	void print_judge_menu(User* user);
	void print_judge_menu();
	void print_main_menu();
	void print_discussion_menu(std::vector<std::string> discussion);
	void print_discussion_body(std::string title);
	void print_self_center();

	void print_self_menu(User* user);
	void print_self_goods(User* user);
	void print_self_deal(User* user);
	

	void print_search_goods(std::vector<std::string> goods);
	void print_my_goods(std::vector<std::string> goods);
	void print_category();

	void print_history_chat(std::string account,std::vector<std::string> chat);
	UI() {};
	~UI() {};
};

extern WSADATA wsaData;
extern SOCKET clientSocket;
extern sockaddr_in serverAddr;

extern UI my_ui;

extern char buffer[512];