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
	//��һ�֡��ڶ����Լ�ʤ���ı������
	vector<int>v_1;
	vector<int>v_2;

	vector<int>v_victory;

	//��ű���Լ�ѡ�ֶ�Ӧ
	map<int, Speaker>map_Speaker;

	bool file_is_empty;

	//����ļ�¼

	map<int, vector<string>> record_;

	//��ű�������
	int round_index;

	//��ʼ����������
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

