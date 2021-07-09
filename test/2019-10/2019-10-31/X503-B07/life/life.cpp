/***************************************************************
	File name: life.cpp
	Author: ljfcnyali
	Create time: 2019年10月31日 星期四 08时25分28秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 300010;
const int maxm = 5010;

int n, m, l[maxn], r[maxn], g[maxn], a[maxn], ans;
int f[maxm][maxm];

namespace Subtask1
{
    inline int main()
    {
        int now = 1, ans = 0;         
        REP(i, 1, m)
        {
            while ( now < l[i] ) ++ now;
            while ( !a[now] ) ++ now;
            if ( l[i] <= now && now <= r[i] ) { -- a[now]; ans += g[i]; }
        }
        printf("%lld\n", ans);
        return 0;
    }
}

namespace Subtask2
{
    multiset<int> Set;
    int last, ret;

    inline int main()
    {
        int now = 1;
        REP(i, 1, m)
        {
            if ( last < l[i] ) { Set.clear(); ret = 0; }
            while ( now <= r[i] ) { ret += a[now]; if ( a[now] ) last = now; ++ now; }
            if ( ret ) { Set.insert(g[i]); ans += g[i]; -- ret; }
            else
            {
                auto it = Set.begin();
                if ( *it < g[i] ) { ans = ans - *it + g[i]; Set.erase(*it); Set.insert(g[i]); }
            }
        }
        printf("%lld\n", ans);
        return 0;
    }
}

signed main()
{
    freopen("life.in", "r", stdin);
    freopen("life.out", "w", stdout);
    scanf("%lld%lld", &n, &m);
    REP(i, 1, n) scanf("%lld", &a[i]);
    bool flag = true;
    REP(i, 1, m) { scanf("%lld%lld%lld", &l[i], &r[i], &g[i]); if ( i > 1 && g[i] != g[i - 1] ) flag = false; } 
    if ( flag ) return Subtask1 :: main();
    if ( n > 5000 ) return Subtask2 :: main();
    int i = 0;
    REP(k, 1, n)
        REP(o, 1, a[k]) 
        {
            ++ i;
            REP(j, 1, m)
            {
                f[i][j] = max(f[i - 1][j], f[i][j - 1]);
                if ( l[j] <= k && k <= r[j] ) f[i][j] = max(f[i][j], f[i - 1][j - 1] + g[j]);
                ans = max(ans, f[i][j]);
            }
        }
    printf("%lld\n", ans);
    return 0;
}
