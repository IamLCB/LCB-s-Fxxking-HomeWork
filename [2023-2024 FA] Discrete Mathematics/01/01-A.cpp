#include <iostream>
#include <chrono>
#include <limits>
#include <Windows.h>

using namespace std;

int main() {
    bool P, Q;
    char s;

    // ��ѭ��������������ѭ�������У�ֱ���û�ѡ���˳�
    while (true) {
        // ��ʾ��ӭ��Ϣ
        cout << "***************************************\n";
        cout << "**                                   **\n";
        cout << "**        ��ӭ�����߼��������       **\n";
        cout << "**                                   **\n";
        cout << "***************************************\n\n";

        // ��ȡP��ֵ����ȷ������0��1
        cout << "\n  ������P��ֵ��0��1��,�Իس�����:";
        while (!(cin >> P) || (P != 0 && P != 1)) {
            cout << "\n  P��ֵ��������,����������!";
            cin.clear(); // ����������Ĵ����־
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ���Դ��������
            Sleep(2000);
        }

        // ��ȡQ��ֵ����ȷ������0��1
        cout << "\n  ������Q��ֵ��0��1��,�Իس�����:";
        while (!(cin >> Q) || (Q != 0 && Q != 1)) {
            cout << "\n  Q��ֵ��������,����������!";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            Sleep(2000);
        }

        // ִ���߼�����
        bool andOp = P && Q; // ������
        bool orOp = P || Q; // ������
        bool implyOp = !P || Q; // �̺�����
        bool biconditionalOp = (implyOp) && (!Q || P); // ��ֵ����

        // ����߼�����Ľ��
        cout << "\n\n  ��ȡ:\n       P/\\Q = " << andOp << "\n";
        cout << "  ��ȡ:\n       P\\/Q = " << orOp << "\n";
        cout << "  ����:\n       P->Q = " << implyOp << "\n";
        cout << "  ˫����:\n       P<->Q = " << biconditionalOp << "\n";

        // ѯ���û��Ƿ��������
        cout << "\n�Ƿ��������?��y/n��";
        cin >> s;
        if (s == 'n') {
            cout << "��ӭ�´��ٴ�ʹ��!\n";
            break; // �˳�����
        } else if (s != 'y') {
            cout << "�������,����������!\n";
        }
    }
    return 0;
}
