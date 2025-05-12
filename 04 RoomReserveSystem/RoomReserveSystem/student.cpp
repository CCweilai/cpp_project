#include<iostream>

#include"student.h"

void Student::OpenMenu() {
	//学生打开菜单实现
	cout << "欢迎学生：" << this->name_ << "登录！" << endl;
	cout << "1.申请预约" << endl;
	cout << "2.查看我的预约" << endl;
	cout << "3.查看所有预约" << endl;
	cout << "4.取消预约" << endl;
	cout << "0.注销登录" << endl;
}


void  Student::ApplyOrder() {
	//申请预约
	cout << "机房开放时间为周一至周五!" << endl;
	cout << "请选择你要预约的时间段" << endl;
	cout << "1.周一 2.周二 3.周三 4.周四 5.周五" << endl;
	int week;
	int interval;
	int room;
	while (true) {
		cin >> week;
		if (week >= 1 && week <= 5) {
			break;
		}
		cout << "输入有误，请重新输入" << endl;
	}
	cout << "1.上午 2.下午" << endl;
	while (true) {
		cin >> interval;
		if (interval == 1 || interval == 2) {
			break;
		}
		cout << "输入有误，请重新输入" << endl;
	}
	cout << "请选择机房" << endl;
	cout << "1号机房容量：" << this->v_room[0].room_capacity_ << endl;
	cout << "2号机房容量：" << this->v_room[1].room_capacity_ << endl;
	cout << "3号机房容量：" << this->v_room[2].room_capacity_ << endl;
	while (true) {
		cin >> room;
		if (room >= 1 || room <= 3) {
			break;
		}
		cout << "输入有误，请重新输入" << endl;
	}
	cout << "预约成功！审核中..." << endl;

	ofstream ofs(ORDER_FILE, ios::app);
	ofs << "week:" << week << " ";
	ofs << "interval:" << interval << " ";
	ofs << "stu_id:" << this->student_id << " ";
	ofs << "stu_name:" << this->name_ << " ";
	ofs << "room_id:" << room << " ";
	ofs << "status:" << 1 << endl;

	ofs.close();

	system("pause");
	system("cls");
}


void  Student::ShowMyOrder() {
	//查看自己的预约

	OrderFile orderfile;
	if (orderfile.order_num == 0) {
		cout << "无预约记录" << endl;
		system("pause");
		system("cls");
		return;
	}
	for (int i = 0; i < orderfile.order_num; i++) {
		if (atoi(orderfile.m_order[i]["stu_id"].c_str())== this->student_id) {
			cout << "预约时间:周" << orderfile.m_order[i]["week"] << (orderfile.m_order[i]["interval"] == "1" ? "上午" : "下午")
				<< "  机房：" << orderfile.m_order[i]["room_id"]
				<< "  预约人id：" << orderfile.m_order[i]["stu_id"]
				<< "  预约人姓名：" << orderfile.m_order[i]["stu_name"];
			string status = "状态：";
			if (orderfile.m_order[i]["status"] == "1") {
				status += "审核中";
			}
			else if (orderfile.m_order[i]["status"] == "2") {
				status += "已预约";

			}
			else if (orderfile.m_order[i]["status"] == "-1") {
				status += "预约失败";

			}
			else if (orderfile.m_order[i]["status"] == "0") {
				status += "取消的预约";

			}
			else {
				status += "状态错误";
			}
			cout << status << endl;
		}
	}
	system("pause");
	system("cls");
}


void  Student::ShowAllOrder() {
	//查看所有预约

	OrderFile orderfile;
	if (orderfile.order_num == 0) {
		cout << "无预约记录" << endl;
		system("pause");
		system("cls");
		return;
	}
	for (int i = 0; i < orderfile.order_num; i++) {
		cout << "预约时间:周" << orderfile.m_order[i]["week"] << (orderfile.m_order[i]["interval"] == "1"?"上午":"下午")
			<< "  机房：" << orderfile.m_order[i]["room_id"]
			<< "  预约人id：" << orderfile.m_order[i]["stu_id"]
			<< "  预约人姓名：" << orderfile.m_order[i]["stu_name"];
		string status = "  状态：";
		if (orderfile.m_order[i]["status"] == "1") {
			status += "审核中";
		}
		else if (orderfile.m_order[i]["status"] == "2") {
			status += "已预约";

		}
		else if (orderfile.m_order[i]["status"] == "-1") {
			status += "预约失败";

		}
		else if (orderfile.m_order[i]["status"] == "0") {
			status += "取消的预约";
		}
		else {
			status += "状态错误";
		}
		cout << status << endl;
	}
	system("pause");
	system("cls");
}


void  Student::CancelOrder() {
	//取消预约
	OrderFile orderfile;

	if (orderfile.order_num == 0) {
		cout << "无预约记录" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "审核中与预约成功的记录可以取消，请输入要取消的记录" << endl;

	vector<int>v;
	int index = 1;
	for (int i = 0; i < orderfile.order_num; i++) {
		if (atoi(orderfile.m_order[i]["stu_id"].c_str()) == this->student_id) {
			if (orderfile.m_order[i]["status"] == "1" || orderfile.m_order[i]["status"] == "2") {
				v.push_back(i);
				cout << index++ << "  ";
				cout << "预约时间:周" << orderfile.m_order[i]["week"] << (orderfile.m_order[i]["interval"] == "1" ? "上午" : "下午")
					<< "  机房：" << orderfile.m_order[i]["room_id"]
					<< "  预约人id：" << orderfile.m_order[i]["stu_id"]
					<< "  预约人姓名：" << orderfile.m_order[i]["stu_name"];
				string status = "  状态：";
				if (orderfile.m_order[i]["status"] == "1") {
					status += "审核中";
				}
				else if (orderfile.m_order[i]["status"] == "2") {
					status += "已预约";
				}
				cout << status << endl;
			}
		}
	}
	cout << "请选择要取消的记录，0代表返回" << endl;
	int select = 0;
	while (true) {
		cin >> select;
		if (select >= 0 && select <= v.size()) {
			if (select == 0) {
				break;
			}
			else {
				orderfile.m_order[v[select - 1]]["status"] = "0";
				orderfile.UpdateOrder();
				cout << "已取消预约" << endl;
				break;
			}
		}
		cout << "输入有误，重新输入" << endl;
	}
	system("pause");
	system("cls");
}


Student::Student() {

}

Student::Student(int student_id, string name, string password) {
	this->student_id = student_id;
	this->name_ = name;
	this->password_ = password;

	ifstream ifs;
	ifs.open(ROOM_FILE, ios::in);

	Room room;
	while (ifs >> room.room_id_ && ifs >> room.room_capacity_) {
		this->v_room.push_back(room);
	}
	ifs.close();
}
Student::~Student() {

}

