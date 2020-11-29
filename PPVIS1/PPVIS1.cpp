#include <iostream>
#include <string>
#include <Windows.h>
#include <fstream>
#include <vocabulary.h>
using namespace std;



void Menu()
{
	cout << "\tМеню\n"
		<< "(1)Добавление элемента\n"
		<< "(2)Вывод данных по элементу\n"
		<< "(3)Удаление элемента\n"
		<< "(4)Вывести словарь\n"
		<< "(5)Размер словаря\n"
		<< "(6)Изменить значение\n"
		<< "(7)Сохранить изменения\n"
		<< "(0)Выйти из программы\n";
}

int main()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Vocabulary<string> vocabulary;
	string Word_E, Word_R;
	int choose;
	ofstream fout;
	ifstream fin;
	fin.open("vocabulary.txt");
	if (!fin.is_open())
	{
		cout << "Файл не найден. Словарь будет пуст" << endl;
	}
	else
	{
		getline(fin, Word_E);
		while (!fin.eof())
		{
			getline(fin, Word_E);
			getline(fin, Word_R);
			vocabulary.push_back(Word_E, Word_R);
		}
		cout << "Файл открыт. Словарь загружен" << endl;
		system("pause");
	}
	fin.close();
	while (1)
	{
		system("cls");
		Menu();
		while (1)
		{
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
			cin >> choose;
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(30000, '\n');
				cout << "Некорректное значение, попробуйте еще раз.\n";
			}
			else
			{
				break;
			}
		}
		switch (choose)
		{
		case 1:
				cout << "Введите английское слово: ";
				cin.ignore(30000, '\n');
				getline(cin, Word_E);
				cout << "\nВведите русское слово: ";
				getline(cin, Word_R);
				vocabulary.push_back(Word_E, Word_R);
				break;
		case 2:
			cout << "Введите слово: ";
			cin.ignore(30000, '\n');
			getline(cin, Word_E);
				vocabulary.show_data(Word_E);
				system("pause");
				break;
		case 3:
			cout << "Введите слово: ";
			cin.ignore(30000, '\n');
			getline(cin, Word_E);
			vocabulary.delete_element(Word_E);
			system("pause");
			break;
		case 4:
			vocabulary.Show_Tree(vocabulary.head); cout << endl;
			system("pause");
			break;
		case 5:
			vocabulary.GetSize();
			system("pause");
			break;
		case 6:
			cout << "Введите английское слово: ";
			cin.ignore(30000, '\n');
			getline(cin, Word_E);
			cout << "\nВведите русское слово для замены: ";
			getline(cin, Word_R);
			vocabulary.change_data(Word_E, Word_R);
			system("pause");
			break;
		case 7:
			fout.open("vocabulary.txt");
			if (!fout.is_open())
			{
				cout << "Ошибка открытия файла" << endl;
			}
			else
			{
				vocabulary.Fout(vocabulary.head, fout);
			}
			fout.close();
			break;
		case 0:
			exit(0);
			break;
		default:
			break;
		}
	}
}