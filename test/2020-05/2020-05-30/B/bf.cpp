/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2020年05月30日 星期六 07时57分31秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 100 + 10;
const int INF = 0x3f3f3f3f;
const int maxm = 64;

int T, N, S, X, f[maxn][maxn][maxn];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("B.in", "r", stdin);
    freopen("B.out", "w", stdout);
#endif
    scanf("%d", &T);
    while ( T -- ) 
    {
        scanf("%d%d%d", &N, &S, &X);
        memset(f, 0x3f, sizeof(f)); f[0][0][0] = 0;
        REP(i, 1, N) REP(j, 0, maxm) REP(k, 0, S) REP(o, 0, k)
            f[i][j][k] = min(f[i][j][k], max(f[i - 1][j ^ o][k - o], o));
        // REP(i, 1, N) REP(j, 0, X) REP(k, 0, S) printf("%d %d %d %d\n", i, j, k, f[i][j][k]);
        printf("%d\n", f[N][X][S] == INF ? -1 : f[N][X][S]);
    }
    return 0;
}
