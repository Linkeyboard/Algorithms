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

const int MAXN=200+2;
int group[MAXN],linker[MAXN];
int n,m,un,vn;
bool graph[MAXN][MAXN],G[MAXN][MAXN],vis[MAXN];
int mapl[MAXN],mapr[MAXN];

bool dfs(int u){
    for(int i=1;i<=vn;i++){
        if(G[u][i]&&!vis[i]){
            vis[i]=1;
            if(linker[i]==-1||dfs(linker[i])){
                linker[i]=u;
                return true;
            }
        }
    }
    return false;
}

int hungary(){
    int res=0;
    memset(linker,-1,sizeof(linker));
    for(int i=1;i<=un;i++){
        memset(vis,0,sizeof(vis));
        if(dfs(i)) res++;
    }
    return res;
}
int main(){
    //freopen("in.txt","r",stdin);
    while(scanf("%d%d",&n,&m)!=EOF){
        int u,v;
        memset(group,-1,sizeof(group));
        memset(graph,0,sizeof(graph));
        memset(G,0,sizeof(G));
        bool flag=true;
        for(int i=1;i<=m;i++){
            scanf("%d%d",&u,&v);
            if(group[u]==-1&&group[v]==-1){
                group[u]=0;
                group[v]=1;
            }else if(group[u]!=-1){
                if(group[v]!=-1&&!(group[u]^group[v])){
                    flag=false;
                }else{
                    if(group[v]==-1) group[v]=group[u]^1;
                }
            }else if(group[v]!=-1){
                if(group[u]!=-1&&group[u]^group[v]==0){
                    flag=false;
                }else{
                    if(group[u]==-1) group[u]=group[v]^1;
                }
            }
            graph[u][v]=graph[v][u]=1;
        }
        if(!flag){
            cout<<"No\n";
            continue;
        }
        un=0;vn=0;
        for(int i=1;i<=n;i++){
            if(group[i]==1){
                un++;
                mapl[i]=un;
            }else if(group[i]==0){
                vn++;
                mapr[i]=vn;
            }
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(graph[i][j]){
                    if(group[i]==0&&group[j]==1){
                        G[mapr[i]][mapl[j]]=G[mapl[j]][mapr[i]]=1;
                    }else{
                        G[mapl[i]][mapr[j]]=G[mapr[j]][mapl[i]]=1;
                    }
                }
            }
        }
        printf("%d\n",hungary());
    }
    return 0;
}
