#include "orderFile.h"

//���캯��
OrderFile::OrderFile()
{
	std::ifstream ifs;
	ifs.open(ORDER_FILE, std::ios::in);

	std::string date;  //����
	std::string interval;  //ʱ���
	std::string stuid;  //ѧ�����
	std::string stuname;  //ѧ������
	std::string roomid;  //�������
	std::string status;  //ԤԼ״̬

	//��ʼ����¼����
	this->m_size = 0;

	while (ifs>>date&& ifs >> interval && ifs >> stuid && ifs >> stuname && ifs >> roomid && ifs >> status)
	{
		/*std::cout << date << std::endl;
		std::cout << interval << std::endl;
		std::cout << stuid << std::endl;
		std::cout << stuname << std::endl;
		std::cout << roomid << std::endl;
		std::cout << status << std::endl;
		std::cout << std::endl;*/
		std::string key;
		std::string value;
		std::map<std::string,std::string> m;

		int pos = date.find(":");  
		//��ȡ����
		if (pos != -1)
		{
			key = date.substr(0, pos);
			value = date.substr(pos + 1, date.size() - pos - 1);
			m.insert(make_pair(key, value));
		}
		//��ȡʱ���
		pos = interval.find(":");
		if (pos != -1)
		{
			key = interval.substr(0, pos);
			value = interval.substr(pos + 1, interval.size() - pos - 1);
			m.insert(make_pair(key, value));
		}
		//��ȡѧ��
		pos = stuid.find(":");
		if (pos != -1)
		{
			key = stuid.substr(0, pos);
			value = stuid.substr(pos + 1, stuid.size() - pos - 1);
			m.insert(make_pair(key, value));
		}
		//��ȡѧ������
		pos = stuname.find(":");
		if (pos != -1)
		{
			key = stuname.substr(0, pos);
			value = stuname.substr(pos + 1, stuname.size() - pos - 1);
			m.insert(make_pair(key, value));
		}
		//��ȡ������
		pos = roomid.find(":");
		if (pos != -1)
		{
			key = roomid.substr(0, pos);
			value = roomid.substr(pos + 1, roomid.size() - pos - 1);
			m.insert(make_pair(key, value));
		}
		//��ȡԤԼ״̬
		pos = status.find(":");
		if (pos != -1)
		{
			key = status.substr(0, pos);
			value = status.substr(pos + 1, status.size() - pos - 1);
			m.insert(make_pair(key, value));
		}

		/*std::cout << "key = " << key << std::endl;
		std::cout << "value = " << value << std::endl;*/
		//��С�� map ���� ������ map ������
		this->m_orderData.insert(make_pair(this->m_size, m));
		this->m_size++;
	}
	ifs.close();

	////������� map ����
	//for (std::map<int, std::map<std::string, std::string>>::iterator it = m_orderData.begin();it != m_orderData.end();it++)
	//{
	//	std::cout << "����Ϊ��" << it->first << " value = " << std::endl;
	//	for (std::map<std::string, std::string>::iterator mit = (*it).second.begin();mit != (*it).second.end();mit++)
	//	{
	//		std::cout << "key = " << mit->first << " value = " << mit->second << std::endl;
	//	}
	//	std::cout << std::endl;
	//}
}

//����ԤԼ��¼
void OrderFile::updateOrder()
{
	if (this->m_size == 0)
	{ 
		return;  //0��ԤԼ��¼  ֱ��return
	}
	std::ofstream ofs(ORDER_FILE, std::ios::trunc);
	for (int i = 0;i < this->m_size;i++)
	{
		ofs << "date:" << this->m_orderData[i]["date"] << " ";
		ofs << "interval:" << this->m_orderData[i]["interval"] << " ";
		ofs << "stuid:" << this->m_orderData[i]["stuid"] << " ";
		ofs << "stuname:" << this->m_orderData[i]["stuname"] << " ";
		ofs << "roomid:" << this->m_orderData[i]["roomid"] << " ";
		ofs << "status:" << this->m_orderData[i]["status"] << std::endl;
	}
	ofs.close();
}