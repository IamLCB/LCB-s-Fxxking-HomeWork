#include <iostream>
#include <iomanip>
#include <limits>
using namespace std;

// 节点结构体
struct Node {
    int number;
    Node* next;
    Node(int num) : number(num), next(nullptr) {}
};

// 创建单循环链表
Node* createCircularList(int N) {
    Node* head = new Node(1);
    Node* current = head;
    for (int i = 2; i <= N; ++i) {
        current->next = new Node(i);
        current = current->next;
    }
    current->next = head; // 形成环形
    return head;
}

void printRemaining(Node* head, int K) {
    int* remaining = new int[K];
    Node* current = head;
    for (int i = 0; i < K; ++i) {
        remaining[i] = current->number;
        current = current->next;
    }

    // 简单的冒泡排序
    for (int i = 0; i < K - 1; i++) {
        for (int j = 0; j < K - i - 1; j++) {
            if (remaining[j] > remaining[j + 1]) {
                int temp = remaining[j];
                remaining[j] = remaining[j + 1];
                remaining[j + 1] = temp;
            }
        }
    }

    cout << "剩余的生者位置为：";
    for (int i = 0; i < K; ++i) {
        cout << remaining[i] << " ";
    }
    cout << endl;

    delete[] remaining;
}

// 约瑟夫生者死者游戏
void josephusGame(int N, int S, int M, int K) {
    Node* head = createCircularList(N);
    Node* prev = head;

    // 定位到第S个人
    for (int i = 1; i < S; ++i) {
        prev = head;
        head = head->next;
    }
    int cnt = 1;
    cout << endl;
    while (N > K) {
        for (int count = 1; count < M; ++count) {
            prev = head;
            head = head->next;
        }
        // 删除第M个节点
        prev->next = head->next;
        cout << "第" << setw(2) <<cnt++ << "个人出局，出局编号为：        ";
        cout << setiosflags(ios::left);
        cout << setw(2) << head->number << endl;
        cout << resetiosflags(ios::left);
        delete head;
        head = prev->next;
        --N;
    }
    cout << endl;

    // 输出剩余的旅客编号
    printRemaining(head, K);
}


int main() {

    int N, S, M, K;
    cout << "现有N人围成一圈，从第S个人开始依次报数，报M的人出局，再又下一人开始报数，如此循环，直至剩下K个人为止" << endl;
    while (true)
    {
        cout << "请输入生死游戏的总人数(N): ";
        cin >> N;
        if (cin.fail() || N <= 0)
        {
            cout << "错误：请输入一个正整数。\n";
            cin.clear();                                         // 清除错误标志
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 忽略错误输入后的字符
            continue;
        }
        break;
    }

    while (true)
    {
        cout << "请输入游戏开始的位置(S): ";
        cin >> S;
        if (cin.fail() || S <= 0 || S > N)
        {
            cout << "错误：请输入一个正整数，且不能超过总人数。\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        break;
    }

    while (true)
    {
        cout << "请输入死亡数字(M): ";
        cin >> M;
        if (cin.fail() || M <= 0)
        {
            cout << "错误：请输入一个正整数。\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        break;
    }

    while (true)
    {
        cout << "请输入剩余的生者人数(K): ";
        cin >> K;
        if (cin.fail() || K < 0 || K >= N)
        {
            cout << "错误：请输入一个非负整数，且不能超过总人数。\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        break;
    }

    josephusGame(N, S, M, K);
    
    system("pause");
    
    return 0;
}
