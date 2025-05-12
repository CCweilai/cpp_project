#include"order_file.h"

OrderFile::OrderFile() {

	ifstream ifs;
	ifs.open(ORDER_FILE, ios::in);

	string week;
	string interval;
	string stu_id;
	string stu_name;
	string room_id;
	string status;

	this->order_num = 0;

	while (ifs >> week && ifs >> interval && ifs >> stu_id && ifs >> stu_name && ifs >> room_id && ifs >> status) {
		string key;
		string value;
		map<string, string>m;
		int pos = week.find(":");
		if (pos != -1) {
			key = week.substr(0, pos);
			value = week.substr(pos + 1, week.size() - pos);
			m.insert(make_pair(key, value));
		}
		pos = interval.find(":");
		if (pos != -1) {
			key = interval.substr(0, pos);
			value = interval.substr(pos + 1, interval.size() - pos);
			m.insert(make_pair(key, value));
		}
		pos = stu_id.find(":");
		if (pos != -1) {
			key = stu_id.substr(0, pos);
			value = stu_id.substr(pos + 1, stu_id.size() - pos);
			m.insert(make_pair(key, value));
		}
		pos = stu_name.find(":");
		if (pos != -1) {
			key = stu_name.substr(0, pos);
			value = stu_name.substr(pos + 1, stu_name.size() - pos);
			m.insert(make_pair(key, value));
		}
		pos = room_id.find(":");
		if (pos != -1) {
			key = room_id.substr(0, pos);
			value = room_id.substr(pos + 1, room_id.size() - pos);
			m.insert(make_pair(key, value));
		}
		pos = status.find(":");
		if (pos != -1) {
			key = status.substr(0, pos);
			value = status.substr(pos + 1, status.size() - pos);
			m.insert(make_pair(key, value));
		}
		this->m_order.insert(make_pair(this->order_num, m));
		this->order_num++;
	}
}

void OrderFile::UpdateOrder() {
	if (this->order_num==0) {
		return;
	}
	ofstream ofs(ORDER_FILE, ios::out | ios::trunc);
	for (int i = 0; i < this->order_num; i++) {
		ofs << "week:" << this->m_order[i]["week"] << " ";
		ofs << "interval:" << this->m_order[i]["interval"] << " ";
		ofs << "stu_id:" << this->m_order[i]["stu_id"] << " ";
		ofs << "stu_name:" << this->m_order[i]["stu_name"] << " ";
		ofs << "room_id:" << this->m_order[i]["room_id"] << " ";
		ofs << "status:" << this->m_order[i]["status"] << endl;
	}
	ofs.close();
}

