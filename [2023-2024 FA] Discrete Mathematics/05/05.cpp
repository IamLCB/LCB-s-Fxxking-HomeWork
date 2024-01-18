#include <iostream>
#include <vector>
#include <memory>
#include <limits>

const int N = 13;  // ���峣��N����ʾ���нڵ���������

// ����������ڵ�ṹ
struct TreeNode {
    int num;  // �洢�ڵ����ֵ��Ƶ�ʣ�
    std::shared_ptr<TreeNode> left;  // ָ�����ӽڵ�
    std::shared_ptr<TreeNode> right; // ָ�����ӽڵ�

    // ���캯������ʼ���ڵ�
    TreeNode(int n) : num(n), left(nullptr), right(nullptr) {}
};

// �Խڵ������������ĺ���
void sort(std::vector<std::shared_ptr<TreeNode>>& array, int n) {
    for (int i = N - n; i < N - 1; i++) {
        // �����һ���ڵ����ֵС��ǰһ���ڵ㣬�򽻻�����
        if (array[i]->num > array[i + 1]->num) {
            std::swap(array[i], array[i + 1]);
        }
    }
}

// ��������2Ԫ���ĺ���
std::shared_ptr<TreeNode> constructTree(const std::vector<int>& f) {
    std::vector<std::shared_ptr<TreeNode>> nodes(N);

    // ʹ��Ƶ�������ʼ���ڵ�
    for (int i = 0; i < N; ++i) {
        nodes[i] = std::make_shared<TreeNode>(f[i]);
    }

    // �����������Ĺ���
    for (int i = 1; i < N; ++i) {
        // �ϲ�����Ƶ����͵Ľڵ�
        auto combined = std::make_shared<TreeNode>(nodes[i - 1]->num + nodes[i]->num);
        combined->left = nodes[i - 1];
        combined->right = nodes[i];
        nodes[i] = combined;
        // ��������ڵ�����
        sort(nodes, N - i);
    }

    // ���ع���������2Ԫ���ĸ��ڵ�
    return nodes[N - 1];
}

// ��������ǰ�������������������ǰ׺��
void preorder(const std::shared_ptr<TreeNode>& node, int depth, char c, std::string& s) {
    if (node) {
        s[depth] = (c == '1') ? '0' : '1';
        // ������Ҷ�ڵ�ʱ������ýڵ��ǰ׺��
        if (!node->left && !node->right) {
            std::cout << node->num << ": ";
            for (int j = 0; j <= depth; ++j) {
                std::cout << s[j];
            }
            std::cout << '\n';
        }
        // �ݹ���������ӽڵ�
        preorder(node->left, depth + 1, '1', s);
        preorder(node->right, depth + 1, '0', s);
    }
}

int main() {
    int n;
    std::cout << "������ڵ����(�������������Ҳ�����13): ";
    while(!(std::cin >> n) || n <= 0 || n > N) {
        std::cout << "������Ч��������һ���������Ҳ�����13: ";
        std::cin.clear();  // ��������־
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // ���Դ�������
    }

    std::vector<int> frequencies(N, 0);
    std::cout << "������" << n << "���ڵ��Ƶ��(�Կո�ָ�): ";
    for (int i = 0; i < n; ++i) {
        while(!(std::cin >> frequencies[i])) {
            std::cout << "��Ч���룬����������ڵ�" << i + 1 << "��Ƶ��: ";
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