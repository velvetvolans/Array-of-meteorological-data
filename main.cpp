#include <deque>
#include <iostream>
#include <locale>
#include <windows.h>

using namespace std;

struct meteo {
    string name; //�������� �������
    unsigned short int date; //���� � ������ ����
    deque<unsigned int> wind; //������ ��������� �������� �����
    deque<int> themperature; //������ ��������� �����������
    unsigned int wind_length, themperature_length; // ����� �������� ������ � ����� � �����������
    long double wind_average = 0, themperature_average = 0; //�������������� ������ � ����� � �����������
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
        cout << "1. ������ �����������" << endl
             << "2. ����� ������ ����������� �� �������������� ������������ ���� ��������" << endl
             << "3. ����� ������ ����������� �� �������������� ��������� ����� ���� ��������" << endl
             << "4. ����� ���������� � ����� ������ ���" << endl
             << "5. ����� �� ���������" << endl
             << "������� ����� ������: ";
        cin >> a;
        switch (a)
        {
            case 1: {
            meteo temp;
            cout << "������� �������� ������������: ";
            cin >> temp.name;
            cout << "������� ���� ��������� ������: ";
            cin >> temp.date;
            cout << "������� ���������� ������� � �������� �����: ";
            cin >> temp.wind_length;
            for (unsigned int i = 0; i < temp.wind_length; i++) {
                cout << "������� " << i + 1 << "-� ������ � �������� �����: ";
                unsigned int wind_entry; //�������� ����� � i + 1 ������
                cin >> wind_entry;
                temp.wind.push_back(wind_entry);
                temp.wind_average += wind_entry;
            }
            if (temp.wind_length != 0) {
                temp.wind_average /= temp.wind_length;
            }
            cout << "������� ���������� ������� � �����������: ";
            cin >> temp.themperature_length;
            for (unsigned int i = 0; i < temp.themperature_length; i++) {
                cout << "������� " << i + 1 << "-� ������ � �����������: ";
                int themperature_entry; //����������� ����� � i + 1 ������
                cin >> themperature_entry;
                temp.themperature.push_back(themperature_entry);
                temp.themperature_average += themperature_entry;
            }
            if (temp.themperature_length != 0) {
                temp.themperature_average /= temp.themperature_length;
            }
            data.push_back(temp);
            number++;
            cout << "���� ������ ��������" << endl;
            break;
        }
        case 2: {
            int themperature;
            cout << "������� �������������� �����������: ";
            cin >> themperature;
            bool isCorrect = false;
            for (int i = 0; i < number; i++) {
                if (!data[i].themperature.empty() && data[i].themperature_average < themperature) {
                    isCorrect = true;
                    cout << "�������� ������������: \"" << data[i].name << "\". ����: " << data[i].date << "." << endl;
                }
            }
            if (!isCorrect) {
                cout << "���������� ����������� ���" << endl;
            }
            break;
        }
        case 3: {
            int wind;
            cout << "������� �������������� �������� �����: ";
            cin >> wind;
            bool isCorrect = false;
            for (int i = 0; i < number; i++) {
                if (!data[i].wind.empty() && data[i].wind_average > wind) {
                    isCorrect = true;
                    cout << "�������� ������������: \"" << data[i].name << "\". ����: " << data[i].date << "." << endl;
                }
            }
            if (!isCorrect) {
                cout << "���������� ����������� ���." << endl;
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
                cout << "���������� ����������� ���" << endl;
            } else {
                cout << "�������� ������������: \"" << data[hottest_index].name << "\". ����: " << data[hottest_index].date << "." << endl
                     << "����������� �� ���������� ���: ";
                for (int i = 0; i < data[hottest_index].themperature_length; i++) {
                    cout << data[hottest_index].themperature[i];
                    if (i != data[hottest_index].themperature_length - 1) {
                        cout << ", ";
                    } else {
                        cout << ".";
                    }
                }
                cout << endl << "�������� ����� �� ���������� ���: ";
                for (int i = 0; i < data[hottest_index].wind_length; i ++) {
                    cout << data[hottest_index].wind[i];
                    if (i != data[hottest_index].wind_length - 1) {
                        cout << ", ";
                    } else {
                        cout << ".";
                    }
                }
                if (!data[hottest_index].wind_length) {
                    cout << "��� ������.";
                }
                cout << endl;
            }
            break;
        }
        case 5:
            ActiveProgram = false;
            break;
        default:
            cout << "\n��������� ����\n\n";
            break;
        }
    }
    return 0;
}
