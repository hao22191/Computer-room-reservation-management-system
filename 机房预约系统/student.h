#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include "identity.h"
#include "computerRoom.h"
#include "globafile.h"
#include "orderFile.h"

class Student :public Identity
{
public:
	//Ĭ�Ϲ���
	Student();

	//�вι���
	Student(int id, std::string name, std::string pwd);

	//�˵�����
	virtual void openMenu();

	//����ԤԼ
	void applyOrder();

	//�鿴����ԤԼ
	void showMyOrder();

	//�鿴����ԤԼ
	void showAllOrder();

	//ȡ��ԤԼ
	void cancleOrder();

	//ѧ��ѧ��
	int m_id;

	//��������
	std::vector<ComputerRoom> vCom;
};