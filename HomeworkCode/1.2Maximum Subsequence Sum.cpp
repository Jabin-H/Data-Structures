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
    int maxI, maxJ, tempI, tempJ;
    maxI = maxJ = tempI = tempJ = 0;
    for (int i = 0; i < k; i++)
    {
        tempSum += arr[i];
        tempJ = i;
        if (tempSum > maxSum)
        {
            maxSum = tempSum;
            maxI = tempI;
            maxJ = tempJ;
        }
        if (tempSum < 0)
        {
            tempSum = 0;
            tempI = i + 1;
        }
    }

    if (maxSum < 0)
    {
        maxSum = 0;
        maxI = 0;
        maxJ = k - 1;
    }

    cout << maxSum << " " << arr[maxI] << " " << arr[maxJ] << endl;

    return 0;
}