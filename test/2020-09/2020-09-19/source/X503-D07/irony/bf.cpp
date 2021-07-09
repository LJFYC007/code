/***************************************************************
	File name: irony.cpp
	Author: ljfcnyali
	Create time: 2020年09月20日 星期日 15时50分18秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1010;
const int INF = 0x3f3f3f3f;

int n, m, a[maxn], b[maxn], f[maxn][maxn], ans;

int main()
{
    freopen("irony.in", "r", stdin);
    freopen("irony.out", "w", stdout);

    int T; scanf("%d", &T);
    while ( T -- ) 
    {
        scanf("%d%d", &n, &m); 
        getchar(); REP(i, 1, n) { char c = getchar(); a[i] = c == '(' ? 1 : -1; }
        getchar(); REP(i, 1, m) { char c = getchar(); b[i] = c == '(' ? 1 : -1; }

        REP(i, 1, n) a[i] += a[i - 1];
        REP(i, 1, m) b[i] += b[i - 1];
        REP(i, 0, n) REP(j, 0, m) f[i][j] = -INF;
        f[0][0] = INF;
        REP(i, 0, n) REP(j, 0, m)
        {
            f[i + 1][j] = max(f[i + 1][j], min(f[i][j], a[i + 1] + b[j]));
            f[i][j + 1] = max(f[i][j + 1], min(f[i][j], a[i] + b[j + 1]));
        }

        ans = 0;
        if ( f[n][m] < 0 ) ans -= f[n][m];
        if ( a[n] + b[m] + ans > 0 ) ans += a[n] + b[m] + ans; 
        printf("%d\n", ans);
    }
    return 0;
}
