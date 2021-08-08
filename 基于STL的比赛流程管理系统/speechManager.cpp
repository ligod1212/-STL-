#include "speechManager.h"

SpeechManager::SpeechManager() {
	this->initSpeech();

	this->createSpeaker();

	//���������¼
	this->loadRecord();
}

void SpeechManager::show_Menu() {

	cout << "**********************************" << endl;
	cout << "*********��ӭ�μ��ݽ�����*********" << endl;
	cout << "**********1.��ʼ�ݽ�����**********" << endl;
	cout << "**********2.�鿴�����¼**********" << endl;
	cout << "**********3.ɾ�������¼**********" << endl;
	cout << "**********0.�˳���������**********" << endl;
	cout << "**********************************" << endl;
	cout  << endl;
}

void SpeechManager::exitSystem() {
	cout << "��ӭ�´�ʹ��,88!" << endl;
	system("pause");
	exit(0);
}

void SpeechManager::initSpeech() {

	//������Ϊ��
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_Speaker.clear();

	//��ʼ������
	this->m_Index = 1;
	this->m_Record.clear();

}

void SpeechManager::createSpeaker() {

	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.size(); i++)
	{
		string name = "ѡ��";
		name += nameSeed[i];


		//��������ѡ��
		Speaker sp;
		sp.m_Name = name;

		for (int j = 0; j < 2; j++)
		{
			sp.m_Score[j] = 0;
		}
		//����ѡ�ֱ�� ���ҷ��뵽v1������
		this->v1.push_back(i + 10001);

		//ѡ�ֶ�Ӧ����Լ���Ӧѡ�ַ����Ӧ��mao������
		this->m_Speaker.insert(make_pair(i + 10001, sp));

	}

}

void  SpeechManager::startSpeech() {

	//��һ�ֱ���
    //1.��ǩ
	this->speechDraw();
	//2.����
	this->speechContest();
	//3.��ʾ�������
	this->showScore();
	//�ڶ��ֱ���
	this->m_Index++;
	 //1.��ǩ
	this->speechDraw();
	//2.����
	this->speechContest();
	//3.��ʾ���ս��
	this->showScore();
	//4.�������
	this->saveRecord();

	//���ñ���
	this->initSpeech();//��ʼ��
	this->createSpeaker();//����ѡ��
	this->loadRecord();//��ȡ�����¼

	cout << "��������" << endl;
	system("pause");
	system("cls");
}

