#include <iostream>
#include <vector>
#include <limits>

using namespace std;

// 使用Warshall算法计算传递闭包
// @param matrix 引用传递的二维向量，代表关系矩阵
// @param n 矩阵的大小（行数和列数）
void warshallAlgorithm(vector<vector<int>>& matrix, const int n) {
    // 三重循环遍历矩阵中的每个元素
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                // 更新矩阵元素以反映传递性
                matrix[i][j] = matrix[i][j] || (matrix[i][k] && matrix[k][j]);
            }
        }
    }

    // 打印传递闭包矩阵
    cout << "传递闭包为:\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << matrix[i][j] << " ";
        }
        cout << "\n";
    }
}

// 检查输入是否有效，并在必要时清除输入缓冲区
bool validateInput() {
    if (cin.fail()) {
        cin.clear(); // 清除输入缓冲区的错误标志
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 忽略缓冲区直到下一个换行符
        return false;
    }
    return true;
}

void selectOption() {
    int n, d;
    cout << "请输入矩阵的行数和列数: ";
    while (!(cin >> n >> d) || n <= 0 || d <= 0) {
        cout << "无效输入，请重新输入矩阵的行数和列数: ";
        validateInput();
    }

    vector<vector<int>> matrix(n, vector<int>(d));
    cout << "请输入关系矩阵:\n";
    for (int i = 0; i < n; i++) {
        cout << "请输入矩阵的第" << i << "行元素(元素以空格分隔): ";
        for (int j = 0; j < d; j++) {
            while (!(cin >> matrix[i][j])) {
                cout << "无效输入，请重新输入第" << i << "行的第" << j << "个元素: ";
                validateInput();
            }
        }
    }

    warshallAlgorithm(matrix, n);
}

int main() {
    selectOption(); // 运行主要功能
    system("pause");
    return 0;
}
