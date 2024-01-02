#include <iostream>
#include <vector>
#include <limits>

using namespace std;

// ʹ��Warshall�㷨���㴫�ݱհ�
// @param matrix ���ô��ݵĶ�ά�����������ϵ����
// @param n ����Ĵ�С��������������
void warshallAlgorithm(vector<vector<int>>& matrix, const int n) {
    // ����ѭ�����������е�ÿ��Ԫ��
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                // ���¾���Ԫ���Է�ӳ������
                matrix[i][j] = matrix[i][j] || (matrix[i][k] && matrix[k][j]);
            }
        }
    }

    // ��ӡ���ݱհ�����
    cout << "���ݱհ�Ϊ:\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << matrix[i][j] << " ";
        }
        cout << "\n";
    }
}

// ��������Ƿ���Ч�����ڱ�Ҫʱ������뻺����
bool validateInput() {
    if (cin.fail()) {
        cin.clear(); // ������뻺�����Ĵ����־
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ���Ի�����ֱ����һ�����з�
        return false;
    }
    return true;
}

void selectOption() {
    int n, d;
    cout << "��������������������: ";
    while (!(cin >> n >> d) || n <= 0 || d <= 0) {
        cout << "��Ч���룬������������������������: ";
        validateInput();
    }

    vector<vector<int>> matrix(n, vector<int>(d));
    cout << "�������ϵ����:\n";
    for (int i = 0; i < n; i++) {
        cout << "���������ĵ�" << i << "��Ԫ��(Ԫ���Կո�ָ�): ";
        for (int j = 0; j < d; j++) {
            while (!(cin >> matrix[i][j])) {
                cout << "��Ч���룬�����������" << i << "�еĵ�" << j << "��Ԫ��: ";
                validateInput();
            }
        }
    }

    warshallAlgorithm(matrix, n);
}

int main() {
    selectOption(); // ������Ҫ����
    system("pause");
    return 0;
}
