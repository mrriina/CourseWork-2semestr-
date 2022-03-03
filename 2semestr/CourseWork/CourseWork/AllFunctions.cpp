#include "AllFunctions.h"

void ReadingTXT(Climate** clim, int& numb, string file)
{
	numb = 0;
	ifstream ReadingClimInfo;

	int typeNum = -1;
	char temp[100];
	ReadingClimInfo.open(file);
	if (!ReadingClimInfo.is_open())
	{
		cout << "Ошибка при открытии файла!" << endl;
	}
	else
	{
		cout << "Файл открыт!" << endl;
		if (ReadingClimInfo.peek() == EOF)
		{
			cout << "Файл пустой!" << endl;
			numb = -1;
			cin.ignore();
			ReadingClimInfo.close();
			return;
		}
		string skip;
		while (ReadingClimInfo.getline(clim[numb]->date, 20))
		{
			ReadingClimInfo >> clim[numb]->atmosphPres;
			ReadingClimInfo >> clim[numb]->temp;
			ReadingClimInfo >> typeNum;
			clim[numb]->_type = define_type(typeNum);

			ReadingClimInfo >> clim[numb]->_wind.num;
			if (clim[numb]->_wind.num == 1)
				clim[numb]->_wind.orient = 'С';
			else if (clim[numb]->_wind.num == 2)
				clim[numb]->_wind.orient = 'Ю';
			else if (clim[numb]->_wind.num == 3)
				clim[numb]->_wind.orient = 'З';
			else if (clim[numb]->_wind.num == 4)
				clim[numb]->_wind.orient = 'В';
			else
				clim[numb]->_wind.orient = '-';
			getline(ReadingClimInfo, skip);
			numb++;
		}

		cout << "Данные считаны из файла." << endl;
		cin.ignore();
		ReadingClimInfo.close();
	}
}

