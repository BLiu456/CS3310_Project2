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
int findKMM(vector<int>, int);
vector<int> quickMMSort(vector<int>);
int medianSelect(vector<int>);
vector<vector<int>> partitionMM(vector<int>, int);

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
    findKMM(a, 3);
}

int findKmerge(vector<int> a, int k)
{
    mergeSort(a, 0, a.size() - 1);
    for (int i = 0; i < a.size(); i++)
    {
        cout << a.at(i) << " ";
    }
    cout << "\nMerge sort found the kth (" << k << ") smallest element is " << a.at(k - 1) << endl;
    return a.at(k - 1);
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
    for (int i = 0; i < a.size(); i++)
    {
        cout << a.at(i) << " ";
    }
    cout << "\nQuick Sort found the kth (" << k << ") smallest element is " << a.at(k - 1) << endl;
    return a.at(k - 1);
}

void quickSort(vector<int>& a, int p, int q, int k)
{
    if (p < q)
    {
        int piv = partition(a, p, q); //Will just use the first position of the array (i.e. p) as the pivot point
        if (piv == (k - 1))
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

int findKMM(vector<int> a, int k)
{
    vector<int> sortedA = quickMMSort(a);
    for (int i = 0; i < sortedA.size(); i++)
    {
        cout << sortedA.at(i) << " ";
    }
    cout << "\nQuick MM Sort found the kth (" << k << ") smallest element is " << sortedA.at(k - 1) << endl;
    return sortedA.at(k - 1);
}

vector<int> quickMMSort(vector<int> a)
{
    if (a.size() <= 1)
    {
        return a;
    }

    int piv = medianSelect(a);
    vector<vector<int>> parts = partitionMM(a, piv);
    vector<int> low = quickMMSort(quickMMSort(parts.at(0)));
    vector<int> eq = parts.at(1);
    vector<int> high = quickMMSort(quickMMSort(parts.at(2)));
    vector<int> sorted;
    sorted.insert(sorted.end(), low.begin(), low.end());
    sorted.insert(sorted.end(), eq.begin(), eq.end());
    sorted.insert(sorted.end(), high.begin(), high.end());
    return sorted;
}

int medianSelect(vector<int> a)
{
    int r = 5; //Will use a subarray size of 5
    if (a.size() <= r)
    {
        //Since the subarray are small sizes, we can do a simple insertion sort to sort out the subarray 
        for (int i = 1; i < a.size(); i++)
        {
            int val = a.at(i);
            int j = i - 1;
            while (j >= 0 && a.at(j) > val)
            {
                a.at(j + 1) = a.at(j);
                j--;
            }
            a.at(j + 1) = val;
        }
        int median = a.size() / 2;
        return a.at(median); 
    }

    //Splitting array a into smaller subarrays of size r.
    vector<vector<int>> subarray;
    vector<int> sub;
    for (int i = 0; i < a.size(); i++)
    {
        sub.push_back(a.at(i));
        if (sub.size() == r)
        {
            subarray.push_back(sub);
            sub.clear();
        }
    }

    vector<int> med;
    for (int s = 0; s < subarray.size(); s++)
    {
        med.push_back(medianSelect(subarray.at(s)));
    }

    return medianSelect(med);
}

vector<vector<int>> partitionMM(vector<int> a, int pivVal)
{
    vector<int> low, high, equal;

    for (int i = 0; i < a.size(); i++)
    {
        if (a.at(i) < pivVal)
        {
            low.push_back(a.at(i));
        }
        else if (a.at(i) > pivVal)
        {
            high.push_back(a.at(i));
        }
        else
        {
            equal.push_back(a.at(i));
        }
    }

    vector<vector<int>> collection{ low, equal, high };
    return collection;
}