#pragma once

#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <thread>
#include <vector>
#include <sqlite3.h>
#pragma comment(lib, "Ws2_32.lib")

void check_personal_info(char* buffer, SOCKET clientSocket);
void login(char* buffer, SOCKET clientSocket);
void sign_up(char* buffer);
void upload_goods(char* buffer);
void get_goods_list(char* buffer, SOCKET clientSocket);
void launch_discussion(char* buffer);
void joinin_discussion(char* buffer);
void get_discussion(char* buffer, SOCKET clientSocket);
void get_discussion_body(char* buffer, SOCKET clientSocket);
void purchase(char* buffer);
void send_chat(char* buffer);
void get_chat(char* buffer, SOCKET clientSocket);
void get_personal_info(char* buffer, SOCKET clientSocket);
void caesar_decrypt(char buffer[512]);