Climate* AddData()
{
	int typeNum;
	bool check = true;
	Climate* newClim = new Climate;


	while (check)
	{
		cout << "Введите дату (формат: дд.мм.гггг): ";
		cin >> newClim->date;

		if ((newClim->date[2] == '.') && (newClim->date[5] == '.') && (1000*((int)newClim->date[6]-'0') + 100*((int)newClim->date[7]-'0') + 10*((int)newClim->date[8]-'0') + (int)newClim->date[9]-'0') <= 2020 && (1000*((int)newClim->date[6]-'0') + 100*((int)newClim->date[7]-'0') + 10*((int)newClim->date[8]-'0') + (int)newClim->date[9]-'0') > 1670 && (10*((int)newClim->date[3]-'0') + (int)newClim->date[4]-'0') > 0 && (10*((int)newClim->date[3]-'0') + (int)newClim->date[4]-'0') <= 12) // point, year, month
		{
			// checking for a leap year (February)
			if ((1000*((int)newClim->date[6]-'0') + 100*((int)newClim->date[7]-'0') + 10*((int)newClim->date[8]-'0') + (int)newClim->date[9]-'0') % 4 == 0 && (1000*((int)newClim->date[6]-'0') + 100*((int)newClim->date[7]-'0') + 10*((int)newClim->date[8]-'0') + (int)newClim->date[9]-'0') % 100 != 0 && (10*((int)newClim->date[3]-'0')+ (int)newClim->date[4]-'0')== 2 && (10*((int)newClim->date[0]-'0') + (int)newClim->date[1]-'0') > 0 && (10*((int)newClim->date[0]-'0') + (int)newClim->date[1]-'0') <= 29)
				check = false;

			// checking for months with 31 days
			else if (((10*((int)newClim->date[3]-'0') + (int)newClim->date[4]-'0') == 1 || (10*((int)newClim->date[3]-'0') + (int)newClim->date[4]-'0') == 3 || (10*((int)newClim->date[3]-'0') + (int)newClim->date[4]-'0') == 5 || (10*((int)newClim->date[3]-'0') + (int)newClim->date[4]-'0') == 7 || (10*((int)newClim->date[3]-'0') + (int)newClim->date[4]-'0') == 8 || (10*((int)newClim->date[3]-'0') + (int)newClim->date[4]-'0') == 10 || (10*((int)newClim->date[3]-'0') + (int)newClim->date[4]-'0') == 12) && (10* ((int)newClim->date[0]-'0') + (int)newClim->date[1]-'0') > 0 && (10* ((int)newClim->date[0]-'0') + (int)newClim->date[1]-'0') <= 31) 
				check = false;

			// checking for months with 30 days
			else if (((10*((int)newClim->date[3]-'0') + (int)newClim->date[4]-'0') == 4 || (10* ((int)newClim->date[3]-'0') + (int)newClim->date[4]-'0') == 6 || (10* ((int)newClim->date[3]-'0') + (int)newClim->date[4]-'0') == 9 || (10* ((int)newClim->date[3]-'0') + (int)newClim->date[4]-'0') == 11) && (10*((int)newClim->date[0]-'0') + (int)newClim->date[1]-'0') > 0 && (10*((int)newClim->date[0]-'0') + (int)newClim->date[1]-'0') <= 30) 
				check = false;

			else
				cout << "Неправильно введена дата!" << endl;
		}
		else
			cout << "Неправильно введена дата!" << endl;
	}
	
	cout << "Введите атмосферное давление (мм.рт.ст.): ";
	while (!(cin >> newClim->atmosphPres) || (cin.peek() != '\n') || (newClim->atmosphPres < 640 || newClim->atmosphPres > 815))
	{
		cin.clear();
		while (cin.get() != '\n');
		cout << "Неправильно введено значение атмосферного давления!" << endl;
	}
	
	cout << "Введите температуру (°C): ";
	while (!(cin >> newClim->temp) || (cin.peek() != '\n') || (newClim->temp < -100 || newClim->temp > 100))
	{
		cin.clear();
		while (cin.get() != '\n');
		cout << "Неправильно введено значение температуры!" << endl;
	}
	
	cout << "Введите тип климата (1 - полярный, 2 - умеренный, 3 - тропический, 4 - экваториальный): ";
	while (!(cin >> typeNum) || (cin.peek() != '\n') || (typeNum != 1 && typeNum != 2 && typeNum != 3 && typeNum != 4))
	{
		cin.clear();
		while (cin.get() != '\n');
		cout << "Неправильно введен тип климата!" << endl;
	}
	newClim->_type = define_type(typeNum);

	cout << "Введите направление ветра (1-С, 2-Ю, 3-З, 4-В): ";
	while (!(cin >> newClim->_wind.num) || (cin.peek() != '\n') || (newClim->_wind.num != 1 && newClim->_wind.num != 2 && newClim->_wind.num != 3 && newClim->_wind.num != 4))
	{
		cin.clear();
		while (cin.get() != '\n');
		cout << "Неправильно введено направление ветра!" << endl;
	}
	if (newClim->_wind.num == 1)
		newClim->_wind.orient = 'С';
	else if (newClim->_wind.num == 2)
		newClim->_wind.orient = 'Ю';
	else if (newClim->_wind.num == 3)
		newClim->_wind.orient = 'З';
	else if (newClim->_wind.num == 4)
		newClim->_wind.orient = 'В';
	else
		newClim->_wind.orient = '-';
	cout <<"Данные успешно добавлены!" << endl;
	return newClim;
}

void PrintData(Climate** clim, int& numb)
{
	if (numb == 0)
	{
		cout << "Для работы с данными необходимо считать информацию из файла!" << endl << "Данных не найдено!" << endl;
		return;
	}
	else if (numb == -1)
	{
		cout << "Файл пустой!" << endl;
		return;
	}

	cout << " __________________________________________________________________________________________________________________________________" << endl;
	cout << "|" << " Дата                " << "|" << " Атмосферное давление     " << "|" << "           Температура         " << "|" << "           Тип климата       " << "|" << " Направление ветра " << "|" << endl;
	cout << "|_____________________|__________________________|_______________________________|_____________________________|___________________|" << endl;

	for (int i = 0; i < numb; i++)
	{
		cout << "|" << setw(9) << clim[i]->date << setw(12) << "|" << setw(13) << clim[i]->atmosphPres << setw(14) << "|" << setw(16) << clim[i]->temp << setw(16) << "|" << setw(20) << convert_TypeToStr(clim[i]->_type) << setw(10) << "|" << setw(10) << clim[i]->_wind.orient << setw(10) << "|" << endl;
		cout << "|_____________________|__________________________|_______________________________|_____________________________|___________________|" << endl;
	}
}

