#include <iostream>
#include <time.h>
#include <iomanip>
using namespace std;

void findsubSet(long long set[], long long subSet[], long long index, long long n, long long currsum, long long sum, long long &finish){
    if(finish > 0) return;
    if(currsum == sum){
        finish++;
        for (long long i = 0; i < n; i++) {
                int l=0;
        l++;
            //if (subSet[i] == 1)
              //cout<<set[i]<<" ";
        }
        //cout<<endl;
    } else if (index == n) return;
    else {
        subSet[index] = 1;
        currsum += set[index];
        findsubSet(set, subSet, index + 1, n, currsum, sum, finish);
        subSet[index] = 0;
        currsum -= set[index];
        findsubSet(set, subSet, index + 1, n, currsum, sum, finish);
    }
}
int main(){
    long long n, sum;
    clock_t start, end;
double cpu_time_used;
        fflush(stdin);
    cin>>n>>sum;
    long long *set = new long long[n];
    for(long long i = 0; i< n; i++){
        cin>>set[i];
    }
    long long *subSet = new long long[n];
    long long finish = 0;



start = clock();
findsubSet(set, subSet, 0, n, 0, sum, finish);
if(finish>0) cout<<"Yes";
else cout<<"No";
end = clock();
cpu_time_used += ((double) (end - start)) / CLOCKS_PER_SEC;
delete set;
delete subSet;
cout<<fixed<<setprecision(2);
cout<<"\nTime: "<<cpu_time_used*1000.0<<endl;
return 0;
}
