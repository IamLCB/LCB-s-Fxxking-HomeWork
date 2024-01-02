#include <iostream>
#include <vector>
#include <memory>
#include <limits>

const int N = 13;  // 定义常量N，表示树中节点的最大数量

// 定义二叉树节点结构
struct TreeNode {
    int num;  // 存储节点的数值（频率）
    std::shared_ptr<TreeNode> left;  // 指向左子节点
    std::shared_ptr<TreeNode> right; // 指向右子节点

    // 构造函数，初始化节点
    TreeNode(int n) : num(n), left(nullptr), right(nullptr) {}
};

// 对节点数组进行排序的函数
void sort(std::vector<std::shared_ptr<TreeNode>>& array, int n) {
    for (int i = N - n; i < N - 1; i++) {
        // 如果后一个节点的数值小于前一个节点，则交换它们
        if (array[i]->num > array[i + 1]->num) {
            std::swap(array[i], array[i + 1]);
        }
    }
}

// 构建最优2元树的函数
std::shared_ptr<TreeNode> constructTree(const std::vector<int>& f) {
    std::vector<std::shared_ptr<TreeNode>> nodes(N);

    // 使用频率数组初始化节点
    for (int i = 0; i < N; ++i) {
        nodes[i] = std::make_shared<TreeNode>(f[i]);
    }

    // 迭代构建树的过程
    for (int i = 1; i < N; ++i) {
        // 合并两个频率最低的节点
        auto combined = std::make_shared<TreeNode>(nodes[i - 1]->num + nodes[i]->num);
        combined->left = nodes[i - 1];
        combined->right = nodes[i];
        nodes[i] = combined;
        // 重新排序节点数组
        sort(nodes, N - i);
    }

    // 返回构建的最优2元树的根节点
    return nodes[N - 1];
}

// 二叉树的前序遍历函数，用于生成前缀码
void preorder(const std::shared_ptr<TreeNode>& node, int depth, char c, std::string& s) {
    if (node) {
        s[depth] = (c == '1') ? '0' : '1';
        // 当到达叶节点时，输出该节点的前缀码
        if (!node->left && !node->right) {
            std::cout << node->num << ": ";
            for (int j = 0; j <= depth; ++j) {
                std::cout << s[j];
            }
            std::cout << '\n';
        }
        // 递归遍历左右子节点
        preorder(node->left, depth + 1, '1', s);
        preorder(node->right, depth + 1, '0', s);
    }
}

int main() {
    int n;
    std::cout << "请输入节点个数(必须是正整数且不超过13): ";
    while(!(std::cin >> n) || n <= 0 || n > N) {
        std::cout << "输入无效，请输入一个正整数且不超过13: ";
        std::cin.clear();  // 清除错误标志
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // 忽略错误输入
    }

    std::vector<int> frequencies(N, 0);
    std::cout << "请输入" << n << "个节点的频率(以空格分隔): ";
    for (int i = 0; i < n; ++i) {
        while(!(std::cin >> frequencies[i])) {
            std::cout << "无效输入，请重新输入节点" << i + 1 << "的频率: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    std::string s(2 * N, ' ');
    auto root = constructTree(frequencies);
    preorder(root, 0, '1', s);

    system("pause");

    return 0;
}