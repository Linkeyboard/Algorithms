#include <iostream>
#include <cstring>
#include <string>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstdlib>
using namespace std;
const int MAXN = 100001+10;
const int M = MAXN * 30;

int a[MAXN],t[MAXN],tot,n,q,m;
int lson[M],rson[M],T[M],c[M];


void init(){
    tot=0;
}


void Init_Hash(){
    for(int i=1;i<=n;i++){
        t[i]=a[i];
    }
    sort(t+1,t+n+1);
    m=unique(t+1,t+n+1)-t-1;
}


int build(int l,int r){
    int root = tot++;
    int mid = (l+r)>>1;
    c[root]=0;
    if(l!=r){
        lson[root] = build(l,mid);
        rson[root] = build(mid+1,r);
    }
    return root;
}

int update(int root,int pos,int val){
    int newroot=tot++,tmp=newroot;
    c[newroot]=c[root]+val;
    int l=1,r=m;
    while(l<r){
        int mid=(l+r)>>1;
        if(pos<=mid){
            lson[newroot]=tot++;rson[newroot]=rson[root];
            newroot=lson[newroot];root=lson[root];
            r=mid;
        }else{
            rson[newroot]=tot++;lson[newroot]=lson[root];
            newroot=rson[newroot];root=rson[root];
            l=mid+1;
        }
        c[newroot]=c[root]+val;
    }
    return tmp;
}


int query(int l_root,int r_root,int k){
    int l=1,r=m;
    while(l<r){
        int mid=(l+r)>>1;
        if(c[lson[l_root]]-c[lson[r_root]]>=k){
            r=mid;
            l_root=lson[l_root];r_root=lson[r_root];
        }else{
            l=mid+1;
            k-=(c[lson[l_root]]-c[lson[r_root]]);
            l_root=rson[l_root];r_root=rson[r_root];
        }
    }
    return l;
}




int Hash(int x){
    return lower_bound(t+1,t+m+1,x)-t;
}



int main(){
    //freopen("in.txt","r",stdin);
    while(scanf("%d%d",&n,&q)!=EOF){
        init();
        for(int i=1;i<=n;i++){
            scanf("%d",&a[i]);
        }
        Init_Hash();
        T[n+1]=build(1,m);
        for(int i=n;i>=1;i--){
            int pos = Hash(a[i]);
            T[i] = update(T[i+1],pos,1);
        }
        while(q--){
            int ql,qr,qk;
            scanf("%d%d%d",&ql,&qr,&qk);
            printf("%d\n",t[query(T[ql],T[qr+1],qk)]);
        }
    }
}