void WriteTXT(Climate** clim, int& numb, string file)
{
	ofstream WriteClimInfo;
	WriteClimInfo.open(file);
	if (!WriteClimInfo.is_open())
	{
		cout << "Ошибка при открытии файла!" << endl;
	}
	else
	{
		cout << "Файл открыт!" << endl;
		for (int i = 0; i < numb; i++)
		{
			WriteClimInfo << clim[i]->date << endl;
			WriteClimInfo << clim[i]->atmosphPres << endl;
			WriteClimInfo << clim[i]->temp << endl;
			WriteClimInfo << clim[i]->_type << endl;

			if (clim[i]->_wind.orient == 'С')
				clim[i]->_wind.num = 1;
			else if (clim[i]->_wind.orient == 'Ю')
				clim[i]->_wind.num = 2;
			else if (clim[i]->_wind.orient == 'З')
				clim[i]->_wind.num = 3;
			else if (clim[i]->_wind.orient == 'В')
				clim[i]->_wind.num = 4;
			else 
				clim[i]->_wind.num = -1;
			WriteClimInfo << clim[i]->_wind.num << endl;
		}
		cout << "Данные успешно сохранены!" << endl;
		cin.ignore();
		WriteClimInfo.close();
	}
	return;
}

void ChangeFieldItem(Climate** clim, int& numb)
{
	if (numb == 0)
	{
		cout << "Для работы с данными необходимо считать информацию из файла!" << endl;
		return;
	}
	else if (numb == -1)
	{
		cout << "Файл пустой!" << endl;
		return;
	}
	int number, numField;
	bool check = true;
		cout << "Введите номер элемента, который хотите изменить (от 1 до " << numb << " ): ";
		while (!(cin >> number) || (cin.peek() != '\n') || (number <1 || number >numb))
		{
			cin.clear();
			while (cin.get() != '\n');
			cout << "Ошибка ввода! Повторите пожалуйста...\n";

		}
			number--;
			cout << "Выберите поле, которое хотите изменить: " << endl
				<< "1) Дата" << endl
				<< "2) Атмосферное давление" << endl
				<< "3) Температура" << endl
				<< "4) Тип климата" << endl
				<< "5) Направление ветра" << endl;
			int numField = 0;
			while (!(cin >> numField) || (cin.peek() != '\n') || (numField < 1 || numField >5))
			{
				cin.clear();
				while (cin.get() != '\n');
				cout << "Ошибка ввода! Повторите пожалуйста...\n";

			}

			switch (numField)
			{
			case 1:
				while (check)
				{
					cout << "Введите дату (формат: дд.мм.гггг): ";
					cin >> clim[number]->date;

					if ((clim[number]->date[2] == '.') && (clim[number]->date[5] == '.') && (1000 * ((int)clim[number]->date[6] - '0') + 100 * ((int)clim[number]->date[7] - '0') + 10 * ((int)clim[number]->date[8] - '0') + (int)clim[number]->date[9] - '0') <= 2020 && (1000 * ((int)clim[number]->date[6] - '0') + 100 * ((int)clim[number]->date[7] - '0') + 10 * ((int)clim[number]->date[8] - '0') + (int)clim[number]->date[9] - '0') > 1670 && (10 * ((int)clim[number]->date[3] - '0') + (int)clim[number]->date[4] - '0') > 0 && (10 * ((int)clim[number]->date[3] - '0') + (int)clim[number]->date[4] - '0') <= 12) // point, year, month
					{
						// checking for a leap year (February)
						if ((1000 * ((int)clim[number]->date[6] - '0') + 100 * ((int)clim[number]->date[7] - '0') + 10 * ((int)clim[number]->date[8] - '0') + (int)clim[number]->date[9] - '0') % 4 == 0 && (1000 * ((int)clim[number]->date[6] - '0') + 100 * ((int)clim[number]->date[7] - '0') + 10 * ((int)clim[number]->date[8] - '0') + (int)clim[number]->date[9] - '0') % 100 != 0 && (10 * ((int)clim[number]->date[3] - '0') + (int)clim[number]->date[4] - '0') == 2 && (10 * ((int)clim[number]->date[0] - '0') + (int)clim[number]->date[1] - '0') > 0 && (10 * ((int)clim[number]->date[0] - '0') + (int)clim[number]->date[1] - '0') <= 29)
							check = false;

						// checking for months with 31 days
						else if (((10 * ((int)clim[number]->date[3] - '0') + (int)clim[number]->date[4] - '0') == 1 || (10 * ((int)clim[number]->date[3] - '0') + (int)clim[number]->date[4] - '0') == 3 || (10 * ((int)clim[number]->date[3] - '0') + (int)clim[number]->date[4] - '0') == 5 || (10 * ((int)clim[number]->date[3] - '0') + (int)clim[number]->date[4] - '0') == 7 || (10 * ((int)clim[number]->date[3] - '0') + (int)clim[number]->date[4] - '0') == 8 || (10 * ((int)clim[number]->date[3] - '0') + (int)clim[number]->date[4] - '0') == 10 || (10 * ((int)clim[number]->date[3] - '0') + (int)clim[number]->date[4] - '0') == 12) && (10 * ((int)clim[number]->date[0] - '0') + (int)clim[number]->date[1] - '0') > 0 && (10 * ((int)clim[number]->date[0] - '0') + (int)clim[number]->date[1] - '0') <= 31)
							check = false;

						// checking for months with 30 days
						else if (((10 * ((int)clim[number]->date[3] - '0') + (int)clim[number]->date[4] - '0') == 4 || (10 * ((int)clim[number]->date[3] - '0') + (int)clim[number]->date[4] - '0') == 6 || (10 * ((int)clim[number]->date[3] - '0') + (int)clim[number]->date[4] - '0') == 9 || (10 * ((int)clim[number]->date[3] - '0') + (int)clim[number]->date[4] - '0') == 11) && (10 * ((int)clim[number]->date[0] - '0') + (int)clim[number]->date[1] - '0') > 0 && (10 * ((int)clim[number]->date[0] - '0') + (int)clim[number]->date[1] - '0') <= 30)
							check = false;

						else
							cout << "Неправильно введена дата!" << endl;
					}
					else
						cout << "Неправильно введена дата!" << endl;
				}
				break;
			case 2:
				cout << "Введите атмосферное давление (мм.рт.ст.): ";
				while (!(cin >> clim[number]->atmosphPres) || (cin.peek() != '\n') || (clim[number]->atmosphPres < 640 || clim[number]->atmosphPres > 815))
				{
					cin.clear();
					while (cin.get() != '\n');
					cout << "Неправильно введено значение атмосферного давления!" << endl;
				}
				break;
			case 3:
				cout << "Введите температуру (°C): ";
				while (!(cin >> clim[number]->temp) || (cin.peek() != '\n') || (clim[number]->temp < -100 || clim[number]->temp > 100))
				{
					cin.clear();
					while (cin.get() != '\n');
					cout << "Неправильно введено значение температуры!" << endl;
				}
				break;
			case 4:
				int typeNum;
				cout << "Введите тип климата (1 - полярный, 2 - умеренный, 3 - тропический, 4 - экваториальный): ";
				while (!(cin >> typeNum) || (cin.peek() != '\n') || (typeNum != 1 && typeNum != 2 && typeNum != 3 && typeNum != 4))
				{
					cin.clear();
					while (cin.get() != '\n');
					cout << "Неправильно введен тип климата!" << endl;
				}
				clim[number]->_type = define_type(typeNum);
				break;
			case 5:
				cout << "Введите направление ветра (1-С, 2-Ю, 3-З, 4-В): ";
				while (!(cin >> clim[number]->_wind.num) || (cin.peek() != '\n') || (clim[number]->_wind.num != 1 && clim[number]->_wind.num != 2 && clim[number]->_wind.num != 3 && clim[number]->_wind.num != 4))
				{
					cin.clear();
					while (cin.get() != '\n');
					cout << "Неправильно введено направление ветра!" << endl;
				}
				if (clim[number]->_wind.num == 1)
					clim[number]->_wind.orient = 'С';
				else if (clim[number]->_wind.num == 2)
					clim[number]->_wind.orient = 'Ю';
				else if (clim[number]->_wind.num == 3)
					clim[number]->_wind.orient = 'З';
				else if (clim[number]->_wind.num == 4)
					clim[number]->_wind.orient = 'В';
				else
					clim[number]->_wind.orient = '-';
				break;
			default:
				cout << "Неправильно введен номер поля!" << endl;
				break;
			}
}

