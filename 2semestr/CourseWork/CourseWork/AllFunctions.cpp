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
		cout << "������ ��� �������� �����!" << endl;
	}
	else
	{
		cout << "���� ������!" << endl;
		if (ReadingClimInfo.peek() == EOF)
		{
			cout << "���� ������!" << endl;
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
				clim[numb]->_wind.orient = '�';
			else if (clim[numb]->_wind.num == 2)
				clim[numb]->_wind.orient = '�';
			else if (clim[numb]->_wind.num == 3)
				clim[numb]->_wind.orient = '�';
			else if (clim[numb]->_wind.num == 4)
				clim[numb]->_wind.orient = '�';
			else
				clim[numb]->_wind.orient = '-';
			getline(ReadingClimInfo, skip);
			numb++;
		}

		cout << "������ ������� �� �����." << endl;
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
		cout << "������� ���� (������: ��.��.����): ";
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
				cout << "����������� ������� ����!" << endl;
		}
		else
			cout << "����������� ������� ����!" << endl;
	}
	
	cout << "������� ����������� �������� (��.��.��.): ";
	while (!(cin >> newClim->atmosphPres) || (cin.peek() != '\n') || (newClim->atmosphPres < 640 || newClim->atmosphPres > 815))
	{
		cin.clear();
		while (cin.get() != '\n');
		cout << "����������� ������� �������� ������������ ��������!" << endl;
	}
	
	cout << "������� ����������� (�C): ";
	while (!(cin >> newClim->temp) || (cin.peek() != '\n') || (newClim->temp < -100 || newClim->temp > 100))
	{
		cin.clear();
		while (cin.get() != '\n');
		cout << "����������� ������� �������� �����������!" << endl;
	}
	
	cout << "������� ��� ������� (1 - ��������, 2 - ���������, 3 - �����������, 4 - ��������������): ";
	while (!(cin >> typeNum) || (cin.peek() != '\n') || (typeNum != 1 && typeNum != 2 && typeNum != 3 && typeNum != 4))
	{
		cin.clear();
		while (cin.get() != '\n');
		cout << "����������� ������ ��� �������!" << endl;
	}
	newClim->_type = define_type(typeNum);

	cout << "������� ����������� ����� (1-�, 2-�, 3-�, 4-�): ";
	while (!(cin >> newClim->_wind.num) || (cin.peek() != '\n') || (newClim->_wind.num != 1 && newClim->_wind.num != 2 && newClim->_wind.num != 3 && newClim->_wind.num != 4))
	{
		cin.clear();
		while (cin.get() != '\n');
		cout << "����������� ������� ����������� �����!" << endl;
	}
	if (newClim->_wind.num == 1)
		newClim->_wind.orient = '�';
	else if (newClim->_wind.num == 2)
		newClim->_wind.orient = '�';
	else if (newClim->_wind.num == 3)
		newClim->_wind.orient = '�';
	else if (newClim->_wind.num == 4)
		newClim->_wind.orient = '�';
	else
		newClim->_wind.orient = '-';
	cout <<"������ ������� ���������!" << endl;
	return newClim;
}

void PrintData(Climate** clim, int& numb)
{
	if (numb == 0)
	{
		cout << "��� ������ � ������� ���������� ������� ���������� �� �����!" << endl << "������ �� �������!" << endl;
		return;
	}
	else if (numb == -1)
	{
		cout << "���� ������!" << endl;
		return;
	}

	cout << " __________________________________________________________________________________________________________________________________" << endl;
	cout << "|" << " ����                " << "|" << " ����������� ��������     " << "|" << "           �����������         " << "|" << "           ��� �������       " << "|" << " ����������� ����� " << "|" << endl;
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
		cout << "������ ��� �������� �����!" << endl;
	}
	else
	{
		cout << "���� ������!" << endl;
		for (int i = 0; i < numb; i++)
		{
			WriteClimInfo << clim[i]->date << endl;
			WriteClimInfo << clim[i]->atmosphPres << endl;
			WriteClimInfo << clim[i]->temp << endl;
			WriteClimInfo << clim[i]->_type << endl;

			if (clim[i]->_wind.orient == '�')
				clim[i]->_wind.num = 1;
			else if (clim[i]->_wind.orient == '�')
				clim[i]->_wind.num = 2;
			else if (clim[i]->_wind.orient == '�')
				clim[i]->_wind.num = 3;
			else if (clim[i]->_wind.orient == '�')
				clim[i]->_wind.num = 4;
			else 
				clim[i]->_wind.num = -1;
			WriteClimInfo << clim[i]->_wind.num << endl;
		}
		cout << "������ ������� ���������!" << endl;
		cin.ignore();
		WriteClimInfo.close();
	}
	return;
}

