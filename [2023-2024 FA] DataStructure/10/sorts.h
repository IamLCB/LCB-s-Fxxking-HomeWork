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
        // �ҵ���СԪ�ص�����
        int min_index = i;
        for (int j = i + 1; j < n; j++) {
            comparisons++;
            if (arr[j] < arr[min_index]) {
                min_index = j;
            }
        }

        // ���ҵ�����СԪ����� i ��Ԫ�ؽ���
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

        // �� arr[i] ���뵽���������� arr[0...i-1] �е��ʵ�λ��
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
            comparisons++;
            swaps++;
        }
        arr[j + 1] = key;

        // �� key �Ѿ�����ȷ��λ��ʱ��������һ�ν���
        if (i != j + 1) {
            swaps++;
        }
    }
}

void shellSort(int* arr, int n, int& comparisons, int& swaps) {
    comparisons = 0;
    swaps = 0;

    // ��ʼʱ�ļ����Ϊ���鳤�ȵ�һ�룬���𽥼���
    for (int gap = n / 2; gap > 0; gap /= 2) {
        // ����ÿ����������в�������
        for (int i = gap; i < n; i += 1) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
                comparisons++; // �ԱȽϴ������м�¼
                swaps++; // ����ĸ�ֵҲ��Ϊһ�ν���
            }
            arr[j] = temp;
            if (j != i) {
                swaps++; // �������Ҳ��Ϊһ�ν���
            }
        }
    }
}

int partition(int* arr, int low, int high, int& comparisons, int& swaps) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        comparisons++; // �Ƚϴ�������
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
            swaps++; // ������������
        }
    }
    swap(arr[i + 1], arr[high]);
    swaps++; // ������������
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
    int largest = i; // ��ʼ�����Ԫ��Ϊ��
    int left = 2 * i + 1; // ����
    int right = 2 * i + 2; // �Һ���

    // ������ӱȸ���
    if (left < n) {
        comparisons++; // �Ƚϴ�������
        if (arr[left] > arr[largest]) {
            largest = left;
        }
    }

    // ����Һ��Ӵ����ұ�Ŀǰ���Ļ���
    if (right < n) {
        comparisons++; // �Ƚϴ�������
        if (arr[right] > arr[largest]) {
            largest = right;
        }
    }

    // ������Ԫ�ز��Ǹ�
    if (largest != i) {
        swap(arr[i], arr[largest]);
        swaps++; // ������������

        // �ݹ�ض����Ӷ�
        heapify(arr, n, largest, comparisons, swaps);
    }
}

void heapSort(int* arr, int n, int& comparisons, int& swaps) {
    // �����ѣ������������飩
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i, comparisons, swaps);
    }

    // һ�����ӶѶ�ȡ��Ԫ��
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        swaps++; // ������������

        // ���� heapify ���ٶѵĴ�С��ά���ѵ�����
        heapify(arr, i, 0, comparisons, swaps);
    }
}

void merge(int* arr, int left, int mid, int right, int& comparisons, int& swaps) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // ������ʱ����
    int* L = new int[n1];
    int* R = new int[n2];

    // �������ݵ���ʱ����
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    // �ϲ���ʱ����
    int i = 0; // ��ʼ������һ��������
    int j = 0; // ��ʼ�����ڶ���������
    int k = left; // ��ʼ�����ϲ���������

    while (i < n1 && j < n2) {
        comparisons++; // ��¼�Ƚ�
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        swaps++; // ��¼����
        k++;
    }

    // ���� L[] ��ʣ��Ԫ��
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
        swaps++; // ��¼����
    }

    // ���� R[] ��ʣ��Ԫ��
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
        swaps++; // ��¼����
    }

    delete[] L;
    delete[] R;
}

void mergeSort(int* arr, int left, int right, int& comparisons, int& swaps) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        // �ݹ�ض����������������
        mergeSort(arr, left, mid, comparisons, swaps);
        mergeSort(arr, mid + 1, right, comparisons, swaps);

        // �ϲ�����
        merge(arr, left, mid, right, comparisons, swaps);
    }
}

void radixSort(int* arr, int n, int& comparisons, int& swaps) {
	int max = arr[0];
    for (int i = 1; i < n; i++) {
		comparisons++; // ��¼�Ƚ�
        if (arr[i] > max) {
			max = arr[i];
		}
	}

	// ��ÿһλ���м�������
    for (int exp = 1; max / exp > 0; exp *= 10) {
		int* output = new int[n]; // �������
		int count[10] = { 0 }; // ��������

		// ͳ��ÿ��Ͱ�е�Ԫ�ظ���
        for (int i = 0; i < n; i++) {
			count[(arr[i] / exp) % 10]++;
		}

		// �� count[i] ����Ϊ���� i ��Ԫ�ص�����
        for (int i = 1; i < 10; i++) {
			count[i] += count[i - 1];
		}

		// ���� count[i] �� arr[i] �ŵ����������
        for (int i = n - 1; i >= 0; i--) {
			output[count[(arr[i] / exp) % 10] - 1] = arr[i];
			count[(arr[i] / exp) % 10]--;
			swaps++; // ��¼����
		}

		// ��������鸴�Ƶ� arr[] �У����� arr[] �����ӵ�ǰλ���������
        for (int i = 0; i < n; i++) {
			arr[i] = output[i];
		}

		delete[] output;
	}
}


