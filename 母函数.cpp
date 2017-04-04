#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <cmath>
#include <vector>
#include <set>
#include <queue>
#include <map>
#include <stack>
#include <algorithm>

using namespace std;
#define ll long long
const int MAXN=300+5;
int c1[MAXN],c2[MAXN],n;

int main(){
    //freopen("in.txt","r",stdin);
    for(int i=0;i<MAXN;i++){
        c1[i]=1;
        c2[i]=0;
    }
    for(int i=2;i<=17;i++){
        int t=i*i;
        for(int j=0;j<MAXN;j++){
            for(int k=0;k+j<MAXN;k+=t){
                c2[j+k]+=c1[j];
            }
        }
        for(int j=0;j<MAXN;j++){
            c1[j]=c2[j];
            c2[j]=0;
        }
    }
    while(scanf("%d",&n)&&n){
        cout<<c1[n]<<endl;
    }
    return 0;
}
