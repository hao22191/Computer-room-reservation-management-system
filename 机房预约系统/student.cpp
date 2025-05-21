#include "student.h"

//Ĭ�Ϲ���
Student::Student()
{

}

//�вι���
Student::Student(int id, std::string name, std::string pwd)
{
	//��ʼ������
	this->m_id = id;
	this->m_name = name;
	this->m_pwd = pwd;

	//��ʼ��������Ϣ
	std::ifstream ifs;
	ifs.open(COMPUTER_FILE, std::ios::in);

	ComputerRoom com;
	while (ifs >> com.m_Comid && ifs >> com.m_Maxnum)
	{
		//����ȡ������Ϣ��ŵ�������
		vCom.push_back(com);
	}
	ifs.close();
}

//�˵�����
void Student::openMenu()
{
	std::cout << "��ӭѧ��" << this->m_name << "��¼��" << std::endl << std::endl;
	std::cout << "\t\t ------------------------------\n";
	std::cout << "\t\t|                              |\n";
	std::cout << "\t\t|         1.����ԤԼ           |\n";
	std::cout << "\t\t|                              |\n";
	std::cout << "\t\t|         2.�鿴�ҵ�ԤԼ       |\n";
	std::cout << "\t\t|                              |\n";
	std::cout << "\t\t|         3.�鿴����ԤԼ       |\n";
	std::cout << "\t\t|                              |\n";
	std::cout << "\t\t|         4.ȡ��ԤԼ           |\n";
	std::cout << "\t\t|                              |\n";
	std::cout << "\t\t|         0.ע����¼           |\n";
	std::cout << "\t\t|                              |\n";
	std::cout << "\t\t ------------------------------\n";
	std::cout << "����������ѡ��";
}

//����ԤԼ
void Student::applyOrder()
{
	std::cout << "�������ŵ�ʱ��Ϊ��һ�����壡" << std::endl;
	std::cout << "����������ԤԼ��ʱ��" << std::endl;
	std::cout << "1.��һ" << std::endl;
	std::cout << "2.�ܶ�" << std::endl;
	std::cout << "3.����" << std::endl;
	std::cout << "4.����" << std::endl;
	std::cout << "5.����" << std::endl;

	char date;  //����
	char interval;  //ʱ���
	char roomid;  //������
	while (true)
	{
		std::cin >> date;
		if (date >= '1' && date <= '5')
		{
			break;
		}
		else
		{
			std::cout << "������������������!" << std::endl;
		}
	}

	std::cout << "�����������ʱ��Σ�" << std::endl;
	std::cout << "1.����" << std::endl;
	std::cout << "2.����" << std::endl;
	while (true)
	{
		std::cin >> interval;
		if (interval >= '1' && interval <= '2')
		{
			break;
		}
		else
		{
			std::cout << "������������������!" << std::endl;
		}
	}

	std::cout << "��ѡ�������" << std::endl;
	for (int i = 0;i < vCom.size();i++)
	{
		std::cout << vCom[i].m_Comid <<"�Ż���������Ϊ��"<<vCom[i].m_Maxnum << std::endl;
	}
	while (true)
	{
		std::cin >> roomid;
		if (roomid >= '1' && roomid <= '3')
		{
			break;
		}
		else
		{
			std::cout << "������������������!" << std::endl;
		}
	}
	std::cout << "ԤԼ�ɹ�������У�" << std::endl;

	std::ofstream ofs;
	ofs.open(ORDER_FILE, std::ios::app);
	ofs << "date:" << date << " ";
	ofs << "interval:" << interval << " ";
	ofs << "stuid:" << this->m_id << " ";
	ofs << "stuname:" << this->m_name << " ";
	ofs << "roomid:" << roomid << " ";
	ofs << "status:" << 1 << std::endl;

	ofs.close();

	system("pause");
	system("cls");
}

