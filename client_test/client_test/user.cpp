#include"head.h"

bool User::setup() {
    my_ui.print_start_menu();
    std::cout << "���Ƿ��Ѿ�ӵ���˺�(y/n)" << std::endl;
    char choice;
    std::cin >> choice;
    switch (choice) {
        case 'y':login(); return true; break;
        case 'n':sign_up(); login(); return true; break;
        default:std::cout << "��������ĸy��n��" << std::endl; setup();
    }

    
}

void User::sign_up() {
    system("cls");
    Sleep(SLEEP_TIME);

    my_ui.print_title("Sign up", 50);
    my_ui.print_space(1);

    int width = 50;
    std::string string = "�������Ϣ��֤��";
    std::cout << std::setw((width + string.length()) / 2) << string << std::endl;
    my_ui.print_space(1);
    std::string d_password;
    std::cout << std::setw(18) << "��������: ";
    std::cin >> name;
    my_ui.print_space(1);
    std::cout << std::setw(18) << "����ѧ��: ";
    std::cin >> school_id;

    std::string msg = "A" + name + "@" + school_id + '@';//ȷ�ϸ�����Ϣ

    if (check_person_info(msg)) {
        Sleep(WAIT_TIME);
        system("cls");
        my_ui.print_title("Sign up", 50);
        my_ui.print_space(3);
        string = "��Ϣ��֤ͨ������������ע�ᡣ";
        std::cout << std::setw((width + string.length()) / 2) << string << std::endl;
    }
    else {
        string = "��Ϣ��֤δͨ�������������������ѧ�š�";
        std::cout << std::setw((width + string.length()) / 2) << string << std::endl;
        Sleep(WAIT_TIME);
        sign_up();
        return;
    }
    Sleep(WAIT_TIME);
    system("cls");
    my_ui.print_title("Sign up", 50);
    my_ui.print_space(1);
    std::cout << std::setw(18) << "�˺�: ";
    std::cin >> account;
    my_ui.print_space(1);

    bool is_set_password = false;
    while (!is_set_password) {
        std::cout << std::setw(18) << "����: ";
        std::cin >> password;
        my_ui.print_space(1);
        std::cout << std::setw(18) << "ȷ������: ";
        std::cin >> d_password;
        my_ui.print_space(1);
        if (password == d_password) is_set_password = true;
        else {
            string = "�������������벻һ�£��������������롣";
            std::cout << std::setw((width + string.length()) / 2) << string << std::endl;
            Sleep(WAIT_TIME);
            system("cls");
            my_ui.print_title("Sign up", 50);
            my_ui.print_space(1);
            std::cout << std::setw(18) << "�˺�: ";
            std::cin >> account;
            my_ui.print_space(1);
        }
    }

    msg = "C" + name + "@" + school_id + "@" + account + "@" + password + '@';//��¼������Ϣ���˺�����
    send_message(msg);
    Sleep(WAIT_TIME);
    system("cls");
    my_ui.print_title("Sign up", 50);
    my_ui.print_space(3);
    string = "��ϲ������˺�ע�ᣬ��������ǰȥ��¼��";
    std::cout << std::setw((width + string.length()) / 2) << string << std::endl;
    Sleep(WAIT_TIME);
}

void User::login() {
    system("cls");
    Sleep(SLEEP_TIME);
    //my_ui.print_setup_menu("Login", "username", "password");
    my_ui.print_title("Login", 50);
    my_ui.print_space(1);
    std::cout << std::setw(18) << "username: ";
    std::cin >> account;
    my_ui.print_space(1);
    std::cout << std::setw(18) << "password: ";
    getchar();
    password = "";
    char key;
    while ((key = _getch()) != '\r') {
        password = password + key;
        std::cout << '*';
    }

    my_ui.print_space(2);
    
    std::string msg = "B" + account + "@" + password +'@' ;//ȷ���˺�����
    if (check_password(msg)) {
        std::string string = "��¼�ɹ���";
        std::cout << std::setw((50 + string.length()) / 2) << string << std::endl;
        my_ui.print_space(2);
        my_ui.print_line('=', 50);
    }
    else {
        std::cout << "�˺������벻ƥ�䣬����������" << std::endl;
        Sleep(WAIT_TIME);
        login();
    }
    Sleep(2000);

}

