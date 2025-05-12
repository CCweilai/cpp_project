#include<stdio.h>
#include<iostream>
#include"worker_manager.h"
#include"worker.h"
#include"employee.h"
#include"manager.h"
#include"boss.h"

using namespace std;

int main() {

	////test
	//Worker * worker = nullptr;
	//worker = new Employee(1, "张三", 1);

	//worker->ShowInfo();
	//delete worker;
	//worker = new Manager(2, "李四", 2);

	//worker->ShowInfo();
	//delete worker;
	//worker = new Boss(3, "王五", 3);

	//worker->ShowInfo();
	//delete worker;

	WorkerManager workermanager;

	/*workermanager.ShowMenu();*/

	int choice = 0;

	while (true) {
		workermanager.ShowMenu();

		cout << "please input your choice" << endl;
		cin >> choice;

		switch (choice) {
		case 0:
			// quit system
			workermanager.ExitSystem();
			break;
		case 1:
			// add worker
			workermanager.AddWorker();
			break;
		case 2:
			// show worker
			workermanager.ShowWorker();
			break;
		case 3:
			// delete worker
			workermanager.DeleteWorker();
			break;
		case 4:
			// alter worker
			workermanager.ModifyWorker();
			break;
		case 5:
			// select worker
			workermanager.FindWorker();
			break;
		case 6:
			//sort worker
			workermanager.SortWorker();
			break;
		case 7:
			// clear file
			workermanager.CleanFile();
			break;
		default:
			system("cls");
			break;
		}
	}
	/*cout << "主函数" << endl;*/

	system("pause");

	return 0;

}