/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2020年07月11日 星期六 16时33分57秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset ( (a), 0, sizeof ( a ) )
#define str(a) strlen ( a )
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e3 + 10;

int q, n, k, f[maxn][maxn][11], g[maxn][maxn];

inline int C(int n, int m) { return (n < 0 || m < 0) ? 0 : g[n][m]; }

inline int lowbit(int x) { return x & -x; }
 
inline int Check(int n, int k)
{
    if ( k == 0 ) return 1;
    if ( lowbit(n) != k || n == k ) return 0;
    return 1;
}

inline int DFS(int n, int k, int t)
{
    if ( k < 0 ) return 0;
    if ( f[n][k][t] != -1 ) return f[n][k][t];
    int ret = 0, num = n / (1 << t);
    if ( num < 2 ) ret = Check(n, k);
	else
	{
        for ( int i = num / 2; i >= 0; -- i ) 
		{
            int sum = num - 2 * i;
            ret += (C(sum + i, i) - C(sum + i - 1, sum - 1) + 2) * DFS(n - sum * (1 << t), k - sum * (1 << t), t + 1);
            -- sum;
            if ( k - sum * (1 << t) < 0 ) break ;  
            int x = C(sum + i, i);
            if ( x && sum >= 0 ) ret += x * DFS(n - sum * (1 << t), k - sum * (1 << t), t + 1);
		}
	}
    ret %= 2; f[n][k][t] = ret; return ret;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("B.in", "r", stdin);
    freopen("B.out", "w", stdout);
#endif
    n = maxn - 10;
    memset(f, -1, sizeof(f));
    REP(i, 0, n) g[i][0] = 1;
    REP(i, 1, n) REP(j, 1, i) g[i][j] = (g[i - 1][j] + g[i - 1][j - 1]) % 2;
    scanf("%d", &q);
    while ( q -- )
    {
        scanf("%d%d", &n, &k);
        printf("%d\n", DFS(n, k, 0) % 2);
    }
    return 0;
}
