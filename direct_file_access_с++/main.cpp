
#include <iostream>

#include <string> // ��� �������� �����

using namespace std;

    /* ������� */


/// <summary>
/// ������� ������ ��������.
/// </summary>
void print_menu()
{
    cout << "�������� ��������:" << endl;
    cout << "\t1. ������� ����" << endl;
    cout << "\t2. ����������� ������ �� �����" << endl;
    cout << "\t3. ����������� ���������� ����" << endl;
    cout << "\t4. �������� ����" << endl;
    cout << "\t5. �������� �������" << endl;
    cout << "\t6. �����" << endl;
}


/// <summary>
/// ������� ������ �� ����� file.
/// </summary>
void print_bytes(FILE *file)
{
    cout << "������ �� �����: " << endl;
    char ch[2];

    int x = 0;
    int counter = 0;
    while (fgets(ch, 2, file))
    {

        
        cout << "\"" << ch << "\"\t";
        
        if (x == 10)
        {
            cout << endl;
            x -= 10;
        }

        x++;
        counter++;
    }
    cout << endl << "������� " << counter << " ������ �� �����." << endl;
    fclose(file);
    system("pause");

}


/// <summary>
/// ������� ���� � �������� pos �� ����� file. ���������� ���������� � ����.
/// </summary>
void print_cur_byte(FILE* file, int pos)
{
    fseek(file, pos, SEEK_SET);

    char ch[3] = {};
    if (fgets(ch, 2, file) == NULL)
    {
        cout << "���� �� �������� " << pos << "�� �����" << endl;
        return;
    }

    cout << pos << "� ����:" << ch << endl;

    system("pause");
}


/// <summary>
/// ������� �������
/// </summary>
void clean_console()
{
    system("cls");
}


/// <summary>
/// �������� ���� �� ����� file � �������� off �� ���� byte.
/// </summary>
/// <param name="file"></param>
/// <param name="off"></param>
/// <param name="byte"></param>
void change_cur_byte(FILE* file, int off, char byte)
{
    fseek(file, off, SEEK_SET);

    fwrite(&byte, sizeof(char), 1, file);
    fclose(file); // ���������� ������� ����, ��� ��� fwrite ��������� �����.
    cout << "���� �������." << endl;
    system("pause");
}


/// <summary>
/// ���������, �������� �� ������ ������. 
/// </summary>
bool is_digit(string str)
{
    return !str.empty() && str.find_first_not_of("0123456789") == string::npos;
}


/// <summary>
/// ���������, �������� �� ������ ������ ������� ��������� � ��������.
/// </summary>
bool is_string(string str)
{
    return !str.empty() && (str).find_first_not_of("qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM����������������������������������������������������������������") == string::npos;
}


/// <summary>
/// ����������� ���� ������ �� ��� ���, ���� ������ �� ����� ��������������� �������� checking_func
/// </summary>
string input_with_checking(bool checking_func(string))
{
    string str;
    cin >> str;
    while (true)
    {
        if (!checking_func(str))
        {
            cout << "�������� ����, ��������� ����: ";
            cin >> str;
        }
        else
        {
            return str;
            break;
        }
    }
}

    
    /* ����� ����� */

void main()
{
    setlocale(LC_ALL, "rus");

    FILE* f = NULL;
    string file_name;
    

    while (true)
    {
        print_menu();

        cout << "�������� �����: ";
        string input;
        input = input_with_checking(is_digit);

        if (input == "1")
        {
            // ��������� ����, ���� �� ��� ������
            if (f)
            {
                fclose(f);
            }

            cout << "������� ���� � �����: ";
            cin >> file_name;

            int err = fopen_s(&f, file_name.c_str(), "r+b");
            
            if (err != 0) // ���� ���� �� ������
            {
                cout << "��������� ������ ��� �������� ����� " << file_name << endl; // �������� �� ������
            }
            else
            {
                cout << "���� " << file_name << " ������� ������" << endl;
            }
            continue;
        }

        if (input == "5")
        {
            clean_console();
        }

        if (input == "6")
        {
            break;
        }

        // ��������: ���� ������?
        if (!f)
        {
            cout << "���� �� ������" << endl; // �������� �� ������
            continue; // � ������������� ���������
        }

        if (input == "2")
        {
            print_bytes(f);
            fopen_s(&f, file_name.c_str(), "r+b"); // ������ ��������� ����, ��� ��� ���� ��� ������ � ���������� ������
        }

        if (input == "3")
        {
            int pos;
            cout << "������� ������� ������� �����: ";
            pos = stoi(input_with_checking(is_digit));

            print_cur_byte(f, pos);
        }

        if (input == "4")
        {
            int off; 
            char byte;
            cout << "������� ������� ������� �����: ";
            off = stoi(input_with_checking(is_digit));
            cout << "������� ����� �������� �����: ";
            cin >> byte;

            change_cur_byte(f, off, byte);
            fopen_s(&f, file_name.c_str(), "r+b"); // ������ ��������� ����, ��� ��� ���� ��� ������ � ���������� ������
        }
    }

    if (f != NULL)
    {
        fclose(f);
    }
}