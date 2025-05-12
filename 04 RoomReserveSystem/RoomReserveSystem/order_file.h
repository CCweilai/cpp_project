#pragma once
#include<iostream>
#include<string>
#include<map>
#include<fstream>

#include"global_file.h"

using namespace std;

class OrderFile {
public:
	map<int, map<string,string>>m_order;

	int order_num;

	OrderFile();

	void UpdateOrder();
	
};