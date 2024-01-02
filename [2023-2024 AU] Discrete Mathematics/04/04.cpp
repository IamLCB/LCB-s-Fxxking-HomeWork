#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define N 100 // ������󶥵���

// ����߽ṹ
struct Edge
{
    int u, v, weight; // �ߵ��������� u, v �ͱߵ�Ȩ�� weight
    // ���� < �����������ں�����Ȩ�ضԱ߽�������
    bool operator<(const Edge &e) const
    {
        return weight < e.weight;
    }
};

int parent[N]; // ���鼯���飬����ά������ļ�����Ϣ

// ���Ҽ��ϵĴ���
int findSet(int i)
{
    // ·��ѹ���Ż���ֱ�ӽ�i�ĸ��ڵ�����Ϊ���ϴ���
    if (i != parent[i])
        parent[i] = findSet(parent[i]);
    return parent[i];
}

// �ϲ���������
void unionSet(int u, int v)
{
    // ��һ�����ϵĴ���ָ����һ�����ϵĴ���
    parent[findSet(u)] = findSet(v);
}

int main()
{
    int n, m; // n ����������m �������
    cout << "�����붥�����ͱ�����";
    cin >> n >> m;

    vector<Edge> edges(m); // �洢���бߵ�����
    cout << "������ߺ����ǵ�Ȩ�أ���ʽ����� �յ� Ȩ�أ���\n";

    // ��ȡ�ߵ���Ϣ
    for (int i = 0; i < m; ++i)
    {
        cin >> edges[i].u >> edges[i].v >> edges[i].weight;
    }

    // ��ʼ�����鼯��ÿ�������ʼʱ�����Լ��Ĵ���
    for (int i = 1; i <= n; ++i)
    {
        parent[i] = i;
    }

    // �Ա߰�Ȩ�ؽ�������
    sort(edges.begin(), edges.end());

    int totalWeight = 0; // ��¼��С����������Ȩ��
    // �������бߣ�������С������
    for (const auto &e : edges)
    {
        // ��������������ڲ�ͬ���ϣ���ѡ��������
        if (findSet(e.u) != findSet(e.v))
        {
            cout << "ѡ���: " << e.u << " - " << e.v << " (Ȩ��: " << e.weight << ")\n";
            totalWeight += e.weight;
            unionSet(e.u, e.v); // �ϲ���������
        }
    }

    // �����С����������Ȩ��
    cout << "��С����������Ȩ��: " << totalWeight << endl;

    system("pause");

    return 0;
}
