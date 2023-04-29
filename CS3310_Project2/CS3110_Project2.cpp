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
void quickSort();

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
}

int findKmerge(vector<int> a, int k)
{
    mergeSort(a, 0, a.size() - 1);
    cout << "The " << "kth (" << k << ") smallest element is " << a.at(k) << endl;
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
        cout << temp.at(k) << " ";
        a.at(l) = temp.at(k);
        k++;
    }
    cout << endl;
}

int findKquick(vector<int> a, int k)
{
    return a.at(k);
}

