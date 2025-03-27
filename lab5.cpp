#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cassert>

void generator(std::vector<int>& a, int n) {
    for (int i = 0; i < n; i++) {
        a[i] = static_cast<int>(std::rand());
    }
}

void bubbleSort(std::vector<int>& a, int n) { // 8+4 = 12 байт
    for (int i = 0; i < n - 1; i++) { // 4 байта
        for (int j = 0; j < n - i - 1; j++) { // 4 байта
            if (a[j] > a[j + 1])
                std::swap(a[j], a[j + 1]);
        }
    }
}

int part(std::vector<int>& a, int left, int right) { // 8+4+4=16 байт
    int pivot = a[right]; // 4 байт
    int i = left - 1; // 4 байт
    for (int j = left; j <= right - 1; j++) { // 4 байт
        if (a[j] < pivot) {
            i++;
            std::swap(a[i], a[j]);
        }
    }
    std::swap(a[i + 1], a[right]);
    return i + 1;
}

void quick_sort(std::vector<int>& a, int left, int right) { // 8+4+4=16 байт
    if (left < right) {
        int pi = part(a, left, right); // 4 байта
        quick_sort(a, left, pi - 1);
        quick_sort(a, pi + 1, right);
    }
}

int getMin(std::vector<int>& a, int n) // 8+4 = 12 байт
{
    int res = a[0]; // 4 байта
    for (int i = 1; i < n; i++) // 4 байта
        res = std::min(res, a[i]);
    return res;
}

int getMax(std::vector<int>& a, int n)
{
    int res = a[0];
    for (int i = 1; i < n; i++)
        res = std::max(res, a[i]);
    return res;
}

void pigeonhole_sort(std::vector<int>& a, int n) { // 8+4 = 12 байт

    int min = getMin(a, n); // 4 байта
    int max = getMax(a, n); // 4 байта
    int size = max - min + 1; // 4 байта
    std::vector<int> holes(size, 0); // 4*k + 32 байта
    for (int i = 0; i < n; i++) // 4 байта
        holes[a[i] - min] += 1;
    int index = 0; // 4 байта
    for (int i = 0; i < size; i++) { // 4 байта
        while (holes[i] > 0) {
            a[index] = i + min;
            holes[i]--;
            index++;
        }
    }

}

bool check(std::vector<int>& a, int n) {
    bool monotony_flag = true;
    for (int i = 0; i < n-1; i++) {
        if (a[i] > a[i + 1]) {
            monotony_flag = false;
            break;
        }
    }
    return monotony_flag;
}

void make_array_mixed_again(std::vector<int>& a, int n) {
    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) {
            a[i] = 2000000 + i;
        }
        else {
            a[i] = 2000000 - i;
        }
    }
}

void generator_pigeon_best(std::vector<int>& a, int n, int val) {
    for (int i = 0; i < n; ++i) {
        a[i] = static_cast<int>(std::rand() % val);
    }
}

void generator_quick_worst(std::vector<int>& a, int n, int val, int val2) {
    for (int i = 0; i < n; i += val2+1) {
        a[i] = i + val;
    }
}

void bubbletest() {

    // лучший
    std::vector<int> m1(10000, 0);
    make_array_mixed_again(m1, 10000);
    auto begin = std::chrono::steady_clock::now();
    bubbleSort(m1, 10000);
    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
    std::cout << "best bubblesort: " << elapsed_ms.count() << " mcrs" << std::endl;

    assert(check(m1, 10000) == true);

    // средний/худший
    std::vector<int> m11(10000, 0);
    generator(m11, 10000);
    auto begin1 = std::chrono::steady_clock::now();
    bubbleSort(m11, 10000);
    auto end1 = std::chrono::steady_clock::now();
    auto elapsed_ms1 = std::chrono::duration_cast<std::chrono::microseconds>(end1 - begin1);
    std::cout << "average/worst bubblesort: " << elapsed_ms1.count() << " mcrs" << std::endl;
    assert(check(m11, 10000) == true);

    std::cout << "success!\n" << std::endl;
}

void quicktest() {

    // лучший/средний
    std::vector<int> m1(2000, 0);
    generator(m1, 2000);
    auto begin = std::chrono::steady_clock::now();
    quick_sort(m1, 0, 1999);
    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
    std::cout << "best/average quicksort: " << elapsed_ms.count() << " mcrs" << std::endl;
    assert(check(m1, 2000) == true);

    // худший
    std::vector<int> m11(2000, 0);
    for (int i = 0; i < 2000; i += 10) {
        m11[i] = i + 2000000;
    }
    auto begin1 = std::chrono::steady_clock::now();
    quick_sort(m11, 0, 1999);
    auto end1 = std::chrono::steady_clock::now();
    auto elapsed_ms1 = std::chrono::duration_cast<std::chrono::microseconds>(end1 - begin1);
    std::cout << "worst quicksort: " << elapsed_ms1.count() << " mcrs" << std::endl;
    assert(check(m11, 2000) == true);

    std::cout << "success!\n" << std::endl;
}

void pigeonholetest() {
    // k << n
    std::vector<int> m1(10000, 0);
    for (int i = 0; i < 10000; i++) {
        m1[i] = static_cast<int>(std::rand() % 100);
    }
    auto begin = std::chrono::steady_clock::now();
    pigeonhole_sort(m1, 10000);
    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
    std::cout << "k << n: " << elapsed_ms.count() << " mcrs" << std::endl;
    assert(check(m1, 10000) == true);

    // k >> n
    std::vector<int> m11(10000, 0);
    generator(m11, 10000);
    auto begin1 = std::chrono::steady_clock::now();
    pigeonhole_sort(m11, 10000);
    auto end1 = std::chrono::steady_clock::now();
    auto elapsed_m1s = std::chrono::duration_cast<std::chrono::microseconds>(end1 - begin1);
    std::cout << "k >> n: " << elapsed_m1s.count() << " mcrs" << std::endl;
    assert(check(m11, 10000) == true);

    std::cout << "success!\n" << std::endl;
}


int main() {
    int i;
    std::srand(static_cast<int>(std::time(nullptr)));
    bubbletest();
    quicktest();
    pigeonholetest();
}
