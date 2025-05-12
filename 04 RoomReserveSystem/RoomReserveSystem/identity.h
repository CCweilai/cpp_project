#pragma once

#include<iostream>
#include<string>

using namespace std;
class Identity {
public:
	//²Ù×÷²Ëµ¥
	virtual void OpenMenu()=0;

	string name_;
	string password_;
};
