#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>

using namespace std;

const int MAXN=20000+10;
int n,m;
int a[MAXN],t[MAXN];
int c[MAXN];

void Init_Hash(){
    for(int i=0;i<n;i++){
        t[i]=a[i];
    }
    sort(t,t+n);
    m=unique(t,t+n)-t;
}
int Hash(int x){
    int l=0;
    int r=m-1;
    int mid;
    while(l<=r){
        mid=(l+r)>>1;
        if(t[mid]==x) return mid;
        else if(t[mid]<x){
            l=mid+1;
        }else{
            r=mid-1;
        }
    }
    return mid;
}
int lowbit(int x){
    return x&-x;
}
void add(int x,int v){
    while(x<=m){
        c[x]+=v;
        x+=lowbit(x);
    }
}
int sum(int x){
    int res=0;
    while(x){
        res+=c[x];
        x-=lowbit(x);
    }
    return res;
}

void debug(){
    for(int i=0;i<n;i++){
        printf("%d%c",a[i],i==n-1?'\n':' ');
    }
    for(int i=0;i<m;i++){
        printf("(%d)%d%c",i,t[i],i==m-1?'\n':' ');
    }
}
int main(){
    //freopen("in.txt","r",stdin);
    while(scanf("%d",&n)!=EOF&&n){
        for(int i=0;i<n;i++){
            scanf("%d",&a[i]);
        }
        Init_Hash();
        memset(c,0,sizeof(c));
        int res=0;
        for(int i=n-1;i>=0;i--){
            int x=Hash(a[i])+1;
            add(x,1);
            res+=sum(x-1);
        }
        printf("%d\n",res);
    }
    return 0;
}