void DelItem(Climate**& clim, int& numb)
{
	if (numb == 0)
	{
		cout << "Для работы с данными необходимо считать информацию из файла!" << endl;
		return;
	}
	else if (numb == -1)
	{
		cout << "Файл пустой!" << endl;
		return;
	}
	int m = 0;
		cout << "Введите номер элемента, который хотите удалить (от 1 до " << numb << "):";
		while (!(cin >> m) || (cin.peek() != '\n') || (m <1 || m >numb))
		{
			cin.clear();
			while (cin.get() != '\n');
			cout << "Ошибка ввода! Повторите пожалуйста...\n";

		}
		m--;
			Climate** new_clim = new Climate * [numb - 1];
			int q = 0;
			for (int i = 0; i < numb; i++)
			{
				if (i != m)
				{
					new_clim[q] = clim[i];
					++q;
				}
			}
			cin.ignore();
			system("cls");
			clim = new_clim;
			numb = q;
			cout << "Данные удалены!" << endl;
}

void Delete(Climate**& clim, int& numb, int j)
{
	for (int i = j; i < numb; i++)
	{
		clim[i] = clim[i + 1];
	}
	numb--;
}

void DelCondition(Climate** clim, int& numb)
{
	if (numb == 0)
	{
		cout << "Для работы с данными необходимо считать информацию из файла!" << endl;
		return;
	}
	else if (numb == -1)
	{
		cout << "Файл пустой!" << endl;
		return;
	}
	int t, cond, n=numb;
	bool check = true;
		cout << "Введите значение температуры: ";
		while (!(cin >> t) || (cin.peek() != '\n') || (t < -100 || t > 100))
		{
			cin.clear();
			while (cin.get() != '\n');
			cout << "Неправильно введено значение температуры!" << endl;
		}

		cout << "Удалить поля, которые больше или меньше заданного значения? (1 - '>', 2 - '<'): ";
		while (!(cin >> cond) || (cin.peek() != '\n') || (cond != 1 && cond != 2))
		{
			cin.clear();
			while (cin.get() != '\n');
			cout << "Неправильно введено условие!" << endl;
		}
		int deleted = 0;
		switch (cond)
		{
		case 1:
			for (int j = 0; j < n; j++)
			{
				if (clim[j - deleted]->temp > t)
				{
					Delete(clim, numb, j - deleted);
					deleted++;
				}
			}
			cout << "Данные по выбранному условию удалены!" << endl;
			break;
		case 2:
			for (int j = 0; j < n; j++)
			{
				if (clim[j - deleted]->temp < t)
				{
					Delete(clim, numb, j - deleted);
					deleted++;
				}
			}
			cout << "Данные по выбранному условию удалены!" << endl;
			break;
		default:
			break;
		}
}

