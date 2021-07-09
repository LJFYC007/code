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

int dis[maxn][maxn], n, ans;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    while ( ~scanf("%d", &n) && n )
    {
        REP(i, 1, n - 1)
            REP(j, i + 1, n)
                scanf("%d", &dis[i][j]);
        ans = dis[1][2];
        REP(i, 3, n)
        {
            int cnt = 0x3f3f3f3f;
            REP(j, 2, i - 1)
            {
                cnt = min(cnt, (dis[1][i] + dis[j][i] - dis[1][j]) / 2); 
            }
            ans += cnt;
        }
        printf("%d\n", ans);
    }
    return 0;
}
