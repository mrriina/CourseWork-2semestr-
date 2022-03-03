#include <iostream>
#include<Windows.h>
#include<locale>
#include <fstream>
#include "AllFunctions.h"

using namespace std;

int main()
{
	system("color F0");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	string file;
	Climate** clim = new Climate * [100];
	for (int i = 0; i < 100; i++)
	{
		clim[i] = new Climate;
	}
	system("cls");
	cout << " Выберите с каким файлом вы хотите работать " << endl;
	cout << " 1) File1.txt " << endl;
	cout << " 2) File2.txt " << endl;

	int n;
	while (!(cin >> n) || (cin.peek() != '\n') || (n != 1 && n != 2))// цикл продолжается до тех пор, пока пользователь не введет корректное значение
	{
		cin.clear();
		while (cin.get() != '\n');
		cout << "Ошибка ввода! Повторите пожалуйста...\n";
	}
	switch (n)
	{
	case 1:
		file = "File1.txt";
		break;
	case 2:
		file = "File2.txt";
		break;
	default:
		break;
	}
	int numb = 0;
	system("pause");
	system("cls");
	while(1)
	{
		cout << "Выберите действие: " << endl
			<< "(1) Выход из программы" << endl
			<< "(2) Ввод информации из текстового файла в массив указателей на записи" << endl
			<< "(3) Добавление новых элементов в конец массива" << endl
			<< "(4) Просмотр всех элементов массива" << endl
			<< "(5) Вывод информации из массива в текстовый файл" << endl
			<< "(6) Корректировка полей выбранного элемента" << endl
			<< "(7) Удаление выбранного элемента" << endl
			<< "(8) Удаление элементов по условию(поле < или > заданного значения)" << endl				
			<< "(9) Замена выбранного элемента" << endl
			<< "(10) Удаление элементов, начиная от выбранного" << endl
			<< "Ваш выбор: " << endl;
		int a;
		cin >> a;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(32767, '\n');
		}

		switch (a)
		{
		case 1:
			cout << "Программа завершена!" << endl;
			return 0;
		case 2:
			ReadingTXT(clim, numb, file);
			system("pause");
			system("cls");
			break;
		case 3:
			cout << "Введите количество данных: ";
			int n;
			while (!(cin >> n) || (cin.peek() != '\n') || n < 0) // цикл продолжается до тех пор, пока пользователь не введет корректное значение
			{
				cin.clear();
				while (cin.get() != '\n');
				cout << "Ошибка ввода! Повторите пожалуйста...\n";
			}
			for (int i = 0; i < n; i++)
			{
				
				clim[numb] = AddData();
				numb++;
			}
			PrintData(clim, numb);
			system("pause");
			system("cls");
			break;
		case 4:
			PrintData(clim, numb);
			system("pause");
			system("cls");
			break;
		case 5:
			WriteTXT(clim, numb, file);
			system("pause");
			system("cls");
			break;
		case 6:
			ChangeFieldItem(clim, numb);
			if(numb!=-1)
				PrintData(clim, numb);
			system("pause");
			system("cls");
			break;
		case 7:
			DelItem(clim, numb);
			if (numb != -1)
				PrintData(clim, numb);
			system("pause");
			system("cls");
			break;
		case 8:
			DelCondition(clim, numb);
			if (numb != -1)
				PrintData(clim, numb);
			system("pause");
			system("cls");
			break;
		case 9:
			ChangeItem(clim, numb);
			if (numb != -1)
				PrintData(clim, numb);
			system("pause");
			system("cls");
			break;
		case 10:
			DelItemsStartSelected(clim, numb);
			if (numb != -1)
				PrintData(clim, numb);
			system("pause");
			system("cls");
			break;
		default:
			cout << "Неверно введён номер действия!" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
	system("pause");
	return 0;
}


