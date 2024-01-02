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
	if (sexStr == "男")
		stu.sex = stu.male;
	else if (sexStr == "女")
		stu.sex = stu.female;

	return is;
}

ostream& operator<<(ostream& os, const Student& stu) {
	printf("%-10d\t%-10s\t%-10s\t%-10d\t%-10s\t", stu.id, stu.name.c_str(),
		(stu.sex == stu.male ? "男" : "女"), stu.age, stu.type.c_str());

	return os;
}

void Student::inputData_noId(istream& is, Student& stu) {
	string sexStr;
	is >> stu.name >> sexStr >> stu.age >> stu.type;
	if (sexStr == "男")
		stu.sex = stu.male;
	else if (sexStr == "女")
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
			cout << "请输入一个正整数！" << endl;
			cin.clear();
			cin.ignore(1024, '\n');
		}
		else
			break;
	}
}

void StudentList::init() {
	int stuCnt = 0;
	cout << "首先请建立考生信息系统！" << endl;
	cout << "请输入考生人数：";
	uniInput(stuCnt);
	if (stuCnt > 0) {
		cout << "请依次输入考生的考号、姓名、性别、年龄及报考类别！" << endl;
		for (int i = 0; i < stuCnt; i++) {
			Student stu;
			cin >> stu;
			if (stuList.find(stu) != stuList.end()) {
				cout << "该考号的考生已存在，请重新输入！" << endl;
			}
			else {
				this->insertProperPlace(stu);
			}
		}
		this->print();
		cout << "考生信息录入完毕！" << endl;
	}
}

void StudentList::print() {
	cout << setiosflags(ios::left);
	cout << setw(8) << "考号" << setw(8) << "姓名" << setw(8) << "性别" << setw(8) << "年龄" << setw(8) << "报考类别" << endl;
	if (stuList.empty()) {
		cout << "考生信息为空！" << endl;
		return;
	}
	else {
		for (auto i = stuList.begin(); i != stuList.end(); i++) {
			cout << setw(8) << (*i).id << setw(8) << (*i).name.c_str() << setw(8) << ((*i).sex == Student::male ? "男" : "女") 
				<< setw(8) << (*i).age << setw(8) << (*i).type.c_str() << endl;
		}
	}
}

void StudentList::find() {
	cout << "请输入要查找的考生的考号：";
	int id;
	uniInput(id);

	auto findRes = stuList.find(id);
	if (findRes == stuList.end()) {
		cout << "不存在考号为" << id << "的考生！" << endl;
	}
	else {
		cout << *findRes << endl;
	}
	wait();
}

void StudentList::insert() {
	cout << "请输入要插入的考生的考号：";
	int id;

	uniInput(id);

	Student stu(id);
	if (stuList.find(stu) != stuList.end()) {
		cout << "该考号的考生已存在！" << endl;
	}
	else {
		cout << "请依次输入考生的姓名、性别、年龄及报考类别！" << endl;
		stu.inputData_noId(cin, stu);
		this->insertProperPlace(stu);
		this->print();
		cout << "考生信息插入完毕！" << endl;
	}
}

void StudentList::erase() {
	cout << "请输入要删除的考生的考号：";
	int id;
	uniInput(id);

	auto it = stuList.find(id);
	if (it == stuList.end()) {
		cout << "不存在考号为" << id << "的考生！" << endl;
	}
	else {
		cout << "您删除的考生信息是：" << (*it).id << endl;
		stuList.remove(it);
		cout << "考生信息删除成功！" << endl;
	}
}

void StudentList::update() {
	cout << "请选择您要修改的考生的考号：";
	int id;
	uniInput(id);
	auto it = stuList.find(id);
	if (it == stuList.end()) {
		cout << "不存在考号为" << id << "的考生！" << endl;
		return;
	}
	cout << "请依次输入要修改的考生的姓名，性别，年龄及报考类别！" << endl;
	Student stu(id);
	stu.inputData_noId(cin, stu);
	(*it) = stu;
}

void StudentList::stat() {
	int sizeStu = stuList.size();
	int sizeMale = 0, sizeFemale = 0;
	if (sizeStu == 0)
	{
		cout << "当前系统内暂无考生！" << endl;
		return;
	}
	for (auto i = stuList.begin(); i != stuList.end(); i++) {
		if((*i).sex == Student::male) sizeMale++;
		else sizeFemale++;
	}
	cout << "当前系统内共有" << sizeStu << "名考生，其中男生" << sizeMale << "名，女生" << sizeFemale << "名。" << endl;
	return;
}

int StudentList::size() {
	return stuList.size();
}

void StudentList::wait()
{
	cout << endl << "回车键继续操作" << endl;
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
		cout << "\n请选择您要进行的操作（1为插入，2为删除，3为查找，4为修改，5为统计，0为退出系统）\n\n";
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
				cout << "未知操作,请重新输入" << endl;
				break;
		}
	}
	return 0;
}