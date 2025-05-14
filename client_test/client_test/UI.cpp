#include"head.h"

void UI::print_line(char c, int length) {
    for (int i = 0; i < length; i++) {
        std::cout << c;
    }
    std::cout << std::endl;
}

void UI::print_c(char c, int length) {
    for (int i = 0; i < length; i++) {
        std::cout << c;
    }
}

void UI::print_space(int num) {
    for (int i = 0; i < num; i++) {
        std::cout << std::endl;
    }
}

void UI::print_title(std::string title, int width) {
   
    print_line('=', width);
    print_space(1);
    std::cout << std::setw((width + title.length()) / 2) << title << std::endl;
    print_space(1);
    print_line('=', width);
}

void UI::print_setup_menu(std::string l_or_s, std::string string1, std::string string2) {
    int width = 50; // Set the width of the login window
    //std::string title = " Welcome to the QingQing Flea Market";
    std::string title = l_or_s;

    print_title(title, width);

    print_space(1);
    std::cout << std::setw(18) << string1 + ": ";
    print_space(1);
    std::cout << std::setw(width - 18 - 1) << std::endl; // Print space for input
    std::cout << std::setw(18) << string2 + ": ";
    print_space(1);
    std::cout << std::setw(width - 18 - 1) << std::endl; // Print space for input
    std::cout << std::setw(0);
    print_space(1);
    print_line('=', width);
}

void UI::print_start_menu() {
    int width = 50; // Set the width of the login window
    std::string title = " Welcome to the QingQing Flea Market";

    print_title(title, width);

    print_space(3);
    std::string string1 = "Created by Easily";
    std::string string2 = "Copyright belongs to Easily";
    std::string string3 = "TWO HANDS are better than one!";

    std::cout << std::setw((width + string3.length()) / 2) << string3 << std::endl;
    print_space(3);
    std::cout << std::setw(width) << string1 << std::endl;
    print_space(1);
    std::cout << std::setw(width) << string2 << std::endl;
    print_space(2);
    print_line('=', width);
}

void UI::print_category() {
    std::string categories[] = { "�鼮","�ľ�","����Ʒ","������е","����" };
    int num_cate = size(categories) / size(categories[0]);
    std::cout << "��ѡ����У�";
    for (int i = 0; i < num_cate; i++) {
        std::cout << categories[i] << " ";
    }
    std::cout << std::endl;
}

void UI::print_search_goods(std::vector<std::string> goods) {
    print_title("Search goods", 50);
    print_space(2);    
    int len = goods.size();
    for (int i = 0; i < len; i++) {
        std::string name, price, description, owner, category;
        int j, k;
        for (j = 0; goods[i][j] != '@'; j++) {
            name = name + goods[i][j];
        }
        for (k = j + 1; goods[i][k] != '@'; k++) {
            category = category + goods[i][k];
        }
        for (j = k + 1; goods[i][j] != '@'; j++) {
            price = price + goods[i][j];
        }
        for (k = j + 1; goods[i][k] != '@'; k++) {
            description = description + goods[i][k];
        }
        for (j = k + 1; goods[i][j] != '#'; j++) {
            owner = owner + goods[i][j];
        }

        std::cout << "    " << i + 1 << ".  ���ƣ�" << name << " �۸�" << price << " ���" << category << " ������" << description << " ӵ���ߣ�" << owner << std::endl;
    }


}

void UI::print_my_goods(std::vector<std::string> goods) {
    int len = goods.size();
    std::string name, price, description, category;
    for (int i = 0; i < len; i++) {
        int j, k;
        for (j = 0; goods[i][j] != '@'; j++) {
            name = name + goods[i][j];
        }
        for (k = j + 1; goods[i][k] != '@'; k++) {
            category = category + goods[i][k];
        }
        for (j = k + 1; goods[i][j] != '@'; j++) {
            price = price + goods[i][j];
        }
        for (k = j + 1; goods[i][k] != '@'; k++) {
            description = description + goods[i][k];
        }
        std::cout << i + 1 << ". " << name << " �۸�" << price << " ���" << category << " ������" << description << std::endl;
    }
}

void UI::print_history_chat(std::string account, std::vector<std::string> chat) {

    int width = 50;

    print_title(account, width);

    print_space(2);
    int chat_num = chat.size();
    for (int i = 0; i < chat_num; i++) {
        int len = sizeof(chat[i]);
        switch (chat[i][len-1]) {
        case 'y':chat[i][len - 1] = '\0'; std::cout << std::setw(width) << chat[i] << std::endl; break;
        case 'h':chat[i][len - 1] = '\0'; std::cout << std::setw(0) << chat[i] << std::endl; break;
        }
    }

}


