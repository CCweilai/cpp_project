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
	cout << "欢迎管理员：" << this->name_ << "登录！" << endl;
	cout << "1.添加账号" << endl;
	cout << "2.查看账号" << endl;
	cout << "3.查看机房" << endl;
	cout << "4.清空预约" << endl;
	cout << "0.注销登录" << endl;
}
//添加账号
void Admin::AddPerson() {
	cout << "请输入添加的账号类型" << endl;
	cout << "1、添加学生" << endl;
	cout << "2、添加老师" << endl;
	cout << "3、添加管理员" << endl;

	string filename;
	string tip;
	string errow_tip;
	ofstream ofs;

	int select = 0;
	cin >> select;
	if (select == 1) {
		filename = STUDENT_FILE;
		tip = "请输入学号：";
		errow_tip = "学号重复,请重新输入";
	}
	else if (select == 2) {
		filename = TEACHER_FILE;
		tip = "请输入职工号：";
		errow_tip = "职工号重复,请重新输入";
	}
	else if (select == 3) {
		filename = ADMIN_FILE;
		tip = "请输入管理员编号：";
		errow_tip = "管理员编号重复,请重新输入";
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

	cout << "请输入姓名" << endl;
	cin >> name;
	cout << "请输入密码" << endl;
	cin >> password;

	ofs << id << " " << name << " " << password << endl;
	cout << "添加成功" << endl;
	this->InitVector();

	system("pause");
	system("cls");

	ofs.close();
}


void PrintStudent(Student student) {
	cout << "学号：" << student.name_ << " 姓名：" << student.name_ << " 密码：" << student.password_ << endl;
}
void PrintTeacher(Teacher teacher) {
	cout << "职工号：" << teacher.name_ << " 姓名：" << teacher.name_ << " 密码：" << teacher.password_ << endl;
}
void PrintAdmin(Admin admin) {
	cout << "编号：" << admin.name_ << " 姓名：" << admin.name_ << " 密码：" << admin.password_ << endl;
}
//查看账号
void Admin::ShowPerson() {
	cout << "请选择要查看的内容" << endl;
	cout << "1.查看所有学生" << endl;
	cout << "2.查看所有老师" << endl;
	cout << "3.查看所有管理员" << endl;
	int select;
	cin >> select;
	if (select == 1) {
		cout << "所有学生信息如下：" << endl;
		for_each(this->v_student.begin(), this->v_student.end(), PrintStudent);
	}
	else if (select == 2) {
		cout << "所有老师信息如下：" << endl;
		for_each(this->v_teacher.begin(), this->v_teacher.end(), PrintTeacher);

	}
	else if(select==3){
		cout << "所有管理员信息如下：" << endl;
		for_each(this->v_admin.begin(), this->v_admin.end(), PrintAdmin);

	}
	else {
		cout << "输入错误" << endl;
	}
	system("pause");
	system("cls");

}

//查看空间信息
void Admin::ShowRoom() {
	cout << "机房信息如下所示：" << endl;
	for (vector<Room>::iterator it = this->v_room.begin(); it != this->v_room.end(); it++) {
		cout << "机房编号:" << it->room_id_ << "  机房容量" << it->room_capacity_ << endl;
	}
	system("pause");
	system("cls");
}

//清空预约记录
void Admin::CleanOrder() {

	ofstream ofs(ORDER_FILE, ios::trunc);
	ofs.close();

	cout << "清空成功" << endl;
	system("pause");
	system("cls");

}

void Admin::InitVector() {
	ifstream ifs;
	this->v_student.clear();
	this->v_teacher.clear();
	this->v_admin.clear();
	this->v_room.clear();

	//学生
	ifs.open(STUDENT_FILE, ios::in);
	if (!ifs.is_open()) {
		cout << "学生文件读取失败" << endl;
		/*return;*/
	}
	else {
		Student student;
		while (ifs >> student.student_id && ifs >> student.name_ && ifs >> student.password_) {
			this->v_student.push_back(student);
		}
		cout << "当前学生数量为：" << this->v_student.size() << endl;
	}
	ifs.close();

	//老师
	ifs.open(TEACHER_FILE, ios::in);
	if (!ifs.is_open()) {
		cout << "老师文件读取失败" << endl;
		/*return;*/
	}
	else {
		Teacher teacher;
		while (ifs >> teacher.teacher_id && ifs >> teacher.name_ && ifs >> teacher.password_) {
			this->v_teacher.push_back(teacher);
		}
		cout << "当前老师数量为：" << this->v_teacher.size() << endl;
	}
	ifs.close();

	//管理员
	ifs.open(ADMIN_FILE, ios::in);
	if (!ifs.is_open()) {
		cout << "管理员文件读取失败" << endl;
		/*return;*/
	}
	else {
		Admin admin;
		while (ifs >> admin.admin_id && ifs >> admin.name_ && ifs >> admin.password_) {
			this->v_admin.push_back(admin);
		}
		cout << "当前管理员数量为：" << this->v_admin.size() << endl;
	}
	ifs.close();
	//机房
	ifs.open(ROOM_FILE, ios::in);
	if (!ifs.is_open()) {
		cout << "机房文件读取失败" << endl;
		/*return;*/
	}
	else {
		Room room;
		while (ifs >> room.room_id_ && ifs >> room.room_capacity_) {
			this->v_room.push_back(room);
		}
		cout << "当前机房数量为：" << this->v_room.size() << endl;
	}
	ifs.close();
}

bool Admin::CheckRepeat(int id, int type) {
	if (type == 1) {//学生
		for (vector<Student>::iterator it = this->v_student.begin(); it != this->v_student.end(); it++) {
			if (it->student_id == id) {
				return true;
			}
		}
	}
	else if (type == 2) {//老师
		for (vector<Teacher>::iterator it = this->v_teacher.begin(); it != this->v_teacher.end(); it++) {
			if (it->teacher_id == id) {
				return true;
			}
		}
	}
	else if (type == 3) {//管理员
		for (vector<Admin>::iterator it = this->v_admin.begin(); it != this->v_admin.end(); it++) {
			if (it->admin_id == id) {
				return true;
			}
		}
	}
	return false;
}