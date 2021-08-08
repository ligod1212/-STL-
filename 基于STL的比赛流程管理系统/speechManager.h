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

//�ݽ�������
class SpeechManager
{
public:
	 SpeechManager();

	 //��ʾ�˵�
	 void show_Menu();
	 
	 //�˳�ϵͳ
	 void exitSystem();

	 //�������
	 void initSpeech();

	 //����ѡ��
	 void createSpeaker();

	 //��ʼ����
	 void startSpeech();

	 //��ǩ
	 void speechDraw();

	 //����
	 void speechContest();

	 //��ʾ������Ϣ
	 void showScore();

	 //�����¼
	 void saveRecord();

	 //��ȡ��¼
	 void loadRecord();

	 //��ʾ��¼
	 void showRecord();

	 //�������
	 void clearRecord();

	~ SpeechManager();

	//����ѡ������ 12��
	vector<int> v1;

	//��һ�ֽ������� 6��
	vector<int> v2;

	//ʤ����ǰ���� 3��
	vector<int>vVictory;

	//��ű���Լ������Ŷ�Ӧ��ѡ������
	map<int,Speaker> m_Speaker;

	//����������¼
	int m_Index;

	//�ļ���־Ϊ��
	bool fileIsEmpty;

	//�����¼
	map<int, vector<string>>m_Record;

};