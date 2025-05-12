#include<iostream>

#include"student.h"

void Student::OpenMenu() {
	//ѧ���򿪲˵�ʵ��
	cout << "��ӭѧ����" << this->name_ << "��¼��" << endl;
	cout << "1.����ԤԼ" << endl;
	cout << "2.�鿴�ҵ�ԤԼ" << endl;
	cout << "3.�鿴����ԤԼ" << endl;
	cout << "4.ȡ��ԤԼ" << endl;
	cout << "0.ע����¼" << endl;
}


void  Student::ApplyOrder() {
	//����ԤԼ
	cout << "��������ʱ��Ϊ��һ������!" << endl;
	cout << "��ѡ����ҪԤԼ��ʱ���" << endl;
	cout << "1.��һ 2.�ܶ� 3.���� 4.���� 5.����" << endl;
	int week;
	int interval;
	int room;
	while (true) {
		cin >> week;
		if (week >= 1 && week <= 5) {
			break;
		}
		cout << "������������������" << endl;
	}
	cout << "1.���� 2.����" << endl;
	while (true) {
		cin >> interval;
		if (interval == 1 || interval == 2) {
			break;
		}
		cout << "������������������" << endl;
	}
	cout << "��ѡ�����" << endl;
	cout << "1�Ż���������" << this->v_room[0].room_capacity_ << endl;
	cout << "2�Ż���������" << this->v_room[1].room_capacity_ << endl;
	cout << "3�Ż���������" << this->v_room[2].room_capacity_ << endl;
	while (true) {
		cin >> room;
		if (room >= 1 || room <= 3) {
			break;
		}
		cout << "������������������" << endl;
	}
	cout << "ԤԼ�ɹ��������..." << endl;

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
	//�鿴�Լ���ԤԼ

	OrderFile orderfile;
	if (orderfile.order_num == 0) {
		cout << "��ԤԼ��¼" << endl;
		system("pause");
		system("cls");
		return;
	}
	for (int i = 0; i < orderfile.order_num; i++) {
		if (atoi(orderfile.m_order[i]["stu_id"].c_str())== this->student_id) {
			cout << "ԤԼʱ��:��" << orderfile.m_order[i]["week"] << (orderfile.m_order[i]["interval"] == "1" ? "����" : "����")
				<< "  ������" << orderfile.m_order[i]["room_id"]
				<< "  ԤԼ��id��" << orderfile.m_order[i]["stu_id"]
				<< "  ԤԼ��������" << orderfile.m_order[i]["stu_name"];
			string status = "״̬��";
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
	}
	system("pause");
	system("cls");
}


void  Student::ShowAllOrder() {
	//�鿴����ԤԼ

	OrderFile orderfile;
	if (orderfile.order_num == 0) {
		cout << "��ԤԼ��¼" << endl;
		system("pause");
		system("cls");
		return;
	}
	for (int i = 0; i < orderfile.order_num; i++) {
		cout << "ԤԼʱ��:��" << orderfile.m_order[i]["week"] << (orderfile.m_order[i]["interval"] == "1"?"����":"����")
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


void  Student::CancelOrder() {
	//ȡ��ԤԼ
	OrderFile orderfile;

	if (orderfile.order_num == 0) {
		cout << "��ԤԼ��¼" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "�������ԤԼ�ɹ��ļ�¼����ȡ����������Ҫȡ���ļ�¼" << endl;

	vector<int>v;
	int index = 1;
	for (int i = 0; i < orderfile.order_num; i++) {
		if (atoi(orderfile.m_order[i]["stu_id"].c_str()) == this->student_id) {
			if (orderfile.m_order[i]["status"] == "1" || orderfile.m_order[i]["status"] == "2") {
				v.push_back(i);
				cout << index++ << "  ";
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
				cout << status << endl;
			}
		}
	}
	cout << "��ѡ��Ҫȡ���ļ�¼��0������" << endl;
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
				cout << "��ȡ��ԤԼ" << endl;
				break;
			}
		}
		cout << "����������������" << endl;
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

