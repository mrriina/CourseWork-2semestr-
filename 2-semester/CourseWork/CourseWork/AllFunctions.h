#pragma once
#include <iostream>
#include <fstream>
#include <iomanip>				   
#include <string>

using namespace std;

enum Type					// ������������
{
	polar = 1, 
	moderate, 
	tropical, 
	equatorial,
	NotFound = -1
};

union Wind					// �����������
{
	int num;
	char orient;
};

struct Climate
{
	char date[20]; // ����
	float atmosphPres; // ����������� ��������
	long int temp; // �����������
	Type _type;  // ��� ������� (������������)
	Wind _wind; // ����������� ����� (�����������)
};

void ReadingTXT(Climate** clim, int& numb, string file);
Climate* AddData();
void PrintData(Climate** clim, int& numb);
void WriteTXT(Climate** clim, int& numb, string file);
void ChangeFieldItem(Climate** clim, int& numb);
void DelItem(Climate**& clim, int& numb);
void Delete(Climate**& clim, int& numb, int j);
void DelCondition(Climate** clim, int& numb);
void ChangeItem(Climate** clim, int& numb);
void DelItemsStartSelected(Climate**& clim, int& numb);

Type define_type(int typeNum);
string convert_TypeToStr(Type type);
