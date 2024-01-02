#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define N 100 // 定义最大顶点数

// 定义边结构
struct Edge
{
    int u, v, weight; // 边的两个顶点 u, v 和边的权重 weight
    // 重载 < 操作符，便于后续按权重对边进行排序
    bool operator<(const Edge &e) const
    {
        return weight < e.weight;
    }
};

int parent[N]; // 并查集数组，用于维护顶点的集合信息

// 查找集合的代表
int findSet(int i)
{
    // 路径压缩优化：直接将i的父节点设置为集合代表
    if (i != parent[i])
        parent[i] = findSet(parent[i]);
    return parent[i];
}

// 合并两个集合
void unionSet(int u, int v)
{
    // 将一个集合的代表指向另一个集合的代表
    parent[findSet(u)] = findSet(v);
}

int main()
{
    int n, m; // n 代表顶点数，m 代表边数
    cout << "请输入顶点数和边数：";
    cin >> n >> m;

    vector<Edge> edges(m); // 存储所有边的向量
    cout << "请输入边和它们的权重（格式：起点 终点 权重）：\n";

    // 读取边的信息
    for (int i = 0; i < m; ++i)
    {
        cin >> edges[i].u >> edges[i].v >> edges[i].weight;
    }

    // 初始化并查集，每个顶点初始时都是自己的代表
    for (int i = 1; i <= n; ++i)
    {
        parent[i] = i;
    }

    // 对边按权重进行排序
    sort(edges.begin(), edges.end());

    int totalWeight = 0; // 记录最小生成树的总权重
    // 遍历所有边，构建最小生成树
    for (const auto &e : edges)
    {
        // 如果两个顶点属于不同集合，则选择这条边
        if (findSet(e.u) != findSet(e.v))
        {
            cout << "选择边: " << e.u << " - " << e.v << " (权重: " << e.weight << ")\n";
            totalWeight += e.weight;
            unionSet(e.u, e.v); // 合并两个集合
        }
    }

    // 输出最小生成树的总权重
    cout << "最小生成树的总权重: " << totalWeight << endl;

    system("pause");

    return 0;
}
