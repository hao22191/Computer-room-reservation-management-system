#pragma once
#include<iostream>

//��ݳ������
class Identity
{
public:
	//�����˵�  ���麯��
	virtual void openMenu() = 0;

	//�û���
	std::string m_name;
	//����
	std::string m_pwd;
};