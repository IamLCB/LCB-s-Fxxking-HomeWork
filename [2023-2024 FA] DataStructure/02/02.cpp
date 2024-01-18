#include <iostream>
#include <iomanip>
#include <limits>
using namespace std;

// �ڵ�ṹ��
struct Node {
    int number;
    Node* next;
    Node(int num) : number(num), next(nullptr) {}
};

// ������ѭ������
Node* createCircularList(int N) {
    Node* head = new Node(1);
    Node* current = head;
    for (int i = 2; i <= N; ++i) {
        current->next = new Node(i);
        current = current->next;
    }
    current->next = head; // �γɻ���
    return head;
}

void printRemaining(Node* head, int K) {
    int* remaining = new int[K];
    Node* current = head;
    for (int i = 0; i < K; ++i) {
        remaining[i] = current->number;
        current = current->next;
    }

    // �򵥵�ð������
    for (int i = 0; i < K - 1; i++) {
        for (int j = 0; j < K - i - 1; j++) {
            if (remaining[j] > remaining[j + 1]) {
                int temp = remaining[j];
                remaining[j] = remaining[j + 1];
                remaining[j + 1] = temp;
            }
        }
    }

    cout << "ʣ�������λ��Ϊ��";
    for (int i = 0; i < K; ++i) {
        cout << remaining[i] << " ";
    }
    cout << endl;

    delete[] remaining;
}

// Լɪ������������Ϸ
void josephusGame(int N, int S, int M, int K) {
    Node* head = createCircularList(N);
    Node* prev = head;

    // ��λ����S����
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
        // ɾ����M���ڵ�
        prev->next = head->next;
        cout << "��" << setw(2) <<cnt++ << "���˳��֣����ֱ��Ϊ��        ";
        cout << setiosflags(ios::left);
        cout << setw(2) << head->number << endl;
        cout << resetiosflags(ios::left);
        delete head;
        head = prev->next;
        --N;
    }
    cout << endl;

    // ���ʣ����ÿͱ��
    printRemaining(head, K);
}


int main() {

    int N, S, M, K;
    cout << "����N��Χ��һȦ���ӵ�S���˿�ʼ���α�������M���˳��֣�������һ�˿�ʼ���������ѭ����ֱ��ʣ��K����Ϊֹ" << endl;
    while (true)
    {
        cout << "������������Ϸ��������(N): ";
        cin >> N;
        if (cin.fail() || N <= 0)
        {
            cout << "����������һ����������\n";
            cin.clear();                                         // ��������־
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ���Դ����������ַ�
            continue;
        }
        break;
    }

    while (true)
    {
        cout << "��������Ϸ��ʼ��λ��(S): ";
        cin >> S;
        if (cin.fail() || S <= 0 || S > N)
        {
            cout << "����������һ�����������Ҳ��ܳ�����������\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        break;
    }

    while (true)
    {
        cout << "��������������(M): ";
        cin >> M;
        if (cin.fail() || M <= 0)
        {
            cout << "����������һ����������\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        break;
    }

    while (true)
    {
        cout << "������ʣ�����������(K): ";
        cin >> K;
        if (cin.fail() || K < 0 || K >= N)
        {
            cout << "����������һ���Ǹ��������Ҳ��ܳ�����������\n";
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