void ChangeItem(Climate** clim, int& numb)
{
	if (numb == 0)
	{
		cout << "Для работы с данными необходимо считать информацию из файла!" << endl;
		return;
	}
	else if (numb == -1)
	{
		cout << "Файл пустой!" << endl;
		return;
	}
	int number, typeNum;
	bool check = true;
	cout << "Введите номер элемента, который хотите изменить (от 1 до " << numb << " ): ";
	while (!(cin >> number) || (cin.peek() != '\n') || (number <1 || number >numb))
	{
		cin.clear();
		while (cin.get() != '\n');
		cout << "Ошибка ввода! Повторите пожалуйста...\n";

	}
	number--;
		while (check)
		{
			cout << "Введите дату (формат: дд.мм.гггг): ";
			cin >> clim[number]->date;

			if ((clim[number]->date[2] == '.') && (clim[number]->date[5] == '.') && (1000 * ((int)clim[number]->date[6] - '0') + 100 * ((int)clim[number]->date[7] - '0') + 10 * ((int)clim[number]->date[8] - '0') + (int)clim[number]->date[9] - '0') <= 2020 && (1000 * ((int)clim[number]->date[6] - '0') + 100 * ((int)clim[number]->date[7] - '0') + 10 * ((int)clim[number]->date[8] - '0') + (int)clim[number]->date[9] - '0') > 1670 && (10 * ((int)clim[number]->date[3] - '0') + (int)clim[number]->date[4] - '0') > 0 && (10 * ((int)clim[number]->date[3] - '0') + (int)clim[number]->date[4] - '0') <= 12) // point, year, month
			{
				// checking for a leap year (February)
				if ((1000 * ((int)clim[number]->date[6] - '0') + 100 * ((int)clim[number]->date[7] - '0') + 10 * ((int)clim[number]->date[8] - '0') + (int)clim[number]->date[9] - '0') % 4 == 0 && (1000 * ((int)clim[number]->date[6] - '0') + 100 * ((int)clim[number]->date[7] - '0') + 10 * ((int)clim[number]->date[8] - '0') + (int)clim[number]->date[9] - '0') % 100 != 0 && (10 * ((int)clim[number]->date[3] - '0') + (int)clim[number]->date[4] - '0') == 2 && (10 * ((int)clim[number]->date[0] - '0') + (int)clim[number]->date[1] - '0') > 0 && (10 * ((int)clim[number]->date[0] - '0') + (int)clim[number]->date[1] - '0') <= 29)
					check = false;

				// checking for months with 31 days
				else if (((10 * ((int)clim[number]->date[3] - '0') + (int)clim[number]->date[4] - '0') == 1 || (10 * ((int)clim[number]->date[3] - '0') + (int)clim[number]->date[4] - '0') == 3 || (10 * ((int)clim[number]->date[3] - '0') + (int)clim[number]->date[4] - '0') == 5 || (10 * ((int)clim[number]->date[3] - '0') + (int)clim[number]->date[4] - '0') == 7 || (10 * ((int)clim[number]->date[3] - '0') + (int)clim[number]->date[4] - '0') == 8 || (10 * ((int)clim[number]->date[3] - '0') + (int)clim[number]->date[4] - '0') == 10 || (10 * ((int)clim[number]->date[3] - '0') + (int)clim[number]->date[4] - '0') == 12) && (10 * ((int)clim[number]->date[0] - '0') + (int)clim[number]->date[1] - '0') > 0 && (10 * ((int)clim[number]->date[0] - '0') + (int)clim[number]->date[1] - '0') <= 31)
					check = false;

				// checking for months with 30 days
				else if (((10 * ((int)clim[number]->date[3] - '0') + (int)clim[number]->date[4] - '0') == 4 || (10 * ((int)clim[number]->date[3] - '0') + (int)clim[number]->date[4] - '0') == 6 || (10 * ((int)clim[number]->date[3] - '0') + (int)clim[number]->date[4] - '0') == 9 || (10 * ((int)clim[number]->date[3] - '0') + (int)clim[number]->date[4] - '0') == 11) && (10 * ((int)clim[number]->date[0] - '0') + (int)clim[number]->date[1] - '0') > 0 && (10 * ((int)clim[number]->date[0] - '0') + (int)clim[number]->date[1] - '0') <= 30)
					check = false;

				else
					cout << "Неправильно введена дата!" << endl;
			}
			else
				cout << "Неправильно введена дата!" << endl;
		}
		
		cout << "Введите атмосферное давление (мм.рт.ст.): ";
		while (!(cin >> clim[number]->atmosphPres) || (cin.peek() != '\n') || (clim[number]->atmosphPres < 640 || clim[number]->atmosphPres > 815))
		{
			cin.clear();
			while (cin.get() != '\n');
			cout << "Неправильно введено значение атмосферного давления!" << endl;
		}

		cout << "Введите температуру (°C): ";
		while (!(cin >> clim[number]->temp) || (cin.peek() != '\n') || (clim[number]->temp < -100 || clim[number]->temp > 100))
		{
			cin.clear();
			while (cin.get() != '\n');
			cout << "Неправильно введено значение температуры!" << endl;
		}

		cout << "Введите тип климата (1 - полярный, 2 - умеренный, 3 - тропический, 4 - экваториальный): ";
		while (!(cin >> typeNum) || (cin.peek() != '\n') || (typeNum != 1 && typeNum != 2 && typeNum != 3 && typeNum != 4))
		{
			cin.clear();
			while (cin.get() != '\n');
			cout << "Неправильно введен тип климата!" << endl;
		}
		clim[number]->_type = define_type(typeNum);

		cout << "Введите направление ветра (1-С, 2-Ю, 3-З, 4-В): ";
		while (!(cin >> clim[number]->_wind.num) || (cin.peek() != '\n') || (clim[number]->_wind.num != 1 && clim[number]->_wind.num != 2 && clim[number]->_wind.num != 3 && clim[number]->_wind.num != 4))
		{
			cin.clear();
			while (cin.get() != '\n');
			cout << "Неправильно введено направление ветра!" << endl;
		}
		if (clim[number]->_wind.num == 1)
			clim[number]->_wind.orient = 'С';
		else if (clim[number]->_wind.num == 2)
			clim[number]->_wind.orient = 'Ю';
		else if (clim[number]->_wind.num == 3)
			clim[number]->_wind.orient = 'З';
		else if (clim[number]->_wind.num == 4)
			clim[number]->_wind.orient = 'В';
		else
			clim[number]->_wind.orient = '-';

		cout << "Элемент успешно изменен!" << endl;
}

