#include <iostream>
#include <chrono>
#include <random>
#include <fstream>
using namespace std;
// #define NDEBUG;
#include <cassert>

using U = unsigned;
using ULL = unsigned long long;

// функция проверки упорядоченности каждого 4-ого элемента массива 
template <typename T>
bool is_N4_sorted(T arr[], U const begin_idx, U const end_idx) {
    U step = (end_idx - begin_idx + 1) / 4;
    bool sorted = true;
    for (U idx = begin_idx; idx + step <= end_idx; idx += step) {
        if (arr[idx] > arr[idx + step])
            sorted = false;
    }
    return sorted;
}


// функция проверки упорядоченности каждого 2-ого элемента массива 
template <typename T>
bool is_N2_sorted(T arr[], U const begin_idx, U const end_idx) {
    U step = (end_idx - begin_idx + 1) / 2;
    bool sorted = true;
    for (U idx = begin_idx; idx + step <= end_idx; idx += step) {
        if (arr[idx] > arr[idx + step])
            sorted = false;
    }
    return sorted;
}


// функция проверки упорядоченности массива
template <typename T>
bool is_sorted(T arr[], U const begin_idx, U const end_idx) {
    bool sorted = true;
    for (U idx = begin_idx; idx != end_idx; idx++) {
        if (arr[idx] > arr[idx + 1]) {
            sorted = false;
        }
    }
    return sorted;
}


// сортировка с шагом N/4
ULL N4_sort(U arr[], U const begin_idx, U const end_idx) {
    U step = (end_idx - begin_idx + 1) / 4;
    ULL count = 0;
    bool sorted = false;
    while (!sorted) {
        sorted = true;
        for (U idx = begin_idx; idx + step <= end_idx; idx += step) {
            if (arr[idx] > arr[idx + step]) {
                auto tmp = arr[idx];
                arr[idx] = arr[idx + step];
                arr[idx + step] = tmp;
                sorted = false;
                count++;
            }
        }
    }
    assert(is_N4_sorted(arr, begin_idx, end_idx));
    return count;
}

// сортировка с шагом N/2
ULL N2_sort(U arr[], U const begin_idx, U const end_idx) {
    U step = (end_idx - begin_idx + 1) / 2;
    ULL count = 0;
    bool sorted = false;
    while (!sorted) {
        sorted = true;
        for (U idx = begin_idx; idx + step <= end_idx; idx += step) {
            if (arr[idx] > arr[idx + step]) {
                auto tmp = arr[idx];
                arr[idx] = arr[idx + step];
                arr[idx + step] = tmp;
                sorted = false;
                count++;
            }
        }
    }
    assert(is_N2_sorted(arr, begin_idx, end_idx));
    return count;
}


// сортировка расчёской
ULL comb_sort(U arr[], U const begin_idx, U const end_idx) {
    ULL count1 = N4_sort(arr, begin_idx, end_idx);
    ULL count2 = N2_sort(arr, begin_idx, end_idx);
    ULL count = 0;

    bool sorted = false;
    while (!sorted) {
        sorted = true;
        for (U idx = begin_idx; idx != end_idx; ++idx) {
            if (arr[idx] > arr[idx + 1]) {
                auto tmp = arr[idx];
                arr[idx] = arr[idx + 1];
                arr[idx + 1] = tmp;
                sorted = false;
                count++;
            }
        }
    }
    return count1 + count2 + count;
}



int main()
{
    // открываем файл для записи данных на txt файл
    ofstream time_data;
    time_data.open("python\\time_data.txt");
    assert(time_data.is_open());

    ofstream transposition_data;
    transposition_data.open("python\\transposition_data.txt");
    assert(transposition_data.is_open());

    // проверка сортировки расчёской на различных случайно сгенерированных массивах
    for (int N = 100; N <= 50000; N += 100) {
        // создаём массив из N случайных чисел от 0 до MAX_RAND
        U* A = new U[N];
        unsigned int seed = rand();
        default_random_engine rng(seed);
        U const MAX_RAND = 1000000;
        uniform_int_distribution<unsigned> dstr(0, MAX_RAND);
        for (int i = 0; i < N; i++) {
            A[i] = dstr(rng);
        }
        // включаем таймер
        auto begin = chrono::steady_clock::now();

        // сортируем расчёской
        U count = comb_sort(A, 0, N - 1);

        // находим время сортировки
        auto end = chrono::steady_clock::now();
        auto time_span = chrono::duration_cast<chrono::milliseconds>(end - begin);

        // проверка, что массив отортирован
        assert(is_sorted(A, 0, N-1));

        // записываем в data.txt
        time_data << N << "\t" << time_span.count() << "\n";
        transposition_data << N << "\t" << count << "\n";

        delete[] A;
    }
}