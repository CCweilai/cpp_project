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
	cout << "��ӭ" << this->name_ << "��¼��" << endl;
	cout << "1.�鿴����ԤԼ" << endl;
	cout << "2.���ԤԼ" << endl;
	cout << "0.ע����¼" << endl;
}




void Teacher::ShowAllOrder() {
	//�鿴����ԤԼ
	OrderFile orderfile;
	if (orderfile.order_num == 0) {
		cout << "��ԤԼ��¼" << endl;
		system("pause");
		system("cls");
		return;
	}
	for (int i = 0; i < orderfile.order_num; i++) {
		cout << "ԤԼʱ��:��" << orderfile.m_order[i]["week"] << (orderfile.m_order[i]["interval"] == "1" ? "����" : "����")
			<< "  ������" << orderfile.m_order[i]["room_id"]
			<< "  ԤԼ��id��" << orderfile.m_order[i]["stu_id"]
			<< "  ԤԼ��������" << orderfile.m_order[i]["stu_name"];
		string status = "  ״̬��";
		if (orderfile.m_order[i]["status"] == "1") {
			status += "�����";
		}
		else if (orderfile.m_order[i]["status"] == "2") {
			status += "��ԤԼ";

		}
		else if (orderfile.m_order[i]["status"] == "-1") {
			status += "ԤԼʧ��";

		}
		else if (orderfile.m_order[i]["status"] == "0") {
			status += "ȡ����ԤԼ";
		}
		else {
			status += "״̬����";
		}
		cout << status << endl;
	}
	system("pause");
	system("cls");
}



void Teacher::VaildOrder() {
	//���ԤԼ
	OrderFile orderfile;

	if (orderfile.order_num == 0) {
		cout << "��ԤԼ��¼" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "����˵ļ�¼���£����������" << endl;

	vector<int>v;
	int index = 1;
	for (int i = 0; i < orderfile.order_num; i++) {
		if (orderfile.m_order[i]["status"] == "1") {
			v.push_back(i);
			cout << index++ << "  ";
			cout << "ԤԼʱ��:��" << orderfile.m_order[i]["week"] << (orderfile.m_order[i]["interval"] == "1" ? "����" : "����")
				<< "  ������" << orderfile.m_order[i]["room_id"]
				<< "  ԤԼ��id��" << orderfile.m_order[i]["stu_id"]
				<< "  ԤԼ��������" << orderfile.m_order[i]["stu_name"]
				<< " ״̬�������" << endl;
		}
	}
	cout << "��ѡ��Ҫ��˵ļ�¼��0������" << endl;
	int select = 0;
	int ret = 0;
	while (true) {
		cin >> select;
		if (select >= 0 && select <= v.size()) {
			if (select == 0) {
				break;
			}
			else {
				cout << "��������˽��" << endl;
				cout << "1.ͨ��" << endl;
				cout << "2.��ͨ��" << endl;
				cin >> ret;
				if (ret == 1) {
					orderfile.m_order[v[select - 1]]["status"] = "2";
				}
				else {
					orderfile.m_order[v[select - 1]]["status"] = "-1";
				}
				orderfile.UpdateOrder();
				cout << "��������" << endl;
				break;
			}
		}
		cout << "����������������" << endl;
	}
	system("pause");
	system("cls");
}