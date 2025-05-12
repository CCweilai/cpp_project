#include"boss.h"


Boss::Boss(int id, string name, int department_id) {
	this->id_ = id;
	this->name_ = name;
	this->department_id_ = department_id;
}

void Boss::ShowInfo() {
	cout << "worker id:" << this->id_ << "\t";
	cout << "worker name:" << this->name_ << "\t";
	cout << "worker department name:" << this->GetDepartmentName() << endl;
}

string Boss::GetDepartmentName() {
	return string("boss");
}

Boss::~Boss() {
}