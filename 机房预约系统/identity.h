#pragma once
#include<iostream>

//身份抽象基类
class Identity
{
public:
	//操作菜单  纯虚函数
	virtual void openMenu() = 0;

	//用户名
	std::string m_name;
	//密码
	std::string m_pwd;
};