//�鿴����ԤԼ
void Student::showMyOrder()
{
	OrderFile of;
	if (of.m_size == 0)
	{
		std::cout << "��ԤԼ��¼��" << std::endl;
		system("pause");
		system("cls");
		return;
	}
	for (int i = 0;i < of.m_size;i++)
	{
		//string ת int
		//string ���� .c_str() ת const char*
		//���� atoi (const char*) ת int
		if (this->m_id == atoi(of.m_orderData[i]["stuid"].c_str()))  //�ҵ��������ԤԼ
		{
			std::cout << "ԤԼ���ڣ���" << of.m_orderData[i]["date"] << " ";
			std::cout << "ʱ��Σ�" << (of.m_orderData[i]["interval"] == "1" ? "����":"����") << " ";
			std::cout << "�����ţ�" << of.m_orderData[i]["roomid"] << " ";
			std::string status = "״̬��";
			//1 ԤԼ��  2 ԤԼ�ɹ�  -1 ԤԼʧ��  0  ȡ��ԤԼ
			if (of.m_orderData[i]["status"] == "1")
			{
				status += "ԤԼ��";
			}
			if (of.m_orderData[i]["status"] == "2")
			{
				status += "ԤԼ�ɹ�";
			}
			if (of.m_orderData[i]["status"] == "0")
			{
				status += "ԤԼ��ȡ��";
			}
			if (of.m_orderData[i]["status"] == "-1")
			{
				status += "ԤԼʧ�ܣ����δͨ��";
			}
			std::cout << status << std::endl;
		}
	}
	system("pause");
	system("cls");
}

//�鿴����ԤԼ
void Student::showAllOrder()
{
	OrderFile of;
	if (of.m_size == 0)
	{
		std::cout << "��ԤԼ��¼��" << std::endl;
		system("pause");
		system("cls");
		return;
	}
	for (int i = 0;i < of.m_size;i++)
	{
		std::cout << i + 1 << "��" ;
		std::cout << "ԤԼ���ڣ���" << of.m_orderData[i]["date"] << " ";
		std::cout << "ʱ��Σ�" << (of.m_orderData[i]["interval"] == "1" ? "����" : "����") << " ";
		std::cout << "ѧ�ţ�" << of.m_orderData[i]["stuid"] << " ";
		std::cout << "������" << of.m_orderData[i]["stuname"] << " ";
		std::cout << "�����ţ�" << of.m_orderData[i]["roomid"] << " ";
		std::string status = "״̬��";
		//1 ԤԼ��  2 ԤԼ�ɹ�  -1 ԤԼʧ��  0  ȡ��ԤԼ
		if (of.m_orderData[i]["status"] == "1")
		{
			status += "ԤԼ��";
		}
		if (of.m_orderData[i]["status"] == "2")
		{
			status += "ԤԼ�ɹ�";
		}
		if (of.m_orderData[i]["status"] == "0")
		{
			status += "ԤԼ��ȡ��";
		}
		if (of.m_orderData[i]["status"] == "-1")
		{
			status += "ԤԼʧ�ܣ����δͨ��";
		}
		std::cout << status << std::endl;
			
	}
	system("pause");
	system("cls");
}

//ȡ��ԤԼ
void Student::cancleOrder()
{
	OrderFile of;
	if (of.m_size == 0)
	{
		std::cout << "��ԤԼ��¼��" << std::endl;
		system("pause");
		system("cls");
		return;
	}
	std::cout << "����л���ԤԼ�ɹ��ļ�¼����ȡ������ѡ��Ҫȡ����ԤԼ��" << std::endl;
	std::vector<int> v;  //�������������е��±���
	int index = 1;
	for (int i = 0;i < of.m_size;i++)
	{
		//���ж��Ƿ�Ϊ������
		if (atoi(of.m_orderData[i]["stuid"].c_str()) == this->m_id)
		{
			if (of.m_orderData[i]["status"] == "1" || of.m_orderData[i]["status"] == "2")
			{
				v.push_back(i);
				std::cout << index++ << "�� ";
				std::cout << "ԤԼ���ڣ���" << of.m_orderData[i]["date"] << " ";
				std::cout << "ʱ��Σ�" << (of.m_orderData[i]["interval"] == "1" ? "����" : "����") << " ";
				std::cout << "�����ţ�" << of.m_orderData[i]["roomid"] << " ";
				std::string status = "״̬��";
				//1 ԤԼ��  2 ԤԼ�ɹ�  -1 ԤԼʧ��  0  ȡ��ԤԼ
				if (of.m_orderData[i]["status"] == "1")
				{
					status += "ԤԼ��";
				}
				if (of.m_orderData[i]["status"] == "2")
				{
					status += "ԤԼ�ɹ�";
				}
				std::cout << status << std::endl;
			}
		}
	}
	std::cout << "������Ҫȡ���ļ�¼��0������" << std::endl;
	int select = 0;
	while (true)
	{
		std::cin >> select;
		if (select >= 0 && select <= v.size())
		{
			if (select == 0)
			{
				break;
			}
			else
			{
				of.m_orderData[v[select - 1]]["status"] = "0";
				of.updateOrder();
				std::cout << "��ȡ��ԤԼ��" << std::endl;
				break;
			}
		}
		std::cout << "�����������������룡" << std::endl;
	}
	system("pause");
	system("cls");
}