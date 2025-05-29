#include <iostream>
#include <pthread.h>
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
int num_threads;

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

struct ThreadData
{
    int low;
    int count;
    bool dir;
};

void *bitonic_parallel_sort(void *arg)
{
    ThreadData *data = (ThreadData *)arg;
    bitonic_sort_seq(data->low, data->count, data->dir);
    return NULL;
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
    cout << "Enter number of threads : ";
    cin >> num_threads;
    arr = new int[size_];

    // Fill the array with random values
    for (int i = 0; i < size_; i++)
    {
        arr[i] = rand() % 1000;
    }
    
    //cout<<"Oreginal Array= ";
    //print_array(arr, size_);

    pthread_t threads[num_threads];
    ThreadData data[num_threads];

    int chunk = size_ / num_threads;

    double start_par = get_time();

    for (int i = 0; i < num_threads; i++)
    {
        bool dir = ((i % 2) == 0);
        data[i] = {i * chunk, chunk, dir};
        pthread_create(&threads[i], NULL, bitonic_parallel_sort, &data[i]);
    }
    for (int i = 0; i < num_threads; i++)
    {
        pthread_join(threads[i], NULL);
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
    cout << "Parallel time: " << duration_par << " s" << endl;

    //cout<<"Parallel Sorted Array= ";
    //print_array(arr,size_);

    return 0;
}