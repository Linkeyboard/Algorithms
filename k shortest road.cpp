#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <string>
#include <cmath>
#include <queue>
using namespace std;

#define ll long long
const int N=100000+10;
const int M=1000000+10;
const int INF=0x3f3f3f3f;
int head[N],n,m,head1[N];
int dis[N],cnt[N];
bool vis[N];
queue <int> nodeq;

struct EdgeNode{
    int to;
    int value;
    int next;
}edge[M],edge1[M];


struct NODE{
    int to;
    int f,g;
    bool operator < (const NODE &r) const{
        if(f==r.f) return r.g<g;
        else return r.f<f;
    }
};



bool spfa(int start){
    while(!nodeq.empty()) nodeq.pop();
    for(int i=0;i<=n;i++){
        dis[i]=INF;
        cnt[i]=0;
        vis[i]=false;
    }
    dis[start]=0;
    vis[start]=true;
    nodeq.push(start);
    while(!nodeq.empty()){
        int tmp=nodeq.front();
        nodeq.pop();
        cnt[tmp]++;
        vis[tmp]=false;
        if(cnt[tmp]>n-1) return false;
        for(int x=head1[tmp];x!=-1;x=edge1[x].next){
            if(dis[tmp]+edge1[x].value<dis[edge1[x].to]){
                dis[edge1[x].to]=dis[tmp]+edge1[x].value;
                if(!vis[edge1[x].to]){
                    vis[edge1[x].to]=true;
                    nodeq.push(edge1[x].to);
                }
            }
        }
    }
    return true;
}

int A_Star(int start,int des,int k){
    if(dis[des]==INF) return -1;
    if(start==des) k++;
    priority_queue <NODE> Aq;
    NODE tmp1,tmp2;
    tmp1.to=start;
    tmp1.g=0;
    tmp1.f=tmp1.g+dis[tmp1.to];
    Aq.push(tmp1);
    int time=0;
    while(!Aq.empty()){
        tmp2=Aq.top();
        Aq.pop();
        if(tmp2.to==des){
            time++;
        }
        if(time==k){
            return tmp2.g;
        }
        for(int x=head[tmp2.to];x!=-1;x=edge[x].next){
            tmp1.to=edge[x].to;
            tmp1.g=tmp2.g+edge[x].value;
            tmp1.f=tmp1.g+dis[tmp1.to];
            Aq.push(tmp1);
        }
    }
    return -1;
}


int main(){
    //freopen("in.txt","r",stdin);
    scanf("%d%d",&n,&m);
    int tot=0,A,B,T,S,K;
    memset(head,-1,sizeof(head));
    memset(head1,-1,sizeof(head1));
    for(int i=0;i<m;i++){
        scanf("%d%d%d",&A,&B,&T);
        edge[tot].to=B;
        edge[tot].value=T;
        edge[tot].next=head[A];
        head[A]=tot;
        edge1[tot].to=A;
        edge1[tot].value=T;
        edge1[tot].next=head1[B];
        head1[B]=tot++;
    }
    scanf("%d%d%d",&S,&T,&K);
    spfa(T);
    printf("%d\n",A_Star(S,T,K));
    return 0;
}
