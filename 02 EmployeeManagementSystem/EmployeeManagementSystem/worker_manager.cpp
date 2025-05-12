#include"worker_manager.h"


WorkerManager::WorkerManager() {

	// file 不存在

	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	if (!ifs.is_open()) {
		//文件不存在
		cout << "文件不存在" << endl;
		this->num_worker_ = 0;
		this->worker_array_ = nullptr;
		this->file_is_empty = true;
		ifs.close();
		return;
	}
	// 文件存在，无数据

	char ch;
	ifs >> ch;
	if (ifs.eof()) {
		//文件为空
		cout << "文件为空" << endl;
		this->num_worker_ = 0;
		this->worker_array_ = nullptr;
		this->file_is_empty = true;
		ifs.close();
		return;
	}

	// 文件存在 有数据
	int num = this->GetWorkerNum();
	cout << "当前职工数为：" << num << endl;
	this->num_worker_ = num;
	this->worker_array_ = new Worker * [this->num_worker_];
	this->InitWorkerArray();

	/*for (int i = 0; i < this->num_worker_; i++) {
		cout << "worker id:" << this->worker_array_[i]->id_
			<< "  worker name:" << this->worker_array_[i]->name_
			<< "  worker department name:" << this->worker_array_[i]->GetDepartmentName()
			<< endl;
	}*/
}


void WorkerManager::ShowMenu(){
	cout <<"*********************************************"<< endl;
	cout << "********欢迎使用职工管理系统******************" << endl;
	cout << "*********0、退出管理系统*****************" << endl;
	cout << "*********1、增加职工信息*****************" << endl;
	cout << "*********2、显示职工信息*****************" << endl;
	cout << "*********3、删除离职职工*****************" << endl;
	cout << "*********4、修改职工信息*****************" << endl;
	cout << "*********5、查找职工信息*****************" << endl;
	cout << "*********6、按照编号排序*****************" << endl;
	cout << "*********7、清空所有文档*****************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}

void WorkerManager::ExitSystem() {
	cout << "bye" << endl;
	system("pause");
	exit(0);
}


void WorkerManager::AddWorker() {
	cout << "input worker number" << endl;
	int add_worker_num = 0;

	cin >> add_worker_num;

	if (add_worker_num > 0) {
		//add worker
		// 计算添加新空间
		int new_size = this->num_worker_ + add_worker_num;

		/*Worker ** new_space = new Worker* [new_size];*/
		Worker** new_space = new Worker * [this->num_worker_ + add_worker_num];
		// 如果使用new_size 后面会报一个缓存区溢出的错误,具体原因可能是编译器无法识别new_size,不知道两个数组的具体大小

		if (this->worker_array_ != nullptr) {
			for (int i = 0; i < this->num_worker_; i++) {
				new_space[i] = this->worker_array_[i];
			}
		}
		for (int i = 0; i < add_worker_num; i++) {
			int id;
			string name;
			int department_id;
			cout << "请输入第" << i + 1 << "个新职工编号：" << endl;
			cin >> id;
			cout << "请输入第" << i + 1 << "个新职工姓名：" << endl;
			cin >> name;
			cout << "请选择第" << i + 1 << "个新职工岗位：" << endl;
			cout << "1、employee 2、manager 3、boss" << endl;
			cin >> department_id;

			Worker* worker = nullptr;

			switch (department_id) {
			case 1:
				worker = new Employee(id, name, department_id);
				break;
			case 2:
				worker = new Manager(id, name, department_id);
				break;
			case 3:
				worker = new Boss(id, name, department_id);
				break;
			default:
				break;
			}
			new_space[this->num_worker_ + i] = worker;
		}
		// 释放原有的空间
		delete[] this->worker_array_;

		// 更改新空间指向

		this->worker_array_ = new_space;
		// 更改新人数

		this->num_worker_ = new_size;

		this->file_is_empty = false;
		cout << "成功添加" << add_worker_num << "个职工" << endl;


		this->SaveFile();
	}
	else {
		cout << "输入数据有误" << endl;
		// break
	}
}

void WorkerManager::SaveFile() {
	ofstream ofs;
	ofs.open(FILENAME, ios::out);

	for (int i = 0; i < this->num_worker_; i++) {
		ofs << this->worker_array_[i]->id_ << " "
			<< this->worker_array_[i]->name_ << " "
			<< this->worker_array_[i]->department_id_ << endl;
	}
	ofs.close();
}


int WorkerManager::GetWorkerNum() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	string department_id;

	int num = 0;

	while (ifs >> id && ifs >> name && ifs >> department_id) {
		num++;
	}
	ifs.close();
	return num;
}

void WorkerManager::InitWorkerArray() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int department_id;

	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> department_id) {
		Worker* worker = nullptr;
		if (department_id == 1) {
			worker = new Employee(id, name, department_id);
		}
		else if (department_id == 2) {
			worker = new Manager(id, name, department_id);
		}
		else if (department_id == 3) {
			worker = new Boss(id, name, department_id);
		}
		else {
			cout << "data errow" << endl;
		}

		this->worker_array_[index] = worker;
		index++;
	}
	ifs.close();
}

void WorkerManager::ShowWorker() {

	if (this->file_is_empty) {
		cout << "file is empty or no data" << endl;
	}
	else {
		for (int i = 0; i < this->num_worker_; i++) {
			this->worker_array_[i]->ShowInfo();
		}
	}
	system("pause");
	system("cls");
}

