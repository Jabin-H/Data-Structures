#include <iostream>
#include <climits>
#include <vector>
using namespace std;

int main()
{
    int k;
    cin >> k;
    //int arr[k];
    vector<int> arr(k);
    for (int i = 0; i < k; i++)
    {
        cin >> arr[i];
    }

    int maxSum = INT_MIN, tempSum = 0;
    for (int i = 0; i < k; i++)
    {
        tempSum += arr[i];
        if (tempSum > maxSum)
        {
            maxSum = tempSum;
        }
        if (tempSum < 0)
        {
            tempSum = 0;
        }
    }

    if (maxSum < 0)
    {
        maxSum = 0;
    }

    cout << maxSum << endl;
    return 0;
}