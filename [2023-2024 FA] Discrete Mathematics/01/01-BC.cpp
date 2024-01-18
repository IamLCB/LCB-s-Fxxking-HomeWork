#include <iostream>
#include <string>
#include <map>
#include <stack>
using namespace std;

// 定义几种不同的映射类型，用于存储不同的数据
typedef map<char, int> Map_ci; // 存储字符和整数的映射
typedef map<int, char> Map_ic; // 存储整数和字符的映射
typedef map<int, int> Map_ii;  // 存储整数和整数的映射
//typedef map<int, bool> Map_ib;

Map_ci priority;

Map_ic getProposition(string formula);
int findProposition(Map_ic, char p);
int pow2(int n);
Map_ii toBinary(int n_proposition, int index);
int calculate(string formula, Map_ic pSet, Map_ii value);
void check(stack<int> &value, stack<char> &opter);

int main() 
{
	priority['('] = 6;
	priority[')'] = 6;
	priority['!'] = 5;
	priority['&'] = 4;
	priority['|'] = 3;
	priority['^'] = 2;
	priority['~'] = 1;
	priority['#'] = 0;
	//运算符优先级

	cout << "***************************************\n";
	cout << "**                                   **\n";
	cout << "**         欢迎进入逻辑运算软件      **\n";
	cout << "**   (可运算真值表,主范式,支持括号)  **\n";
	cout << "**                                   **\n";
	cout << "**              用!表示非            **\n";
	cout << "**              用&表示与            **\n";
	cout << "**              用|表示或            **\n";
	cout << "**             用^表示蕴含           **\n";
	cout << "**             用~表示等值           **\n";
	cout << "**                                   **\n";
	cout << "***************************************\n\n";
	cout << "Please enter a legitimate proposition formula: " << endl;
	string formula;
	cin >> formula;
	Map_ic proposition_set = getProposition(formula);
	cout << "该式子中的变量个数为：" << proposition_set.size() << endl << "输出真值表如下：" << endl;
	for (unsigned int i = 0; i < proposition_set.size(); i++)
	{
		cout << proposition_set[i] << "\t";
	}
	cout << formula << endl;
	int *m;
	m = (int*)malloc(sizeof(int)*pow2(proposition_set.size()));   //该数组依次存放命题公式的各行(0或1)的运算结果的值
	// int z = pow2(proposition_set.size());
	// cout << z << endl;
	for (int i = 0; i < pow2(proposition_set.size()); i++) 
	{
		Map_ii bina_set = toBinary(proposition_set.size(), i);
		for (unsigned int j = 0; j < bina_set.size(); j++)
		{
			cout << bina_set[j] << "\t";
		}
		int result = calculate(formula, proposition_set, bina_set);
		//m[i] = result;
		*(m+i) = result;
		cout << result << endl;
	}
	int n_m = 0, n_M = 0;
	cout << "该命题公式的主析取范式：" << endl;
	for (int i = 0; i < pow2(proposition_set.size()); i++) 
	{
		if (*(m + i) == 1)
		{
			if (n_m == 0) 
			{
				cout << "m<" << i << ">";
			}
			else 
			{
				cout << " \\/ m<" << i << "> ";
			}
			n_m++;
		}
	}
	if (n_m == 0) 
	{
		cout << "0";
	}
	cout << endl;
	cout << "该命题公式的主合取范式：" << endl;
	for (int i = 0; i < pow2(proposition_set.size()); i++) 
	{
		if (*(m + i) == 0)
		{
			if (n_M == 0) 
			{
				cout << "M<" << i << ">";
			}
			else 
			{
				cout << " /\\ M<" << i << "> ";
			}
			n_M++;
		}
	}
	if (n_M == 0) 
	{
		cout << "0";
	}
	cout << endl;

	system("pause");

	return 0;
}

// 此函数用于在映射中查找给定的命题变量。
// pSet: 存储命题变量和其对应索引的映射
// p: 要查找的命题变量
// 返回值: 如果找到命题变量，则返回其在映射中的索引；如果未找到，则返回-1。
int findProposition(Map_ic pSet, char p) 
{
    Map_ic::iterator it = pSet.begin(); // 创建迭代器，从映射的开始位置遍历
    while (it != pSet.end()) // 遍历映射
    {
        if (it->second == p) 
        {
            return it->first; // 如果找到匹配的命题变量，返回其索引
        }
        it++; // 移动到下一个元素
    }
    return -1; // 如果未找到，返回-1
}

