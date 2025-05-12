#include<iostream>
#include<string>

using namespace std;

#define MAX 1000

struct Person {
	// 联系人结构体 姓名、性别、年龄、电话、住址
	string m_Name;
	int m_Sex;
	int m_Age;
	string m_Phone;
	string m_Address;
};

struct AddressBooks {
	//通讯录结构体 联系人数组 联系人个数
	Person PersonArray[MAX];
	int m_Size=0;
};

int CheckPerson(AddressBooks * abs,string name) {
	//检测传入的人名是不是在通讯录中存在
	//遍历查找

	for (int i = 0; i < abs->m_Size; i++) {
		if (abs->PersonArray[i].m_Name == name) {
			//遍历返回索引 便于后续使用
			return i;
		}
	}
	return -1;
}
void DeleteAllPerson(AddressBooks* abs) {
	//逻辑上清空
	abs->m_Size = 0;
	cout << "通讯录已清空" << endl;
	system("pause");
	system("cls");
}
void ModifyPerson(AddressBooks *abs) {

	cout << "请输入你要修改的联系人" << endl;
	string name;
	cin >> name;
	int isExit = CheckPerson(abs, name);
	if (isExit == -1) {
		cout << "查无此人" << endl;
	}
	else {
		string name;
		int sex;
		int age;
		string phone, address;
		cout << "请重新输入姓名" << endl;
		cin >> name;
		abs->PersonArray[isExit].m_Name = name;
		cout << "请重新输入性别" << endl;
		cin >> sex;
		abs->PersonArray[isExit].m_Sex = sex;
		cout << "请重新输入年龄" << endl;
		cin >> age;
		abs->PersonArray[isExit].m_Age = age;
		cout << "请重新输入电话" << endl;
		cin >> phone;
		abs->PersonArray[isExit].m_Phone = phone;
		cout << "请重新输入地址" << endl;
		cin >> address;
		abs->PersonArray[isExit].m_Address = address;
		cout << "修改成功" << endl;
	}



}
void FindPerson(AddressBooks* abs) {
	string name;
	cout << "请输入要查找的人" << endl;
	cin >> name;
	int isExit = CheckPerson(abs, name);
	if (isExit == -1) {
		cout << "查无此人" << endl;
	}
	else {
		cout << "姓名：" << abs->PersonArray[isExit].m_Name << "\t";
		cout << "性别：" << abs->PersonArray[isExit].m_Sex << "\t";
		cout << "年龄：" << abs->PersonArray[isExit].m_Age << "\t";
		cout << "电话：" << abs->PersonArray[isExit].m_Phone << "\t";
		cout << "地址：" << abs->PersonArray[isExit].m_Address << endl;
	}

}
void DeletePerson(AddressBooks* abs) {
	cout << "请输入要删除的人名" << endl;
	string name;
	cin >> name;
	int isExit = CheckPerson(abs, name);
	if (isExit == -1) {
		cout << "查无此人，无法删除" << endl;
	}
	else {
		//删除 让数据覆盖 逻辑上的删除
		for (int i = isExit; i < abs->m_Size; i++) {
			//数据前移
			abs->PersonArray[i] = abs->PersonArray[i + 1];		
		}
		abs->m_Size--;
		cout << name << "删除成功" << endl;
	}
	
}
void AddPerson(AddressBooks* abs) {
	if (abs->m_Size == MAX) {
		cout << "联系人已满，无法添加" << endl;
	}
	else {
		// 添加联系人姓名、性别、年龄、电话、住址
		string name;
		cout << "请输入姓名" << endl;
		cin >> name;
		abs->PersonArray[abs->m_Size].m_Name = name;
		
		int sex=0;
		while (true) {
			cout << "请输入性别 男1 女2 其他3" << endl;
			cin >> sex;

			if (sex == 1 || sex == 2 || sex == 0) {
				abs->PersonArray[abs->m_Size].m_Sex = sex;
				break;
			}
			else {
				cout << "违法输入，请重新输入" << endl;
			}
		}
		


		int age=0;
		while (true) {
			cout << "请输入年龄 >0<120" << endl;
			cin >> age;

			if (age>=0 && age<=150) {
				abs->PersonArray[abs->m_Size].m_Age = age;
				break;
			}
			else {
				cout << "违法输入，请重新输入" << endl;
			}
		}

		string phone;
		cout << "请输入电话号码" << endl;
		cin >> phone;
		abs->PersonArray[abs->m_Size].m_Phone = phone;

		string address;
		cout << "请输入住址" << endl;
		cin >> address;
		abs->PersonArray[abs->m_Size].m_Address = address;

		abs->m_Size++;
		
		cout << "成功添加" << endl;
	}
}
void ShowPerson(AddressBooks *abs) {
	for (int i = 0; i < abs->m_Size; i++) {
		cout << "序号:" << i + 1 << "\t";
		cout << "姓名：" << abs->PersonArray[i].m_Name << "\t";
		cout << "性别：" << abs->PersonArray[i].m_Sex << "\t";
		cout << "年龄：" << abs->PersonArray[i].m_Age << "\t";
		cout << "电话：" << abs->PersonArray[i].m_Phone << "\t";
		cout << "地址：" << abs->PersonArray[i].m_Address << endl;
	};
	cout << "所有联系人全部显示" << endl;


}
void ShowMenu() {
	// 菜单函数
	cout << "***** 通讯录菜单   *****" << endl;
	cout << "***** 1 添加联系人 *****" << endl;
	cout << "***** 2 显示联系人 *****" << endl;
	cout << "***** 3 删除联系人 *****" << endl;
	cout << "***** 4 查找联系人 *****" << endl;
	cout << "***** 5 修改联系人 *****" << endl;
	cout << "***** 6 清空联系人 *****" << endl;
	cout << "***** 0 退出通讯录 *****" << endl;
}

int main() {

	int select;
	AddressBooks abs;
	abs.m_Size = 0;

	while (true) {

		ShowMenu();

		cin >> select;

		switch (select) {
		case 1:
			AddPerson(& abs);
			break;
		case 2:
			ShowPerson(&abs);
			break;
		case 3:
			DeletePerson(&abs);
			break;
		case 4:
			FindPerson(&abs);
			break;
		case 5:
			ModifyPerson(&abs);
			break;
		case 6:
			DeleteAllPerson(&abs);
			break;
		case 0: // exit
			cout << "欢迎下次使用" << endl;
			system("pause");
			return 0;
			break;
		}
		/*system("cls");*/
	}
	
	system("pause");
	return 0;
}