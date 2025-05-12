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

	//申请预约
	void ApplyOrder();

	//查看自己的预约
	void ShowMyOrder();

	//查看所有预约
	void ShowAllOrder();

	//取消预约
	void CancelOrder();
};
