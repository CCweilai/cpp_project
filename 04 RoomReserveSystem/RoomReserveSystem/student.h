#pragma once

#include<iostream>
#include<string>
#include<vector>
#include<fstream>

#include"identity.h"
#include"global_file.h"
#include"room.h"
#include"order_file.h"

using namespace std;
class Student :public Identity {

public:

	int student_id;
	vector<Room>v_room;

	Student();
	Student(int student_id, string name, string password);
	~Student();

	virtual void OpenMenu();

	//����ԤԼ
	void ApplyOrder();

	//�鿴�Լ���ԤԼ
	void ShowMyOrder();

	//�鿴����ԤԼ
	void ShowAllOrder();

	//ȡ��ԤԼ
	void CancelOrder();
};
