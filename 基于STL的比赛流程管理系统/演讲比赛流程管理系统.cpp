#include<iostream>
using namespace std;
#include"speechManager.h"
#include"speaker.h"
#include<ctime>

int main() {
	
	SpeechManager sm;

	int choice = 0;

	//随机数种子
	srand((unsigned int)time(NULL));

	////测试选手创建
	//for (map<int,Speaker> ::iterator it=sm.m_Speaker.begin(); it !=sm.m_Speaker.end(); it++)
	//{
	//	cout << "选手编号" << it->first << "  姓名" << it->second.m_Name << "  分数" << it->second.m_Score[1] << endl;
	//}

	while (true)
	{

		sm.show_Menu();

		cout << "请选择功能菜单" << endl;
		cin >> choice;

		switch (choice)
		{
		case 1://开始比赛
			sm.startSpeech();
			break;
		case 2://查看记录
			sm.showRecord();
			break;
		case 3:sm.clearRecord();//删除记录
			break;
		case 0: sm.exitSystem();//退出系统
			break;
		default:
			system("cls");
			cout << "没有您所选择的选项,请重新选择" << endl;
			break;
		}
	}
	

	system("pause");

	return 0;
}