void DelItemsStartSelected(Climate**& clim, int& numb)
{
	if (numb == 0)
	{
		cout << "Для работы с данными необходимо считать информацию из файла!" << endl;
		return;
	}
	else if (numb == -1)
	{
		cout << "Файл пустой!" << endl;
		return;
	}
	int m = 0;
	cout << "Введите номер элемента, с которого нужно начать удаление (от 1 до " << numb << "):";
	while (!(cin >> m) || (cin.peek() != '\n') || (m <1 || m >numb))
	{
		cin.clear();
		while (cin.get() != '\n');
		cout << "Ошибка ввода! Повторите пожалуйста...\n";

	}
	m--;
		Climate** new_clim = new Climate * [numb - 1];
		int q = 0;
		for (int i = 0; i < m; i++)
		{
				new_clim[q] = clim[i];
				++q;
		}
		clim = new_clim;
		numb = q;
		cout << "Данные удалены!" << endl;
}

Type define_type(int typeNum)
{
	switch (typeNum)
	{
	case polar:
		return polar;
	case moderate:
		return moderate;
	case tropical:
		return tropical;
	case equatorial:
		return equatorial;
	default:
		return NotFound;
	}
}

string convert_TypeToStr(Type type)
{
	switch (type)
	{
	case polar:
		return "полярный";
		break;
	case moderate:
		return "умеренный";
		break;
	case tropical:
		return "тропический";
		break;
	case equatorial:
		return "экваториальный";
		break;
	case NotFound:
		return "Не найдено";
		break;
	}
}