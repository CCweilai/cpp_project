#include"speech_manager.h"

SpeechManager::SpeechManager() {
	this->InitSpeech();

	this->CreateSpeaker();

	this->ReadRecord();

}

void SpeechManager::ShowMenu() {
	cout << "*************************" << endl;
	cout << "欢迎参加演讲比赛" << endl;
	cout << "1.开始演讲比赛" << endl;
	cout << "2.查看往届记录" << endl;
	cout << "3.清空比赛记录" << endl;
	cout << "0.退出比赛程序" << endl;
	cout << endl;
}

void SpeechManager::ExitSystem() {
	cout << "欢迎下次使用" << endl;
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
		string name = "选手";
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
	cout << "确认要清空全部的记录吗？" << endl;
	cout << "1.yes 2.no" << endl;
	int select;
	cin >> select;
	if (select == 1) {
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();

		this->InitSpeech();
		this->CreateSpeaker();
		this->ReadRecord();
		cout << "清空全部记录" << endl;
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
	cout << "记录已保存" << endl;
}

void SpeechManager::ShowRecord() {

	if (this->file_is_empty) {
		cout << "无往届记录" << endl;
	}
	else {
		/*for (map<int, vector<string>>::iterator it = this->record_.begin(); it != this->record_.end(); it++) {
			cout << "第" << it->first << "届记录：" << it->second[0] << endl;
		}*/
		for (int i = 0; i < this->record_.size(); i++) {
			cout << "第" << i + 1 << "届记录：" <<
				"冠军编号：" << this->record_[i][0] << "得分：" << this->record_[i][1] <<
				"亚军编号：" << this->record_[i][2] << "得分：" << this->record_[i][3] <<
				"季军编号：" << this->record_[i][4] << "得分：" << this->record_[i][5] <<
				endl;
		}
	}
}

void SpeechManager::StartSpeech() {
	//第一轮比赛
	this->round_index = 1;
	this->SpeechDraw();
	this->SpeechContest();
	this->ShowScore();

	//第二轮比赛
	this->round_index = 2;
	this->SpeechDraw();
	this->SpeechContest();
	this->ShowScore();

	//保存并更新
	this->SaveRecord();
	this->InitSpeech();

	this->CreateSpeaker();
	this->ReadRecord();

	system("pause");
	system("cls");
}
void SpeechManager::ShowScore() {
	cout << "第" << this->round_index << "获得胜利的选手:" << endl;
	if (this->round_index == 1) {
		for (vector<int>::iterator it = this->v_2.begin(); it != this->v_2.end(); it++) {

			cout << "编号：" << *it << "  " << "姓名：" << this->map_Speaker[*it].spreker_name_ 
				<< "分数:" << this->map_Speaker[*it].sperker_score_[this->round_index - 1]
				<< endl;
		}
	}
	else {
		for (vector<int>::iterator it = this->v_victory.begin(); it != this->v_victory.end(); it++) {

			cout << "编号：" << *it << "  " << "姓名：" << this->map_Speaker[*it].spreker_name_
				<< "分数:" << this->map_Speaker[*it].sperker_score_[this->round_index - 1]
				<< endl;
		}
	}
}
void SpeechManager::ReadRecord() {

	ifstream ifs("speech.csv", ios::in);

	if (!ifs.is_open()) {
		this->file_is_empty = true;
		cout << "文件不存在" << endl;
		ifs.close();
		return;
	}
	char ch;
	ifs >> ch;
	if (ifs.eof()) {
		cout << "文件为空" << endl;
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
	cout << "第" << this->round_index << "比赛正式开始" << endl;

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
		//打分最好用deque容器 两段操作很好进行去掉最高分最低分操作
		deque<double> d;

		for (int i = 0; i < 10; i++) {
			double score = (rand() % 401 + 600) / 10.f;//600-1000
			d.push_back(score);
		}

		sort(d.begin(), d.end(), greater<double>());//排序
		d.pop_front();
		d.pop_back();

		double sum = accumulate(d.begin(), d.end(),0.0f);
		double avg_score = sum / (double)d.size();

		//存储平均分
		this->map_Speaker[*it].sperker_score_[this->round_index - 1] = avg_score;

		group_score.insert(make_pair(avg_score, *it));
		if (num % 6 == 0) {
			cout << "第" << num / 6 << "小组比赛名次" << endl;
			for (multimap<double, int, greater<double>>::iterator it = group_score.begin(); it != group_score.end(); it++) {
				cout << "编号：" << it->second << "姓名:" << this->map_Speaker[it->second].spreker_name_ << "成绩："
					<< it->first << "测试" << this->map_Speaker[it->second].sperker_score_[this->round_index - 1] << endl;
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

	cout << "第" << this->round_index << "抽签" << endl;
	cout << "```````````````````````````````" << endl;
	cout << "抽前后演讲顺序如下:" << endl;
	if (this->round_index == 1) {
		//第一轮比赛
		random_shuffle(v_1.begin(), v_1.end());

		for (vector<int>::iterator it = v_1.begin(); it < v_1.end(); it++) {
			cout << *it << " ";
		}
		cout << endl;
	}
	else {
		//第二轮比赛
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
