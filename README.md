Bitonic Sort Projects – Pthreads & OpenMP

This repository contains two implementations of the Bitonic Sort algorithm:

- Project 1: Sequential and parallel versions using **Pthreads**
- Project 2: Improved parallel version using **OpenMP**

---

## Project 1 – Bitonic Sort using Pthreads

In this project, Bitonic Sort is implemented using both:
- A sequential recursive version.
- A parallel version that creates a thread for each chunk using **Pthreads**.

The array is split into `N` chunks and each chunk is sorted in a separate thread. After that, a series of merge operations combine the chunks to produce a final sorted array.


Compile:
```bash
g++ sequential.cpp -o seq
g++ parallel.cpp -pthread -o par
```

## Project 2 – Bitonic Sort using OpenMP:
This project upgrades the previous implementation by replacing Pthreads with OpenMP, making the parallelization simpler and more efficient.

The array is divided into chunks. Each chunk is sorted independently in parallel using OpenMP's #pragma omp parallel for, then merged sequentially.

Compile:
```bash
g++ -fopenmp openmp_bitonic.cpp -o omp
```
Hardware Specifications:
	CPU: Intel(R) Core(TM) i5-7300U @ 2.60GHz
	Cores: 2 physical cores, 4 logical processors (hyper-threaded)
	RAM: 16 GB
	Operating System: Windows 11
Input sizes:
Tested array sizes = 32, 512, 1024, 4096, 8192, 16384, 32768.   
Threads count = 2, 4, 8.


