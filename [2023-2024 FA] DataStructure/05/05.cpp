#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    string filename;
    cout << "请输入文件名: ";
    getline(cin, filename);

    // Creating and opening a file with the provided filename
    ofstream outfile(filename);
    if (!outfile.is_open()) {
        // Error message if the file fails to create
        cerr << "文件创建失败" << endl;
        return 1;
    }

    cout << "请输入一段英文：";
    string text;
    getline(cin, text);
    // Writing the entered text to the file
    outfile << text;
    // Closing the file
    outfile.close();

    // Confirming the text has been saved
    cout << "本段文本已保存在文本文件" << "\" " << filename << " \"中。" << endl;
    

    string keyword;
    cout << "\n请输入要检索的关键字（严格匹配，大小写敏感）：";
    cin >> keyword;
    
    // Displaying the content of the file
    cout << "显示源文件" << "\" " << filename << " \"：" << endl << endl;

    // Opening the file for reading
    ifstream infile(filename);
    if (!infile.is_open()) {
        // Error message if the file fails to open
        cerr << "文件读取失败" << endl;
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

    cout << "在源文件中共检索到 " << count << " 个关键字 " << "\" " << keyword << " \"" << "。" << endl;

    // Closing the file
    infile.close();
    system("pause");

    return 0;
}
