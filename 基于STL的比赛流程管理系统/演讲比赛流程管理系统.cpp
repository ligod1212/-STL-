#include<iostream>
using namespace std;
#include"speechManager.h"
#include"speaker.h"
#include<ctime>

int main() {
	
	SpeechManager sm;

	int choice = 0;

	//���������
	srand((unsigned int)time(NULL));

	////����ѡ�ִ���
	//for (map<int,Speaker> ::iterator it=sm.m_Speaker.begin(); it !=sm.m_Speaker.end(); it++)
	//{
	//	cout << "ѡ�ֱ��" << it->first << "  ����" << it->second.m_Name << "  ����" << it->second.m_Score[1] << endl;
	//}

	while (true)
	{

		sm.show_Menu();

		cout << "��ѡ���ܲ˵�" << endl;
		cin >> choice;

		switch (choice)
		{
		case 1://��ʼ����
			sm.startSpeech();
			break;
		case 2://�鿴��¼
			sm.showRecord();
			break;
		case 3:sm.clearRecord();//ɾ����¼
			break;
		case 0: sm.exitSystem();//�˳�ϵͳ
			break;
		default:
			system("cls");
			cout << "û������ѡ���ѡ��,������ѡ��" << endl;
			break;
		}
	}
	

	system("pause");

	return 0;
}