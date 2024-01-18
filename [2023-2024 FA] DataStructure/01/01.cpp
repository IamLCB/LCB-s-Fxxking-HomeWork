#include <iostream>
#include <iomanip>
#include <string>
#include "myList.h"

using namespace std;

class Student {

private:
	int id;
	string name;
	enum { male, female } sex;
	int age;
	string type;

public:
	//constructor
	Student() : id(0), name(), sex(male), age(0), type() {}
	Student(int ids) : id(ids), name(), sex(male), age(0), type() {}

	friend istream& operator>>(istream& is, Student& stu);
    friend ostream& operator<<(ostream& os, const Student& stu);

	void inputData_noId(istream& is, Student& stu);

	bool operator==(const Student& stu) {
		return this->id == stu.id;
	}
	
	friend class StudentList;
};

istream& operator>>(istream& is, Student& stu) {
	string sexStr;

	is >> stu.id >> stu.name >> sexStr >> stu.age >> stu.type;
	if (sexStr == "��")
		stu.sex = stu.male;
	else if (sexStr == "Ů")
		stu.sex = stu.female;

	return is;
}

ostream& operator<<(ostream& os, const Student& stu) {
	printf("%-10d\t%-10s\t%-10s\t%-10d\t%-10s\t", stu.id, stu.name.c_str(),
		(stu.sex == stu.male ? "��" : "Ů"), stu.age, stu.type.c_str());

	return os;
}

void Student::inputData_noId(istream& is, Student& stu) {
	string sexStr;
	is >> stu.name >> sexStr >> stu.age >> stu.type;
	if (sexStr == "��")
		stu.sex = stu.male;
	else if (sexStr == "Ů")
		stu.sex = stu.female;

	return;
}

class StudentList {
private:
	List<Student> stuList;

public:
	//constructor and destructorw
	StudentList() {}
	~StudentList() {}

	//base functions
	void uniInput(int& id);
	void init();
	void print();
	void find();
	void insert();
	void erase();
	void update();
	void stat();
	int size();
	void wait();


private:
	void insertProperPlace(Student& stu);
};

void StudentList::uniInput(int& id) {
	while (1) {
		cin >> id;
		if (cin.fail() || id <= 0) {
			cout << "������һ����������" << endl;
			cin.clear();
			cin.ignore(1024, '\n');
		}
		else
			break;
	}
}

void StudentList::init() {
	int stuCnt = 0;
	cout << "�����뽨��������Ϣϵͳ��" << endl;
	cout << "�����뿼��������";
	uniInput(stuCnt);
	if (stuCnt > 0) {
		cout << "���������뿼���Ŀ��š��������Ա����估�������" << endl;
		for (int i = 0; i < stuCnt; i++) {
			Student stu;
			cin >> stu;
			if (stuList.find(stu) != stuList.end()) {
				cout << "�ÿ��ŵĿ����Ѵ��ڣ����������룡" << endl;
			}
			else {
				this->insertProperPlace(stu);
			}
		}
		this->print();
		cout << "������Ϣ¼����ϣ�" << endl;
	}
}

void StudentList::print() {
	cout << setiosflags(ios::left);
	cout << setw(8) << "����" << setw(8) << "����" << setw(8) << "�Ա�" << setw(8) << "����" << setw(8) << "�������" << endl;
	if (stuList.empty()) {
		cout << "������ϢΪ�գ�" << endl;
		return;
	}
	else {
		for (auto i = stuList.begin(); i != stuList.end(); i++) {
			cout << setw(8) << (*i).id << setw(8) << (*i).name.c_str() << setw(8) << ((*i).sex == Student::male ? "��" : "Ů") 
				<< setw(8) << (*i).age << setw(8) << (*i).type.c_str() << endl;
		}
	}
}

void StudentList::find() {
	cout << "������Ҫ���ҵĿ����Ŀ��ţ�";
	int id;
	uniInput(id);

	auto findRes = stuList.find(id);
	if (findRes == stuList.end()) {
		cout << "�����ڿ���Ϊ" << id << "�Ŀ�����" << endl;
	}
	else {
		cout << *findRes << endl;
	}
	wait();
}

void StudentList::insert() {
	cout << "������Ҫ����Ŀ����Ŀ��ţ�";
	int id;

	uniInput(id);

	Student stu(id);
	if (stuList.find(stu) != stuList.end()) {
		cout << "�ÿ��ŵĿ����Ѵ��ڣ�" << endl;
	}
	else {
		cout << "���������뿼�����������Ա����估�������" << endl;
		stu.inputData_noId(cin, stu);
		this->insertProperPlace(stu);
		this->print();
		cout << "������Ϣ������ϣ�" << endl;
	}
}

void StudentList::erase() {
	cout << "������Ҫɾ���Ŀ����Ŀ��ţ�";
	int id;
	uniInput(id);

	auto it = stuList.find(id);
	if (it == stuList.end()) {
		cout << "�����ڿ���Ϊ" << id << "�Ŀ�����" << endl;
	}
	else {
		cout << "��ɾ���Ŀ�����Ϣ�ǣ�" << (*it).id << endl;
		stuList.remove(it);
		cout << "������Ϣɾ���ɹ���" << endl;
	}
}

void StudentList::update() {
	cout << "��ѡ����Ҫ�޸ĵĿ����Ŀ��ţ�";
	int id;
	uniInput(id);
	auto it = stuList.find(id);
	if (it == stuList.end()) {
		cout << "�����ڿ���Ϊ" << id << "�Ŀ�����" << endl;
		return;
	}
	cout << "����������Ҫ�޸ĵĿ������������Ա����估�������" << endl;
	Student stu(id);
	stu.inputData_noId(cin, stu);
	(*it) = stu;
}

void StudentList::stat() {
	int sizeStu = stuList.size();
	int sizeMale = 0, sizeFemale = 0;
	if (sizeStu == 0)
	{
		cout << "��ǰϵͳ�����޿�����" << endl;
		return;
	}
	for (auto i = stuList.begin(); i != stuList.end(); i++) {
		if((*i).sex == Student::male) sizeMale++;
		else sizeFemale++;
	}
	cout << "��ǰϵͳ�ڹ���" << sizeStu << "����������������" << sizeMale << "����Ů��" << sizeFemale << "����" << endl;
	return;
}

int StudentList::size() {
	return stuList.size();
}

void StudentList::wait()
{
	cout << endl << "�س�����������" << endl;
	cin.clear();
	cin.ignore(1024, '\n');
	cin.get();
	return;
}

void StudentList::insertProperPlace(Student& stu) {
	if (stuList.empty()) {
		stuList.push_back(stu);
	}
	else {
		for (auto i = stuList.begin(); i != stuList.end(); i++) {
			if ((*i).id > stu.id) {
				stuList.insert(i, stu);
				return;
			}
		}
		stuList.push_back(stu);
	}
}

int main() {
	StudentList base;
	base.init();
	string cmd;
	bool quit = false;
	while (!quit) {
		cout << "\n��ѡ����Ҫ���еĲ�����1Ϊ���룬2Ϊɾ����3Ϊ���ң�4Ϊ�޸ģ�5Ϊͳ�ƣ�0Ϊ�˳�ϵͳ��\n\n";
		cin >> cmd;
		switch (cmd[0]) {
			case '0' :
				quit = true;
				break;
			case '1' :
				base.insert();
				break;
			case '2' :
				base.erase();
				break;
			case '3' :
				base.find();
				break;
			case '4' :
				base.update();
				break;
			case '5' :
				base.stat();
				break;
			default :
				cout << "δ֪����,����������" << endl;
				break;
		}
	}
	return 0;
}