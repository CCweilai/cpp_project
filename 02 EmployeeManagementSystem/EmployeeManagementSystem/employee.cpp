#include"employee.h"


Employee::Employee(int id, string name, int department_id) {
	this->id_ = id;
	this->name_ = name;
	this->department_id_ = department_id;
}

void Employee::ShowInfo() {
	cout << "worker id:" << this->id_ << "\t";
	cout << "worker name:" << this->name_ << "\t";
	cout << "worker department name:" << this->GetDepartmentName() << endl;
}

string Employee::GetDepartmentName() {
	return string("employee");
}

Employee::~Employee() {

}