#include <iostream>
#include <algorithm>
#include <cstdio>
#include <string>
#include <cstring>

using namespace std;

const int MAXN=60000+10;
const int M=2500010;

int lson[M],rson[M],c[M];
int tot,n,q,m;
int a[MAXN],t[MAXN*2];
int use[MAXN],S[MAXN],T[MAXN];

struct qnode{
    int kind;
    int l;
    int r;
    int k;
}qn[10000+10];

void init(){
    tot=0;
}

void Init_Hash(int index){
    for(int i=1;i<=n;i++){
        t[i]=a[i];
    }
    sort(t+1,t+1+index);
    m=unique(t+1,t+1+index)-t-1;
}

int get_pos(int x){
    return lower_bound(t+1,t+1+m,x)-t;
}

int build(int l,int r){
    int root=tot++;
    c[root]=0;
    if(l!=r){
        int mid=(l+r)>>1;
        lson[root]=build(l,mid);
        rson[root]=build(mid+1,r);

    }
    return root;
}


int update(int root,int pos,int val){
    int newroot=tot++;
    int tmp=newroot;
    c[newroot]=c[root]+val;
    int l=1,r=m;
    while(l<r){
        int mid=(l+r)>>1;
        if(pos>mid){
            lson[newroot]=lson[root];
            rson[newroot]=tot++;
            newroot=rson[newroot];root=rson[root];
            l=mid+1;
        }else{
            rson[newroot]=rson[root];
            lson[newroot]=tot++;
            newroot=lson[newroot];root=lson[root];
            r=mid;
        }
        c[newroot]=c[root]+val;
    }
    return tmp;
}




int lowbit(int k){
    return k&(-k);
}


void add(int x,int pos,int v){
    while(x<=n){
        S[x]=update(S[x],pos,v);
        x+=lowbit(x);
    }
}

int sum(int x){
    int tmp=x;
    int res=0;
    while(x){
        res+=c[lson[use[x]]];
        x-=lowbit(x);
    }
    return res;
}


int query(int left,int right,int k){
    int l_root=T[left],r_root=T[right];
    int l=1,r=m;
    for(int i=left;i;i-=lowbit(i)) use[i]=S[i];
    for(int i=right;i;i-=lowbit(i)) use[i]=S[i];
    while(l<r){
        int mid=(l+r)>>1;
        int tmp=sum(right)-sum(left)+c[lson[r_root]]-c[lson[l_root]];
        if(tmp>=k){
            for(int i=left;i;i-=lowbit(i)) use[i]=lson[use[i]];
            for(int i=right;i;i-=lowbit(i)) use[i]=lson[use[i]];
            l_root=lson[l_root];
            r_root=lson[r_root];
            r=mid;
        }else{
            k-=tmp;
            for(int i=left;i;i-=lowbit(i)) use[i]=rson[use[i]];
            for(int i=right;i;i-=lowbit(i)) use[i]=rson[use[i]];
            l_root=rson[l_root];
            r_root=rson[r_root];
            l=mid+1;
        }
    }
    return l;
}

void Travel(int root,int l,int r){
    printf("l:%d r:%d c[root]:%d\n",l,r,c[root]);
    if(l!=r){
        int mid=(l+r)>>1;
        Travel(lson[root],l,mid);
        Travel(rson[root],mid+1,r);
    }

}


int main(){
    //freopen("in.txt","r",stdin);
    int X;
    scanf("%d",&X);
    while(X--){
        init();
        scanf("%d%d",&n,&q);
        for(int i=1;i<=n;i++){
            scanf("%d",&a[i]);
        }
        int Tindex=n;
        for(int i=0;i<q;i++){
            char tmp[10];
            scanf("%s",tmp);
            if(tmp[0]=='Q'){
                qn[i].kind=0;
                scanf("%d%d%d",&qn[i].l,&qn[i].r,&qn[i].k);
            }else{
                qn[i].kind=1;
                scanf("%d%d",&qn[i].l,&qn[i].r);
                t[++Tindex]=qn[i].r;
            }
        }
        Init_Hash(Tindex);
        T[0]=build(1,m);
        for(int i=0;i<=n+1;i++) S[i]=T[0];
        for(int i=1;i<=n;i++){
            int pos=get_pos(a[i]);
            T[i]=update(T[i-1],pos,1);
        }

        int l,r,k,index,v;
        for(int i=0;i<q;i++){
            if(qn[i].kind==0){
                int tmp=query(qn[i].l-1,qn[i].r,qn[i].k);
                printf("%d\n",t[tmp]);
            }else{
                add(qn[i].l,get_pos(a[qn[i].l]),-1);
                add(qn[i].l,get_pos(qn[i].r),1);
                a[qn[i].l]=qn[i].r;
            }
        }
    }
    return 0;
}
