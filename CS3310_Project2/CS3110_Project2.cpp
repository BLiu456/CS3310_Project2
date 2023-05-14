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

//Function Prototypes here
int getListMan(vector<int>&);
bool getListFile(vector<int>&);
int getListRand(vector<int>&);
void printList(vector<int>);
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
    vector<int> l;
    int k = 0, op = 0;
    //Display menu and prompt user for how they want to enter in the data
    cout << "---Find Kth smallest element in list---\n";
    cout << "Choose an option:\n"
        << "(1) Enter the list and k value manually\n"
        << "(2) Load a file of the list\n"
        << "(3) Generate random matrices and find a random k value\n"
        << "(4) Exit\n"
        << "Enter: ";
    cin >> op;

    switch (op) //Doing the chosen option
    {
    case 1: //Allowing the user to enter in the list maunally
        k = getListMan(l);
        break;
    case 2: //Get list from file
        if (getListFile(l))
        {
            cout << "Contents of list:\n"; //Display the list so user can confirm if the contents are correct
            printList(l);

            cout << "\nEnter the kth smallest value you would like to search for: "; //Ask user for the kth smallest value they would like to find
            cin >> k;
        }
        else //List could not be retrieved from file, will end the program
        {
            return 0;
        }
        break;
    case 3: //Randomly generate the list and kth value
        k = getListRand(l);
        cout << "Contents of randomized list:\n";
        printList(l);

        cout << "\nSearching for kth (" << k << ") smallest value";
        break;
    case 4:
        cout << "Exit has been selected, ending program\n";
        return 0;
    default:
        cout << "Valid option not selected, ending program.\n";
        return 0;
    }
    //Start testing the times of each algortihm
    cout << "\n---Merge Sort---\n";
    auto start = high_resolution_clock::now();
    findKmerge(l, k);
    auto end = high_resolution_clock::now();
    auto timeMerge = duration_cast<microseconds>(end - start);

    cout << "\n---Quick Sort---\n";
    start = high_resolution_clock::now();
    findKquick(l, k);
    end = high_resolution_clock::now();
    auto timeQuick = duration_cast<microseconds>(end - start);

    cout << "\n---MM Quick Sort---\n";
    start = high_resolution_clock::now();
    findKMM(l, k);
    end = high_resolution_clock::now();
    auto timeMM = duration_cast<microseconds>(end - start);

    //Displaying the times of each algorithms
    cout << "\nTime elapsed for Merge Sort: " << timeMerge.count() << " microseconds" << endl;
    cout << "Time elapsed for Quick Sort: " << timeQuick.count() << " microseconds" << endl;
    cout << "Time elapsed for MM Quick Sort: " << timeMM.count() << " microseconds" << endl;
    return 0; //End of program
}

/* Function to let the user enter in the list manually
   list is passed in by reference so the list will be directly edited
   Function will return the kth value the user wants to search for*/
int getListMan(vector<int>& l)
{
    int listSize = 0; //Prompting for number of elements in list
    cout << "\nEnter the number of elements in list: ";
    cin >> listSize;
    
    int val;
    cout << "Enter elements of list:\n";
    for (int i = 0; i < listSize; i++) //Keep entering in values until loop is done
    {
        cin >> val;
        l.push_back(val);
    }
    //Prompting for kth smallest value
    int k;
    cout << "Enter the kth smallest value you would like to search for: ";
    cin >> k;
    return k;
}

/* Function to get data of the list from a file
   list is passed in by reference so the list will be directly edited
   Returns a bool value for if the file was successfully opened and read in*/
bool getListFile(vector<int>& l)
{
    string fileName = "";

    cout << "\nEnter file name: "; //Getting filename
    cin >> fileName;

    ifstream listFile;
    listFile.open(fileName);
    if (!listFile) //Checking if file could be opened
    {
        cout << "Could not open file, ending program.\n"; //File couldn't be opened so return false
        return false;
    }

    string nums, n;
    while (!listFile.eof()) 
    {
        getline(listFile, nums); //Read in the line (all the data should be on one line). Is read in as a string
        istringstream ss(nums); //Seperates the row of data by spaces

        while (ss >> n) //Read in each number and push it into the list
        {
            l.push_back(stoi(n));
        }
    }

    listFile.close();
    return true; //Data was loaded successfully, return true
}


/* This function will randomly generate a list and the kth value. The function will also store the randomly generated list into a file
   Will just prompt the user for the size of the list, and randomly generate that many numbers for the list
   Returns the randomly generated kth value
*/
int getListRand(vector<int>& l)
{
    srand(time(0));

    int listSize = 0;
    cout << "Enter size of the random list: ";
    cin >> listSize;

    ofstream listFile("randList.txt"); //randList.txt is the file we are going to store the random list to
    for (int i = 0; i < listSize; i++)
    {
        int r = rand() % 100; //Will generate a random number between 0 - 99
        l.push_back(r);

        listFile << r << " "; //Seperate each number with a space
    }

    listFile.close();

    int k = (rand() % listSize) + 1; //Make sure the kth value is between 1 to listSize
    return k;
}

//A simple function to print the contents of the list
void printList(vector<int> l)
{
    for (int i = 0; i < l.size(); i++)
    {
        cout << l.at(i) << " ";
    }
}

