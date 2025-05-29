#include <iostream>
#include <cmath>
#include <sys/time.h>

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

    cout << "Enter array size : ";
    cin >> size_;
    arr = new int[size_];

    // Fill the array with random values
    for (int i = 0; i < size_; i++)
    {
        arr[i] = rand() % 1000;
    }

   // cout<<"Oreginal Array= ";
   // print_array(arr, size_);


    // Call Sequential sort
    double start_seq = get_time();
    bitonic_sort_seq(0, size_, true);
    double end_seq = get_time();
    double duration_seq = end_seq - start_seq;
    cout << "Sequential time: " << duration_seq << " s" << endl;

    // cout<<"Sequential Sorted Array= ";
   //  print_array(arr,size_);

   
    return 0;
}