#pragma once
#include<iostream>
#include<string>

using namespace std;

class Worker{
public:
	//show person info
	virtual void ShowInfo() = 0;
	// get department name
	virtual string GetDepartmentName() = 0;

	int id_;
	string name_;
	int department_id_;
};