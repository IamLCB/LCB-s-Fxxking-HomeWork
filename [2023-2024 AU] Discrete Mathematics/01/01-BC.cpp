#include <iostream>
#include <string>
#include <map>
#include <stack>
using namespace std;

// ���弸�ֲ�ͬ��ӳ�����ͣ����ڴ洢��ͬ������
typedef map<char, int> Map_ci; // �洢�ַ���������ӳ��
typedef map<int, char> Map_ic; // �洢�������ַ���ӳ��
typedef map<int, int> Map_ii;  // �洢������������ӳ��
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
	//��������ȼ�

	cout << "***************************************\n";
	cout << "**                                   **\n";
	cout << "**         ��ӭ�����߼��������      **\n";
	cout << "**   (��������ֵ��,����ʽ,֧������)  **\n";
	cout << "**                                   **\n";
	cout << "**              ��!��ʾ��            **\n";
	cout << "**              ��&��ʾ��            **\n";
	cout << "**              ��|��ʾ��            **\n";
	cout << "**             ��^��ʾ�̺�           **\n";
	cout << "**             ��~��ʾ��ֵ           **\n";
	cout << "**                                   **\n";
	cout << "***************************************\n\n";
	cout << "Please enter a legitimate proposition formula: " << endl;
	string formula;
	cin >> formula;
	Map_ic proposition_set = getProposition(formula);
	cout << "��ʽ���еı�������Ϊ��" << proposition_set.size() << endl << "�����ֵ�����£�" << endl;
	for (unsigned int i = 0; i < proposition_set.size(); i++)
	{
		cout << proposition_set[i] << "\t";
	}
	cout << formula << endl;
	int *m;
	m = (int*)malloc(sizeof(int)*pow2(proposition_set.size()));   //���������δ�����⹫ʽ�ĸ���(0��1)����������ֵ
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
	cout << "�����⹫ʽ������ȡ��ʽ��" << endl;
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
	cout << "�����⹫ʽ������ȡ��ʽ��" << endl;
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

// �˺���������ӳ���в��Ҹ��������������
// pSet: �洢������������Ӧ������ӳ��
// p: Ҫ���ҵ��������
// ����ֵ: ����ҵ�����������򷵻�����ӳ���е����������δ�ҵ����򷵻�-1��
int findProposition(Map_ic pSet, char p) 
{
    Map_ic::iterator it = pSet.begin(); // ��������������ӳ��Ŀ�ʼλ�ñ���
    while (it != pSet.end()) // ����ӳ��
    {
        if (it->second == p) 
        {
            return it->first; // ����ҵ�ƥ����������������������
        }
        it++; // �ƶ�����һ��Ԫ��
    }
    return -1; // ���δ�ҵ�������-1
}

// �˺���������ȡ�������߼���ʽ������Ψһ�����������
// formula: ������߼���ʽ�ַ���
// ����ֵ: ������ʽ������Ψһ���������ӳ�䣬ÿ��������Ӧһ��Ψһ������
Map_ic getProposition(string formula) 
{
    Map_ic proposition; // �����洢���������ӳ��
    int n_proposition = 0; // ���ڸ������������Ψһ������
    for (unsigned int i = 0; i < formula.length(); i++) // ������ʽ�е�ÿ���ַ�
    {
        char c = formula[i]; // ��ǰ�ַ�
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) 
        {
            int r = findProposition(proposition, c); // ����ַ��Ƿ��Ѿ���ӳ����
            if (r == -1) 
            {
                // ������ַ��������������δ��ӳ���У������
                proposition[n_proposition] = c;
                n_proposition++; // ������������
            }
        }
        else if (!priority.count(c)) // ����ַ�����һ���Ѷ���������
        {
            cout << c << " is undefined!" << endl; // ��ӡ������Ϣ
            exit(2); // �˳�����
        }
    }
    return proposition; // ���ذ����������������ӳ��
}

Map_ii toBinary(int n_proposition, int index)  //�ú��������������Ķ�����(0��1)ȡֵ
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

int pow2(int n)    //�ú�������ָ�����ֵĶ��η���ֵ
{
	if (n == 0)
		return 1;
	else
		return 2 * pow2(n - 1);
}

// �ú�������������߼����ʽ��ֵ�������������߼��еĻ������㣬���(!)����(&)����(|)�ȡ�
// formula: Ҫ������߼���ʽ�ַ���
// pSet: ������ʽ��������������ļ���
// value: �������������Ӧֵ��ӳ�䣬ÿ��������Ӧһ������ֵ(0��1)
int calculate(string formula, Map_ic pSet, Map_ii value) 
{
    stack<char> opter; // �洢�������ջ
    stack<int> pvalue; // �洢�������ֵ��ջ
    opter.push('#'); // ��ջ�����һ�������ַ��Ա�ʶջ��
    formula = formula + "#"; // �ڹ�ʽĩβҲ��������ַ��Ա�ʶ����

    // ����������ʽ
    for (unsigned int i = 0; i < formula.length(); i++)
    {
        char c = formula[i]; // ��ǰ�ַ�

        // �ж��ַ��Ƿ�Ϊ�������
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) 
        {
            // ����������������Ӧ�Ĳ���ֵѹ��ջ
            pvalue.push(value[findProposition(pSet, c)]);
        }
        else 
        {
            // ���������
            char tmp = opter.top(); // �鿴ջ�������
            // ���ջ������������ȼ����ڵ�ǰ�����
            if (priority[tmp] > priority[c]) 
            {
                // ��ջ������������ȼ����ڵ�ǰ�����ʱ��ִ������
                while (priority[tmp] > priority[c] && tmp != '(') 
                {
                    check(pvalue, opter); // ִ������
                    tmp = opter.top(); // ����ջ�������
                    // ���������ʽ������ʶ�����򷵻ؽ��
                    if (tmp == '#' && c == '#') 
                    {
                        return pvalue.top(); // ���ؼ�����
                    }
                }
                // ��ǰ�����ѹ��ջ
                opter.push(c);
            }
            else
            {
                // ���ջ����������ȼ������ڵ�ǰ�������ֱ��ѹջ
                opter.push(c);
            }
        }
    }
    // ���û����ȷ�����������򷵻�-1
    return -1;
}


void check(stack<int> &value, stack<char> &opter) //�ú������������������(ȡֵ0��1)�ĸ���������(0��1)
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