#include"worker_manager.h"


WorkerManager::WorkerManager() {

	// file ������

	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	if (!ifs.is_open()) {
		//�ļ�������
		cout << "�ļ�������" << endl;
		this->num_worker_ = 0;
		this->worker_array_ = nullptr;
		this->file_is_empty = true;
		ifs.close();
		return;
	}
	// �ļ����ڣ�������

	char ch;
	ifs >> ch;
	if (ifs.eof()) {
		//�ļ�Ϊ��
		cout << "�ļ�Ϊ��" << endl;
		this->num_worker_ = 0;
		this->worker_array_ = nullptr;
		this->file_is_empty = true;
		ifs.close();
		return;
	}

	// �ļ����� ������
	int num = this->GetWorkerNum();
	cout << "��ǰְ����Ϊ��" << num << endl;
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
	cout << "********��ӭʹ��ְ������ϵͳ******************" << endl;
	cout << "*********0���˳�����ϵͳ*****************" << endl;
	cout << "*********1������ְ����Ϣ*****************" << endl;
	cout << "*********2����ʾְ����Ϣ*****************" << endl;
	cout << "*********3��ɾ����ְְ��*****************" << endl;
	cout << "*********4���޸�ְ����Ϣ*****************" << endl;
	cout << "*********5������ְ����Ϣ*****************" << endl;
	cout << "*********6�����ձ������*****************" << endl;
	cout << "*********7����������ĵ�*****************" << endl;
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
		// ��������¿ռ�
		int new_size = this->num_worker_ + add_worker_num;

		/*Worker ** new_space = new Worker* [new_size];*/
		Worker** new_space = new Worker * [this->num_worker_ + add_worker_num];
		// ���ʹ��new_size ����ᱨһ������������Ĵ���,����ԭ������Ǳ������޷�ʶ��new_size,��֪����������ľ����С

		if (this->worker_array_ != nullptr) {
			for (int i = 0; i < this->num_worker_; i++) {
				new_space[i] = this->worker_array_[i];
			}
		}
		for (int i = 0; i < add_worker_num; i++) {
			int id;
			string name;
			int department_id;
			cout << "�������" << i + 1 << "����ְ����ţ�" << endl;
			cin >> id;
			cout << "�������" << i + 1 << "����ְ��������" << endl;
			cin >> name;
			cout << "��ѡ���" << i + 1 << "����ְ����λ��" << endl;
			cout << "1��employee 2��manager 3��boss" << endl;
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
		// �ͷ�ԭ�еĿռ�
		delete[] this->worker_array_;

		// �����¿ռ�ָ��

		this->worker_array_ = new_space;
		// ����������

		this->num_worker_ = new_size;

		this->file_is_empty = false;
		cout << "�ɹ����" << add_worker_num << "��ְ��" << endl;


		this->SaveFile();
	}
	else {
		cout << "������������" << endl;
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
		cout << "����������ɾ����ְ�����" << endl;

		cin >> delete_worker_id;
		int index = this->WorkerIsExist(delete_worker_id);

		if (index == -1) {
			cout << "��Ҫɾ����ְ��������" << endl;
		}
		else {
			for (int i = index; i < this->num_worker_-1; i++) {
				this->worker_array_[i] = this->worker_array_[i + 1];
			}
			this->num_worker_--;
			this->SaveFile();
			cout << "�ɹ�ɾ��" << endl;

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
		cout << "�����������޸ĵ�ְ�����" << endl;
		cin >> modify_worker_id;

		int index = this->WorkerIsExist(modify_worker_id);

		if (index == -1) {
			cout << "��Ҫ�޸ĵ�ְ��������" << endl;
		}
		else {
			cout << "��Ҫ�޸�ְ������Ϣ:" << endl;
			this->worker_array_[index]->ShowInfo();
			cout << "�����������ְ����Ϣ" << endl;
			int id;
			string name;
			int department_id;
			cout << "������ְ�����" << endl;
			cin >> id;
			cout << "����������" << endl;
			cin >> name;
			cout << "�����벿��id" << endl;
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


			cout << "���ĺ����Ϣ" << endl;
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
		cout << "��ѡ���ѯ�ķ�ʽ��1�����ݱ�Ų� 2���������ֲ�" << endl;
		cin >> select;
		if (select == 1) {
			int find_id;
			cout << "������Ҫ��ѯ�ı��" << endl;
			cin >> find_id;
			int index = this->WorkerIsExist(find_id);
			if (index == -1) {
				cout << "���޴���" << endl;
			}
			else {
				this->worker_array_[index]->ShowInfo();
			}
		}
		else if (select == 2) {
			string find_name;
			cout << "������Ҫ��ѯ�˵�����" << endl;
			cin >> find_name;
			bool flag = false;
			for (int i = 0; i < this->num_worker_; i++) {
				if (this->worker_array_[i]->name_ == find_name) {
					cout << "���ҳɹ�" << endl;
					this->worker_array_[i]->ShowInfo();
					flag = true;
				}
			}
			if (flag == false) {
				cout << "û���ҵ�" << endl;
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
		cout << "��ѡ������ķ�ʽ" << endl;
		cout << "1.����  2.����" << endl;
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
		cout << "����ɹ�,���Ϊ��" << endl;
		this->ShowWorker();
	}
}

void WorkerManager::CleanFile(){
	cout << "ȷ����գ�" << endl;
	cout << "1.ȷ�� 2.ȡ��" << endl;
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
		cout << "������" << endl;
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