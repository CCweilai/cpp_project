#pragma once  

#include<iostream>
#include<fstream>

#include"worker.h"
#include"employee.h"
#include"manager.h"
#include"boss.h"


#define FILENAME "worker_file.txt"




using namespace std;


class WorkerManager {
public:
	//number of worker
	int num_worker_;
	// worker array
	Worker** worker_array_;

	bool file_is_empty;

	WorkerManager();

	void ShowMenu();
	void ExitSystem();

	void AddWorker();
	void SaveFile();

	int GetWorkerNum();

	void InitWorkerArray();
	void ShowWorker();

	int WorkerIsExist(int id);
	void DeleteWorker();
	void ModifyWorker();

	void FindWorker();

	void SortWorker();

	void CleanFile();

	~WorkerManager();
};


