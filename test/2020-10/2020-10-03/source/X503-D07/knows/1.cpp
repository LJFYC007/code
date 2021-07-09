/***************************************************************
	File name: know.cpp
	Author: ljfcnyali
	Create time: 2020年10月03日 星期六 09时14分55秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1010;
const int INF = 2e9 + 10;

int n, p[maxn], q[maxn], c[maxn], f[maxn][maxn][2];

int main()
{
    freopen("knows.in", "r", stdin);
    freopen("knows.out", "w", stdout);
    scanf("%d", &n);
    REP(i, 1, n) { scanf("%d", &p[i]); q[p[i]] = i; }
    REP(i, 1, n) scanf("%d", &c[i]);
    REP(i, 0, n) REP(k, 0, n) f[i][k][0] = f[i][k][1] = INF; f[0][0][0] = 0;
    REP(i, 1, n) REP(k, 0, n) REP(op, 0, 1)
    {
        if ( q[i] < k ) { f[i][k][op] = min(f[i][k][op], f[i - 1][k][op]); continue ; }
        if ( op == 0 )
        {
            f[i][k][1] = min(f[i][k][1], f[i - 1][k][0]);
            f[i][q[i]][0] = min(f[i][q[i]][0], f[i - 1][k][0] + c[q[i]]);
        }
        else 
        {
            f[i][k][1] = min(f[i][k][1], f[i - 1][k][1]);
            int Min = q[i], now = i - 1;
            while ( q[now] != k && now > 0 ) 
            { 
                if ( q[now] > k ) Min = min(Min, q[now]); 
                -- now; 
            }
            cerr << i - 1 << " " << k << " " << f[i - 1][k][1] << endl;
            if ( k != 0 && now == 0 ) 
                assert(f[i - 1][k][1] >= INF);
            // if ( now == 0 ) continue ;
            if ( q[i] <= Min ) f[i][q[i]][0] = min(f[i][q[i]][0], f[i - 1][k][1] + c[q[i]]);
        }
    }
    int ans = INF;
    REP(i, 0, n) ans = min(ans, f[n][i][0]);
    printf("%d\n", ans);
    return 0;
}
