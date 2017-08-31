#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstring>
using namespace std;

#define LL unsigned long long

const int MAXN=1000+10;

int NEXT[MAXN];
char s1[MAXN],s2[MAXN];
void getNEXT(char *p){
    NEXT[0]=-1;
    int len=strlen(p);
    int k=-1,j=0;
    while(j<len-1){
        if(k==-1||p[k]==p[j]){
            ++k;++j;
            if(p[k]!=p[j]) NEXT[j]=k;
            else NEXT[j]=NEXT[k];
        }else{
            k=NEXT[k];
        }
    }
}


int KMP(char *s,char *p){
    int slen=strlen(s);
    int plen=strlen(p);
    int i=0,j=0;
    int time=0;
    while(i<slen){
        if(j==-1||s[i]==p[j]){
            j++;
            i++;
            if(j==plen){
                time++;
                j=0;
            }
        }else{
            j=NEXT[j];
        }
    }
    return time;
}

int main(){
    while(scanf("%s",s1)!=EOF){
        if(!strcmp(s1,"#")) break;
        scanf("%s",s2);
        getNEXT(s2);
        printf("%d\n",KMP(s1,s2));
    }
    return 0;
}
