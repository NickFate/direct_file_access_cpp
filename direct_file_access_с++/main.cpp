
#include <iostream>

#include <string> // для проверки ввода

using namespace std;

    /* ФУНКЦИИ */


/// <summary>
/// Выводит список действий.
/// </summary>
void print_menu()
{
    cout << "Выберите действие:" << endl;
    cout << "\t1. Выбрать файл" << endl;
    cout << "\t2. Просмотреть данные из файла" << endl;
    cout << "\t3. Просмотреть конкретный байт" << endl;
    cout << "\t4. Изменить байт" << endl;
    cout << "\t5. Очистить консоль" << endl;
    cout << "\t6. Выход" << endl;
}


/// <summary>
/// Выводит данные из файла file.
/// </summary>
void print_bytes(FILE *file)
{
    cout << "Данные из файла: " << endl;
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
    cout << endl << "Считано " << counter << " байтов из файла." << endl;
    fclose(file);
    system("pause");

}


/// <summary>
/// Выводит байт с индексом pos из файла file. Индексация начинается с нуля.
/// </summary>
void print_cur_byte(FILE* file, int pos)
{
    fseek(file, pos, SEEK_SET);

    char ch[3] = {};
    if (fgets(ch, 2, file) == NULL)
    {
        cout << "Файл не содержит " << pos << "го байта" << endl;
        return;
    }

    cout << pos << "й байт:" << ch << endl;

    system("pause");
}


/// <summary>
/// Очищает консоль
/// </summary>
void clean_console()
{
    system("cls");
}


/// <summary>
/// Изменяет байт из файла file с индексом off на байт byte.
/// </summary>
/// <param name="file"></param>
/// <param name="off"></param>
/// <param name="byte"></param>
void change_cur_byte(FILE* file, int off, char byte)
{
    fseek(file, off, SEEK_SET);

    fwrite(&byte, sizeof(char), 1, file);
    fclose(file); // необходимо закрыть файл, так как fwrite блокирует поток.
    cout << "байт изменен." << endl;
    system("pause");
}


/// <summary>
/// Проверяет, является ли строка числом. 
/// </summary>
bool is_digit(string str)
{
    return !str.empty() && str.find_first_not_of("0123456789") == string::npos;
}


/// <summary>
/// Проверяет, содержит ли строка только символы кириллицы и латиницы.
/// </summary>
bool is_string(string str)
{
    return !str.empty() && (str).find_first_not_of("qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNMЙЦУКЕНГШЩЗХЪФЫВАПРОЛДЖЭЯЧСМИТЬБЮйцукенгшщзхъфывапролджэячсмитьбю") == string::npos;
}


/// <summary>
/// запрашивает ввод строки до тех пор, пока строка не будет соответствовать проверке checking_func
/// </summary>
string input_with_checking(bool checking_func(string))
{
    string str;
    cin >> str;
    while (true)
    {
        if (!checking_func(str))
        {
            cout << "Неверный ввод, повторите ввод: ";
            cin >> str;
        }
        else
        {
            return str;
            break;
        }
    }
}

    
    /* ТОЧКА ВХОДА */

void main()
{
    setlocale(LC_ALL, "rus");

    FILE* f = NULL;
    string file_name;
    

    while (true)
    {
        print_menu();

        cout << "Ожидание ввода: ";
        string input;
        input = input_with_checking(is_digit);

        if (input == "1")
        {
            // закрываем файл, если он уже открыт
            if (f)
            {
                fclose(f);
            }

            cout << "Введите путь к файлу: ";
            cin >> file_name;

            int err = fopen_s(&f, file_name.c_str(), "r+b");
            
            if (err != 0) // если файл не открыт
            {
                cout << "Произошла ошибка при открытии файла " << file_name << endl; // сообщаем об ошибке
            }
            else
            {
                cout << "Файл " << file_name << " успешно открыт" << endl;
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

        // проверка: файл открыт?
        if (!f)
        {
            cout << "Файл не выбран" << endl; // сообщаем об ошибке
            continue; // и перезапускаем программу
        }

        if (input == "2")
        {
            print_bytes(f);
            fopen_s(&f, file_name.c_str(), "r+b"); // заново открываем файл, так как файл был закрыт в предыдущей строке
        }

        if (input == "3")
        {
            int pos;
            cout << "Введите позицую нужного байта: ";
            pos = stoi(input_with_checking(is_digit));

            print_cur_byte(f, pos);
        }

        if (input == "4")
        {
            int off; 
            char byte;
            cout << "Введите позицую нужного байта: ";
            off = stoi(input_with_checking(is_digit));
            cout << "Введите новое значение байта: ";
            cin >> byte;

            change_cur_byte(f, off, byte);
            fopen_s(&f, file_name.c_str(), "r+b"); // заново открываем файл, так как файл был закрыт в предыдущей строке
        }
    }

    if (f != NULL)
    {
        fclose(f);
    }
}