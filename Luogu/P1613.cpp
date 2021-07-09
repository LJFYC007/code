#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset ( (a), 0, sizeof ( a ) )
#define str(a) strlen ( a )
typedef long long LL;
template<class T> int maxx(T a, T b) { return a > b ? a : b; }
template<class T> int minn(T a, T b) { return a < b ? a : b; }
template<class T> int abss(T a) { return a > 0 ? a : -a; }
#define max maxx
#define min minn
#define abs abss

const int maxn = 110;
const LL INF = 0x3f3f3f3f3f3f3f3f;

bool F[maxn][maxn][maxn];
LL Map[maxn][maxn], n, m;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld", &n, &m);
    REP(i, 1, n) REP(j, 1, n) Map[i][j] = INF;
    REP(i, 1, m)
    {
        LL u, v; scanf("%lld%lld", &u, &v);
        Map[u][v] = 1;
        F[u][v][0] = true;
    }
    REP(k, 1, 64)
    {
        REP(u, 1, n)
            REP(v, 1, n)
                REP(i, 1, n)
                    if ( F[u][i][k - 1] == true && F[i][v][k - 1] == true ) 
                    {
                        F[u][v][k] = true;
                        Map[u][v] = 1;
                    }
    }
    REP(k, 1, n)
        REP(i, 1, n)
            REP(j, 1, n)
                if ( Map[i][j] && Map[j][k] ) 
                {
                    Map[i][k] = min(Map[i][k], Map[i][j] + Map[j][k]);
                }
    printf("%lld\n", Map[1][n]);
    return 0;
}
