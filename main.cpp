#include <deque>
#include <iostream>
#include <locale>
#include <windows.h>

using namespace std;

struct meteo {
    string name; //Название станции
    unsigned short int date; //День с начала года
    deque<unsigned int> wind; //Массив изменений скорости ветра
    deque<int> themperature; //Массив изменений температуры
    unsigned int wind_length, themperature_length; // Длины массивов данных о ветре и температуре
    long double wind_average = 0, themperature_average = 0; //Среднесуточные данные о ветре и температуре
};

int main()
{
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    deque<meteo> data;
    unsigned int number = 0;
    int a;
    bool ActiveProgram = true;

    while (ActiveProgram)
    {
        cout << "1. Ввести метеоданные" << endl
             << "2. Вывод списка метеоданных со среднесуточной температурой ниже заданной" << endl
             << "3. Вывод списка метеоданных со среднесуточной скоростью ветра выше заданной" << endl
             << "4. Вывод информации о самом жарком дне" << endl
             << "5. Выход из программы" << endl
             << "Введите номер пункта: ";
        cin >> a;
        switch (a)
        {
            case 1: {
            meteo temp;
            cout << "Введите название метеостанции: ";
            cin >> temp.name;
            cout << "Введите день получения данных: ";
            cin >> temp.date;
            cout << "Введите количество записей о скорости ветра: ";
            cin >> temp.wind_length;
            for (unsigned int i = 0; i < temp.wind_length; i++) {
                cout << "Введите " << i + 1 << "-ю запись о скорости ветра: ";
                unsigned int wind_entry; //Скорость ветра в i + 1 момент
                cin >> wind_entry;
                temp.wind.push_back(wind_entry);
                temp.wind_average += wind_entry;
            }
            if (temp.wind_length != 0) {
                temp.wind_average /= temp.wind_length;
            }
            cout << "Введите количество записей о температуре: ";
            cin >> temp.themperature_length;
            for (unsigned int i = 0; i < temp.themperature_length; i++) {
                cout << "Введите " << i + 1 << "-ю запись о температуре: ";
                int themperature_entry; //Температура ветра в i + 1 момент
                cin >> themperature_entry;
                temp.themperature.push_back(themperature_entry);
                temp.themperature_average += themperature_entry;
            }
            if (temp.themperature_length != 0) {
                temp.themperature_average /= temp.themperature_length;
            }
            data.push_back(temp);
            number++;
            cout << "Ввод данных закончен" << endl;
            break;
        }
        case 2: {
            int themperature;
            cout << "Введите среднесуточную температуру: ";
            cin >> themperature;
            bool isCorrect = false;
            for (int i = 0; i < number; i++) {
                if (!data[i].themperature.empty() && data[i].themperature_average < themperature) {
                    isCorrect = true;
                    cout << "Название метеостанции: \"" << data[i].name << "\". День: " << data[i].date << "." << endl;
                }
            }
            if (!isCorrect) {
                cout << "Подходящих метеоданных нет" << endl;
            }
            break;
        }
        case 3: {
            int wind;
            cout << "Введите среднесуточную скорость ветра: ";
            cin >> wind;
            bool isCorrect = false;
            for (int i = 0; i < number; i++) {
                if (!data[i].wind.empty() && data[i].wind_average > wind) {
                    isCorrect = true;
                    cout << "Название метеостанции: \"" << data[i].name << "\". День: " << data[i].date << "." << endl;
                }
            }
            if (!isCorrect) {
                cout << "Подходящих метеоданных нет." << endl;
            }
            break;
        }
        case 4: {
            bool isCorrect = false;
            int hottest_value, hottest_index;
            for (int i = 0; i < number; i++) {
                if (!data[i].themperature.empty() && (!isCorrect || (data[i].themperature_average > hottest_value))) {
                    isCorrect = true;
                    hottest_value = data[i].themperature_average;
                    hottest_index = i;
                }
            }
            if (!isCorrect) {
                cout << "Подходящих метеоданных нет" << endl;
            } else {
                cout << "Название метеостанции: \"" << data[hottest_index].name << "\". День: " << data[hottest_index].date << "." << endl
                     << "Температура на протяжении дня: ";
                for (int i = 0; i < data[hottest_index].themperature_length; i++) {
                    cout << data[hottest_index].themperature[i];
                    if (i != data[hottest_index].themperature_length - 1) {
                        cout << ", ";
                    } else {
                        cout << ".";
                    }
                }
                cout << endl << "Скорость ветра на протяжении дня: ";
                for (int i = 0; i < data[hottest_index].wind_length; i ++) {
                    cout << data[hottest_index].wind[i];
                    if (i != data[hottest_index].wind_length - 1) {
                        cout << ", ";
                    } else {
                        cout << ".";
                    }
                }
                if (!data[hottest_index].wind_length) {
                    cout << "нет данных.";
                }
                cout << endl;
            }
            break;
        }
        case 5:
            ActiveProgram = false;
            break;
        default:
            cout << "\nПовторите ввод\n\n";
            break;
        }
    }
    return 0;
}
