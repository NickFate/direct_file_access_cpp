#include <stdio.h>
#include <iostream>

using namespace std;

    /* ������� */

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


void print_bytes(FILE *file)
{
    cout << "������ �� �����: " << endl;
    char ch[3];

    int x = 0;
    int counter = 0;
    while (!feof(file))
    {
        

        fgets(ch, 2, file);
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

}


void print_cur_byte(FILE* file, int pos)
{
    fseek(file, pos, SEEK_SET);

    char ch[3] = {};
    if (fgets(ch, 2, file) == NULL)
    {
        cout << "���� �� �������� " << pos << "�� �����" << endl;
        return;
    }
    //fgets(ch, 2, file);
    cout << ch << endl;
}


void clean_console()
{
    system("cls");
}


void change_cur_byte(FILE* file, int off, char byte)
{
    fseek(file, off, SEEK_SET);

    fwrite(&byte, sizeof(char), 1, file);
    fclose(file);
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

        string input;
        cin >> input;
        if (input == "1")
        {
            
            cin >> file_name;

            fopen_s(&f, file_name.c_str(), "r+b");
        }
        if (input == "2")
        {
            print_bytes(f);
        }
        if (input == "3")
        {
            int pos;
            cin >> pos;

            print_cur_byte(f, pos);
        }
        if (input == "4")
        {
            int off; 
            char byte;

            cin >> off;
            cin >> byte;

            change_cur_byte(f, off, byte);
            fopen_s(&f, file_name.c_str(), "r+b");
        }
        if (input == "5")
        {
            clean_console();
        }
        if (input == "6")
        {
            break;
        }

    }

    if (f != NULL)
    {
        fclose(f);
    }
}