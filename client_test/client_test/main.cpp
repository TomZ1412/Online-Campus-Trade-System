#include "head.h"


int main() {
    init_window();
 
    init_socket();
    
    User self;
    if (self.setup()) {
    //if(1){

        self.init();

        bool isQuit = false;
        while (!isQuit) {
            Sleep(SLEEP_TIME);
            system("cls");
            my_ui.print_main_menu();

            std::cout << "��ѡ������Ҫ���еĲ������������Ӧ�����" << std::endl;
            std::cout << "��ţ�";
            int choice;
            std::cin >> choice;
            switch (choice) {
            case 1:self.upload_goods(); break;
            case 2:self.search_goods(); break;
            case 3:self.discuss(); break;
            case 4:self.check_self(); break;
            case 5:isQuit = true; break;
            }
        }
        
    }
    


    /*
    // ������Ϣ
    std::string message = "Hello from the client!";
    send(clientSocket, message.c_str(), message.length(), 0);
    std::cout << "Sent message: " << message << std::endl;

    // ������Ӧ
    char buffer[512];
    int bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
    if (bytesReceived > 0) {
        buffer[bytesReceived] = '\0'; // ����ַ���������
        std::cout << "Received response: " << buffer << std::endl;
    }
    else {
        std::cerr << "Receive failed." << std::endl;
    }

    // �ر��׽���
    closesocket(clientSocket);
    WSACleanup();

    return 0;
    */

    /*char buffer[1024]="I am a person.y#Yes,you are a person.h#";

    
    int len = strlen(buffer);

    std::vector<std::string> message(find_char_in_msg('#', buffer));
    std::cout << find_char_in_msg('#', buffer);
        for (int i = 0, j = 0; i < len; i++) {
            if (buffer[i] != '#') {
                message[j] = message[j] + buffer[i];
            }
            else {
                message[j] = message[j] + '\0';
                j++;
            }
        }
        std::cout << message.size();
        std::cout << message[1];*/
}
