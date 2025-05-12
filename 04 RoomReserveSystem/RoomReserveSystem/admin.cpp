#include"admin.h"


Admin::Admin() {

}
Admin::Admin(int admin_id, string name, string password) {
	this->admin_id = admin_id;
	this->name_ = name;
	this->password_ = password;

	this->InitVector();
}
Admin::~Admin() {

}

void Admin::OpenMenu() {
	cout << "��ӭ����Ա��" << this->name_ << "��¼��" << endl;
	cout << "1.����˺�" << endl;
	cout << "2.�鿴�˺�" << endl;
	cout << "3.�鿴����" << endl;
	cout << "4.���ԤԼ" << endl;
	cout << "0.ע����¼" << endl;
}
//����˺�
void Admin::AddPerson() {
	cout << "��������ӵ��˺�����" << endl;
	cout << "1�����ѧ��" << endl;
	cout << "2�������ʦ" << endl;
	cout << "3����ӹ���Ա" << endl;

	string filename;
	string tip;
	string errow_tip;
	ofstream ofs;

	int select = 0;
	cin >> select;
	if (select == 1) {
		filename = STUDENT_FILE;
		tip = "������ѧ�ţ�";
		errow_tip = "ѧ���ظ�,����������";
	}
	else if (select == 2) {
		filename = TEACHER_FILE;
		tip = "������ְ���ţ�";
		errow_tip = "ְ�����ظ�,����������";
	}
	else if (select == 3) {
		filename = ADMIN_FILE;
		tip = "���������Ա��ţ�";
		errow_tip = "����Ա����ظ�,����������";
	}

	ofs.open(filename, ios::out | ios::app);
	int id;
	string name;
	string password;

	
	while (true) {
		cout << tip << endl;
		cin >> id;
		if (this->CheckRepeat(id, select)) {
			cout << errow_tip << endl;
		}
		else {
			break;
		}
	}

	cout << "����������" << endl;
	cin >> name;
	cout << "����������" << endl;
	cin >> password;

	ofs << id << " " << name << " " << password << endl;
	cout << "��ӳɹ�" << endl;
	this->InitVector();

	system("pause");
	system("cls");

	ofs.close();
}


void PrintStudent(Student student) {
	cout << "ѧ�ţ�" << student.name_ << " ������" << student.name_ << " ���룺" << student.password_ << endl;
}
void PrintTeacher(Teacher teacher) {
	cout << "ְ���ţ�" << teacher.name_ << " ������" << teacher.name_ << " ���룺" << teacher.password_ << endl;
}
void PrintAdmin(Admin admin) {
	cout << "��ţ�" << admin.name_ << " ������" << admin.name_ << " ���룺" << admin.password_ << endl;
}
//�鿴�˺�
void Admin::ShowPerson() {
	cout << "��ѡ��Ҫ�鿴������" << endl;
	cout << "1.�鿴����ѧ��" << endl;
	cout << "2.�鿴������ʦ" << endl;
	cout << "3.�鿴���й���Ա" << endl;
	int select;
	cin >> select;
	if (select == 1) {
		cout << "����ѧ����Ϣ���£�" << endl;
		for_each(this->v_student.begin(), this->v_student.end(), PrintStudent);
	}
	else if (select == 2) {
		cout << "������ʦ��Ϣ���£�" << endl;
		for_each(this->v_teacher.begin(), this->v_teacher.end(), PrintTeacher);

	}
	else if(select==3){
		cout << "���й���Ա��Ϣ���£�" << endl;
		for_each(this->v_admin.begin(), this->v_admin.end(), PrintAdmin);

	}
	else {
		cout << "�������" << endl;
	}
	system("pause");
	system("cls");

}

//�鿴�ռ���Ϣ
void Admin::ShowRoom() {
	cout << "������Ϣ������ʾ��" << endl;
	for (vector<Room>::iterator it = this->v_room.begin(); it != this->v_room.end(); it++) {
		cout << "�������:" << it->room_id_ << "  ��������" << it->room_capacity_ << endl;
	}
	system("pause");
	system("cls");
}

//���ԤԼ��¼
void Admin::CleanOrder() {

	ofstream ofs(ORDER_FILE, ios::trunc);
	ofs.close();

	cout << "��ճɹ�" << endl;
	system("pause");
	system("cls");

}

void Admin::InitVector() {
	ifstream ifs;
	this->v_student.clear();
	this->v_teacher.clear();
	this->v_admin.clear();
	this->v_room.clear();

	//ѧ��
	ifs.open(STUDENT_FILE, ios::in);
	if (!ifs.is_open()) {
		cout << "ѧ���ļ���ȡʧ��" << endl;
		/*return;*/
	}
	else {
		Student student;
		while (ifs >> student.student_id && ifs >> student.name_ && ifs >> student.password_) {
			this->v_student.push_back(student);
		}
		cout << "��ǰѧ������Ϊ��" << this->v_student.size() << endl;
	}
	ifs.close();

	//��ʦ
	ifs.open(TEACHER_FILE, ios::in);
	if (!ifs.is_open()) {
		cout << "��ʦ�ļ���ȡʧ��" << endl;
		/*return;*/
	}
	else {
		Teacher teacher;
		while (ifs >> teacher.teacher_id && ifs >> teacher.name_ && ifs >> teacher.password_) {
			this->v_teacher.push_back(teacher);
		}
		cout << "��ǰ��ʦ����Ϊ��" << this->v_teacher.size() << endl;
	}
	ifs.close();

	//����Ա
	ifs.open(ADMIN_FILE, ios::in);
	if (!ifs.is_open()) {
		cout << "����Ա�ļ���ȡʧ��" << endl;
		/*return;*/
	}
	else {
		Admin admin;
		while (ifs >> admin.admin_id && ifs >> admin.name_ && ifs >> admin.password_) {
			this->v_admin.push_back(admin);
		}
		cout << "��ǰ����Ա����Ϊ��" << this->v_admin.size() << endl;
	}
	ifs.close();
	//����
	ifs.open(ROOM_FILE, ios::in);
	if (!ifs.is_open()) {
		cout << "�����ļ���ȡʧ��" << endl;
		/*return;*/
	}
	else {
		Room room;
		while (ifs >> room.room_id_ && ifs >> room.room_capacity_) {
			this->v_room.push_back(room);
		}
		cout << "��ǰ��������Ϊ��" << this->v_room.size() << endl;
	}
	ifs.close();
}

bool Admin::CheckRepeat(int id, int type) {
	if (type == 1) {//ѧ��
		for (vector<Student>::iterator it = this->v_student.begin(); it != this->v_student.end(); it++) {
			if (it->student_id == id) {
				return true;
			}
		}
	}
	else if (type == 2) {//��ʦ
		for (vector<Teacher>::iterator it = this->v_teacher.begin(); it != this->v_teacher.end(); it++) {
			if (it->teacher_id == id) {
				return true;
			}
		}
	}
	else if (type == 3) {//����Ա
		for (vector<Admin>::iterator it = this->v_admin.begin(); it != this->v_admin.end(); it++) {
			if (it->admin_id == id) {
				return true;
			}
		}
	}
	return false;
}