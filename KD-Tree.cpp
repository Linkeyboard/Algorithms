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

int n,k,idx;
const int MAXN=50000+10;
int flag[MAXN*4];
#define Pair pair<int,Node>


struct Node{
    int f[5];
    bool operator < (const Node &u) const{
        return f[idx]<u.f[idx];
    }
}point[MAXN];

priority_queue <Pair> q;
Node node[4*MAXN];

int dis(Node a,Node b){
    int ans=0;
    for(int i=0;i<k;i++){
        ans+=(a.f[i]-b.f[i])*(a.f[i]-b.f[i]);
    }
    return ans;
}

void Build(int l,int r,int cur,int depth){
    if(l>r) return;
    flag[cur]=1;
    int lson=cur<<1;
    int rson=cur<<1|1;
    flag[lson]=flag[rson]=-1;
    int mid=(l+r)>>1;
    idx=depth%k;
    nth_element(point+l,point+mid,point+r+1);
    node[cur]=point[mid];
    Build(l,mid-1,lson,depth+1);
    Build(mid+1,r,rson,depth+1);
}

void query(Node p,int m,int cur,int depth){
    if(flag[cur]==-1) return;
    Pair tmp(0,node[cur]);
    tmp.first=dis(node[cur],p);
    int dim=depth%k;
    bool fg=false;//测试是否需要遍历右子树
    int lson=cur<<1;int rson=cur<<1|1;
    if(p.f[dim]>=node[cur].f[dim]){
        swap(lson,rson);
    }
    if(~(flag[lson])) query(p,m,lson,depth+1);
    if(q.size()<m){
        q.push(tmp);
        fg=1;
    }else{
        if(tmp.first<q.top().first){
            q.pop();
            q.push(tmp);
        }
        if((node[cur].f[dim]-p.f[dim])*(node[cur].f[dim]-p.f[dim])<q.top().first){
            fg=1;
        }
    }
    if(fg&&~flag[rson]){
        query(p,m,rson,depth+1);
    }
}

void Print(Node data)
{
    for(int i = 0; i < k; i++)
        printf("%d%c", data.f[i], i==k-1?'\n':' ');
}

void Travel(int cur,int depth){
    if(flag[cur]==-1) return;
    int lson=cur<<1;
    int rson=cur<<1|1;
    printf("cur:%d flag[cur]:%d ",cur,flag[cur]);
    for(int i=0;i<k;i++){
        printf("%d ",node[cur].f[i]);
    }
    printf("depth:%d\n",depth);
    if(~flag[lson]) Travel(lson,depth+1);
    if(~flag[rson]) Travel(rson,depth+1);
}

void debug(){
    Travel(1,0);
}
int main(){
    freopen("in.txt","r",stdin);
    while(scanf("%d%d",&n,&k)!=EOF){
        for(int i=0;i<n;i++){
            for(int j=0;j<k;j++){
                scanf("%d",&point[i].f[j]);
            }
        }
        Build(0,n-1,1,0);
        //debug();
        int t,m;
        scanf("%d",&t);
        while(t--){
            while(!q.empty()) q.pop();
            Node p;
            for(int i=0;i<k;i++){
                scanf("%d",&p.f[i]);
            }
            scanf("%d",&m);
            query(p,m,1,0);
            printf("the closest %d points are:\n", m);
            Node tmp[25];
            for(int i = 0;!q.empty(); i++)
            {
                tmp[i] = q.top().second;
                q.pop();
            }
            for(int i = m - 1; i >= 0; i--)
                Print(tmp[i]);
        }
    }
}
