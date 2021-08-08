#include "speechManager.h"

SpeechManager::SpeechManager() {
	this->initSpeech();

	this->createSpeaker();

	//加载往届记录
	this->loadRecord();
}

void SpeechManager::show_Menu() {

	cout << "**********************************" << endl;
	cout << "*********欢迎参加演讲比赛*********" << endl;
	cout << "**********1.开始演讲比赛**********" << endl;
	cout << "**********2.查看往届记录**********" << endl;
	cout << "**********3.删除往届记录**********" << endl;
	cout << "**********0.退出比赛程序**********" << endl;
	cout << "**********************************" << endl;
	cout  << endl;
}

void SpeechManager::exitSystem() {
	cout << "欢迎下次使用,88!" << endl;
	system("pause");
	exit(0);
}

void SpeechManager::initSpeech() {

	//容器置为空
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_Speaker.clear();

	//初始化轮数
	this->m_Index = 1;
	this->m_Record.clear();

}

void SpeechManager::createSpeaker() {

	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.size(); i++)
	{
		string name = "选手";
		name += nameSeed[i];


		//创建具体选手
		Speaker sp;
		sp.m_Name = name;

		for (int j = 0; j < 2; j++)
		{
			sp.m_Score[j] = 0;
		}
		//创建选手编号 并且放入到v1容器中
		this->v1.push_back(i + 10001);

		//选手对应编号以及对应选手放入对应的mao容器中
		this->m_Speaker.insert(make_pair(i + 10001, sp));

	}

}

void  SpeechManager::startSpeech() {

	//第一轮比赛
    //1.抽签
	this->speechDraw();
	//2.比赛
	this->speechContest();
	//3.显示晋级结果
	this->showScore();
	//第二轮比赛
	this->m_Index++;
	 //1.抽签
	this->speechDraw();
	//2.比赛
	this->speechContest();
	//3.显示最终结果
	this->showScore();
	//4.保存分数
	this->saveRecord();

	//重置比赛
	this->initSpeech();//初始化
	this->createSpeaker();//创建选手
	this->loadRecord();//获取往届记录

	cout << "比赛结束" << endl;
	system("pause");
	system("cls");
}

