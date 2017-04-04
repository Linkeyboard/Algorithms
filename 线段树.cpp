#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <cmath>
#include <vector>
#include <set>
#include <queue>
#include <map>
#include <algorithm>

using namespace std;

const int MAXN=100000+5;
#define ll long long
int n,m;
ll a[MAXN];
char op[10];
struct Node{
    int l,r;
    ll sum;
    ll add;
}Tree[4*MAXN];

void push_up(int u){
    int lson=u<<1;
    int rson=lson|1;
    Tree[u].sum=Tree[lson].sum+Tree[rson].sum;
}

void push_down(int u){
    int lson=u<<1;
    int rson=lson|1;
    Tree[lson].add+=Tree[u].add;
    Tree[rson].add+=Tree[u].add;
    Tree[u].sum+=(Tree[u].r-Tree[u].l+1)*Tree[u].add;
    Tree[u].add=0;
}
void build(int u,int l,int r){
    Tree[u].l=l;
    Tree[u].r=r;
    Tree[u].add=0;
    Tree[u].sum=0;
    if(l==r) {
        Tree[u].sum=a[l];
        return;
    }
    int mid=(l+r)>>1;
    build((u<<1),l,mid);
    build((u<<1|1),mid+1,r);
    push_up(u);
}

void change(int u,int l,int r,int c){
    if(l==Tree[u].l&&r==Tree[u].r){
        Tree[u].add+=c;
        return;
    }
    Tree[u].sum+=(ll)(r-l+1)*c;
    int mid=(Tree[u].l+Tree[u].r)>>1;
    if(l>mid){
        change(u<<1|1,l,r,c);
    }else if(r<=mid){
        change(u<<1,l,r,c);
    }else{
        change(u<<1,l,mid,c);
        change(u<<1|1,mid+1,r,c);
    }
}

ll query(int u,int l,int r){
    if(Tree[u].l==l&&Tree[u].r==r){
        return Tree[u].sum+(Tree[u].r-Tree[u].l+1)*Tree[u].add;
    }
    int mid=(Tree[u].l+Tree[u].r)>>1;
    int lson=u<<1;
    int rson=u<<1|1;
    push_down(u);
    if(l>mid){
        return query(rson,l,r);
    }else if(r<=mid){
        return query(lson,l,r);
    }else{
        return query(lson,l,mid)+query(rson,mid+1,r);
    }
}

int main(){
    //freopen("in.txt","r",stdin);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%lld",&a[i]);
    }
    build(1,1,n);
    while(m--){
        scanf("%s",op);
        int i,j,k;
        if(op[0]=='Q'){
            scanf("%d%d",&i,&j);
            printf("%lld\n",query(1,i,j));
        }else if(op[0]=='C'){
            scanf("%d%d%d",&i,&j,&k);
            change(1,i,j,k);
        }
    }
    return 0;
}
