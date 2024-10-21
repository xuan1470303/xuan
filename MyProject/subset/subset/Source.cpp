#include <iostream>
using namespace std;

void printSubset(int subset[], int size) 
{
    cout << "{ ";
    for (int i = 0; i < size; i++) 
    {
        cout << subset[i] << " ";
    }
    cout << "}, ";
}

void findSubsets(int nums[], int n)
{
    int totalSubsets = 1 << n; 
    int subset[10]; 

    for (int i = 0; i < totalSubsets; i++)
    {
        int size = 0;
        for (int j = 0; j < n; ++j)
        {
            if (i & (1 << j)) 
            {
                subset[size++] = nums[j];
            }
        }
        printSubset(subset, size);
    }
}

int main() 
{
    int n;
    cout << "請輸入元素的個數: ";
    cin >> n;

    int inputSet[10]; 
    cout << "請輸入 " << n << " 個整數: ";
    for (int i = 0; i < n; i++)
    {
        cin >> inputSet[i];
    }

    cout << "S = { ";
    findSubsets(inputSet, n);
    cout << " }" << endl; 
    return 0;
}