void ChangeFieldItem(Climate** clim, int& numb)
{
	if (numb == 0)
	{
		cout << "��� ������ � ������� ���������� ������� ���������� �� �����!" << endl;
		return;
	}
	else if (numb == -1)
	{
		cout << "���� ������!" << endl;
		return;
	}
	int number, numField;
	bool check = true;
		cout << "������� ����� ��������, ������� ������ �������� (�� 1 �� " << numb << " ): ";
		while (!(cin >> number) || (cin.peek() != '\n') || (number <1 || number >numb))
		{
			cin.clear();
			while (cin.get() != '\n');
			cout << "������ �����! ��������� ����������...\n";

		}
			number--;
			cout << "�������� ����, ������� ������ ��������: " << endl
				<< "1) ����" << endl
				<< "2) ����������� ��������" << endl
				<< "3) �����������" << endl
				<< "4) ��� �������" << endl
				<< "5) ����������� �����" << endl;
			int numField = 0;
			while (!(cin >> numField) || (cin.peek() != '\n') || (numField < 1 || numField >5))
			{
				cin.clear();
				while (cin.get() != '\n');
				cout << "������ �����! ��������� ����������...\n";

			}

			switch (numField)
			{
			case 1:
				while (check)
				{
					cout << "������� ���� (������: ��.��.����): ";
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
							cout << "����������� ������� ����!" << endl;
					}
					else
						cout << "����������� ������� ����!" << endl;
				}
				break;
			case 2:
				cout << "������� ����������� �������� (��.��.��.): ";
				while (!(cin >> clim[number]->atmosphPres) || (cin.peek() != '\n') || (clim[number]->atmosphPres < 640 || clim[number]->atmosphPres > 815))
				{
					cin.clear();
					while (cin.get() != '\n');
					cout << "����������� ������� �������� ������������ ��������!" << endl;
				}
				break;
			case 3:
				cout << "������� ����������� (�C): ";
				while (!(cin >> clim[number]->temp) || (cin.peek() != '\n') || (clim[number]->temp < -100 || clim[number]->temp > 100))
				{
					cin.clear();
					while (cin.get() != '\n');
					cout << "����������� ������� �������� �����������!" << endl;
				}
				break;
			case 4:
				int typeNum;
				cout << "������� ��� ������� (1 - ��������, 2 - ���������, 3 - �����������, 4 - ��������������): ";
				while (!(cin >> typeNum) || (cin.peek() != '\n') || (typeNum != 1 && typeNum != 2 && typeNum != 3 && typeNum != 4))
				{
					cin.clear();
					while (cin.get() != '\n');
					cout << "����������� ������ ��� �������!" << endl;
				}
				clim[number]->_type = define_type(typeNum);
				break;
			case 5:
				cout << "������� ����������� ����� (1-�, 2-�, 3-�, 4-�): ";
				while (!(cin >> clim[number]->_wind.num) || (cin.peek() != '\n') || (clim[number]->_wind.num != 1 && clim[number]->_wind.num != 2 && clim[number]->_wind.num != 3 && clim[number]->_wind.num != 4))
				{
					cin.clear();
					while (cin.get() != '\n');
					cout << "����������� ������� ����������� �����!" << endl;
				}
				if (clim[number]->_wind.num == 1)
					clim[number]->_wind.orient = '�';
				else if (clim[number]->_wind.num == 2)
					clim[number]->_wind.orient = '�';
				else if (clim[number]->_wind.num == 3)
					clim[number]->_wind.orient = '�';
				else if (clim[number]->_wind.num == 4)
					clim[number]->_wind.orient = '�';
				else
					clim[number]->_wind.orient = '-';
				break;
			default:
				cout << "����������� ������ ����� ����!" << endl;
				break;
			}
}

void DelItem(Climate**& clim, int& numb)
{
	if (numb == 0)
	{
		cout << "��� ������ � ������� ���������� ������� ���������� �� �����!" << endl;
		return;
	}
	else if (numb == -1)
	{
		cout << "���� ������!" << endl;
		return;
	}
	int m = 0;
		cout << "������� ����� ��������, ������� ������ ������� (�� 1 �� " << numb << "):";
		while (!(cin >> m) || (cin.peek() != '\n') || (m <1 || m >numb))
		{
			cin.clear();
			while (cin.get() != '\n');
			cout << "������ �����! ��������� ����������...\n";

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
			cout << "������ �������!" << endl;
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
		cout << "��� ������ � ������� ���������� ������� ���������� �� �����!" << endl;
		return;
	}
	else if (numb == -1)
	{
		cout << "���� ������!" << endl;
		return;
	}
	int t, cond, n=numb;
	bool check = true;
		cout << "������� �������� �����������: ";
		while (!(cin >> t) || (cin.peek() != '\n') || (t < -100 || t > 100))
		{
			cin.clear();
			while (cin.get() != '\n');
			cout << "����������� ������� �������� �����������!" << endl;
		}

		cout << "������� ����, ������� ������ ��� ������ ��������� ��������? (1 - '>', 2 - '<'): ";
		while (!(cin >> cond) || (cin.peek() != '\n') || (cond != 1 && cond != 2))
		{
			cin.clear();
			while (cin.get() != '\n');
			cout << "����������� ������� �������!" << endl;
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
			cout << "������ �� ���������� ������� �������!" << endl;
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
			cout << "������ �� ���������� ������� �������!" << endl;
			break;
		default:
			break;
		}
}

