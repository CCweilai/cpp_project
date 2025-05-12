#pragma once
#include<iostream>
#include"worker.h"

using namespace std;

class Manager :public Worker {

public:

	Manager(int id, string name, int department_id);

	//show person info
	virtual void ShowInfo();
	// get department name
	virtual string GetDepartmentName();

	~Manager();

};

