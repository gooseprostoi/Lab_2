#include <iostream>
#include <chrono>
#include <random>
#include <fstream>
#include <cmath>
using namespace std;
// #define NDEBUG;
#include <cassert>

using U = unsigned;
using ULL = unsigned long long;

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

// сортировка с шагом
ULL shell_sort_i(U arr[], U const begin_idx, U const end_idx, U step) {
    ULL count = 0;
    if (begin_idx + step > end_idx)
        return 0;
    for (int last = end_idx - step; last >= 0; last -= step) {
        auto tmp_idx = last;
        while (tmp_idx + step <= end_idx && arr[tmp_idx] > arr[tmp_idx + step]) {
            auto tmp = arr[tmp_idx];
            arr[tmp_idx] = arr[tmp_idx + step];
            arr[tmp_idx + step] = tmp;
            tmp_idx += step;
            count++;
        }
    }
    return count;
}

// сортирока Шелла с последовательностью Хиббарда
ULL shell_sort(U arr[], U const begin_idx, U const end_idx) {
    ULL count = 0;
    U i = 0;
    while ((U)pow(2, i) - 1 <= (end_idx - begin_idx + 1)) {
        ++i;
    } 
    --i;
    U step = (U) pow(2, i) - 1;
    while (step != 0) {
        count += shell_sort_i(arr, begin_idx, end_idx, step);
        i--;
        step = pow(2, i) - 1;
    }
    return count;
}



int main()
{
    // открываем файл для записи данных на txt файл
    ofstream time_data;
    time_data.open("..\\python\\time_data2.txt");
    assert(time_data.is_open());

    ofstream transposition_data;
    transposition_data.open("..\\python\\transposition_data2.txt");
    assert(transposition_data.is_open());

    // сортировка Шелла на различных случайно сгенерированных массивах
    for (int N = 10000; N <= 100000; N += 2500) {
        cout << N << "\n";
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

        // сортируем
        U count = shell_sort(A, 0, N - 1);

        // находим время сортировки
        auto end = chrono::steady_clock::now();
        auto time_span = chrono::duration_cast<chrono::milliseconds>(end - begin);

        // проверка, что массив отортирован
        assert(is_sorted(A, 0, N - 1));

        // записываем в data.txt
        time_data << N << "\t" << time_span.count() << "\n";
        transposition_data << N << "\t" << count << "\n";

        delete[] A;
    }
}