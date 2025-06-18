#include <iostream>
#include <omp.h>
#include <cmath>
#include <sys/time.h>
#include <cstdlib>

using namespace std;

double get_time()
{
    timeval tv;
    gettimeofday(&tv, nullptr);
    return tv.tv_sec + tv.tv_usec * 1e-6;
}

int *arr;
int size_;

void bitonic_merge(int low, int cnt, bool dir)
{
    if (cnt > 1)
    {
        int k = cnt / 2;
        for (int i = low; i < low + k; i++)
        {
            if ((dir && arr[i] > arr[i + k]) || (!dir && arr[i] < arr[i + k]))
            {
                swap(arr[i], arr[i + k]);
            }
        }
        bitonic_merge(low, k, dir);
        bitonic_merge(low + k, k, dir);
    }
}

void bitonic_sort_seq(int low, int cnt, bool dir)
{
    if (cnt > 1)
    {
        int k = cnt / 2;
        bitonic_sort_seq(low, k, true);
        bitonic_sort_seq(low + k, k, false);
        bitonic_merge(low, cnt, dir);
    }
}

void print_array(int *a, int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;
}

int main()
{
    int num_threads;
    cout << "Enter array size : ";
    cin >> size_;
    cout << "Enter number of threads : ";
    cin >> num_threads;
    arr = new int[size_];

    for (int i = 0; i < size_; i++)
    {
        arr[i] = rand() % 1000;
    }

    cout<<"Oreginal Array= ";
    print_array(arr, size_);

    int chunk = size_ / num_threads;

    double start_par = get_time();

    #pragma omp parallel for num_threads(num_threads)
    for (int i = 0; i < num_threads; i++)
    {
        int low = i * chunk;
        bool dir = ((i % 2) == 0);
        bitonic_sort_seq(low, chunk, dir);
    }

    for (int size = 2 * chunk; size <= size_; size *= 2)
    {
        for (int i = 0; i < size_; i += size)
        {
            bool dir = ((i / size) % 2 == 0);
            bitonic_merge(i, size, dir);
        }
    }

    double end_par = get_time();
    double duration_par = end_par - start_par;
    cout << "Parallel time (OpenMP): " << duration_par << " s" << endl;

    cout<<"Parallel Sorted Array= ";
    print_array(arr, size_);

    return 0;
}
