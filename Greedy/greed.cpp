#include <iostream>
#include <time.h>
#include <iomanip>
using namespace std;

void QuickSort(int *a, int l, int r){
    int i = l, j = r, mid = a[(l + r)/2];
    do{
        while(a[i] > mid) i++;
        while(a[j] < mid) j--;
        if(i <= j){
            swap(a[i],a[j]);
            i++;
            j--;
        }
    }while(i < j);
    if(i < r) QuickSort(a, i, r);
    if(j > l) QuickSort(a, l, j);
}

void findsubsetSum(int *set, int n, int sum){
    QuickSort(set, 0, n-1);
    int s = 0;
    int j = 0;
    while(j < n){
        if(s + set[j] <= sum)
            s = s + set[j];
        j++;
    }
    if( s == sum) cout<<"Yes\n";
    else cout<<"No\n";
}

int main(){
    int n, s;
    clock_t start, end;
    double cpu_time_used=0.0;
            fflush(stdin);
    cin>>n;
    cin>>s;
    int *set = new int[n];
    for(int i=0; i< n; i++){
        cin>>set[i];
    }
    start = clock();
    findsubsetSum(set, n, s);
    end = clock();
    cpu_time_used += ((double) (end - start)) / CLOCKS_PER_SEC;
    delete set;
cout<<fixed<<setprecision(2);
cout<<"\nTime: "<<cpu_time_used*1000.0<<endl;

return 0;
}
