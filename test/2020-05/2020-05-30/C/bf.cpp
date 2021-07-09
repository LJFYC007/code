/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2020年05月30日 星期六 08时34分11秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 3e5 + 10;
const int Mod = 1e9 + 7;

int T, n, f[20][20][4], ans, g[6][50][4];
char P[maxn], S[maxn];

inline void Solve(int L, int R)
{
    if ( L > R || f[L][R][0] != -1 ) return ;
    REP(i, 0, 3) f[L][R][i] = 0;
    REP(i, L, R)
    {
        Solve(L, i - 1); Solve(i + 1, R);
        REP(j, 0, 3) REP(k, 0, 3)
        {
            if ( L <= i - 1 && f[L][i - 1][j] != 1 ) continue ;
            if ( R >= i + 1 && f[i + 1][R][k] != 1 ) continue ;

            int x = 0, len = 0;
            if ( L <= i - 1 ) 
            {
                if ( !((i - L) & 1) ) { len += 2; x = (x << 2) | j; }
                else { ++ len; x = (x << 1) | j; }
            }
            ++ len; x = (x << 1) | (S[i] - '0');
            if ( R >= i + 1 ) 
            {
                if ( !((R - i) & 1) ) { len += 2; x = (x << 2) | k; }
                else { ++ len; x = (x << 1) | k; }
            }

            REP(o, 0, 3) if ( g[len][x][o] ) f[L][R][o] = 1;
        }
    }
}

inline void DFS1(int len, int x, int a, int b)
{
    if ( len <= 2 ) { g[a][b][x] = 1; return ; }
    static int h[6]; 
    REP(i, 1, len - 2)
    {
        REP(j, 1, len) h[len - j + 1] = (x >> j - 1) & 1;
        int y = 0, t = 0; 
        REP(j, 1, i - 1) y = (y << 1) | h[j];
        REP(j, i, i + 2) t = (t << 1) | h[j];
        y = (y << 1) | (P[t] - '0');
        REP(j, i + 3, len) y = (y << 1) | h[j];
        DFS1(len - 2, y, a, b);
    }
}

inline void DFS(int x)
{
    if ( x == n + 1 ) 
    { 
        REP(i, 1, n) REP(j, i, n) REP(k, 0, 3) f[i][j][k] = -1;
        Solve(1, n); if ( f[1][n][1] == 1 ) ++ ans;
        return ;
    }
    if ( S[x] != '?' ) { DFS(x + 1); return ; }
    S[x] = '0'; DFS(x + 1); S[x] = '1'; DFS(x + 1); S[x] = '?';
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("C.in", "r", stdin);
    freopen("C.out", "w", stdout);
#endif
    scanf("%d", &T);
    while ( T -- ) 
    {
        ans = 0; scanf("%s", P); 
        mem(g); REP(len, 1, 5) REP(i, 0, (1 << len) - 1) DFS1(len, i, len, i);
        scanf("%s", S + 1); n = str(S + 1);
        reverse(S + 1, S + n + 1);
        DFS(1);
        printf("%d\n", ans);
    }
    return 0;
}
