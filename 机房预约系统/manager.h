#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<algorithm>
#include "identity.h"
#include "globafile.h"
#include "student.h"
#include "teacher.h"
#include "computerRoom.h"

class Manager :public Identity
{
public:
	//Ĭ�Ϲ���
	Manager();

	//�вι���
	Manager(std::string name, std::string pwd);

	//�˵�����
	virtual void openMenu();

	//����˺�
	void addPerson();

	//�鿴�˺�
	void showPerson();

	//�鿴������Ϣ
	void showComputer();

	//���ԤԼ��¼
	void cleanFile();

	//����ظ�
	bool checkRepeat(int id, char type);

	//��ʼ������
	void initVector();

	//ѧ������
	std::vector<Student> vStu;

	//��ʦ����
	std::vector<Teacher> vTea;

	//������Ϣ����
	std::vector<ComputerRoom> vCom;
};