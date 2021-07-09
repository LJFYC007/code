/***************************************************************
	File name: 1.cpp
	Author: ljfcnyali
	Create time: 2019年10月17日 星期四 15时38分17秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 510;

int f[maxn][maxn][20], n, a[maxn], ans;

int main()
{
    freopen("2048.in", "r", stdin);
    freopen("2048.out", "w", stdout);
    scanf("%d", &n);
    memset(f, -0x3f, sizeof(f));
    REP(i, 1, n) scanf("%d", &a[i]);
    REP(i, 1, n)
        REP(j, i, n)
            REP(k, i, j)
                REP(o, 1, 4)
                    if ( (1 << o) == a[k] ) f[i][j][o] = a[k];
    REP(o, 2, 15)
        REP(len, 1, n)
            REP(i, 1, n - len + 1)
            {
                int j = i + len - 1;
                REP(k, i, j - 1)
                    f[i][j][o] = max(f[i][j][o], f[i][k][o - 1] + f[k + 1][j][o - 1] + (1 << o));
                ans = max(ans, f[i][j][o]);
            }
    REP(i, 1, n) REP(j, i, n) REP(o, 1, 5) printf("%d %d %d %d\n", i, j, o, f[i][j][o]);
    printf("%d\n", ans);
    return 0;
}
