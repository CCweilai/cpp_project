#include"teacher.h"

Teacher::Teacher() {

}
Teacher::Teacher(int teacher_id, string name, string password) {
	this->teacher_id = teacher_id;
	this->name_ = name;
	this->password_ = password;
}
Teacher::~Teacher() {

}
void Teacher::OpenMenu() {
	cout << "欢迎" << this->name_ << "登录！" << endl;
	cout << "1.查看所有预约" << endl;
	cout << "2.审核预约" << endl;
	cout << "0.注销登录" << endl;
}




void Teacher::ShowAllOrder() {
	//查看所有预约
	OrderFile orderfile;
	if (orderfile.order_num == 0) {
		cout << "无预约记录" << endl;
		system("pause");
		system("cls");
		return;
	}
	for (int i = 0; i < orderfile.order_num; i++) {
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



void Teacher::VaildOrder() {
	//审核预约
	OrderFile orderfile;

	if (orderfile.order_num == 0) {
		cout << "无预约记录" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "待审核的记录如下，请逐条审核" << endl;

	vector<int>v;
	int index = 1;
	for (int i = 0; i < orderfile.order_num; i++) {
		if (orderfile.m_order[i]["status"] == "1") {
			v.push_back(i);
			cout << index++ << "  ";
			cout << "预约时间:周" << orderfile.m_order[i]["week"] << (orderfile.m_order[i]["interval"] == "1" ? "上午" : "下午")
				<< "  机房：" << orderfile.m_order[i]["room_id"]
				<< "  预约人id：" << orderfile.m_order[i]["stu_id"]
				<< "  预约人姓名：" << orderfile.m_order[i]["stu_name"]
				<< " 状态：审核中" << endl;
		}
	}
	cout << "请选择要审核的记录，0代表返回" << endl;
	int select = 0;
	int ret = 0;
	while (true) {
		cin >> select;
		if (select >= 0 && select <= v.size()) {
			if (select == 0) {
				break;
			}
			else {
				cout << "请输入审核结果" << endl;
				cout << "1.通过" << endl;
				cout << "2.不通过" << endl;
				cin >> ret;
				if (ret == 1) {
					orderfile.m_order[v[select - 1]]["status"] = "2";
				}
				else {
					orderfile.m_order[v[select - 1]]["status"] = "-1";
				}
				orderfile.UpdateOrder();
				cout << "已完成审核" << endl;
				break;
			}
		}
		cout << "输入有误，重新输入" << endl;
	}
	system("pause");
	system("cls");
}