// 此函数用于提取并返回逻辑公式中所有唯一的命题变量。
// formula: 输入的逻辑公式字符串
// 返回值: 包含公式中所有唯一命题变量的映射，每个变量对应一个唯一索引。
Map_ic getProposition(string formula) 
{
    Map_ic proposition; // 创建存储命题变量的映射
    int n_proposition = 0; // 用于给命题变量分配唯一的索引
    for (unsigned int i = 0; i < formula.length(); i++) // 遍历公式中的每个字符
    {
        char c = formula[i]; // 当前字符
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) 
        {
            int r = findProposition(proposition, c); // 检查字符是否已经在映射中
            if (r == -1) 
            {
                // 如果该字符（命题变量）还未在映射中，添加它
                proposition[n_proposition] = c;
                n_proposition++; // 增加索引计数
            }
        }
        else if (!priority.count(c)) // 如果字符不是一个已定义的运算符
        {
            cout << c << " is undefined!" << endl; // 打印错误消息
            exit(2); // 退出程序
        }
    }
    return proposition; // 返回包含所有命题变量的映射
}

Map_ii toBinary(int n_proposition, int index)  //该函数返回命题变项的二进制(0或1)取值
{
	Map_ii result;
	for (int i = 0; i < n_proposition; i++) 
	{
		int r = index % 2;
		result[n_proposition - 1 - i] = r;
		index = index / 2;
	}
	return result;
}

int pow2(int n)    //该函数返回指定数字的二次方的值
{
	if (n == 0)
		return 1;
	else
		return 2 * pow2(n - 1);
}

// 该函数计算给定的逻辑表达式的值。它处理命题逻辑中的基本运算，如非(!)、与(&)、或(|)等。
// formula: 要计算的逻辑公式字符串
// pSet: 包含公式中所有命题变量的集合
// value: 包含命题变量对应值的映射，每个变量对应一个布尔值(0或1)
int calculate(string formula, Map_ic pSet, Map_ii value) 
{
    stack<char> opter; // 存储运算符的栈
    stack<int> pvalue; // 存储命题变量值的栈
    opter.push('#'); // 在栈底添加一个特殊字符以标识栈底
    formula = formula + "#"; // 在公式末尾也添加特殊字符以标识结束

    // 遍历整个公式
    for (unsigned int i = 0; i < formula.length(); i++)
    {
        char c = formula[i]; // 当前字符

        // 判断字符是否为命题变量
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) 
        {
            // 是命题变量，将其对应的布尔值压入栈
            pvalue.push(value[findProposition(pSet, c)]);
        }
        else 
        {
            // 处理运算符
            char tmp = opter.top(); // 查看栈顶运算符
            // 如果栈顶运算符的优先级高于当前运算符
            if (priority[tmp] > priority[c]) 
            {
                // 当栈顶运算符的优先级大于当前运算符时，执行运算
                while (priority[tmp] > priority[c] && tmp != '(') 
                {
                    check(pvalue, opter); // 执行运算
                    tmp = opter.top(); // 更新栈顶运算符
                    // 如果遇到公式结束标识符，则返回结果
                    if (tmp == '#' && c == '#') 
                    {
                        return pvalue.top(); // 返回计算结果
                    }
                }
                // 当前运算符压入栈
                opter.push(c);
            }
            else
            {
                // 如果栈顶运算符优先级不高于当前运算符，直接压栈
                opter.push(c);
            }
        }
    }
    // 如果没有正确计算出结果，则返回-1
    return -1;
}


void check(stack<int> &value, stack<char> &opter) //该函数返回两个命题变项(取值0或1)的各种运算结果(0或1)
{
	int p, q, result;
	char opt = opter.top();

	switch (opt) 
	{
	case '&':
		p = value.top();
		value.pop();
		q = value.top();
		value.pop();
		result = p && q;
		value.push(result);
		opter.pop();
		break;

	case '|':
		p = value.top();
		value.pop();
		q = value.top();
		value.pop();
		result = p || q;
		value.push(result);
		opter.pop();
		break;

	case '!':
		p = value.top();
		value.pop();
		result = !p;
		value.push(result);
		opter.pop();
		break;

	case '^':
		q = value.top();
		value.pop();
		p = value.top();
		value.pop();
		result = !p || q;
		value.push(result);
		opter.pop();
		break;

	case '~':
		p = value.top();
		value.pop();
		q = value.top();
		value.pop();
		result = (!p || q) && (p || !q);
		value.push(result);
		opter.pop();
		break;

	case '#':
		break;

	case '(':
		break;

	case ')':
		opter.pop();
		while (opter.top() != '(') 
		{
			check(value, opter);
		}
		if (opter.top() == '(') 
		{
			opter.pop();
		}
		break;

	default:
		break;
	}
}