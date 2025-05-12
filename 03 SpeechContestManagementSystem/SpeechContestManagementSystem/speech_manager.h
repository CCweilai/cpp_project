#pragma once

#include<iostream>
#include<vector>
#include<map>
#include<algorithm>
#include<deque>
#include<numeric>
#include<fstream>

#include"speaker.h"
using namespace std;

class SpeechManager {
public:
	//第一轮、第二轮以及胜利的编号容器
	vector<int>v_1;
	vector<int>v_2;

	vector<int>v_victory;

	//存放编号以及选手对应
	map<int, Speaker>map_Speaker;

	bool file_is_empty;

	//往届的记录

	map<int, vector<string>> record_;

	//存放比赛轮数
	int round_index;

	//初始化容器属性
	void InitSpeech();

	void CreateSpeaker();

	void StartSpeech();

	void SpeechDraw();

	void SpeechContest();

	void ShowScore();
	void SaveRecord();
	void ReadRecord();
	void ShowRecord();
	void CleanRecord();

	SpeechManager();

	void ShowMenu();

	void ExitSystem();

	~SpeechManager();

};