//This function will call the merge sort algorithm. Once the list is sorted we can directly find the kth smallest value by index
int findKmerge(vector<int> a, int k)
{
    mergeSort(a, 0, a.size() - 1);
    printList(a);
    cout << "\nMerge sort found the kth (" << k << ") smallest element is " << a.at(k - 1) << endl;
    return a.at(k - 1);
}
//low and high refers to the index of list a
void mergeSort(vector<int>& a, int low, int high)
{
    if (low < high) 
    {
        int mid = (low + high) / 2; 
        mergeSort(a, low, mid); //Recursivley call merge sort to divide the lower part
        mergeSort(a, mid + 1, high); //Recursivley call merge sort to divide the upper part
        merge(a, low, mid, high); //Merge the split parts together and sort
    }
}
//This function will merge together the divided parts and sort in ascending order
void merge(vector<int>& a, int low, int mid, int high)
{
    int i = low;
    int j = mid + 1;
    vector<int> temp;

    while (i <= mid && j <= high) //Keeps looping until one of the parts reaches their end
    {
        if (a.at(i) < a.at(j)) //If value at the lower part is less than the value at the higher part, push it into the list
        {
            temp.push_back(a.at(i));
            i++;
        }
        else //If value at the higher part is less than the value at the lower part, push it into the list
        {
            temp.push_back(a.at(j));
            j++;
        }
    }

    while (i <= mid) //If there are any values left in the lower part, then just simply push them into the list
    {
        temp.push_back(a.at(i));
        i++;
    }

    while (j <= high) //If there are any values left in the upper part, then just simply push them into the list
    {
        temp.push_back(a.at(j));
        j++;
    }

    int k = 0;
    for (int l = low; l <= high; l++) //Reflect the changes into the actual list
    {
        a.at(l) = temp.at(k);
        k++;
    }
}

//This function will call the quick sort algorithm to sort the list. We can find the kth smallest value by index after it is sorted.
int findKquick(vector<int> a, int k)
{
    quickSort(a, 0, a.size() - 1, k);
    printList(a);
    cout << "\nQuick Sort found the kth (" << k << ") smallest element is " << a.at(k - 1) << endl;
    return a.at(k - 1);
}

void quickSort(vector<int>& a, int p, int q, int k)
{
    if (p < q)
    {
        int piv = partition(a, p, q); 
        if (piv == (k - 1)) //Since the piv will be in its sorted position, so if it is already at the kth position then we are done
        {
            return;
        }
        quickSort(a, p, piv - 1, k);
        quickSort(a, piv + 1, q, k);
    }
}

int partition(vector<int>& a, int p, int q)
{
    int pivVal = a.at(p); //Will use the first value as the pivot
    int pivotPos = p;

    for (int i = p + 1; i <= q; i++)
    {
        if (a.at(i) < pivVal) //If value is less than the pivVal, then swap them so that the smaller value is left of the piv.
        {
            pivotPos++;
            int temp = a.at(i);
            a.at(i) = a.at(pivotPos);
            a.at(pivotPos) = temp;
        } //If the value is greater it will be to the right side of the pivot
    }

    int temp = a.at(p); //Put the pivot at the correct position
    a.at(p) = a.at(pivotPos);
    a.at(pivotPos) = temp;

    return pivotPos; //Return where the pivot is at currently
}

//Will call the MM quick sort algorithm to sort the list in ascending order. After sorted, we can find the kth smallest value by index.
int findKMM(vector<int> a, int k)
{
    vector<int> sortedA = quickMMSort(a);
    printList(sortedA);
    cout << "\nQuick MM Sort found the kth (" << k << ") smallest element is " << sortedA.at(k - 1) << endl;
    return sortedA.at(k - 1);
}

vector<int> quickMMSort(vector<int> a)
{
    if (a.size() <= 1) //Base case, we have a list size of 1
    {
        return a;
    }

    int piv = medianSelect(a); //Select the median of medians value to be the pivot
    vector<vector<int>> parts = partitionMM(a, piv); //Divide the list into 3 parts: low, equal, and high
    vector<int> low = quickMMSort(quickMMSort(parts.at(0))); //Sort the lower part with MM
    vector<int> eq = parts.at(1); //Retrieve the middle part
    vector<int> high = quickMMSort(quickMMSort(parts.at(2))); //Sort the higher part with MM
    //Merge back all the parts, and each part should be sorted at this point
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
        int median = a.size() / 2; //Getting the index of the median of medians
        return a.at(median); //Returning the value of the MM
    }

    //Splitting array a into smaller subarrays of size r.
    vector<vector<int>> subarray; //Subarray will hold all the subarraies
    vector<int> sub; //sub will be each individual subarray
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
        med.push_back(medianSelect(subarray.at(s))); //Find the median of each subarray
    }

    return medianSelect(med); //Find and return the MM
}

vector<vector<int>> partitionMM(vector<int> a, int pivVal) //The pivVal will be the MM
{
    vector<int> low, high, equal;

    for (int i = 0; i < a.size(); i++)
    {
        if (a.at(i) < pivVal) //If the val is less than pivVal then it goes in the lower part
        {
            low.push_back(a.at(i));
        }
        else if (a.at(i) > pivVal) //If the val is greater than pivVal then it goes in the higher part
        {
            high.push_back(a.at(i));
        }
        else //If the val is the MM then it goes in the middle
        {
            equal.push_back(a.at(i));
        }
    }

    vector<vector<int>> collection{ low, equal, high }; //Return all 3 of the parts
    return collection;
}