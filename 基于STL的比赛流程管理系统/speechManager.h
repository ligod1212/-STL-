#pragma once 
#include <iostream>
using namespace std;
#include <vector>
#include <map>
#include "speaker.h"
#include <algorithm>
#include <deque>
#include <functional>
#include <numeric>
#include <string>
#include <fstream>

//演讲管理类
class SpeechManager
{
public:
	 SpeechManager();

	 //显示菜单
	 void show_Menu();
	 
	 //退出系统
	 void exitSystem();

	 //清空容器
	 void initSpeech();

	 //创建选手
	 void createSpeaker();

	 //开始比赛
	 void startSpeech();

	 //抽签
	 void speechDraw();

	 //比赛
	 void speechContest();

	 //显示晋级信息
	 void showScore();

	 //保存记录
	 void saveRecord();

	 //读取记录
	 void loadRecord();

	 //显示记录
	 void showRecord();

	 //清空数据
	 void clearRecord();

	~ SpeechManager();

	//比赛选手容器 12人
	vector<int> v1;

	//第一轮晋级容器 6人
	vector<int> v2;

	//胜利者前三名 3人
	vector<int>vVictory;

	//存放编号以及具体编号对应的选手容器
	map<int,Speaker> m_Speaker;

	//比赛轮数记录
	int m_Index;

	//文件标志为空
	bool fileIsEmpty;

	//往届记录
	map<int, vector<string>>m_Record;

};