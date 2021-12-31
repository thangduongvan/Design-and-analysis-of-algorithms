#include <iostream>
#include <time.h>
#include <iomanip>
using namespace std;
bool isSubsetSum(int arr[], int n, int sum)
{
    // The value of subset[i%2][j] will be true
    // if there exists a subset of sum j in
    // arr[0, 1, ...., i-1]
    bool subset[2][sum + 1];

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= sum; j++) {

            // A subset with sum 0 is always possible
            if (j == 0)
                subset[i % 2][j] = true;

            // If there exists no element no sum
            // is possible
            else if (i == 0)
                subset[i % 2][j] = false;
            else if (arr[i - 1] <= j)
                subset[i % 2][j] = subset[(i + 1) % 2]
             [j - arr[i - 1]] || subset[(i + 1) % 2][j];
            else
                subset[i % 2][j] = subset[(i + 1) % 2][j];
        }
    }

    return subset[n % 2][sum];
}

int main()
{
    int n,sum;
     clock_t start, end;
double cpu_time_used=0.0;

    cin>>n>>sum;
    int *arr = new int[n];
    for(int i =0; i< n; i++){
        cin>>arr[i];
    }




start = clock();
if (isSubsetSum(arr, n, sum) == true)
        cout<<"Yes";
    else
        cout<<"No";
end = clock();
cpu_time_used += ((double) (end - start)) / CLOCKS_PER_SEC;
delete arr;
cout<<fixed<<setprecision(2);
cout<<"\nTime: "<<cpu_time_used*1000.0<<endl;

return 0;
}
