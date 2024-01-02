#include <iostream>
using namespace std;

int main()
{
    std::string yes = "是作案者", no = "不是作案者";
    int A, B, C, D, E;
    for (A = 0; A <= 1; A++)
        for (B = 0; B <= 1; B++)
            for (C = 0; C <= 1; C++)
                for (D = 0; D <= 1; D++)
                    for (E = 0; E <= 1; E++)
                        if ((A || B) && (!A || C) && (!D || E) && (D || !C) && !E)
                            cout << "A" << ((A == 1) ? yes : no) << ", B" << ((B == 1) ? yes : no) << endl;
   
   
    system("pause");
    return 0;
}


