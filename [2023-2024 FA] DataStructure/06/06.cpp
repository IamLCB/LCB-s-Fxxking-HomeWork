#include "myPair.h"
#include "myList.h"
#include "myVector.h"
#include <iostream>
#include <string>
using namespace std;

// �������ͺ������ֱ����ڼ������ֵ����Сֵ
template<typename T1, typename T2>
constexpr auto MAX(T1 x, T2 y) { return (((x)>(y))?(x):(y)); }
template<typename T1, typename T2>
constexpr auto MIN(T1 x, T2 y) { return (((x)<(y))?(x):(y)); }

struct treeNode
{
    string name;
    Vector<treeNode*> children;
    treeNode(const string& Name):name(Name) {}
};

class tree
{
private:
    treeNode* root = nullptr; 
public:
    tree() {}
    ~tree() { delete root; }
    void buildTree(); // ������
    void buildFamily(); // ��������
    void addFamilyMember(); // ��Ӽ����Ա
    void delFamily(); // ɾ������
    void renameFamilyMember(); // ������

public:
    treeNode* findFamily(const string& name) const; // ����name
    treeNode* searchAt(treeNode* root, const string& name)const; // ��rootΪ�������в���name
    inline int countFamily(const string& name) const; // ����name�ļ�������
    void displayFamilyTree() const; // ��ʾ����
    void printFamilyTree(treeNode* root, const string& indent = "") const; // ��������
};

void tree::buildTree()
{
    if (root != nullptr)
    {
        cout << "�Ѿ������˼�����" << endl;
        return;
    }

    cout << "�������������ȵ����֣�";
    string name;
    cin >> name;
    root = new treeNode(name);
    cout << "�Ѿ������˼�����" << endl;
}

void tree::buildFamily()
{
    if (root == nullptr)
    {
        cout << "���Ƚ���������" << endl;
        return;
    }

    cout << "������Ҫ����������˵����֣�";
    string name;
    cin >> name;
    treeNode* ptr = findFamily(name);
    if (ptr == nullptr)
    {
        cout << "û���ҵ������" << endl;
        return;
    }

    cout << "������" << name << "�Ķ�Ů������";
    int num;
    cin >> num;
    cout << "����������" << name << "�Ķ�Ů��������";
    for (int i = 0; i < num; ++i)
    {
        cin >> name;
        if (!countFamily(name)) {
            ptr->children.push_back(new treeNode(name)); // ����³�Ա
        }
        else{
            cout << "����Ϊ " << name << " �����Ѿ�����" << endl;
        }
    }
    cout << "�Ѿ������˼���" << endl;
}

void tree::addFamilyMember()
{
    if (root == nullptr)
    {
        cout << "���Ƚ���������" << endl;
        return;
    }

    cout << "������Ҫ��Ӽ����Ա���˵����֣�";
    string name;
    cin >> name;
    treeNode* ptr = findFamily(name);
    if (ptr == nullptr)
    {
        cout << "û���ҵ������" << endl;
        return;
    }

    cout << "������" << name << "����Ӷ��ӣ���Ů������������";
    cin >> name;
    if (!countFamily(name)) {
        ptr->children.push_back(new treeNode(name)); // ����³�Ա
    }
    else {
        cout << "����Ϊ " << name << " �����Ѿ�����" << endl;
    }
    cout << "�Ѿ�����˼����Ա" << endl;
}

void tree::delFamily()
{
    if (root == nullptr)
    {
        cout << "���Ƚ���������" << endl;
        return;
    }

    cout << "������Ҫɾ��������˵����֣�";
    string name;
    cin >> name;
    treeNode* ptr = findFamily(name);
    if (ptr == nullptr)
    {
        cout << "û���ҵ������" << endl;
        return;
    }

    cout << "Ҫ��ɢ���������" << name << endl;
    ptr->children.clear();
    cout << "�Ѿ�ɾ���˼���" << endl;
}

void tree::renameFamilyMember()
{
    if (root == nullptr)
    {
        cout << "���Ƚ���������" << endl;
        return;
    }

    cout << "������Ҫ���������˵����֣�";
    string name;
    cin >> name;
    treeNode* ptr = findFamily(name);
    if (ptr == nullptr)
    {
        cout << "û���ҵ������" << endl;
        return;
    }

    cout << "������" << name << "�������֣�";
    cin >> name;
    if (!countFamily(name)) {
        cout << "�Ѿ���" << ptr->name << "������Ϊ" << name << endl;
        ptr->name = name;
    }
    else {
        cout << "����Ϊ " << name << " �����Ѿ�����" << endl;
    }
    cout << "�Ѿ��������˼����Ա" << endl;
}

treeNode* tree::findFamily(const string& name) const
{
    if (root == nullptr)
        return nullptr;
    else
        return searchAt(root, name);
}

treeNode* tree::searchAt(treeNode* root, const string& name) const
{
    if (root->name == name)
        return root; // �ҵ���
    treeNode* result = nullptr;
    for (auto ptr : root->children)
    {
        result = searchAt(ptr, name); // �ݹ����
        if (result != nullptr)
            break;
    }
    return result;
}

inline int tree::countFamily(const string& name) const
{
    return searchAt(root, name) == nullptr ? 0 : 1;
}

void tree::displayFamilyTree() const {
    if (root == nullptr) {
        cout << "������Ϊ�ա�" << endl;
    } else {
        cout << "��������" << endl;
        printFamilyTree(root); // �Ӹ���ʼ��ӡ������
    }
}

void tree::printFamilyTree(treeNode* node, const string& indent) const {
    if (node != nullptr) {
        cout << indent << "- " << node->name << endl; // ��ӡ��ǰ�ڵ�
        for (auto child : node->children) {
            printFamilyTree(child, indent + "  "); // �ݹ��ӡ�ӽڵ㣬��������
        }
    }
}

int main() {
    cout << endl << "**                 ���׹���ϵͳ                 **" << endl;
    cout << "==================================================" << endl;
    cout << "**\t\t��ѡ��Ҫִ�еĲ�����\t\t**" << endl;
    cout << "**\t\tA --- ���Ƽ�ͥ\t\t\t**" << endl;
    cout << "**\t\tB --- ��Ӽ�ͥ��Ա\t\t**" << endl;
    cout << "**\t\tC --- ��ɢ�ֲ���ͥ\t\t**" << endl;
    cout << "**\t\tD --- ���ļ�ͥ��Ա����\t\t**" << endl;
    cout << "**\t\tE --- ��ʾ����\t\t\t**" << endl;
    cout << "**\t\tF --- �˳�����\t\t\t**" << endl;
    cout << "==================================================" << endl;
    tree tree;
    tree.buildTree();

    char input;
    bool exit = false;
    while (!exit) {
        cout << endl << "��ѡ��Ҫִ�еĲ�����";
        cin >> input;
        switch (input) {
            case 'A':
            case 'a':
                tree.buildFamily();
                break;
            case 'B':
            case 'b':
                tree.addFamilyMember();
                break;
            case 'C':
            case 'c':
                tree.delFamily();
                break;
            case 'D':
            case 'd':
                tree.renameFamilyMember();
                break;
            case 'E':
            case 'e':
                tree.displayFamilyTree();
                break;
            case 'F':
            case 'f':
                exit = true;
                break;
            default:
                cin.clear();
                cin.ignore(1024, '\n');
                cout << "������Ϸ���ִ�в�����" << endl;
        }
    }

    system("pause");

    return 0;
}