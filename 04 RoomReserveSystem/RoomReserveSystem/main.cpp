#include<iostream>
#include<fstream>

#include"global_file.h"
#include"identity.h"
#include"student.h"
#include"teacher.h"
#include"admin.h"

using namespace std;


void AdminMenu(Identity * & admin) {//���ù���Ա�Ӳ˵�
	while (true) {
		admin->OpenMenu();//�������麯��������ָ����������ʵ��
		Admin* adm = (Admin*)admin; //����ָ��תΪ���࣬���Ե�������ĺ���u

		int select=0;
		cout << "���������ѡ��" << endl;
		cin >> select;
		if (select == 1) {//����˺�
			adm->AddPerson();
		}
		else if (select == 2) {//�鿴�˺�
			adm->ShowPerson();

		}
		else if (select == 3) {//�鿴����
			adm->ShowRoom();

		}
		else if (select == 4) {//���ԤԼ
			adm->CleanOrder();

		}
		else{//ע��ģ��
			delete admin;
			cout << "ע���ɹ�" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
}

void StudentMenu(Identity*& student) {//����ѧ���Ӳ˵�
	while (true) {
		student->OpenMenu();//�������麯��������ָ����������ʵ��
		Student* stu = (Student*)student; //����ָ��תΪ���࣬���Ե�������ĺ���u

		int select = 0;
		cout << "���������ѡ��" << endl;
		cin >> select;
		if (select == 1) {//����ԤԼ
			stu->ApplyOrder();
		}
		else if (select == 2) {//�鿴�ҵ�ԤԼ
			stu->ShowMyOrder();
		}
		else if (select == 3) {//�鿴����ԤԼ
			stu->ShowAllOrder();
		}
		else if (select == 4) {//ȡ��ԤԼ
			stu->CancelOrder();
		}
		else {//ע��ģ��
			delete student;
			cout << "ע���ɹ�" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
}

void TeacherMenu(Identity*& teacher) {//���ý�ʦ�Ӳ˵�
	while (true) {
		teacher->OpenMenu();//�������麯��������ָ����������ʵ��
		Teacher* tch = (Teacher*)teacher; //����ָ��תΪ���࣬���Ե�������ĺ���u

		int select = 0;
		cout << "���������ѡ��" << endl;
		cin >> select;
		if (select == 1) {//�鿴ԤԼ
			tch->ShowAllOrder();
		}
		else if (select == 2) {//���ԤԼ
			tch->VaildOrder();
		}
		else {//ע��ģ��
			delete teacher;
			cout << "ע���ɹ�" << endl;
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
		cout << "��¼�ļ�������" << endl;
		ifs.close();
		return;
	}

	int id = 0,fid;
	string name,fname;
	string password,fpassword;

	if (type == 1) {//ѧ����¼
		cout << "���������ѧ��:" << endl;
		cin >> id;
		cout << "�������������" << endl;
		cin >> name;
		cout << "�������������:" << endl;
		cin >> password;
		while (ifs >> fid && ifs >> fname && ifs >> fpassword) {
			if (id == fid && name == fname && password == fpassword) {
				cout << "ѧ����֤��¼�ɹ�" << endl;
				system("pause");
				system("cls");
				person = new Student(id, name, password);
				StudentMenu(person);//����ѧ���ӽ���
				return;
			}
		}
	}
	else if (type == 2) {//��ʦ��¼
		cout << "���������ְ����" << endl;
		cin >> id;
		cout << "�������������" << endl;
		cin >> name;
		cout << "�������������:" << endl;
		cin >> password;
		while (ifs >> fid && ifs >> fname && ifs >> fpassword) {
			if (id == fid && name == fname && password == fpassword) {
				cout << "��ʦ��֤��¼�ɹ�" << endl;
				system("pause");
				system("cls");
				person = new Teacher(id, name, password);
				TeacherMenu(person);
				return;
			}
		}
	}
	else if (type == 3) {//����Ա��¼
		//��¼��������µ��˺ŵ�¼
		cout << "��������Ĺ���Ա���" << endl;
		cin >> id;
		cout << "�������������" << endl;
		cin >> name;
		cout << "�������������:" << endl;
		cin >> password;
		while (ifs >> fid && ifs >> fname && ifs >> fpassword) {
			if (id == fid && name == fname && password == fpassword) {
				cout << "����Ա��֤��¼�ɹ�" << endl;
				system("pause");
				system("cls");
				person = new Admin(id, name, password);
				AdminMenu(person);//�������Ա�ӽ���
				return;
			}
		}
	}
	cout << "��֤��¼ʧ��" << endl;

	system("pause");
	system("cls");
	return;
}

int main() {
	//�ռ�(������ԤԼϵͳ
	//�˵�
	int select;
	while (true) {
		cout << "*****************����ԤԼϵͳ*********" << endl;
		cout << "��ѡ��������" << endl;
		cout << "1.ѧ������" << endl;
		cout << "2.��   ʦ" << endl;
		cout << "3.����Ա" << endl;
		cout << "0.�˳�ϵͳ" << endl;

		cout << "�������ѡ��" << endl;
		cin >> select;
		switch (select) {
		case 1://ѧ������
			Login(STUDENT_FILE, 1);
			break;
		case 2://
			Login(TEACHER_FILE, 2);
			break;
		case 3:
			Login(ADMIN_FILE, 3);
			break;
		case 0:
			cout << "��ӭ�´�ʹ��ԤԼϵͳ" << endl;
			system("pause");
			return 0;
			break;
		default:
			cout << "��������" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
	return 0;
}