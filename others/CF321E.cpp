/***************************************************************
	File name: CF321E.cpp
	Author: ljfcnyali
	Create time: 2019年09月19日 星期四 13时27分27秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 4010;

int f[maxn][810], n, k, a[maxn][maxn];

inline void Solve(int l, int r, int L, int R, int now)
{
    if ( l > r ) return ;
    int Mid = l + r >> 1, k = 0x3f3f3f3f, pos = 0;
    REP(i, L, min(Mid, R))
    {
        int tmp = f[i][now - 1] + (a[Mid][Mid] + a[i][i] - 2 * a[i][Mid]) / 2;
        if ( tmp < k ) { k = tmp; pos = i; }
    }
    f[Mid][now] = k;
    Solve(l, Mid - 1, L, pos, now);
    Solve(Mid + 1, r, pos, R, now);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &k);
    REP(i, 1, n)
        REP(j, 1, n)
        {
            scanf("%d", &a[i][j]);
            a[i][j] += a[i - 1][j] + a[i][j - 1] - a[i - 1][j - 1];
        }
    memset(f, 0x3f, sizeof(f)); f[0][0] = 0;
    REP(i, 1, k) Solve(1, n, 0, n, i);
    printf("%d\n", f[n][k]);
    return 0;
}