void SpeechManager::speechDraw() {
	cout << "当前为第" << this->m_Index << "轮比赛选手正在进行抽签"<<endl;
	cout << "----------------------------------" << endl;
	cout << "抽取顺序如下:" << endl;
	if (this->m_Index == 1) {
		//第一轮比赛
		random_shuffle(v1.begin(), v1.end());
		for (vector<int> ::iterator it = v1.begin(); it!=v1.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	else {
		random_shuffle(v2.begin(), v2.end());
		for (vector<int> ::iterator it = v2.begin(); it != v2.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	} 
	cout << "----------------------------------" << endl;
	system("pause");
}

void SpeechManager::speechContest() {
	cout << "当前为第" << this->m_Index << "轮比赛正式开始" << endl;

	multimap<double, int, greater<double>> grourpScore;//临时容器 保存key分数 value 选手编号
	int num = 0;//记录人员数量 6人一组


	vector<int>v_Src;//比赛选手容器
	if (this->m_Index == 1)
	{
		v_Src = v1;
	}
	else
	{
		v_Src = v2;
	}

	//遍历所有参赛选手
	for (vector<int>::iterator it=v_Src.begin();it!=v_Src.end();it++)
	{
		num++;
		//评委打分
		deque<double>d;
		for (int i = 0; i < 10; i++)
		{
			double score = (rand()%401+600)/10.f;
			//cout << score;
			d.push_back(score);
		}

		sort(d.begin(), d.end(), greater<double>());//排序
		d.pop_front();//去掉最高分 头
		d.pop_back();//去掉最低分 尾

		double sum = accumulate(d.begin(), d.end(), 0.0f);//总分
		double avg = sum / (double)d.size();//平均分

		//平均分放入map容器中
		this->m_Speaker[*it].m_Score[this->m_Index - 1] = avg;

		//打分数据放入临时容器中
		grourpScore.insert(make_pair(avg, *it));

		if (num % 6 == 0) {
			cout << "第" << num / 6 <<"小组比赛名次:"<< endl;
			for (multimap<double, int, greater<double>> ::iterator it = grourpScore.begin(); it != grourpScore.end(); it++) {
				cout << "编号: " << it->second << " 姓名: " << this->m_Speaker[it->second].m_Name
					<< " 成绩: " << this->m_Speaker[it->second].m_Score[this->m_Index-1] << endl;
			}
			int count = 0;
			cout << endl;
			for (multimap<double, int, greater<double>> ::iterator it = grourpScore.begin(); it != grourpScore.end() && count < 3; it++,count++) {

				if (this->m_Index == 1) {
					v2.push_back((*it).second);
				}
				else
				{
					vVictory.push_back((*it).second);
				}

			}

			grourpScore.clear();
		}

	}
	cout <<"第"<< this->m_Index<<"轮比赛完成" << endl;
	system("pause");
}

void SpeechManager::showScore() {
	
	cout << "第" << this->m_Index << "轮晋级选手信息:" << endl;

	vector<int>v;
	if (this->m_Index == 1) {
		v = v2;
	}
	else {
		v = vVictory;
	}

	for (vector<int>::iterator it = v.begin(); it != v.end(); it++){

		cout << "选手编号: " << *it << " 姓名: " << this->m_Speaker[*it].m_Name
			<< " 分数: " << this->m_Speaker[*it].m_Score[this->m_Index-1]<<endl;

	}
	cout << endl;
	system("pause");
	system("cls");
	this->show_Menu();
}

void SpeechManager::saveRecord() {

	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);//输出方式打开文件 追加写文件

	//遍历数据存入文件之中
	for (vector<int> ::iterator it = vVictory.begin(); it < vVictory.end(); it++){

		ofs << *it << ","
			<< m_Speaker[*it].m_Score[1] << ",";

	}
	ofs << endl;

	//关闭文件
	ofs.close();

	cout << "记录已经保存成功" << endl;
	this->fileIsEmpty = false;
}

void SpeechManager::loadRecord() {

	ifstream ifs("speech.csv", ios::in);

	if (!ifs.is_open()) {
		this->fileIsEmpty = true;
		//cout << "文件不存在" << endl;
		ifs.close();
		return;
	}

	char ch;
	ifs >> ch;

	if (ifs.eof()){
		//cout << "文件为空" << endl;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}

	this->fileIsEmpty = false;
	ifs.putback(ch);//将读取的字符放回

	string data;
	int index = 0;

	while (ifs >> data) {
		
		vector<string>v;

		int pos = -1;//查到","位置遍变量
		int start = 0;

		while (true)
		{
			pos = data.find(",", start);
			if (pos == -1) {
				break;
			}
			string temp = data.substr(start, pos - start);
			//cout << temp << endl;
			v.push_back(temp);
			start = pos + 1;
		}
		
		this->m_Record.insert(make_pair(index, v));
		index++;
	}
	ifs.close();
	
	/*for (map<int, vector<string>>::iterator it = this->m_Record.begin(); it != this->m_Record.end(); it++)
	{
		cout << it->first << "冠军编号： " << it->second[0] << " 分数： " << it->second[1] << endl;
	}*/

}

void SpeechManager::showRecord() {

	if (this->fileIsEmpty)
	{
		cout << "文件为空或者不存在" << endl;
	}

	for (int i = 0; i < this->m_Record.size(); i++)
	{
		cout << "第" << i + 1 << "届 " <<
			"冠军编号: " << this->m_Record[i][0] << " 得分: " << this->m_Record[i][1] << " "
			"亚军编号: " << this->m_Record[i][2] << " 得分: " << this->m_Record[i][3] << " "
			"季军编号: " << this->m_Record[i][4] << " 得分: " << this->m_Record[i][5] << " " 
			<<endl;
	}

	system("pause");
	system("cls");
}

void SpeechManager::clearRecord() {
	
	cout << "请确认是否清空数据:" << endl;
	cout << "1. 确认" << endl;
	cout << "2. 返回" << endl;

	int select = 0;
	cin >> select;

	if (select==1)
	{
		ofstream ofs("speech.csv", ios::trunc);

		ofs.close();
		this->initSpeech();
		this->createSpeaker();
		this->loadRecord();

		cout << "清空成功" << endl;
	}

	system("pause");
	system("cls");
}

SpeechManager::~SpeechManager() {

}