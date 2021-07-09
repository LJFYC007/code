/***************************************************************
	File name: UOJ549.cpp
	Author: ljfcnyali
	Create time: 2020年08月12日 星期三 19时33分56秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;
const int INF = 0x3f3f3f3f;
const int M = (1 << 8) - 1;

int n, k, a[maxn], f[maxn][9];

struct node 
{
    int f[300][300];

    inline int Get(int x)
    {
        int ret = INF;
        REP(i, 0, (1 << 8) - 1) ret = min(ret, f[i][x & M] + ((i ^ (x >> 8)) << 8));
        return ret;
    }

    inline void insert(int x, int val)
    {
        REP(i, 0, (1 << 8) - 1) f[x >> 8][i] = min(f[x >> 8][i], val + ((x & M) ^ i));
    }
} F[9];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &k);
    REP(i, 1, n) { scanf("%d", &a[i]); a[i] ^= a[i - 1]; }
    memset(f, 0x3f, sizeof(f)); memset(F, 0x3f, sizeof(F)); 
    f[0][0] = 0; F[0].insert(0, 0);
    REP(i, 1, n) 
    {
        for ( int j = k; j >= 1; -- j ) { f[i][j] = F[j - 1].Get(a[i]); F[j].insert(a[i], f[i][j]); }
        if ( i >= k ) printf("%d ", f[i][k]);
    }
    return 0;
}
