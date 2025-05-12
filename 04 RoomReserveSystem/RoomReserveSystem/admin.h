#pragma once

#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<algorithm>

#include"identity.h"
#include"global_file.h"
#include"student.h"
#include"teacher.h"
#include"room.h"


using namespace std;

class Admin :public Identity {
public:
	int admin_id;

	vector<Student>v_student;
	vector<Teacher>v_teacher;
	vector<Admin>v_admin;
	vector<Room>v_room;

	void InitVector();
	bool CheckRepeat(int id, int type);
	Admin();
	Admin(int admin_id, string name, string password);
	~Admin();

	virtual void OpenMenu();
	//添加账号
	void AddPerson();

	//查看账号
	void ShowPerson();

	//查看空间信息
	void ShowRoom();

	//清空预约记录
	void CleanOrder();


};