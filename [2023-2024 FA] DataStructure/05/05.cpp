#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    string filename;
    cout << "�������ļ���: ";
    getline(cin, filename);

    // Creating and opening a file with the provided filename
    ofstream outfile(filename);
    if (!outfile.is_open()) {
        // Error message if the file fails to create
        cerr << "�ļ�����ʧ��" << endl;
        return 1;
    }

    cout << "������һ��Ӣ�ģ�";
    string text;
    getline(cin, text);
    // Writing the entered text to the file
    outfile << text;
    // Closing the file
    outfile.close();

    // Confirming the text has been saved
    cout << "�����ı��ѱ������ı��ļ�" << "\" " << filename << " \"�С�" << endl;
    

    string keyword;
    cout << "\n������Ҫ�����Ĺؼ��֣��ϸ�ƥ�䣬��Сд���У���";
    cin >> keyword;
    
    // Displaying the content of the file
    cout << "��ʾԴ�ļ�" << "\" " << filename << " \"��" << endl << endl;

    // Opening the file for reading
    ifstream infile(filename);
    if (!infile.is_open()) {
        // Error message if the file fails to open
        cerr << "�ļ���ȡʧ��" << endl;
        return 1;
    }
    else {
        // Printing the content of the file
        cout << text << endl << endl;
    }

    int count = 0;
    string word;
    // Reading each word from the file
    while (infile >> word) {
        // Incrementing count if the word matches the keyword
        if (word == keyword) { 
            ++count;
        }
    }

    cout << "��Դ�ļ��й������� " << count << " ���ؼ��� " << "\" " << keyword << " \"" << "��" << endl;

    // Closing the file
    infile.close();
    system("pause");

    return 0;
}
