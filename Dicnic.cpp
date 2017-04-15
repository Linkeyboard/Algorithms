#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <vector>
#include <queue>
#include <string>
#include <cstring>
using namespace std;


const int MAXN=1000+10;
const int INF=100000;
int k,c,m;
int maze[MAXN][MAXN];


void floyd(){
    for(int i=1;i<=k+c;i++){
        for(int j=1;j<=k+c;j++){
            for(int l=1;l<=k+c;l++){
                maze[j][l]=min(maze[j][l],maze[j][i]+maze[i][l]);
            }
        }
    }
}


struct Edge{
    int from,to,cap,flow;
};

vector <Edge> edges;
vector <int> G[MAXN];


void AddEdge(int from,int to,int cap){
    edges.push_back((Edge){from,to,cap,0});
    edges.push_back((Edge){to,from,0,0});
    int cnt=edges.size();
    G[from].push_back(cnt-2);
    G[to].push_back(cnt-1);
}


struct Dicnic{
    bool vis[MAXN];
    int d[MAXN];
    int cur[MAXN];
    int s,t;


    bool BFS(){
        memset(vis,0,sizeof(vis));
        queue <int> Q;
        Q.push(s);
        d[s]=0;
        vis[s]=1;
        while(!Q.empty()){
            int x=Q.front();
            Q.pop();
            for(int i=0;i<G[x].size();i++){
                Edge &e=edges[G[x][i]];
                if(!vis[e.to]&&e.cap>e.flow){
                    vis[e.to]=1;
                    d[e.to]=d[x]+1;
                    Q.push(e.to);
                }
            }
        }
        return vis[t];
    }

    int DFS(int x,int a){
        if(x==t||a==0){
            return a;
        }
        int flow=0,f;
        for(int &i=cur[x];i<G[x].size();i++){
            Edge &e=edges[G[x][i]];
            if(d[x]+1==d[e.to]&&(f=DFS(e.to,min(a,e.cap-e.flow)))>0){
                e.flow+=f;
                edges[G[x][i]^1].flow-=f;
                flow+=f;
                a-=f;
                if(a==0) break;
            }
        }
        return flow;
    }

    int Maxflow(int s,int t){
        this->s=s;
        this->t=t;
        int flow=0;
        while(BFS()){
            memset(cur,0,sizeof(cur));
            flow+=DFS(s,INF);
        }
        return flow;
    }
}dicnic;

void Buildgraph(int L){
    edges.clear();
    for(int i=0;i<=k+c+2;i++){
        G[i].clear();
    }
    for(int i=1;i<=k;i++){
        for(int j=1+k;j<=k+c;j++){
            if(maze[i][j]<=L){
                AddEdge(j,i,1);
            }
        }
    }
    for(int i=1;i<=k;i++){
        AddEdge(i,k+c+1,m);
    }
    for(int i=1+k;i<=k+c;i++){
        AddEdge(0,i,1);
    }
}


int main()
{
    //freopen("in.txt","r",stdin);
    while(scanf("%d%d%d",&k,&c,&m)!=EOF){
        for(int i=1;i<=k+c;i++){
            for(int j=1;j<=k+c;j++){
                scanf("%d",&maze[i][j]);
                if(!maze[i][j]&&i!=j){
                    maze[i][j]=INF;
                }
            }
        }
        floyd();
        int low=0,high=INF,ans;
        while(low<=high){
            int mid=(low+high)>>1;
            Buildgraph(mid);
            if(dicnic.Maxflow(0,k+c+1)==c){
                ans=mid;
                high=mid-1;
            }else{
                low=mid+1;
            }
        }
        printf("%d\n",ans);
    }

    return 0;
}