void UI::print_judge_menu() {
    Sleep(SLEEP_TIME);
    system("cls");
    my_ui.print_title("Judge", 50);
    my_ui.print_space(2);
}

void UI::print_judge_menu(User* user) {
    Sleep(SLEEP_TIME);
    system("cls");
    my_ui.print_title("Judge", 50);
    my_ui.print_space(2);

    int i = 0;
    std::cout << "  ���ԣ�" << std::endl;
    while (user->leave_message[i].owner != "") {
        std::cout << "    " << i + 1 << "." << user->leave_message[i].owner << ": " << user->leave_message[i].body << std::endl;
        i++;
    }
    print_space(1);
    int choice;
    std::string string1 = "����1�ظ����ԣ�����0�˳���ǰ����";
    std::cout << std::setw((50 + string1.length()) / 2) << string1 << std::endl;
    std::cout << "ѡ��";
    std::cin >> choice;
    switch (choice) {
    case 0:break;
    case 1:std::cout << "������Ҫ�ظ����˺�" << std::endl;
        std::string callback_account;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin >> callback_account;
        user->chat(callback_account);
    }
    
}

void UI::print_main_menu() {
    print_title("Main", 50);
    print_space(1);
    std::string string = "����ѡ��";
    std::cout << std::setw((50 + string.length()) / 2) << string << std::endl;
    print_space(1);
    print_c(' ', 10);
    std::cout << "1:������Ʒ" << std::endl;
    print_c(' ', 10);
    std::cout << "2:������Ʒ" << std::endl;
    print_c(' ', 10);
    std::cout << "3:��У԰Ȧ" << std::endl;
    print_c(' ', 10);
    std::cout << "4:�򿪸������� " << std::endl;
    print_c(' ', 10);
    std::cout << "5:�˳����� " << std::endl;
    print_space(2);
    print_line('=', 50);
}

void UI::print_discussion_menu(std::vector<std::string> discussion) {
    print_title("Discussion", 50);
    print_space(1);
    int num = discussion.size();
    char c;
    for (int i = 0; i < num; i++) {
        std::string counter_account, title, ID;
        int j = 0;
        while ((c = discussion[i][j]) != '@') {
            counter_account = counter_account + c;
            j++;
        }
        j++;
        while ((c = discussion[i][j]) != '#') {
            title = title + c;
            j++;
        }
        std::cout << "    " << i+1 << ". ��" << title << "�� by " << counter_account << std::endl;
    }
    print_space(2);
    print_line('=', 50);
}

void UI::print_self_center() {
    print_title("Account", 50);
    print_space(1);
    //std::cout << std::setw(width) << string1 << std::endl;
    std::string string1 = "1.�鿴�����˺���Ϣ";
    std::string string2 = "2.�鿴�ѷ�����Ʒ";
    std::string string3 = "3.�鿴���˽��׼�¼";
    std::string string4 = "4.�鿴��������";
    std::string string5 = "5.�˳���ǰ����";
    print_space(1);
    
    std::cout << "    " << string1 << std::endl;
    std::cout << "    " << string2 << std::endl;
    std::cout << "    " << string3 << std::endl;
    std::cout << "    " << string4 << std::endl;
    std::cout << "    " << string5 << std::endl;

   
}

void UI::print_self_menu(User* user) {
    Sleep(SLEEP_TIME);
    system("cls");
    print_title("Account-->account information", 50);
    print_space(1);
    std::cout << "    �˺ţ�" << user->account << std::endl;
    std::cout << "    ���룺" << user->password << std::endl;
    std::cout << "    ������" << user->name << std::endl;
    std::cout << "    ѧ�ţ�" << user->school_id << std::endl;
    std::cout << "    ��" << user->money << std::endl;
    char choice;
    std::string string1 = "����������˳���ǰ����";
    std::cout << std::setw((50 + string1.length()) / 2) << string1 << std::endl;
    std::cout << ">>>";
    std::cin >> choice;
    //getchar();
    //user->check_self();
}

