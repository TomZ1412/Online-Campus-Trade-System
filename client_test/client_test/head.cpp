#include"head.h"

WSADATA wsaData;
SOCKET clientSocket = INVALID_SOCKET;
sockaddr_in serverAddr;

UI my_ui;

char buffer[512];