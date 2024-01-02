#include <iomanip>
#include "sorts.h"

void generateRandomNumbers(int* numbers, int n) {
    for (int i = 0; i < n; i++) {
        numbers[i] = rand() % 10000; 
    }
}

void printStats(const string& sortMethod, int comparisons, int swaps, double duration) {
    cout << sortMethod << ":\n";
    cout << "  比较次数: " << comparisons << "\n";
    cout << "  交换次数: " << swaps << "\n";
    cout << "  所用时间: " << duration << " ms\n";
}

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    cout << setw(48) << setfill('=') << "" << endl;
    cout << setfill(' ');
    cout << "**" << setw(16) << "" << "排序算法比较" << setw(16) << "" << "**\n";
    cout << setw(48) << setfill('=') << "" << endl;
    cout << setfill(' ');
    cout << "**" << setw(16) << "" << "1 --- 冒泡排序" << setw(14) << "" << "**\n";
    cout << "**" << setw(16) << "" << "2 --- 选择排序" << setw(14) << "" << "**\n";
    cout << "**" << setw(16) << "" << "3 --- 直接插入排序" << setw(10) << "" << "**\n";
    cout << "**" << setw(16) << "" << "4 --- 希尔排序" << setw(14) << "" << "**\n";
    cout << "**" << setw(16) << "" << "5 --- 快速排序" << setw(14) << "" << "**\n";
    cout << "**" << setw(16) << "" << "6 --- 堆排序" << setw(16) << "" << "**\n";
    cout << "**" << setw(16) << "" << "7 --- 归并排序" << setw(14) << "" << "**\n";
    cout << "**" << setw(16) << "" << "8 --- 基数排序" << setw(14) << "" << "**\n";
    cout << "**" << setw(16) << "" << "9 --- 退出程序" << setw(14) << "" << "**\n";
    cout << setw(48) << setfill('=') << "" << setfill(' ') << endl << endl;

    int n;
    cout << "请输入要产生的随机数的个数: ";
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
        cout << "\n请选择排序算法: ";
        cin >> choice;
        switch (choice)
        {
            case 1:
                copy(numbers, numbers + n, temp);
                start = high_resolution_clock::now();
                bubbleSort(temp, n, comparisons, swaps);
                stop = high_resolution_clock::now();
                duration = stop - start;
                printStats("冒泡排序", comparisons, swaps, duration.count());
                delete[] temp;
                break;
            case 2:
                copy(numbers, numbers + n, temp);
				start = high_resolution_clock::now();
				selectionSort(temp, n, comparisons, swaps);
				stop = high_resolution_clock::now();
				duration = stop - start;
				printStats("选择排序", comparisons, swaps, duration.count());
				delete[] temp;
				break;
            case 3:
				copy(numbers, numbers + n, temp);
                start = high_resolution_clock::now();
                insertionSort(temp, n, comparisons, swaps);
                stop = high_resolution_clock::now();
                duration = stop - start;
                printStats("直接插入排序", comparisons, swaps, duration.count());
                delete[] temp;
                break;
            case 4:
                copy(numbers, numbers + n, temp);
				start = high_resolution_clock::now();
				shellSort(temp, n, comparisons, swaps);
				stop = high_resolution_clock::now();
				duration = stop - start;
				printStats("希尔排序", comparisons, swaps, duration.count());
				delete[] temp;
				break;
            case 5:
                copy(numbers, numbers + n, temp);
                start = high_resolution_clock::now();
                quickSort(temp, 0, n - 1, comparisons, swaps);
                stop = high_resolution_clock::now();
                duration = stop - start;
                printStats("快速排序", comparisons, swaps, duration.count());
                delete[] temp;
                break;
            case 6:
                copy(numbers, numbers + n, temp);
				start = high_resolution_clock::now();
				heapSort(temp, n, comparisons, swaps);
				stop = high_resolution_clock::now();
				duration = stop - start;
				printStats("堆排序", comparisons, swaps, duration.count());
				delete[] temp;
				break;
            case 7:
                copy(numbers, numbers + n, temp);
				start = high_resolution_clock::now();
                mergeSort(temp, 0, n - 1, comparisons, swaps);
				stop = high_resolution_clock::now();
				duration = stop - start;
				printStats("归并排序", comparisons, swaps, duration.count());
				delete[] temp;
				break;
            case 8:
                copy(numbers, numbers + n, temp);
                start = high_resolution_clock::now();
                radixSort(temp, n, comparisons, swaps);
                stop = high_resolution_clock::now();
                duration = stop - start;
                printStats("基数排序", comparisons, swaps, duration.count());
                delete[] temp;
                break;
            case 9:
                exit = true;
				break;
            default:
                cin.clear();
                cin.ignore(1024, '\n');
                cout << "请输入合法的执行操作符" << endl;
        }

    }
    delete[] numbers;

    system("pause");

    return 0;
}
