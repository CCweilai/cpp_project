#pragma once
#pragma once

#include<iostream>
#include<string>
#include<vector>

#include"identity.h"
#include"order_file.h"

using namespace std;

class Teacher :public Identity {

public:

	int teacher_id;

	Teacher();
	Teacher(int teacher_id, string name, string password);
	~Teacher();
	virtual void OpenMenu();

	//�鿴����ԤԼ
	void ShowAllOrder();

	//���ԤԼ
	void VaildOrder();

};
