// https://blog.csdn.net/Hemk340200600/article/details/63792088

#include <cstring>
#include <algorithm>
#include <stdio.h>

using namespace std;

#define N 2
#define M 2

int w[N][M] = {
    {4, 1},
    {4, 2},
};


// int w[N][M] = {
//     4,
// };
const int inf=(1<<20)-1;
int m = M,n = N;//n左m右
int cx[N],cy[M];//顶标
bool usex[N],usey[M];
int link[M];//link[i]=x代表：在y图中的i与x相连
bool dfs(int u){
    // printf("dfs:u:%d\n", u);
    usex[u]=1;
    for(int i=0;i<m;i++) {
        if(!usey[i]&&cx[u]+cy[i]==w[u][i]) {
            usey[i]=1;
            if(link[i]==-1||dfs(link[i])) {
                link[i]=u;
                return 1;
            }
        }
    }
    return 0;
}
int KM(){
    memset(cy,0,sizeof(cy));
    memset(cx,-1,sizeof(cx));
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            cx[i]=max(cx[i],w[i][j]);
    for(int i=0;i<n;i++) {
        printf("for loop for i:%d\n", i);
        while(1){
            int d=inf;
            memset(usex,0,sizeof(usex));
            memset(usey,0,sizeof(usey));
            if(dfs(i)) {
                printf("complete i:%d\n\n", i);
                break;
            }
            for(int i=0;i<n;i++)
            {
            	if(usex[i])
            	{
            		for(int j=0;j<m;j++)
            		{
            			if(!usey[j])
							d=min(d,cx[i]+cy[j]-w[i][j]);
					}
				}
			}
            if(d==inf)return -1;
            for(int i=0;i<n;i++) {
                if(usex[i]) {
                    printf("update cx[%d]:%d -=%d\n", i, cx[i], d);
                    cx[i]-=d;
                }
            }

            for(int i=0;i<m;i++) {
                if(usey[i]) {
                    printf("update cy[%d]:%d -=%d\n", i, cy[i], d);
                    cy[i]+=d;
                }
            }

        }
    }
    int ans=0;
    for(int i=0;i<m;i++){
        if(~link[i])ans+=w[link[i]][i];
    }
    return ans;
}

int main() {
    n = N;
    m = M;
    memset(&link[0], -1, sizeof(link));
    int ans = KM();
    printf("ans:%d\n", ans);
}