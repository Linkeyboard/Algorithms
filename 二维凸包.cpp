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
const int MAXN=310+5;
const int INF=0x3f3f3f3f;
int n;
struct point{
    int x,y;
};

point List[MAXN];
int Stack[MAXN],top;
int cross(point p0,point p1,point p2){
    return (p1.x-p0.x)*(p2.y-p0.y)-(p1.y-p0.y)*(p2.x-p0.x);
}

double dis(point p1,point p2){
    return sqrt((double)(p2.x-p1.x)*(p2.x-p1.x)+(p2.y-p1.y)*(p2.y-p1.y));
}


bool cmp(point p1,point p2){
    int tmp=cross(List[0],p1,p2);
    if(tmp>0) return true;
    else if(tmp==0&&dis(List[0],p1)<dis(List[0],p2)) return true;
    else return false;
}

void init(){
    int k;
    point p0;
    scanf("%d%d",&List[0].x,&List[0].y);
    p0.x=List[0].x;
    p0.y=List[0].y;
    k=0;
    for(int i=1;i<n;i++){
        scanf("%d%d",&List[i].x,&List[i].y);
        if((p0.y>List[i].y)||((p0.y==List[i].y)&&(p0.x>List[i].x))){
            p0.x=List[i].x;
            p0.y=List[i].y;
            k=i;
        }
    }
    List[k]=List[0];
    List[0]=p0;
    sort(List+1,List+n,cmp);
}


void graham(){
    if(n==1){
        top=0;
        Stack[0]=0;
    }else if(n==2){
        top=1;
        Stack[0]=0;
        Stack[1]=1;
    }else if(n>2){
        for(int i=0;i<=1;i++) Stack[i]=i;
        top=1;
        for(int i=2;i<n;i++){
            while(top>0&&cross(List[Stack[top-1]],List[Stack[top]],List[i])<=0) top--;
            top++;
            Stack[top]=i;
        }
    }

}



int main(){
   //freopen("in.txt","r",stdin);
    while(scanf("%d",&n)!=EOF){
        init();
        graham();
        if(top!=n-1){
            printf("No\n");
        }else printf("YES\n");
    }
    return 0;
}


