/***************************************************************
	File name: HaHa
	Author: ljfcnyali
	Create time: 2019年11月06日 20时19分54秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2000010;

int n, a[maxn], f[maxn][2], son[maxn][2], g[maxn];
char s[10];

inline void DFS2(int u)
{
    if ( a[u] <= 1 ) { g[u] = a[u]; return ; }
    if ( a[u] == 5 ) { DFS2(son[u][0]); g[u] = g[son[u][0]] ^ 1; return ; }
    DFS2(son[u][0]); DFS2(son[u][1]);
    if ( a[u] == 2 ) g[u] = g[son[u][0]] & g[son[u][1]];
    if ( a[u] == 3 ) g[u] = g[son[u][0]] | g[son[u][1]];
    if ( a[u] == 4 ) g[u] = g[son[u][0]] ^ g[son[u][1]];
}

inline void DFS1(int u)
{
    if ( a[u] <= 1 ) return ;
    if ( a[u] == 5 ) 
    {
        f[son[u][0]][0] = f[u][1];
        f[son[u][0]][1] = f[u][0];
        DFS1(son[u][0]); return ;
    }
    REP(i, 0, 1)
    {
        int x = son[u][i], y = son[u][i ^ 1];
        if ( a[u] == 2 ) 
        {
            if ( g[y] ) { f[x][0] = f[u][0]; f[x][1] = f[u][1]; }
            else f[x][0] = f[x][1] = f[u][0]; 
        }
        if ( a[u] == 3 ) 
        {
            if ( g[y] ) f[x][0] = f[x][1] = f[u][1];
            else { f[x][0] = f[u][0]; f[x][1] = f[u][1]; }
        }
        if ( a[u] == 4 ) 
        {
            if ( g[y] ) { f[x][0] = f[u][1]; f[x][1] = f[u][0]; }
            else { f[x][0] = f[u][0]; f[x][1] = f[u][1]; }
        }
    }
    DFS1(son[u][0]); DFS1(son[u][1]);
}

inline void read(int &x)
{
    char c = getchar(); x = 0;
    while ( c < '0' || c > '9' ) c = getchar();
    while ( c >= '0' && c <= '9' ) { x = x * 10 + c - '0'; c = getchar(); }
}

int main()
{
    read(n);
    REP(i, 1, n)
    {
        char c = getchar();
        while ( c < 'A' || c > 'Z' ) c = getchar();
        if ( c == 'A' ) a[i] = 2;
        else if ( c == 'O' ) a[i] = 3;
        else if ( c == 'X' ) a[i] = 4;
        else if ( c == 'N' ) a[i] = 5;
        else { read(a[i]); continue ; }
        int x; read(x); son[i][0] = x;
        if ( a[i] <= 4 ) { read(x); son[i][1] = x; }
    }
    DFS2(1);
    f[1][0] = 0; f[1][1] = 1; 
    DFS1(1);
    REP(i, 1, n) if ( a[i] <= 1 ) putchar(f[i][a[i] ^ 1] + '0'); puts("");
    return 0;
}