void SpeechManager::speechDraw() {
	cout << "��ǰΪ��" << this->m_Index << "�ֱ���ѡ�����ڽ��г�ǩ"<<endl;
	cout << "----------------------------------" << endl;
	cout << "��ȡ˳������:" << endl;
	if (this->m_Index == 1) {
		//��һ�ֱ���
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
	cout << "��ǰΪ��" << this->m_Index << "�ֱ�����ʽ��ʼ" << endl;

	multimap<double, int, greater<double>> grourpScore;//��ʱ���� ����key���� value ѡ�ֱ��
	int num = 0;//��¼��Ա���� 6��һ��


	vector<int>v_Src;//����ѡ������
	if (this->m_Index == 1)
	{
		v_Src = v1;
	}
	else
	{
		v_Src = v2;
	}

	//�������в���ѡ��
	for (vector<int>::iterator it=v_Src.begin();it!=v_Src.end();it++)
	{
		num++;
		//��ί���
		deque<double>d;
		for (int i = 0; i < 10; i++)
		{
			double score = (rand()%401+600)/10.f;
			//cout << score;
			d.push_back(score);
		}

		sort(d.begin(), d.end(), greater<double>());//����
		d.pop_front();//ȥ����߷� ͷ
		d.pop_back();//ȥ����ͷ� β

		double sum = accumulate(d.begin(), d.end(), 0.0f);//�ܷ�
		double avg = sum / (double)d.size();//ƽ����

		//ƽ���ַ���map������
		this->m_Speaker[*it].m_Score[this->m_Index - 1] = avg;

		//������ݷ�����ʱ������
		grourpScore.insert(make_pair(avg, *it));

		if (num % 6 == 0) {
			cout << "��" << num / 6 <<"С���������:"<< endl;
			for (multimap<double, int, greater<double>> ::iterator it = grourpScore.begin(); it != grourpScore.end(); it++) {
				cout << "���: " << it->second << " ����: " << this->m_Speaker[it->second].m_Name
					<< " �ɼ�: " << this->m_Speaker[it->second].m_Score[this->m_Index-1] << endl;
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
	cout <<"��"<< this->m_Index<<"�ֱ������" << endl;
	system("pause");
}

void SpeechManager::showScore() {
	
	cout << "��" << this->m_Index << "�ֽ���ѡ����Ϣ:" << endl;

	vector<int>v;
	if (this->m_Index == 1) {
		v = v2;
	}
	else {
		v = vVictory;
	}

	for (vector<int>::iterator it = v.begin(); it != v.end(); it++){

		cout << "ѡ�ֱ��: " << *it << " ����: " << this->m_Speaker[*it].m_Name
			<< " ����: " << this->m_Speaker[*it].m_Score[this->m_Index-1]<<endl;

	}
	cout << endl;
	system("pause");
	system("cls");
	this->show_Menu();
}

void SpeechManager::saveRecord() {

	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);//�����ʽ���ļ� ׷��д�ļ�

	//�������ݴ����ļ�֮��
	for (vector<int> ::iterator it = vVictory.begin(); it < vVictory.end(); it++){

		ofs << *it << ","
			<< m_Speaker[*it].m_Score[1] << ",";

	}
	ofs << endl;

	//�ر��ļ�
	ofs.close();

	cout << "��¼�Ѿ�����ɹ�" << endl;
	this->fileIsEmpty = false;
}

void SpeechManager::loadRecord() {

	ifstream ifs("speech.csv", ios::in);

	if (!ifs.is_open()) {
		this->fileIsEmpty = true;
		//cout << "�ļ�������" << endl;
		ifs.close();
		return;
	}

	char ch;
	ifs >> ch;

	if (ifs.eof()){
		//cout << "�ļ�Ϊ��" << endl;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}

	this->fileIsEmpty = false;
	ifs.putback(ch);//����ȡ���ַ��Ż�

	string data;
	int index = 0;

	while (ifs >> data) {
		
		vector<string>v;

		int pos = -1;//�鵽","λ�ñ����
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
		cout << it->first << "�ھ���ţ� " << it->second[0] << " ������ " << it->second[1] << endl;
	}*/

}

void SpeechManager::showRecord() {

	if (this->fileIsEmpty)
	{
		cout << "�ļ�Ϊ�ջ��߲�����" << endl;
	}

	for (int i = 0; i < this->m_Record.size(); i++)
	{
		cout << "��" << i + 1 << "�� " <<
			"�ھ����: " << this->m_Record[i][0] << " �÷�: " << this->m_Record[i][1] << " "
			"�Ǿ����: " << this->m_Record[i][2] << " �÷�: " << this->m_Record[i][3] << " "
			"�������: " << this->m_Record[i][4] << " �÷�: " << this->m_Record[i][5] << " " 
			<<endl;
	}

	system("pause");
	system("cls");
}

void SpeechManager::clearRecord() {
	
	cout << "��ȷ���Ƿ��������:" << endl;
	cout << "1. ȷ��" << endl;
	cout << "2. ����" << endl;

	int select = 0;
	cin >> select;

	if (select==1)
	{
		ofstream ofs("speech.csv", ios::trunc);

		ofs.close();
		this->initSpeech();
		this->createSpeaker();
		this->loadRecord();

		cout << "��ճɹ�" << endl;
	}

	system("pause");
	system("cls");
}

SpeechManager::~SpeechManager() {

}