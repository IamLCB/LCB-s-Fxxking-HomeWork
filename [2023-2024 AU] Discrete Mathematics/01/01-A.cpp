#include <iostream>
#include <chrono>
#include <limits>
#include <Windows.h>

using namespace std;

int main() {
    bool P, Q;
    char s;

    // 主循环：程序会在这个循环中运行，直到用户选择退出
    while (true) {
        // 显示欢迎信息
        cout << "***************************************\n";
        cout << "**                                   **\n";
        cout << "**        欢迎进入逻辑运算程序       **\n";
        cout << "**                                   **\n";
        cout << "***************************************\n\n";

        // 获取P的值，并确保它是0或1
        cout << "\n  请输入P的值（0或1）,以回车结束:";
        while (!(cin >> P) || (P != 0 && P != 1)) {
            cout << "\n  P的值输入有误,请重新输入!";
            cin.clear(); // 清除输入流的错误标志
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 忽略错误的输入
            Sleep(2000);
        }

        // 获取Q的值，并确保它是0或1
        cout << "\n  请输入Q的值（0或1）,以回车结束:";
        while (!(cin >> Q) || (Q != 0 && Q != 1)) {
            cout << "\n  Q的值输入有误,请重新输入!";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            Sleep(2000);
        }

        // 执行逻辑运算
        bool andOp = P && Q; // 与运算
        bool orOp = P || Q; // 或运算
        bool implyOp = !P || Q; // 蕴含运算
        bool biconditionalOp = (implyOp) && (!Q || P); // 等值运算

        // 输出逻辑运算的结果
        cout << "\n\n  合取:\n       P/\\Q = " << andOp << "\n";
        cout << "  析取:\n       P\\/Q = " << orOp << "\n";
        cout << "  条件:\n       P->Q = " << implyOp << "\n";
        cout << "  双条件:\n       P<->Q = " << biconditionalOp << "\n";

        // 询问用户是否继续运算
        cout << "\n是否继续运算?（y/n）";
        cin >> s;
        if (s == 'n') {
            cout << "欢迎下次再次使用!\n";
            break; // 退出程序
        } else if (s != 'y') {
            cout << "输入错误,请重新输入!\n";
        }
    }
    return 0;
}
