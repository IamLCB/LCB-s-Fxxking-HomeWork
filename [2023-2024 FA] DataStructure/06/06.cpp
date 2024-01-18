#include "myPair.h"
#include "myList.h"
#include "myVector.h"
#include <iostream>
#include <string>
using namespace std;

// 两个泛型函数，分别用于计算最大值和最小值
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
    void buildTree(); // 建立树
    void buildFamily(); // 建立家族
    void addFamilyMember(); // 添加家族成员
    void delFamily(); // 删除家族
    void renameFamilyMember(); // 重命名

public:
    treeNode* findFamily(const string& name) const; // 查找name
    treeNode* searchAt(treeNode* root, const string& name)const; // 在root为根的树中查找name
    inline int countFamily(const string& name) const; // 计算name的家族人数
    void displayFamilyTree() const; // 显示家谱
    void printFamilyTree(treeNode* root, const string& indent = "") const; // 辅助函数
};

void tree::buildTree()
{
    if (root != nullptr)
    {
        cout << "已经建立了家族树" << endl;
        return;
    }

    cout << "请输入家族的祖先的名字：";
    string name;
    cin >> name;
    root = new treeNode(name);
    cout << "已经建立了家族树" << endl;
}

void tree::buildFamily()
{
    if (root == nullptr)
    {
        cout << "请先建立家族树" << endl;
        return;
    }

    cout << "请输入要建立家族的人的名字：";
    string name;
    cin >> name;
    treeNode* ptr = findFamily(name);
    if (ptr == nullptr)
    {
        cout << "没有找到这个人" << endl;
        return;
    }

    cout << "请输入" << name << "的儿女个数：";
    int num;
    cin >> num;
    cout << "请依次输入" << name << "的儿女的姓名：";
    for (int i = 0; i < num; ++i)
    {
        cin >> name;
        if (!countFamily(name)) {
            ptr->children.push_back(new treeNode(name)); // 添加新成员
        }
        else{
            cout << "姓名为 " << name << " 的人已经存在" << endl;
        }
    }
    cout << "已经建立了家族" << endl;
}

void tree::addFamilyMember()
{
    if (root == nullptr)
    {
        cout << "请先建立家族树" << endl;
        return;
    }

    cout << "请输入要添加家族成员的人的名字：";
    string name;
    cin >> name;
    treeNode* ptr = findFamily(name);
    if (ptr == nullptr)
    {
        cout << "没有找到这个人" << endl;
        return;
    }

    cout << "请输入" << name << "新添加儿子（或女儿）的姓名：";
    cin >> name;
    if (!countFamily(name)) {
        ptr->children.push_back(new treeNode(name)); // 添加新成员
    }
    else {
        cout << "姓名为 " << name << " 的人已经存在" << endl;
    }
    cout << "已经添加了家族成员" << endl;
}

void tree::delFamily()
{
    if (root == nullptr)
    {
        cout << "请先建立家族树" << endl;
        return;
    }

    cout << "请输入要删除家族的人的名字：";
    string name;
    cin >> name;
    treeNode* ptr = findFamily(name);
    if (ptr == nullptr)
    {
        cout << "没有找到这个人" << endl;
        return;
    }

    cout << "要解散家族的人是" << name << endl;
    ptr->children.clear();
    cout << "已经删除了家族" << endl;
}

void tree::renameFamilyMember()
{
    if (root == nullptr)
    {
        cout << "请先建立家族树" << endl;
        return;
    }

    cout << "请输入要重命名的人的名字：";
    string name;
    cin >> name;
    treeNode* ptr = findFamily(name);
    if (ptr == nullptr)
    {
        cout << "没有找到这个人" << endl;
        return;
    }

    cout << "请输入" << name << "的新名字：";
    cin >> name;
    if (!countFamily(name)) {
        cout << "已经将" << ptr->name << "重命名为" << name << endl;
        ptr->name = name;
    }
    else {
        cout << "姓名为 " << name << " 的人已经存在" << endl;
    }
    cout << "已经重命名了家族成员" << endl;
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
        return root; // 找到了
    treeNode* result = nullptr;
    for (auto ptr : root->children)
    {
        result = searchAt(ptr, name); // 递归查找
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
        cout << "家谱树为空。" << endl;
    } else {
        cout << "家谱树：" << endl;
        printFamilyTree(root); // 从根开始打印家谱树
    }
}

void tree::printFamilyTree(treeNode* node, const string& indent) const {
    if (node != nullptr) {
        cout << indent << "- " << node->name << endl; // 打印当前节点
        for (auto child : node->children) {
            printFamilyTree(child, indent + "  "); // 递归打印子节点，增加缩进
        }
    }
}

int main() {
    cout << endl << "**                 家谱管理系统                 **" << endl;
    cout << "==================================================" << endl;
    cout << "**\t\t请选择要执行的操作：\t\t**" << endl;
    cout << "**\t\tA --- 完善家庭\t\t\t**" << endl;
    cout << "**\t\tB --- 添加家庭成员\t\t**" << endl;
    cout << "**\t\tC --- 解散局部家庭\t\t**" << endl;
    cout << "**\t\tD --- 更改家庭成员姓名\t\t**" << endl;
    cout << "**\t\tE --- 显示家谱\t\t\t**" << endl;
    cout << "**\t\tF --- 退出程序\t\t\t**" << endl;
    cout << "==================================================" << endl;
    tree tree;
    tree.buildTree();

    char input;
    bool exit = false;
    while (!exit) {
        cout << endl << "请选择要执行的操作：";
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
                cout << "请输入合法的执行操作符" << endl;
        }
    }

    system("pause");

    return 0;
}