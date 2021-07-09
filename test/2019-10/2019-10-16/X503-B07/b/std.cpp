/***************************************************************
	File name: std.cpp
	Author: ljfcnyali
	Create time: 2019年10月16日 星期三 14时38分47秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define ls(x) Tree[x].lson
#define rs(x) Tree[x].rson
typedef long long LL;

const int maxn = 3010;
const int maxm = 1e5 + 10;

int n, m, k, a[maxn][maxn], f[maxn], sum[maxn], Max, ans;
bitset<maxn> Color[maxm];

inline void read(int &x)
{
    char c = getchar(); x = 0;
    while ( c < '0' || c > '9' ) c = getchar();
    while ( c >= '0' && c <= '9' ) { x = x * 10 + c - '0'; c = getchar(); }
}

inline int Find_Pre(int x, int pos)
{
    if ( Color[x]._Find_first() == maxn ) return 0;
    int now = 0;
    while ( Color[x]._Find_next(now) != pos ) now = Color[x]._Find_next(now);
    return now;
}

int main()
{
    freopen("b.in", "r", stdin);
    freopen("b.out", "w", stdout);
    scanf("%d%d%d", &n, &m, &k);
    REP(i, 1, n) REP(j, 1, m) read(a[i][j]);
    REP(i, 1, k) REP(j, 1, m) Color[a[i][j]].set(j, true);
    REP(i, 1, k) REP(j, 1, k) { ++ sum[a[i][j]]; if ( sum[a[i][j]] == 1 ) ++ f[1]; }
    Max = ans = f[1];
    REP(j, 2, m - k + 1)
    {
        f[j] = f[j - 1];
        REP(i, 1, k)
        {
            -- sum[a[i][j - 1]]; if ( !sum[a[i][j - 1]] ) -- f[j];
            ++ sum[a[i][j + k - 1]]; if ( sum[a[i][j + k - 1]] == 1 ) ++ f[j];
        }
        Max = max(Max, f[j]); ans += f[j];
    }
    REP(i, 2, m - k + 1) f[i] = f[i] - f[i - 1];
    REP(i, 2, n - k + 1)
    {
        REP(j, 1, m)
        {
            int L = Find_Pre(a[i][j], j), R = Color[a[i][j]]._Find_next(j);
        }
    }
    return 0;
}
