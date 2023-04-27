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
vector<int> mergeSort(vector<int>, int, int);

int main()
{

}

vector<int> mergeSort(vector<int> a, int low, int high)
{
    if (low < high)
    {
        int mid = (low + high) / 2;
        mergeSort(a, low, mid);
        mergeSort(a, mid, high);
        
    }

    return a;
}