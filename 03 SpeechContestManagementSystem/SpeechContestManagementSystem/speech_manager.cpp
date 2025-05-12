#include"speech_manager.h"

SpeechManager::SpeechManager() {
	this->InitSpeech();

	this->CreateSpeaker();

	this->ReadRecord();

}

void SpeechManager::ShowMenu() {
	cout << "*************************" << endl;
	cout << "��ӭ�μ��ݽ�����" << endl;
	cout << "1.��ʼ�ݽ�����" << endl;
	cout << "2.�鿴�����¼" << endl;
	cout << "3.��ձ�����¼" << endl;
	cout << "0.�˳���������" << endl;
	cout << endl;
}

void SpeechManager::ExitSystem() {
	cout << "��ӭ�´�ʹ��" << endl;
	exit(0);
}

void SpeechManager::InitSpeech() {
	this->v_1.clear();
	this->v_2.clear();
	this->v_victory.clear();
	this->map_Speaker.clear();
	this->round_index = 0;
	this->record_.clear();
}

void  SpeechManager::CreateSpeaker() {

	string name_seed = "ABCDEFGHIJKL";
	for (int i=0; i < name_seed.size(); i++) {
		string name = "ѡ��";
		name += name_seed[i];

		Speaker speaker;
		speaker.spreker_name_ = name;
		for (int i = 0; i < 2; i++) {
			speaker.sperker_score_[i] = 0;
		}
		this->v_1.push_back(i + 10001);

		this->map_Speaker.insert(make_pair(i + 10001, speaker));
	}
}

void SpeechManager::CleanRecord() {
	cout << "ȷ��Ҫ���ȫ���ļ�¼��" << endl;
	cout << "1.yes 2.no" << endl;
	int select;
	cin >> select;
	if (select == 1) {
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();

		this->InitSpeech();
		this->CreateSpeaker();
		this->ReadRecord();
		cout << "���ȫ����¼" << endl;
	}
	system("pause");
	system("cls");
}

void SpeechManager::SaveRecord() {
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);

	for (vector<int>::iterator it = v_victory.begin(); it != v_victory.end(); it++) {
		ofs << *it << "," << map_Speaker[*it].sperker_score_[1] << ",";
	}
	ofs << endl;

	ofs.close();
	cout << "��¼�ѱ���" << endl;
}

void SpeechManager::ShowRecord() {

	if (this->file_is_empty) {
		cout << "�������¼" << endl;
	}
	else {
		/*for (map<int, vector<string>>::iterator it = this->record_.begin(); it != this->record_.end(); it++) {
			cout << "��" << it->first << "���¼��" << it->second[0] << endl;
		}*/
		for (int i = 0; i < this->record_.size(); i++) {
			cout << "��" << i + 1 << "���¼��" <<
				"�ھ���ţ�" << this->record_[i][0] << "�÷֣�" << this->record_[i][1] <<
				"�Ǿ���ţ�" << this->record_[i][2] << "�÷֣�" << this->record_[i][3] <<
				"������ţ�" << this->record_[i][4] << "�÷֣�" << this->record_[i][5] <<
				endl;
		}
	}
}

