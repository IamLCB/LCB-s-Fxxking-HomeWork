#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;
using namespace std::chrono;

void bubbleSort(int* arr, int n, int& comparisons, int& swaps) {
    comparisons = 0;
    swaps = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            comparisons++;
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swaps++;
            }
        }
    }
}

void selectionSort(int* arr, int n, int& comparisons, int& swaps) {
    comparisons = 0;
    swaps = 0;

    for (int i = 0; i < n - 1; i++) {
        // 找到最小元素的索引
        int min_index = i;
        for (int j = i + 1; j < n; j++) {
            comparisons++;
            if (arr[j] < arr[min_index]) {
                min_index = j;
            }
        }

        // 将找到的最小元素与第 i 个元素交换
        if (min_index != i) {
            swap(arr[i], arr[min_index]);
            swaps++;
        }
    }
}

void insertionSort(int* arr, int n, int& comparisons, int& swaps) {
    comparisons = 0;
    swaps = 0;

    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        // 将 arr[i] 插入到已排序序列 arr[0...i-1] 中的适当位置
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
            comparisons++;
            swaps++;
        }
        arr[j + 1] = key;

        // 当 key 已经在正确的位置时，不算作一次交换
        if (i != j + 1) {
            swaps++;
        }
    }
}

void shellSort(int* arr, int n, int& comparisons, int& swaps) {
    comparisons = 0;
    swaps = 0;

    // 开始时的间隔设为数组长度的一半，并逐渐减半
    for (int gap = n / 2; gap > 0; gap /= 2) {
        // 对于每个间隔，进行插入排序
        for (int i = gap; i < n; i += 1) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
                comparisons++; // 对比较次数进行记录
                swaps++; // 这里的赋值也视为一次交换
            }
            arr[j] = temp;
            if (j != i) {
                swaps++; // 插入操作也视为一次交换
            }
        }
    }
}

int partition(int* arr, int low, int high, int& comparisons, int& swaps) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        comparisons++; // 比较次数增加
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
            swaps++; // 交换次数增加
        }
    }
    swap(arr[i + 1], arr[high]);
    swaps++; // 交换次数增加
    return (i + 1);
}

void quickSort(int* arr, int low, int high, int& comparisons, int& swaps) {
    if (low < high) {
        int pi = partition(arr, low, high, comparisons, swaps);

        quickSort(arr, low, pi - 1, comparisons, swaps);
        quickSort(arr, pi + 1, high, comparisons, swaps);
    }
}

void heapify(int* arr, int n, int i, int& comparisons, int& swaps) {
    int largest = i; // 初始化最大元素为根
    int left = 2 * i + 1; // 左孩子
    int right = 2 * i + 2; // 右孩子

    // 如果左孩子比根大
    if (left < n) {
        comparisons++; // 比较次数增加
        if (arr[left] > arr[largest]) {
            largest = left;
        }
    }

    // 如果右孩子存在且比目前最大的还大
    if (right < n) {
        comparisons++; // 比较次数增加
        if (arr[right] > arr[largest]) {
            largest = right;
        }
    }

    // 如果最大元素不是根
    if (largest != i) {
        swap(arr[i], arr[largest]);
        swaps++; // 交换次数增加

        // 递归地定义子堆
        heapify(arr, n, largest, comparisons, swaps);
    }
}

void heapSort(int* arr, int n, int& comparisons, int& swaps) {
    // 构建堆（重新排列数组）
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i, comparisons, swaps);
    }

    // 一个个从堆顶取出元素
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        swaps++; // 交换次数增加

        // 调用 heapify 减少堆的大小并维护堆的性质
        heapify(arr, i, 0, comparisons, swaps);
    }
}

void merge(int* arr, int left, int mid, int right, int& comparisons, int& swaps) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // 创建临时数组
    int* L = new int[n1];
    int* R = new int[n2];

    // 拷贝数据到临时数组
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    // 合并临时数组
    int i = 0; // 初始索引第一个子数组
    int j = 0; // 初始索引第二个子数组
    int k = left; // 初始索引合并的子数组

    while (i < n1 && j < n2) {
        comparisons++; // 记录比较
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        swaps++; // 记录交换
        k++;
    }

    // 拷贝 L[] 的剩余元素
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
        swaps++; // 记录交换
    }

    // 拷贝 R[] 的剩余元素
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
        swaps++; // 记录交换
    }

    delete[] L;
    delete[] R;
}

void mergeSort(int* arr, int left, int right, int& comparisons, int& swaps) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        // 递归地对左右两半进行排序
        mergeSort(arr, left, mid, comparisons, swaps);
        mergeSort(arr, mid + 1, right, comparisons, swaps);

        // 合并两半
        merge(arr, left, mid, right, comparisons, swaps);
    }
}

void radixSort(int* arr, int n, int& comparisons, int& swaps) {
	int max = arr[0];
    for (int i = 1; i < n; i++) {
		comparisons++; // 记录比较
        if (arr[i] > max) {
			max = arr[i];
		}
	}

	// 对每一位进行计数排序
    for (int exp = 1; max / exp > 0; exp *= 10) {
		int* output = new int[n]; // 输出数组
		int count[10] = { 0 }; // 计数数组

		// 统计每个桶中的元素个数
        for (int i = 0; i < n; i++) {
			count[(arr[i] / exp) % 10]++;
		}

		// 将 count[i] 更新为包含 i 的元素的总数
        for (int i = 1; i < 10; i++) {
			count[i] += count[i - 1];
		}

		// 按照 count[i] 将 arr[i] 放到输出数组中
        for (int i = n - 1; i >= 0; i--) {
			output[count[(arr[i] / exp) % 10] - 1] = arr[i];
			count[(arr[i] / exp) % 10]--;
			swaps++; // 记录交换
		}

		// 将输出数组复制到 arr[] 中，现在 arr[] 包含从当前位排序的数字
        for (int i = 0; i < n; i++) {
			arr[i] = output[i];
		}

		delete[] output;
	}
}


