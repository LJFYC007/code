/***************************************************************
	File name: P1841.cpp
	Author: ljfcnyali
	Create time: 2019年06月24日 星期一 09时08分55秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define min minn

const int maxn = 210;

int f1[maxn][maxn], f2[maxn][maxn], f[maxn][maxn], n, m;
bool flag = false;

inline int minn(int a, int b) { return a < b ? a : b; }

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    memset(f1, 0x3f, sizeof(f1));
    memset(f, 0x3f, sizeof(f));
    REP(i, 1, m) 
    { 
        int u, v, w; 
        scanf("%d%d%d", &u,  &v, &w); 
        f[u][v] = f[v][u] = w;
        f1[u][v] = f1[v][u] = w; 
    }
    REP(i, 1, n) f1[i][i] = 0;
    REP(k, 1, n) REP(i, 1, n) REP(j, 1, n) f1[i][j] = min(f1[i][j], f1[i][k] + f1[k][j]);
    REP(o, 1, n)
    {
        REP(i, 1, n) REP(j, 1, n) f2[i][j] = f[i][j]; 
        REP(i, 1, n) f2[o][i] = f2[i][o] = 0x3f3f3f3f;
        REP(i, 1, n) f2[i][i] = 0;
        REP(k, 1, n) 
            REP(i, 1, n) 
            {
                int t = f2[i][k];
                REP(j, 1, i)
                {
                    f2[i][j] = min(f2[i][j], t + f2[k][j]);
                    f2[j][i] = f2[i][j];
                }
            }
        bool Flag = false;
        REP(i, 1, n)
            REP(j, 1, n)
            {
                if ( i == o || j == o ) continue ;
                if ( f2[i][j] > f1[i][j] ) Flag = true;
            }
        if ( Flag == true ) { flag = true; printf("%d ", o); }
    }
    if ( flag == false ) printf("No important cities.\n");
    return 0;
}
