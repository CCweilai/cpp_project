#pragma once
#include<iostream>
#include"worker.h"

using namespace std;

class Boss :public Worker {
public:

	Boss(int id, string name, int department_id);

	//show person info
	virtual void ShowInfo();
	// get department name
	virtual string GetDepartmentName();

	~Boss();

};