void SpeechManager::StartSpeech() {
	//��һ�ֱ���
	this->round_index = 1;
	this->SpeechDraw();
	this->SpeechContest();
	this->ShowScore();

	//�ڶ��ֱ���
	this->round_index = 2;
	this->SpeechDraw();
	this->SpeechContest();
	this->ShowScore();

	//���沢����
	this->SaveRecord();
	this->InitSpeech();

	this->CreateSpeaker();
	this->ReadRecord();

	system("pause");
	system("cls");
}
void SpeechManager::ShowScore() {
	cout << "��" << this->round_index << "���ʤ����ѡ��:" << endl;
	if (this->round_index == 1) {
		for (vector<int>::iterator it = this->v_2.begin(); it != this->v_2.end(); it++) {

			cout << "��ţ�" << *it << "  " << "������" << this->map_Speaker[*it].spreker_name_ 
				<< "����:" << this->map_Speaker[*it].sperker_score_[this->round_index - 1]
				<< endl;
		}
	}
	else {
		for (vector<int>::iterator it = this->v_victory.begin(); it != this->v_victory.end(); it++) {

			cout << "��ţ�" << *it << "  " << "������" << this->map_Speaker[*it].spreker_name_
				<< "����:" << this->map_Speaker[*it].sperker_score_[this->round_index - 1]
				<< endl;
		}
	}
}
void SpeechManager::ReadRecord() {

	ifstream ifs("speech.csv", ios::in);

	if (!ifs.is_open()) {
		this->file_is_empty = true;
		cout << "�ļ�������" << endl;
		ifs.close();
		return;
	}
	char ch;
	ifs >> ch;
	if (ifs.eof()) {
		cout << "�ļ�Ϊ��" << endl;
		this->file_is_empty = true;
		ifs.close();
		return;
	}
	this->file_is_empty = false;

	ifs.putback(ch);

	string data;
	int index = 0;
	while (ifs >> data) {
		vector<string> v;
		int pos = -1;
		int start = 0;

		while (true) {
			pos = data.find(",", start);
			if (pos == -1) {
				break;
			}
			string tmp = data.substr(start, pos - start);

			v.push_back(tmp);
			start = pos + 1;
		}
		this->record_.insert(make_pair(index, v));
		index++;
	}
	ifs.close();
}


void SpeechManager::SpeechContest() {
	cout << "��" << this->round_index << "������ʽ��ʼ" << endl;

	multimap<double, int, greater<double>> group_score;

	vector<int>v_contest;
	if (this->round_index == 1) {
		v_contest = this->v_1;
	}
	else {
		v_contest = this->v_2;
	}
	int num = 0;
	for (vector<int>::iterator it = v_contest.begin(); it < v_contest.end(); it++) {
		num++;
		//��������deque���� ���β����ܺý���ȥ����߷���ͷֲ���
		deque<double> d;

		for (int i = 0; i < 10; i++) {
			double score = (rand() % 401 + 600) / 10.f;//600-1000
			d.push_back(score);
		}

		sort(d.begin(), d.end(), greater<double>());//����
		d.pop_front();
		d.pop_back();

		double sum = accumulate(d.begin(), d.end(),0.0f);
		double avg_score = sum / (double)d.size();

		//�洢ƽ����
		this->map_Speaker[*it].sperker_score_[this->round_index - 1] = avg_score;

		group_score.insert(make_pair(avg_score, *it));
		if (num % 6 == 0) {
			cout << "��" << num / 6 << "С���������" << endl;
			for (multimap<double, int, greater<double>>::iterator it = group_score.begin(); it != group_score.end(); it++) {
				cout << "��ţ�" << it->second << "����:" << this->map_Speaker[it->second].spreker_name_ << "�ɼ���"
					<< it->first << "����" << this->map_Speaker[it->second].sperker_score_[this->round_index - 1] << endl;
			}

			int count = 0;
			for (multimap<double, int, greater<double>>::iterator it = group_score.begin(); it != group_score.end() && count < 3; it++, count++) {
				if (this->round_index == 1) {
					this->v_2.push_back(it->second);
				}
				else {
					this->v_victory.push_back(it->second);
				}
			}
			group_score.clear();
			cout << endl;
		}
	}
	system("pause");
}

void SpeechManager::SpeechDraw() {

	cout << "��" << this->round_index << "��ǩ" << endl;
	cout << "```````````````````````````````" << endl;
	cout << "��ǰ���ݽ�˳������:" << endl;
	if (this->round_index == 1) {
		//��һ�ֱ���
		random_shuffle(v_1.begin(), v_1.end());

		for (vector<int>::iterator it = v_1.begin(); it < v_1.end(); it++) {
			cout << *it << " ";
		}
		cout << endl;
	}
	else {
		//�ڶ��ֱ���
		random_shuffle(v_2.begin(), v_2.end());

		for (vector<int>::iterator it = v_2.begin(); it < v_2.end(); it++) {
			cout << *it << " ";
		}
		cout << endl;
	}
	cout << "---------------------------" << endl;
	system("pause");
	cout << endl;
}


SpeechManager::~SpeechManager() {

}
