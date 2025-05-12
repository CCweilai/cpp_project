#include<iostream>
#include<fstream>

#include"global_file.h"
#include"identity.h"
#include"student.h"
#include"teacher.h"
#include"admin.h"

using namespace std;


void AdminMenu(Identity * & admin) {//调用管理员子菜单
	while (true) {
		admin->OpenMenu();//这里是虚函数，父类指针调用子类的实现
		Admin* adm = (Admin*)admin; //父类指针转为子类，用以调用子类的函数u

		int select=0;
		cout << "请输入你的选择" << endl;
		cin >> select;
		if (select == 1) {//添加账号
			adm->AddPerson();
		}
		else if (select == 2) {//查看账号
			adm->ShowPerson();

		}
		else if (select == 3) {//查看机房
			adm->ShowRoom();

		}
		else if (select == 4) {//清空预约
			adm->CleanOrder();

		}
		else{//注销模块
			delete admin;
			cout << "注销成功" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
}

void StudentMenu(Identity*& student) {//调用学生子菜单
	while (true) {
		student->OpenMenu();//这里是虚函数，父类指针调用子类的实现
		Student* stu = (Student*)student; //父类指针转为子类，用以调用子类的函数u

		int select = 0;
		cout << "请输入你的选择" << endl;
		cin >> select;
		if (select == 1) {//申请预约
			stu->ApplyOrder();
		}
		else if (select == 2) {//查看我的预约
			stu->ShowMyOrder();
		}
		else if (select == 3) {//查看所有预约
			stu->ShowAllOrder();
		}
		else if (select == 4) {//取消预约
			stu->CancelOrder();
		}
		else {//注销模块
			delete student;
			cout << "注销成功" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
}

void TeacherMenu(Identity*& teacher) {//调用教师子菜单
	while (true) {
		teacher->OpenMenu();//这里是虚函数，父类指针调用子类的实现
		Teacher* tch = (Teacher*)teacher; //父类指针转为子类，用以调用子类的函数u

		int select = 0;
		cout << "请输入你的选择" << endl;
		cin >> select;
		if (select == 1) {//查看预约
			tch->ShowAllOrder();
		}
		else if (select == 2) {//审核预约
			tch->VaildOrder();
		}
		else {//注销模块
			delete teacher;
			cout << "注销成功" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
}
void Login(string filename, int type) {

	Identity* person = nullptr;
	ifstream ifs;

	ifs.open(filename, ios::in);

	if (!ifs.is_open()) {
		cout << "记录文件不存在" << endl;
		ifs.close();
		return;
	}

	int id = 0,fid;
	string name,fname;
	string password,fpassword;

	if (type == 1) {//学生登录
		cout << "请输入你的学号:" << endl;
		cin >> id;
		cout << "请输入你的姓名" << endl;
		cin >> name;
		cout << "请输入你的密码:" << endl;
		cin >> password;
		while (ifs >> fid && ifs >> fname && ifs >> fpassword) {
			if (id == fid && name == fname && password == fpassword) {
				cout << "学生验证登录成功" << endl;
				system("pause");
				system("cls");
				person = new Student(id, name, password);
				StudentMenu(person);//进入学生子界面
				return;
			}
		}
	}
	else if (type == 2) {//教师登录
		cout << "请输入你的职工号" << endl;
		cin >> id;
		cout << "请输入你的姓名" << endl;
		cin >> name;
		cout << "请输入你的密码:" << endl;
		cin >> password;
		while (ifs >> fid && ifs >> fname && ifs >> fpassword) {
			if (id == fid && name == fname && password == fpassword) {
				cout << "教师验证登录成功" << endl;
				system("pause");
				system("cls");
				person = new Teacher(id, name, password);
				TeacherMenu(person);
				return;
			}
		}
	}
	else if (type == 3) {//管理员登录
		//登录不了添加新的账号登录
		cout << "请输入你的管理员编号" << endl;
		cin >> id;
		cout << "请输入你的姓名" << endl;
		cin >> name;
		cout << "请输入你的密码:" << endl;
		cin >> password;
		while (ifs >> fid && ifs >> fname && ifs >> fpassword) {
			if (id == fid && name == fname && password == fpassword) {
				cout << "管理员验证登录成功" << endl;
				system("pause");
				system("cls");
				person = new Admin(id, name, password);
				AdminMenu(person);//进入管理员子界面
				return;
			}
		}
	}
	cout << "验证登录失败" << endl;

	system("pause");
	system("cls");
	return;
}

int main() {
	//空间(机房）预约系统
	//菜单
	int select;
	while (true) {
		cout << "*****************机房预约系统*********" << endl;
		cout << "请选择你的身份" << endl;
		cout << "1.学生代表" << endl;
		cout << "2.老   师" << endl;
		cout << "3.管理员" << endl;
		cout << "0.退出系统" << endl;

		cout << "输入你的选择" << endl;
		cin >> select;
		switch (select) {
		case 1://学生代表
			Login(STUDENT_FILE, 1);
			break;
		case 2://
			Login(TEACHER_FILE, 2);
			break;
		case 3:
			Login(ADMIN_FILE, 3);
			break;
		case 0:
			cout << "欢迎下次使用预约系统" << endl;
			system("pause");
			return 0;
			break;
		default:
			cout << "输入有误" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
	return 0;
}