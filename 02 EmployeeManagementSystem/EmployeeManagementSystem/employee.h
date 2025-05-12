#pragma once
#include<iostream>
#include"worker.h"

using namespace std;

class Employee :public Worker {
public:


	Employee(int id,string name,int department_id);

	//show person info
	virtual void ShowInfo();
	// get department name
	virtual string GetDepartmentName();

	~Employee();
};