void User::upload_goods() {
    Sleep(SLEEP_TIME);
    system("cls");
    //std::vector<std::string> my_goods = get_goods(account, "self", NULL);
    //my_ui.print_my_goods(my_goods);
    my_ui.print_title("Upload goods", 50);
    my_ui.print_space(2);
    std::string name, price, category, description;
    std::cout << std::setw(8) << "��������Ҫ��ӵ���Ʒ���ƣ�";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, name);
    std::cout << std::setw(8) << "��������Ҫ��ӵ���Ʒ���(book/Stationery/necessity/sports equipment/clothes/other)��" << std::endl;
    //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin , category);

    std::cout << std::setw(8) << "��������Ҫ��ӵ���Ʒ�۸�" << std::endl;
    //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin >> price;
    std::cout << std::setw(8) << "������������һ��Ʒ��������" << std::endl;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, description);


    std::string msg = "D" + name + "@" + category + "@" + price + "@" + description + "@" + account +  "@";
    send_message(msg);
    Sleep(WAIT_TIME);
    system("cls");
    my_ui.print_title("Upload goods", 50);
    my_ui.print_space(2);
    msg = "�ɹ������Ʒ" + name + ",���" + category + ",�۸�" + price;
    std::string string1 = "��ѡ�����������Ĳ�����";
    std::string string2 = "1.����1���������Ʒ";
    std::string string3 = "2.����2�˳���ǰ����";
    std::cout << std::setw((50 + msg.length()) / 2) << msg << std::endl;
    my_ui.print_space(1);
    std::cout << std::setw((50 + string1.length()) / 2) << string1 << std::endl;
    my_ui.print_space(1);
    std::cout << std::setw((50 + string2.length()) / 2) << string2 << std::endl;
    my_ui.print_space(1);
    std::cout << std::setw((50 + string3.length()) / 2) << string3 << std::endl;
    my_ui.print_space(1);
    std::cout << "����ѡ��";
    int choice;
    //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin >> choice;
    switch (choice) {
    case 1:upload_goods(); break;
    case 2:break;
    }
    //my_goods = get_goods(account, "self", NULL);
    //my_ui.print_my_goods(my_goods);

    
}