int WorkerManager::WorkerIsExist(int id) {
	int index = -1;
	for (int i = 0; i < this->num_worker_; i++) {
		if (this->worker_array_[i]->id_ == id) {
			index = i;
			break;
		}
	}
	return index;
}

void WorkerManager::DeleteWorker() {
	if (this->file_is_empty) {
		cout << "no data" << endl;
	}
	else {
		int delete_worker_id;
		cout << "请输入你想删除的职工编号" << endl;

		cin >> delete_worker_id;
		int index = this->WorkerIsExist(delete_worker_id);

		if (index == -1) {
			cout << "你要删除的职工不存在" << endl;
		}
		else {
			for (int i = index; i < this->num_worker_-1; i++) {
				this->worker_array_[i] = this->worker_array_[i + 1];
			}
			this->num_worker_--;
			this->SaveFile();
			cout << "成功删除" << endl;

		}
	}

	system("pause");
	system("cls");
}

void WorkerManager::ModifyWorker() {
	if (this->file_is_empty) {
		cout << "no data" << endl;
	}
	else {
		int modify_worker_id;
		cout << "请输入你想修改的职工编号" << endl;
		cin >> modify_worker_id;

		int index = this->WorkerIsExist(modify_worker_id);

		if (index == -1) {
			cout << "你要修改的职工不存在" << endl;
		}
		else {
			cout << "你要修改职工的信息:" << endl;
			this->worker_array_[index]->ShowInfo();
			cout << "请重新输入该职工信息" << endl;
			int id;
			string name;
			int department_id;
			cout << "请输入职工编号" << endl;
			cin >> id;
			cout << "请输入姓名" << endl;
			cin >> name;
			cout << "请输入部门id" << endl;
			cout << "1.employee 2.manager 3.boss" << endl;
			cin >> department_id;
			Worker* worker = nullptr;

			switch (department_id) {
			case 1:
				worker = new Employee(id, name, department_id);
				break;
			case 2:
				worker = new Manager(id, name, department_id);
				break;
			case 3:
				worker = new Boss(id, name, department_id);
				break;
			default:
				break;
			}
			this->worker_array_[index] = worker;


			cout << "更改后的信息" << endl;
			this->worker_array_[index]->ShowInfo();
			this->SaveFile();
		}

	}
	 
	system("pause");
	system("cls");
}
void WorkerManager::FindWorker() {
	if (this->file_is_empty) {
		cout << "no data" << endl;
	}
	else {
		int select;
		cout << "请选择查询的方式：1、根据编号查 2、根据名字查" << endl;
		cin >> select;
		if (select == 1) {
			int find_id;
			cout << "请输入要查询的编号" << endl;
			cin >> find_id;
			int index = this->WorkerIsExist(find_id);
			if (index == -1) {
				cout << "查无此人" << endl;
			}
			else {
				this->worker_array_[index]->ShowInfo();
			}
		}
		else if (select == 2) {
			string find_name;
			cout << "请输入要查询人的姓名" << endl;
			cin >> find_name;
			bool flag = false;
			for (int i = 0; i < this->num_worker_; i++) {
				if (this->worker_array_[i]->name_ == find_name) {
					cout << "查找成功" << endl;
					this->worker_array_[i]->ShowInfo();
					flag = true;
				}
			}
			if (flag == false) {
				cout << "没有找到" << endl;
			}
		}
	}

	system("pause");
	system("cls");
}

void WorkerManager::SortWorker() {
	if (this->file_is_empty) {
		cout << "no data" << endl;
		system("pause");
		system("cls");
	}
	else {
		cout << "请选择排序的方式" << endl;
		cout << "1.升序  2.降序" << endl;
		int select = 0;
		cin >> select;
		for (int i = 0; i < this->num_worker_; i++) {
			int MinorMax = i;
			for (int j = i + 1; j < this->num_worker_; j++) {
				if (select == 1) {
					if (this->worker_array_[MinorMax]->id_ > this->worker_array_[j]->id_) {
						MinorMax = j;
					}
				}
				else {
					if (this->worker_array_[MinorMax]->id_ < this->worker_array_[j]->id_) {
						MinorMax = j;
					}

				}


			}
			
			if (i != MinorMax) {
				Worker* temp = this->worker_array_[i];
				this->worker_array_[i] = this->worker_array_[MinorMax];
				this->worker_array_[MinorMax] = temp;
			}

		}
		cout << "排序成功,结果为：" << endl;
		this->ShowWorker();
	}
}

void WorkerManager::CleanFile(){
	cout << "确认清空？" << endl;
	cout << "1.确认 2.取消" << endl;
	int select = 0;
	cin >> select;
	if (select == 1) {
		ofstream ofs(FILENAME, ios::trunc);
		ofs.close();
		if (this->worker_array_ != nullptr) {
			for (int i = 0; i < this->num_worker_; i++) {
				if (this->worker_array_[i] != nullptr) {
					delete this->worker_array_[i];
				}
			}
			this->num_worker_ = 0;
			delete[] this->worker_array_;
			this->worker_array_ = nullptr;
			this->file_is_empty = true;
		}
		cout << "清空完毕" << endl;
	}
	system("pause");
	system("cls");
	
}


WorkerManager::~WorkerManager() {
	if (this->worker_array_ != nullptr) {
		for (int i = 0; i < this->num_worker_; i++) {
			if (this->worker_array_[i] != nullptr) {
				delete this->worker_array_[i];
			}
			delete[] this->worker_array_;
			this->worker_array_ = nullptr;
		}
		this->file_is_empty = true;
	}
}