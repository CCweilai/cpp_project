#include<iostream>
#include<string>

using namespace std;

#define MAX 1000

struct Person {
	// ��ϵ�˽ṹ�� �������Ա����䡢�绰��סַ
	string m_Name;
	int m_Sex;
	int m_Age;
	string m_Phone;
	string m_Address;
};

struct AddressBooks {
	//ͨѶ¼�ṹ�� ��ϵ������ ��ϵ�˸���
	Person PersonArray[MAX];
	int m_Size=0;
};

int CheckPerson(AddressBooks * abs,string name) {
	//��⴫��������ǲ�����ͨѶ¼�д���
	//��������

	for (int i = 0; i < abs->m_Size; i++) {
		if (abs->PersonArray[i].m_Name == name) {
			//������������ ���ں���ʹ��
			return i;
		}
	}
	return -1;
}
void DeleteAllPerson(AddressBooks* abs) {
	//�߼������
	abs->m_Size = 0;
	cout << "ͨѶ¼�����" << endl;
	system("pause");
	system("cls");
}
void ModifyPerson(AddressBooks *abs) {

	cout << "��������Ҫ�޸ĵ���ϵ��" << endl;
	string name;
	cin >> name;
	int isExit = CheckPerson(abs, name);
	if (isExit == -1) {
		cout << "���޴���" << endl;
	}
	else {
		string name;
		int sex;
		int age;
		string phone, address;
		cout << "��������������" << endl;
		cin >> name;
		abs->PersonArray[isExit].m_Name = name;
		cout << "�����������Ա�" << endl;
		cin >> sex;
		abs->PersonArray[isExit].m_Sex = sex;
		cout << "��������������" << endl;
		cin >> age;
		abs->PersonArray[isExit].m_Age = age;
		cout << "����������绰" << endl;
		cin >> phone;
		abs->PersonArray[isExit].m_Phone = phone;
		cout << "�����������ַ" << endl;
		cin >> address;
		abs->PersonArray[isExit].m_Address = address;
		cout << "�޸ĳɹ�" << endl;
	}



}
void FindPerson(AddressBooks* abs) {
	string name;
	cout << "������Ҫ���ҵ���" << endl;
	cin >> name;
	int isExit = CheckPerson(abs, name);
	if (isExit == -1) {
		cout << "���޴���" << endl;
	}
	else {
		cout << "������" << abs->PersonArray[isExit].m_Name << "\t";
		cout << "�Ա�" << abs->PersonArray[isExit].m_Sex << "\t";
		cout << "���䣺" << abs->PersonArray[isExit].m_Age << "\t";
		cout << "�绰��" << abs->PersonArray[isExit].m_Phone << "\t";
		cout << "��ַ��" << abs->PersonArray[isExit].m_Address << endl;
	}

}
void DeletePerson(AddressBooks* abs) {
	cout << "������Ҫɾ��������" << endl;
	string name;
	cin >> name;
	int isExit = CheckPerson(abs, name);
	if (isExit == -1) {
		cout << "���޴��ˣ��޷�ɾ��" << endl;
	}
	else {
		//ɾ�� �����ݸ��� �߼��ϵ�ɾ��
		for (int i = isExit; i < abs->m_Size; i++) {
			//����ǰ��
			abs->PersonArray[i] = abs->PersonArray[i + 1];		
		}
		abs->m_Size--;
		cout << name << "ɾ���ɹ�" << endl;
	}
	
}
void AddPerson(AddressBooks* abs) {
	if (abs->m_Size == MAX) {
		cout << "��ϵ���������޷����" << endl;
	}
	else {
		// �����ϵ���������Ա����䡢�绰��סַ
		string name;
		cout << "����������" << endl;
		cin >> name;
		abs->PersonArray[abs->m_Size].m_Name = name;
		
		int sex=0;
		while (true) {
			cout << "�������Ա� ��1 Ů2 ����3" << endl;
			cin >> sex;

			if (sex == 1 || sex == 2 || sex == 0) {
				abs->PersonArray[abs->m_Size].m_Sex = sex;
				break;
			}
			else {
				cout << "Υ�����룬����������" << endl;
			}
		}
		


		int age=0;
		while (true) {
			cout << "���������� >0<120" << endl;
			cin >> age;

			if (age>=0 && age<=150) {
				abs->PersonArray[abs->m_Size].m_Age = age;
				break;
			}
			else {
				cout << "Υ�����룬����������" << endl;
			}
		}

		string phone;
		cout << "������绰����" << endl;
		cin >> phone;
		abs->PersonArray[abs->m_Size].m_Phone = phone;

		string address;
		cout << "������סַ" << endl;
		cin >> address;
		abs->PersonArray[abs->m_Size].m_Address = address;

		abs->m_Size++;
		
		cout << "�ɹ����" << endl;
	}
}
void ShowPerson(AddressBooks *abs) {
	for (int i = 0; i < abs->m_Size; i++) {
		cout << "���:" << i + 1 << "\t";
		cout << "������" << abs->PersonArray[i].m_Name << "\t";
		cout << "�Ա�" << abs->PersonArray[i].m_Sex << "\t";
		cout << "���䣺" << abs->PersonArray[i].m_Age << "\t";
		cout << "�绰��" << abs->PersonArray[i].m_Phone << "\t";
		cout << "��ַ��" << abs->PersonArray[i].m_Address << endl;
	};
	cout << "������ϵ��ȫ����ʾ" << endl;


}
void ShowMenu() {
	// �˵�����
	cout << "***** ͨѶ¼�˵�   *****" << endl;
	cout << "***** 1 �����ϵ�� *****" << endl;
	cout << "***** 2 ��ʾ��ϵ�� *****" << endl;
	cout << "***** 3 ɾ����ϵ�� *****" << endl;
	cout << "***** 4 ������ϵ�� *****" << endl;
	cout << "***** 5 �޸���ϵ�� *****" << endl;
	cout << "***** 6 �����ϵ�� *****" << endl;
	cout << "***** 0 �˳�ͨѶ¼ *****" << endl;
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
			cout << "��ӭ�´�ʹ��" << endl;
			system("pause");
			return 0;
			break;
		}
		/*system("cls");*/
	}
	
	system("pause");
	return 0;
}