void User::search_goods() {
    Sleep(SLEEP_TIME);
    system("cls");
    std::vector<std::string> empty;
    std::vector<std::string> goods;
    my_ui.print_search_goods(empty);
    std::cout << "��ѡ����ҷ�ʽ����������������1�������Ʋ���������2" << std::endl;
    int choice;
    std::cout << std::setw(8) << "����ѡ��";
    std::cin >> choice;
    std::string input;
    switch (choice) {
    case 1:my_ui.print_space(1);
        std::cout << std::setw(8) << "���������(book/Stationery/necessity/sports equipment/clothes/other)��" << std::endl;
        //my_ui.print_category();
        std::cout << "���";
        getchar();
        std::getline(std::cin,input);     
        goods = get_goods(account, "category", input);
        break;
    case 2:std::cout << std::setw(8) << "��������Ҫ���ҵ���Ʒ�ؼ���" << std::endl;
        my_ui.print_space(1);
        std::cout << std::setw(8) << "�ؼ��֣�";
        std::cin >> input;
        goods = get_goods(account, "name", input);
        break;
    default:std::cout << "����1,2��ѡ��" << std::endl; search_goods();
    }
    Sleep(WAIT_TIME);
    system("cls");
    my_ui.print_search_goods(goods);
    my_ui.print_space(1);
    std::string string1 = "��ѡ�����������Ĳ�����";
    std::string string2 = "1.����1����������Ʒ";
    std::string string3 = "2.����2�˳���ǰ����";
    std::string string4 = "3.����3����ָ����Ʒ";
    std::string string5 = "4.����4��ָ���̼�����";
    std::cout << std::setw((50 + string1.length()) / 2) << string1 << std::endl;
    std::cout << std::setw((50 + string2.length()) / 2) << string2 << std::endl;
    std::cout << std::setw((50 + string3.length()) / 2) << string3 << std::endl;
    std::cout << std::setw((50 + string4.length()) / 2) << string4 << std::endl;
    std::cout << std::setw((50 + string5.length()) / 2) << string5 << std::endl;
    std::cout << "����ѡ��";
    //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin >> choice;
    std::string _counter_account,_name;
    int _price;
    switch (choice) {
    case 1:search_goods(); break;
    case 2:break;
    case 3:string1 = "��������Ʒ���";
        std::cout << std::setw((50 + string1.length()) / 2) << string1 << std::endl;
        std::cin >> choice;
        _counter_account = get_owner(goods[choice - 1]);
        _price = get_price(goods[choice - 1]);
        _name = get_name(goods[choice - 1]);
        purchase(_name, _counter_account, _price);
        break;
    case 4:string1 = "��������Ʒ���";
        std::cout << std::setw((50 + string1.length()) / 2) << string1 << std::endl;
        std::cin >> choice;
        _counter_account = get_owner(goods[choice - 1]);
        chat(_counter_account);
        //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

void User::chat(std::string counter_account) {
    Sleep(SLEEP_TIME);
    system("cls");
    my_ui.print_title("Purchase with "+counter_account, 50);
    my_ui.print_space(2);

    std::cout << "    ��������:";
    std::string body;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, body);
    std::string msg = 'I' + account + '@' + body + '@' + counter_account + "@";
    send_message(msg);
    Sleep(SLEEP_TIME);
    system("cls");
    my_ui.print_title("Purchase with " + counter_account, 50);
    my_ui.print_space(2);

    body = "�������";
    std::cout << std::setw((50 + body.length()) / 2) << body << std::endl;
    Sleep(WAIT_TIME);
}

void User::judge(std::string counter_account) {
    my_ui.print_judge_menu();
    std::string string = "����������Է������֣�1-5��";
    std::cout << std::setw((50 + string.length()) / 2) << string << std::endl;
    std::cout << "���֣�";
    char counter_score;
    std::cin >> counter_score;
    std::string msg = 'K' + counter_score + "@" + counter_account;
    send_message(msg);
}

void User::launch_discussion() {
    Sleep(SLEEP_TIME);
    system("cls");
    my_ui.print_title("Lauch discussion", 50);
    
    std::string title, body;
    std::cout << "����:";
    getchar();
    std::getline(std::cin, title);
    std::cout << std::endl;
    std::cout << "����:" << std::endl;
    std::getline(std::cin, body);
    std::string msg = "F" + account + "@" + title + "@" + body + "@";
    send_message(msg);

    std::cout << "�ѷ���һ��У԰Ȧ��Ϣ��" << std::endl;
    Sleep(WAIT_TIME);
}

void User::joinin_discussion(std::string title) {
    my_ui.print_title("Join in discussion", 50);
    my_ui.print_space(2);
    std::string body;
    std::cout << "��������:" << std::endl;
    std::getline(std::cin, body);
    std::string msg = "G" + account + "@" + title + "@" + body + "@";
    send_message(msg);

    std::cout << "�ѶԸ�У԰Ȧ�������ۡ�" << std::endl;
    Sleep(WAIT_TIME);
}

void User::discuss() {
    bool isQuit = false;
    while (!isQuit) {
        Sleep(SLEEP_TIME);
        system("cls");
        std::vector<std::string> discussion;
        discussion = get_discussion_title();
        //std::cout << discussion[0] << std::endl;
        my_ui.print_discussion_menu(discussion);
        std::cout << "��ѡ����Ҫ���еĲ���,����0����У԰Ȧ������1�鿴����ĳһ��У԰Ȧ������2����ĳһ����У԰Ȧ������3�˳���ǰҳ�档" << std::endl;
        int choice;
        std::cout << "����ѡ��";
        std::cin >> choice;
        std::string id; 
        switch (choice) {
        case 0:launch_discussion(); break;
        case 1:std::cout << "��������Ҫ�鿴��У԰Ȧ����" << std::endl; 
            getchar();
            std::getline(std::cin, id);
            my_ui.print_discussion_body(id); break;
        case 2:
            std::cout << "��������Ҫ�鿴��У԰Ȧ����" << std::endl;
            getchar();
            std::getline(std::cin, id);
            joinin_discussion(id); break;
        case 3:isQuit = true; break;
        }
    }    
}

void User::check_self() {
    bool isQuit = false;
    while (!isQuit) {
        Sleep(SLEEP_TIME);
        system("cls");

        my_ui.print_self_center();
        init();
        std::cout << "���������ѡ��" << std::endl;
        std::cout << "ѡ��";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        int choice;

        std::cin >> choice;
        //std::cout << choice << std::endl;
        switch (choice) {
        case 1:my_ui.print_self_menu(this); break;
        case 2:my_ui.print_self_goods(this); break;
        case 3:my_ui.print_self_deal(this); break;
        case 4:my_ui.print_judge_menu(this); break;
        default:isQuit = true; break;
        }
    }    
    //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

User::User() {
    
}

void User::purchase(std::string name, std::string counter_account, int price) {
    Sleep(SLEEP_TIME);
    system("cls");
    my_ui.print_title("Purchase", 50);
    my_ui.print_space(2);
    money -= price;
    std::string msg = "N" + name + '@' + account + '@' + std::to_string(price) + '@' + counter_account + '@';
    send_message(msg);

    msg = "���֧��";
    std::cout << std::setw((50 + msg.length()) / 2) << msg << std::endl;

    Sleep(WAIT_TIME);
}

void User::init() {
    send_message("M" + account + '@');
    
    name = "";
    school_id = "";

    int i = 0;
    if (receive_message()) {
        //������Ϣ
        std::string _money;
        while (buffer[i] != '@') {
            name = name + buffer[i];
            i++;
        }
        i++;
        while (buffer[i] != '@') {
            school_id = school_id + buffer[i];
            i++;
        }
        i++;
        while (buffer[i] != '%') {
            _money = _money + buffer[i];
            i++;
        }
        i++;
        money = std::stoi(_money);

        //�ѷ���
        for (int j = 0; buffer[i] != '%';j++) {
            std::string  _name, _category, _price, _description, _owner, _isPurchased, _buyer;
            while (buffer[i] != '@') {
                _name = _name + buffer[i];
                i++;
            }
            i++;
            while (buffer[i] != '@') {
                _category = _category + buffer[i];
                i++;
            }
            i++;
            while (buffer[i] != '@') {
                _price = _price + buffer[i];
                i++;
            }
            i++;
            while (buffer[i] != '@') {
                _description = _description + buffer[i];
                i++;
            }
            i++;
            while (buffer[i] != '#') {
                _isPurchased = _isPurchased + buffer[i];
                i++;
            }
            i++;
            my_goods[j].name = _name;
            my_goods[j].categpry = _category;
            my_goods[j].price = _price;
            my_goods[j].description = _description;
            my_goods[j].owner = account;
            my_goods[j].isPurchased = _isPurchased;
        }
        i++;
        //������
        
        for (int j = 0; buffer[i] != '%';j++) {
            std::string  _name, _buyer;
            while (buffer[i] != '@') {
                _name = _name + buffer[i];
                i++;
            }
            i++;
            while (buffer[i] != '#') {
                _buyer = _buyer + buffer[i];
                i++;
            }
            i++;
            sold_goods[j].name = _name;
            sold_goods[j].buyer = _buyer;
        }
        i++;

        //������
        for (int j = 0; buffer[i] != '%'; j++) {
            std::string  _name, _owner;
            while (buffer[i] != '@') {
                _name = _name + buffer[i];
                i++;
            }
            i++;
            while (buffer[i] != '#') {
                _owner = _owner + buffer[i];
                i++;
            }
            i++;
            buy_goods[j].name = _name;
            buy_goods[j].owner = _owner;
        }
        i++;
    }
    //����

    for (int j = 0; buffer[i] != '%'; j++) {
        std::string  _counter_account, _body;
        while (buffer[i] != '@') {
            _counter_account = _counter_account + buffer[i];
            i++;
        }
        i++;
        while (buffer[i] != '#') {
            _body = _body + buffer[i];
            i++;
        }
        i++;
        leave_message[j].owner = _counter_account;
        leave_message[j].body = _body;
    }

    //std::cout << "init success" << std::endl;
    //system("pause");
}