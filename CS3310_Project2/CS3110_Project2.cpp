/*
	Name: Benjamin Liu
    Class: CS3310.01
    Assignment: Project 2 
    Due Date: 05/18/2023
*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdlib.h>
#include <ctime>
#include <chrono>
using namespace std;
using namespace std::chrono;

int findKmerge(vector<int>, int);
void mergeSort(vector<int>&, int, int);
void merge(vector<int>&, int, int, int);
int findKquick(vector<int>, int);
void quickSort(vector<int>&, int, int, int);
int partition(vector<int>&, int, int);

int main()
{
    srand(time(0));
    vector<int> a;
    for (int i = 0; i < 10; i++)
    {
        a.push_back(rand() % 100);
        cout << a.at(i) << " ";
    }
    cout << endl << endl;
    
    findKmerge(a, 3);
    findKquick(a, 3);

    for (int i = 0; i < 10; i++)
    {
        cout << a.at(i) << " ";
    }
}

int findKmerge(vector<int> a, int k)
{
    mergeSort(a, 0, a.size() - 1);
    for (int i = 0; i < 10; i++)
    {
        cout << a.at(i) << " ";
    }
    cout << "\nMerge sort found the kth (" << k << ") smallest element is " << a.at(k) << endl;
    return a.at(k);
}

void mergeSort(vector<int>& a, int low, int high)
{
    if (low < high)
    {
        int mid = (low + high) / 2;
        mergeSort(a, low, mid);
        mergeSort(a, mid + 1, high);
        merge(a, low, mid, high);
    }
}

void merge(vector<int>& a, int low, int mid, int high)
{
    int i = low;
    int j = mid + 1;
    vector<int> temp;

    while (i <= mid && j <= high)
    {
        if (a.at(i) < a.at(j))
        {
            temp.push_back(a.at(i));
            i++;
        }
        else
        {
            temp.push_back(a.at(j));
            j++;
        }
    }

    while (i <= mid)
    {
        temp.push_back(a.at(i));
        i++;
    }

    while (j <= high)
    {
        temp.push_back(a.at(j));
        j++;
    }

    int k = 0;
    for (int l = low; l <= high; l++)
    {
        a.at(l) = temp.at(k);
        k++;
    }
}

int findKquick(vector<int> a, int k)
{
    quickSort(a, 0, a.size() - 1, k);
    for (int i = 0; i < 10; i++)
    {
        cout << a.at(i) << " ";
    }
    cout << "\nQuick Sort found the kth (" << k << ") smallest element is " << a.at(k) << endl;
    return a.at(k);
}

void quickSort(vector<int>& a, int p, int q, int k)
{
    if (p < q)
    {
        int piv = partition(a, p, q);
        if (piv == k)
        {
            return;
        }
        quickSort(a, p, piv - 1, k);
        quickSort(a, piv + 1, q, k);
    }
}

int partition(vector<int>& a, int p, int q)
{
    int pivVal = a.at(p);
    int pivotPos = p;

    for (int i = p + 1; i <= q; i++)
    {
        if (a.at(i) < pivVal)
        {
            pivotPos++;
            int temp = a.at(i);
            a.at(i) = a.at(pivotPos);
            a.at(pivotPos) = temp;
        }
    }

    int temp = a.at(p);
    a.at(p) = a.at(pivotPos);
    a.at(pivotPos) = temp;

    return pivotPos;
}