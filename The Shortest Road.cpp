#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#include <cmath>
#include <vector>
using namespace std;

const int MAXN=1000+10;
const int INF=0x3f3f3f3f;
int t,n;

struct qnode{
    int v,c;
    qnode(int vv=0,int cc=0):v(vv),c(cc){}
    bool operator <(const qnode &r) const{
        return c>r.c;
    }
};

struct edge{
    int v;
    int dis;
    edge(int vv=0,int dd=0):v(vv),dis(dd){}
};

vector <edge> E[MAXN];
bool vis[MAXN];
priority_queue<qnode> q;
int dis[MAXN];
void dijisktra(int start){
    while(!q.empty()) q.pop();
    q.push(qnode(start,0));
    for(int i=0;i<=t;i++){
        dis[i]=INF;
        vis[i]=false;
    }
    dis[start]=0;
    while(!q.empty()){
        qnode tmp=q.top();
        q.pop();
        int u=tmp.v;
        if(vis[u]) continue;
        vis[u]=true;
        for(int i=0;i<E[u].size();i++){
            int v=E[u][i].v;
            int cost=E[u][i].dis;
            if(!vis[v]&&dis[v]>dis[u]+cost){
                dis[v]=dis[u]+cost;
                //cout<<"v:"<<v<<" dis[v]:"<<dis[v]<<endl;
                q.push(qnode(v,dis[v]));
            }
        }
    }
}

void AddEdge(int u,int v,int d){
    E[u].push_back(edge(v,d));
    E[v].push_back(edge(u,d));
}

int main(){
    //freopen("in.txt","r",stdin);
    scanf("%d%d",&n,&t);
    int u,v,d;
    for(int i=0;i<n;i++){
        scanf("%d%d%d",&u,&v,&d);
        AddEdge(u,v,d);
    }
    dijisktra(1);
    cout<<dis[t]<<endl;
    return 0;
}
