#include <iostream>
#include <vector>
#include <limits>
using namespace std;

void output(const vector<vector<int>>& s);
void reflexiveClosure(vector<vector<int>>& s);
void symmetricClosure(vector<vector<int>>& s);
void transitiveClosure(vector<vector<int>>& s);
void selectOption();

vector<vector<int>> s;
int n, d;

int main() {
    selectOption();
    return 0;
}

void selectOption() {
    cout << "请输入矩阵的行数和列数: ";
    cin >> n >> d;
    s.resize(n, vector<int>(d));

    cout << "请输入关系矩阵:\n";
    for (int i = 0; i < n; i++) {
        cout << "请输入矩阵的第" << i << "行元素(元素以空格分隔): ";
        for (int j = 0; j < d; j++) {
            cin >> s[i][j];
        }
    }

    cout << "输入对应序号选择算法\n1:自反闭包\n2:传递闭包\n3:对称闭包\n4:退出\n";
    char choice;
    cin >> choice;
    bool ex = false;
    while(!ex)
    {
        switch (choice) {
        case '1': reflexiveClosure(s); break;
        case '2': transitiveClosure(s); break;
        case '3': symmetricClosure(s); break;
        case '4': exit(0);
        default: 
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.clear(); 
            cout << "无效选择\n"; selectOption();
            ex = true;
        }
    }
}

void output(const vector<vector<int>>& s) {
    cout << "所求关系矩阵为:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < d; j++) {
            cout << s[i][j] << " ";
        }
        cout << endl;
    }
}

void reflexiveClosure(vector<vector<int>>& s) {
    for (int i = 0; i < n; i++) {
        s[i][i] = 1;
    }
    output(s);
    selectOption();
}

void symmetricClosure(vector<vector<int>>& s) {
    vector<vector<int>> s1 = s;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < d; j++) {
            s[i][j] = s[i][j] || s1[j][i];
        }
    }
    output(s);
    selectOption();
}

void dfs(int start, int current, vector<vector<int>>& t) {
    for (int next = 0; next < d; next++) {
        if (s[current][next] && !t[start][next]) {
            t[start][next] = 1;
            dfs(start, next, t);
        }
    }
}

void transitiveClosure(vector<vector<int>>& s) {
    vector<vector<int>> t(n, vector<int>(d, 0));
    for (int i = 0; i < n; i++) {
        dfs(i, i, t);
    }
    output(t);
    selectOption();
}
