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

		cout << "��ѡ����Ĳ���" << endl;
		cin >> select;

		switch (select) {
		case 1://��ʼ����
			speech_manager.StartSpeech();
			break;
		case 2://�鿴��¼
			speech_manager.ShowRecord();
			break;
		case 3://��ձ�����¼
			speech_manager.CleanRecord();
			break;
		case 0://�˳�ϵͳ
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