void ChangeItem(Climate** clim, int& numb)
{
	if (numb == 0)
	{
		cout << "��� ������ � ������� ���������� ������� ���������� �� �����!" << endl;
		return;
	}
	else if (numb == -1)
	{
		cout << "���� ������!" << endl;
		return;
	}
	int number, typeNum;
	bool check = true;
	cout << "������� ����� ��������, ������� ������ �������� (�� 1 �� " << numb << " ): ";
	while (!(cin >> number) || (cin.peek() != '\n') || (number <1 || number >numb))
	{
		cin.clear();
		while (cin.get() != '\n');
		cout << "������ �����! ��������� ����������...\n";

	}
	number--;
		while (check)
		{
			cout << "������� ���� (������: ��.��.����): ";
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
					cout << "����������� ������� ����!" << endl;
			}
			else
				cout << "����������� ������� ����!" << endl;
		}
		
		cout << "������� ����������� �������� (��.��.��.): ";
		while (!(cin >> clim[number]->atmosphPres) || (cin.peek() != '\n') || (clim[number]->atmosphPres < 640 || clim[number]->atmosphPres > 815))
		{
			cin.clear();
			while (cin.get() != '\n');
			cout << "����������� ������� �������� ������������ ��������!" << endl;
		}

		cout << "������� ����������� (�C): ";
		while (!(cin >> clim[number]->temp) || (cin.peek() != '\n') || (clim[number]->temp < -100 || clim[number]->temp > 100))
		{
			cin.clear();
			while (cin.get() != '\n');
			cout << "����������� ������� �������� �����������!" << endl;
		}

		cout << "������� ��� ������� (1 - ��������, 2 - ���������, 3 - �����������, 4 - ��������������): ";
		while (!(cin >> typeNum) || (cin.peek() != '\n') || (typeNum != 1 && typeNum != 2 && typeNum != 3 && typeNum != 4))
		{
			cin.clear();
			while (cin.get() != '\n');
			cout << "����������� ������ ��� �������!" << endl;
		}
		clim[number]->_type = define_type(typeNum);

		cout << "������� ����������� ����� (1-�, 2-�, 3-�, 4-�): ";
		while (!(cin >> clim[number]->_wind.num) || (cin.peek() != '\n') || (clim[number]->_wind.num != 1 && clim[number]->_wind.num != 2 && clim[number]->_wind.num != 3 && clim[number]->_wind.num != 4))
		{
			cin.clear();
			while (cin.get() != '\n');
			cout << "����������� ������� ����������� �����!" << endl;
		}
		if (clim[number]->_wind.num == 1)
			clim[number]->_wind.orient = '�';
		else if (clim[number]->_wind.num == 2)
			clim[number]->_wind.orient = '�';
		else if (clim[number]->_wind.num == 3)
			clim[number]->_wind.orient = '�';
		else if (clim[number]->_wind.num == 4)
			clim[number]->_wind.orient = '�';
		else
			clim[number]->_wind.orient = '-';

		cout << "������� ������� �������!" << endl;
}

void DelItemsStartSelected(Climate**& clim, int& numb)
{
	if (numb == 0)
	{
		cout << "��� ������ � ������� ���������� ������� ���������� �� �����!" << endl;
		return;
	}
	else if (numb == -1)
	{
		cout << "���� ������!" << endl;
		return;
	}
	int m = 0;
	cout << "������� ����� ��������, � �������� ����� ������ �������� (�� 1 �� " << numb << "):";
	while (!(cin >> m) || (cin.peek() != '\n') || (m <1 || m >numb))
	{
		cin.clear();
		while (cin.get() != '\n');
		cout << "������ �����! ��������� ����������...\n";

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
		cout << "������ �������!" << endl;
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
		return "��������";
		break;
	case moderate:
		return "���������";
		break;
	case tropical:
		return "�����������";
		break;
	case equatorial:
		return "��������������";
		break;
	case NotFound:
		return "�� �������";
		break;
	}
}