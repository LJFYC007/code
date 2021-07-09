/***************************************************************
    File name: C.cpp
    Author: ljfcnyali
    Create time: 2020年05月30日 星期六 08时34分11秒
***************************************************************/
#include<bits/stdc++.h>
 
using namespace std;
 
#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset ( (a), 0, sizeof ( a ) )
#define str(a) strlen ( a )
#define pii pair<int, int>
#define int long long
typedef long long LL;
 
const int maxn = 3e5 + 10;
const int Mod = 998244353;
 
int T, n, f[20][2], ans, cur, m, g[8], Edge[500][2], dp[maxn][50], a[20];
char P[10], S[maxn];
struct node { char s[9]; int len; } p[500], h[500];
 
inline void Solve(int n)
{
    REP(i, 1, n) REP(j, 0, 1) f[i][j] = 0;
    f[1][a[1]] = 1;
    for ( int i = 1; i < n; i += 2 ) 
        for ( int j = i + 2; j <= n; j += 2 ) 
            REP(k, 0, 1)
            {
                if ( !f[i][k] ) continue ;
                int now = a[j];
                for ( int o = j - 1; o > i + 1; o -= 2 ) 
                {
                    now = now | (a[o] << 1);
                    now = now | (a[o - 1] << 2);
                    now = g[now];
                }
                now = now | (a[i + 1] << 1);
                now = now | (k << 2);
                now = g[now];
                f[j][now] = 1;
            }
}
 
inline bool Check(node s, node t)
{
    if ( s.len % 2 != t.len % 2 ) return false;
    int len;
    REP(i, 1, m)
    {
        if ( !((s.len + h[i].len) & 1) ) continue ;
 
        REP(j, 1, s.len) a[j] = s.s[j] - '0';
        REP(j, 1, h[i].len) a[s.len + j] = h[i].s[j] - '0';
        len = s.len + h[i].len;
        Solve(len); int x = f[len][1];
 
        REP(j, 1, t.len) a[j] = t.s[j] - '0';
        REP(j, 1, h[i].len) a[t.len + j] = h[i].s[j] - '0';
        len = t.len + h[i].len;
        Solve(len); if ( f[len][1] != x ) return false;
    }
    return true;
}

signed main()
{
    freopen("junior.in", "r", stdin);
    freopen("junior.out", "w", stdout);
    srand(time(0));
    h[++ m].len = 0;
    REP(i, 1, 7)
    {
        int x = 0;
        while ( x < (1 << i) )
        {
            h[++ m].len = i;
            REP(j, 1, i) h[m].s[j] = '0' + ((x >> j - 1) & 1);
            ++ x;
        }
    }
 
    scanf("%lld", &T);
    Edge[0][0] = 1; Edge[0][1] = 2;
    while ( T -- )
    {
        scanf("%s", P); 
        g[0] = P[0]; g[1] = P[4]; g[2] = P[2]; g[3] = P[6]; g[4] = P[1]; g[5] = P[5]; g[6] = P[3]; g[7] = P[7];
        REP(i, 0, 7) g[i] = g[i] - '0';

        cur = ans = 0;
        queue<int> Q;
        p[++ cur].len = 1; p[cur].s[1] = '0';
        p[++ cur].len = 1; p[cur].s[1] = '1';
        Q.push(1); Q.push(2);
        while ( !Q.empty() )
        {
            int x = Q.front(); Q.pop();
            REP(i, 0, 1)
            {
                p[++ cur].len = p[x].len + 1;
                REP(j, 0, p[x].len) p[cur].s[j] = p[x].s[j];
                p[cur].s[p[cur].len] = i + '0';
                bool flag = true;
                REP(j, 1, cur - 1) if ( Check(p[cur], p[j]) ) { -- cur; Edge[x][i] = j; flag = false; break ; }
                if ( flag ) { Q.push(cur); Edge[x][i] = cur; }
            }
        }

        /*
        REP(i, 1, cur)
        {
            printf("%lld %lld ", i, p[i].len);
            REP(j, 1, p[i].len) printf("%c", p[i].s[j]); puts("");
        }
        REP(i, 1, cur) printf("%lld %lld %lld\n", i, Edge[i][0], Edge[i][1]);
        */
 
        scanf("%s", S + 1); n = str(S + 1);
        dp[0][0] = 1;
        REP(i, 1, n)
        {
            REP(j, 0, cur) dp[i][j] = 0;
            REP(j, 0, cur)
            {
                if ( S[i] != '1' ) dp[i][Edge[j][0]] = (dp[i][Edge[j][0]] + dp[i - 1][j]) % Mod;
                if ( S[i] != '0' ) dp[i][Edge[j][1]] = (dp[i][Edge[j][1]] + dp[i - 1][j]) % Mod;
            }
        }

        REP(i, 1, cur)
        {
            if ( p[i].len % 2 == 0 ) continue ;
            int len = p[i].len;
            REP(j, 1, len) a[j] = p[i].s[j] - '0';
            Solve(len);
            if ( f[len][1] == 1 ) ans = (ans + dp[n][i]) % Mod;
        }
        printf("%lld\n", ans);
    }
    return 0;
}

