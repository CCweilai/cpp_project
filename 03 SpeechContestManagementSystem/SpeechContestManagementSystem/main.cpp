#include<iostream>
#include"speech_manager.h"
#include<ctime>


using namespace std;


int main() {
	srand((unsigned int)time(NULL));

	SpeechManager speech_manager;

	int select = 0;
	while (true) {
		speech_manager.ShowMenu();

		cout << "请选择你的操作" << endl;
		cin >> select;

		switch (select) {
		case 1://开始比赛
			speech_manager.StartSpeech();
			break;
		case 2://查看记录
			speech_manager.ShowRecord();
			break;
		case 3://清空比赛记录
			speech_manager.CleanRecord();
			break;
		case 0://退出系统
			speech_manager.ExitSystem();
			break;
		default:
			system("cls");
			break;
		}
	}

	/*cout << "main" << endl;

	system("pause");*/

	return 0;


}