void UI::print_self_goods(User* user) {
    Sleep(SLEEP_TIME);
    system("cls");
    print_title("Account-->goods uploaded", 50);
    print_space(1);

    int i = 0;
    while (user->my_goods[i].owner == user->account) {
        std::cout << "    " << i + 1 << "." << user->my_goods[i].name << std::endl;
        i++;
    }

    print_space(2);
    std::string string1 = "��ѡ�����������Ĳ������鿴������Ʒ��������Ʒ��Ӧ��ţ��˳���ǰ��������0";
    std::cout << std::setw((50 + string1.length()) / 2) << string1 << std::endl;

    std::cout << "ѡ��";
    int choice;
    std::cin >> choice;
    switch (choice) {
    case 0:user->check_self(); break;
    default:Sleep(SLEEP_TIME);
        system("cls"); print_title("Account-->goods uploaded-->" + user->my_goods[choice-1].name, 50);
        print_space(1);
        std::cout << "    ����:" << user->my_goods[choice-1].name << std::endl;
        std::cout << "    ���:" << user->my_goods[choice-1].categpry << std::endl;
        std::cout << "    ����:" << user->my_goods[choice-1].price << std::endl;
        std::cout << "    ����:" << user->my_goods[choice-1].description << std::endl;
        std::cout << "    ����״̬:" << user->my_goods[choice-1].isPurchased << std::endl;
        print_space(2);
        string1 = "����������˳���ǰ����";
        std::cout << std::setw((50 + string1.length()) / 2) << string1 << std::endl;
        std::cout << ">>>";
        char c;
        std::cin >> c;
        //print_self_center();
        break;
    }
    
}

void UI::print_self_deal(User* user) {
    Sleep(SLEEP_TIME);
    system("cls");
    print_title("Account-->goods purchased", 50);
    print_space(1);

    int i = 0;
    std::cout << "  ������" << std::endl;
    while (user->sold_goods[i].buyer != "None" && user->sold_goods[i].buyer != "") {
        std::cout << "    " << i + 1 << "." << user->sold_goods[i].name << " to " << user->sold_goods[i].buyer << std::endl;
        i++;
    }
    i = 0;
    std::cout << std::endl;
    std::cout << "  ���룺" << std::endl;
    while (user->buy_goods[i].owner !="") {
        std::cout << "    " << i + 1 << "." << user->buy_goods[i].name << " from " << user->buy_goods[i].owner << std::endl;
        i++;
    }
    
    print_space(2);
    std::string string1 = "��ѡ�����������Ĳ����������̼�����������Ʒ��Ӧ��ţ��˳���ǰ��������0";
    std::cout << std::setw((50 + string1.length()) / 2) << string1 << std::endl;

    std::cout << "ѡ��";
    int choice;
    std::cin >> choice;
    switch (choice) {
    case 0: break;
    default:Sleep(SLEEP_TIME);
        system("cls"); print_title("Account-->goods uploaded-->" + user->buy_goods[choice-1].name, 50);
        print_space(1);
        /*
        std::cout << "    ����:" << user->deal_goods[choice-1].name << std::endl;
        std::cout << "    ���:" << user->deal_goods[choice-1].categpry << std::endl;
        std::cout << "    ����:" << user->deal_goods[choice-1].price << std::endl;
        std::cout << "    ����:" << user->deal_goods[choice-1].description << std::endl;
        std::cout << "    ����:" << user->deal_goods[choice-1].isPurchased << std::endl;
        print_space(2);
        string1 = "��������������1���˳�����0";
        std::cout << std::setw((50 + string1.length()) / 2) << string1 << std::endl;
        std::cout << "ѡ��";
        int choice1;
        std::cin >> choice1;
        switch (choice1) {
        case 0:print_self_deal(user); break;
        case 1:user->judge(user->buy_goods[choice-1].owner); print_self_deal(user); break;
        }*/

        user->judge(user->buy_goods[choice - 1].owner);
        
    }
}

void UI::print_discussion_body(std::string title) {
    Sleep(SLEEP_TIME);
    system("cls");
    std::string msg = "L" + title + '@';
    send_message(msg);

    if (receive_message()) {
        int i = 0;
        std::string account, title, body;
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
        while (buffer[i] != '#') {
            body = body + buffer[i];
            i++;
        }
        i++;

        print_title(title + " by " + account, 50);
        print_space(1);
        std::cout << "    ���ݣ�" << std::endl;
        std::cout << "    " << body;
        print_space(2);
        std::cout << "    ���ۣ�" << std::endl;
        print_space(1);

        while (buffer[i] != '\0') {
            account = "";
            body = "";
            while (buffer[i] != '@') {
                account = account + buffer[i];
                i++;
            }
            i++;
            while (buffer[i] != '#') {
                body = body + buffer[i];
                i++;
            }
            i++;
            std::cout << "    " << account << ":" << body << std::endl;
        }
    }

    char choice;
    std::string string1 = "����������˳���ǰ����";
    std::cout << std::setw((50 + string1.length()) / 2) << string1 << std::endl;
    std::cout << ">>>";
    std::cin >> choice;
}