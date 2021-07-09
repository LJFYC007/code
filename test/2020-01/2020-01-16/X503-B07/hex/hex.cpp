/***************************************************************
	File name: hex.cpp
	Author: ljfcnyali
	Create time: 2020年01月16日 星期四 10时10分43秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e6 + 10;

int a[maxn], n, p[maxn], len, sum[maxn][16];

inline void DFS()
{
    if ( n > 1000000 ) return ;
    ++ p[1]; 
    int i = 1;
    while ( p[i] == 16 ) { p[i] = 0; ++ i; ++ p[i]; }
    len = max(len, i);
    for ( int i = len; i >= 1; -- i ) a[++ n] = p[i];
    DFS();
}

int main()
{
    freopen("hex.in", "r", stdin);
    freopen("hex.out", "w", stdout);
    len = 1; DFS();
    REP(i, 1, n) REP(j, 0, 15) sum[i][j] = sum[i - 1][j] + (a[i] == j ? 1 : 0);
    int T = 1; scanf("%d", &T);
    while ( T -- ) 
    {
        int type; char c; scanf("%d%d", &type, &n);
        if ( type == 2 ) { getchar(); scanf("%c", &c); }
        if ( n <= 1000000 ) 
        { 
            if ( type == 1 ) printf("%c\n", c = a[n] < 10 ? '0' + a[n] : 'A' + a[n] - 10);
            else printf("%d\n", sum[n][c <= '9' ? c - '0' : c - 'A' + 10]);
            continue ; 
        }
        else 
        {
        }
    }
    return 0;
}
