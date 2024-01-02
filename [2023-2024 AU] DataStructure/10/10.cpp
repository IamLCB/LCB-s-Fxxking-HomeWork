#include <iomanip>
#include "sorts.h"

void generateRandomNumbers(int* numbers, int n) {
    for (int i = 0; i < n; i++) {
        numbers[i] = rand() % 10000; 
    }
}

void printStats(const string& sortMethod, int comparisons, int swaps, double duration) {
    cout << sortMethod << ":\n";
    cout << "  �Ƚϴ���: " << comparisons << "\n";
    cout << "  ��������: " << swaps << "\n";
    cout << "  ����ʱ��: " << duration << " ms\n";
}

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    cout << setw(48) << setfill('=') << "" << endl;
    cout << setfill(' ');
    cout << "**" << setw(16) << "" << "�����㷨�Ƚ�" << setw(16) << "" << "**\n";
    cout << setw(48) << setfill('=') << "" << endl;
    cout << setfill(' ');
    cout << "**" << setw(16) << "" << "1 --- ð������" << setw(14) << "" << "**\n";
    cout << "**" << setw(16) << "" << "2 --- ѡ������" << setw(14) << "" << "**\n";
    cout << "**" << setw(16) << "" << "3 --- ֱ�Ӳ�������" << setw(10) << "" << "**\n";
    cout << "**" << setw(16) << "" << "4 --- ϣ������" << setw(14) << "" << "**\n";
    cout << "**" << setw(16) << "" << "5 --- ��������" << setw(14) << "" << "**\n";
    cout << "**" << setw(16) << "" << "6 --- ������" << setw(16) << "" << "**\n";
    cout << "**" << setw(16) << "" << "7 --- �鲢����" << setw(14) << "" << "**\n";
    cout << "**" << setw(16) << "" << "8 --- ��������" << setw(14) << "" << "**\n";
    cout << "**" << setw(16) << "" << "9 --- �˳�����" << setw(14) << "" << "**\n";
    cout << setw(48) << setfill('=') << "" << setfill(' ') << endl << endl;

    int n;
    cout << "������Ҫ������������ĸ���: ";
    cin >> n;
    int* numbers = new int[n];
    generateRandomNumbers(numbers, n);

    int comparisons, swaps;
    duration<double, milli> duration;
    auto start = high_resolution_clock::now();
    auto stop = high_resolution_clock::now();
    
    int choice;
    bool exit = false;
    while (!exit) {
        comparisons = 0;
        swaps = 0;
        int* temp = new int[n];
        cout << "\n��ѡ�������㷨: ";
        cin >> choice;
        switch (choice)
        {
            case 1:
                copy(numbers, numbers + n, temp);
                start = high_resolution_clock::now();
                bubbleSort(temp, n, comparisons, swaps);
                stop = high_resolution_clock::now();
                duration = stop - start;
                printStats("ð������", comparisons, swaps, duration.count());
                delete[] temp;
                break;
            case 2:
                copy(numbers, numbers + n, temp);
				start = high_resolution_clock::now();
				selectionSort(temp, n, comparisons, swaps);
				stop = high_resolution_clock::now();
				duration = stop - start;
				printStats("ѡ������", comparisons, swaps, duration.count());
				delete[] temp;
				break;
            case 3:
				copy(numbers, numbers + n, temp);
                start = high_resolution_clock::now();
                insertionSort(temp, n, comparisons, swaps);
                stop = high_resolution_clock::now();
                duration = stop - start;
                printStats("ֱ�Ӳ�������", comparisons, swaps, duration.count());
                delete[] temp;
                break;
            case 4:
                copy(numbers, numbers + n, temp);
				start = high_resolution_clock::now();
				shellSort(temp, n, comparisons, swaps);
				stop = high_resolution_clock::now();
				duration = stop - start;
				printStats("ϣ������", comparisons, swaps, duration.count());
				delete[] temp;
				break;
            case 5:
                copy(numbers, numbers + n, temp);
                start = high_resolution_clock::now();
                quickSort(temp, 0, n - 1, comparisons, swaps);
                stop = high_resolution_clock::now();
                duration = stop - start;
                printStats("��������", comparisons, swaps, duration.count());
                delete[] temp;
                break;
            case 6:
                copy(numbers, numbers + n, temp);
				start = high_resolution_clock::now();
				heapSort(temp, n, comparisons, swaps);
				stop = high_resolution_clock::now();
				duration = stop - start;
				printStats("������", comparisons, swaps, duration.count());
				delete[] temp;
				break;
            case 7:
                copy(numbers, numbers + n, temp);
				start = high_resolution_clock::now();
                mergeSort(temp, 0, n - 1, comparisons, swaps);
				stop = high_resolution_clock::now();
				duration = stop - start;
				printStats("�鲢����", comparisons, swaps, duration.count());
				delete[] temp;
				break;
            case 8:
                copy(numbers, numbers + n, temp);
                start = high_resolution_clock::now();
                radixSort(temp, n, comparisons, swaps);
                stop = high_resolution_clock::now();
                duration = stop - start;
                printStats("��������", comparisons, swaps, duration.count());
                delete[] temp;
                break;
            case 9:
                exit = true;
				break;
            default:
                cin.clear();
                cin.ignore(1024, '\n');
                cout << "������Ϸ���ִ�в�����" << endl;
        }

    }
    delete[] numbers;

    system("pause");

    return 0;
}
