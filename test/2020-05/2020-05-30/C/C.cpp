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
typedef long long LL;
 
const int maxn = 3e5 + 10;
const int Mod = 1e9 + 7;
 
int T, n, f[2][16][16][4], ans, g[6][50][4], cur, m, Edge[50][2], dp[maxn][50], len, a[20];
char P[10], S[maxn];
struct node { char s[9]; int len; } p[50], h[500];
int b[6][50][4], size[6][50];
 
inline void Solve(const int op, const int L, const int R)
{
    if ( f[op][L][R][0] != -1 ) return ;
    const int lim = ((R - L + 1) & 1) ? 1 : 3;
    REP(i, 0, lim) f[op][L][R][i] = 0;
    REP(i, L, R)
    {
        if ( L < i ) Solve(op, L, i - 1); if ( R > i ) Solve(op, i + 1, R);
        const int limx = ((i - L) & 1) ? 1 : 3, limy = ((R - i) & 1) ? 1 : 3;
        REP(j, 0, limx)
        {
            if ( L < i && !f[op][L][i - 1][j] ) continue ;
            REP(k, 0, limy)
            {
                if ( R > i && !f[op][i + 1][R][k] ) continue ;
 
                int x = 0, len = 0;
                if ( L < i )
                {
                    if ( limx == 3 ) { len += 2; x = (x << 2) | j; }
                    else { ++ len; x = (x << 1) | j; }
                }
                ++ len; x = (x << 1) | a[i];
                if ( R > i )
                {
                    if ( limy == 3 ) { len += 2; x = (x << 2) | k; }
                    else { ++ len; x = (x << 1) | k; }
                }
 
                for ( register int o = 0; o < size[len][x]; ++ o ) f[op][L][R][b[len][x][o]] |= 1;
            }
        }
        if ( L == 1 && R == len && f[op][1][len][1] ) return ;
        bool flag = true;
        REP(k, 0, lim) if ( !f[op][L][R][k] ) flag = false;
        if ( flag == true ) return ;
    }
}
 
inline bool Check(node s, node t)
{
    if ( s.len % 2 != t.len % 2 ) return false;
    REP(i, 1, max(s.len, t.len)) REP(j, i, max(s.len, t.len)) REP(o, 0, 3) f[0][i][j][o] = f[1][i][j][o] = -1;
    REP(i, 1, m)
    {
        if ( !((s.len + h[i].len) & 1) ) continue ;
 
        REP(j, 1, s.len) a[j] = s.s[j] - '0';
        REP(j, 1, h[i].len) a[s.len + j] = h[i].s[j] - '0';
        len = s.len + h[i].len;
        REP(j, 1, len) REP(k, max(j, s.len + 1), len) REP(o, 0, 3) f[0][j][k][o] = -1;
        Solve(0, 1, len); int x = f[0][1][len][1];
 
        REP(j, 1, t.len) a[j] = t.s[j] - '0';
        REP(j, 1, h[i].len) a[t.len + j] = h[i].s[j] - '0';
        len = t.len + h[i].len;
        REP(j, 1, len) REP(k, max(j, t.len + 1), len) REP(o, 0, 3) f[1][j][k][o] = -1;
        Solve(1, 1, len);
        if ( f[1][1][len][1] != x ) 
        {
            printf("%d\n", h[i].len);
            REP(j, 1, h[i].len)  printf("%c", h[i].s[j]); puts("");
            return false;
        }
    }
    return true;
}
 
inline void DFS1(int len, int x, int a, int b)
{
    if ( len <= 2 ) { g[a][b][x] = 1; return ; }
    static int h[6];
    REP(i, 1, len - 2)
    {
        REP(j, 1, len) h[len - j + 1] = (x >> j - 1) & 1;
        int y = 0, t = 0;
        REP(j, 1, i - 1) y = (y << 1) | h[j];
        REP(j, i, i + 2) t = (t << 1) | h[j];
        y = (y << 1) | (P[t] - '0');
        REP(j, i + 3, len) y = (y << 1) | h[j];
        DFS1(len - 2, y, a, b);
    }
}
 
signed main()
{
#ifndef ONLINE_JUDGE
    freopen("C.in", "r", stdin);
    freopen("C.out", "w", stdout);
#endif
    srand(time(0));
    h[++ m].len = 0;
    REP(i, 1, 5)
    {
        int x = 0;
        while ( x < (1 << i) )
        {
            h[++ m].len = i;
            REP(j, 1, i) h[m].s[j] = '0' + ((x >> j - 1) & 1);
            ++ x;
        }
    }
    m -= 3;
 
    scanf("%d", &T);
    Edge[0][0] = 1; Edge[0][1] = 2;
    while ( T -- )
    {
        scanf("%s", P); cur = ans = 0;
        mem(g); REP(len, 1, 5) REP(i, 0, (1 << len) - 1) DFS1(len, i, len, i);
        REP(i, 1, 5) REP(j, 0, (1 << i) - 1)
        {
            size[i][j] = 0;
            REP(o, 0, 3) if ( g[i][j][o] == 1 ) b[i][j][size[i][j] ++] = o;
        }
        p[1].len = 2; p[1].s[1] = '0'; p[1].s[2] = '1';
        p[2].len = 2; p[2].s[1] = '1'; p[2].s[2] = '0';
        Check(p[1], p[2]);
        return 0;
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

        scanf("%s", S + 1); n = str(S + 1);
        dp[0][0] = 1;
        reverse(S + 1, S + n + 1);
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
            REP(j, 1, len) REP(k, j, len) REP(o, 0, 3) f[0][j][k][o] = -1;
            Solve(0, 1, len);
            if ( f[0][1][len][1] == 1 ) ans = (ans + dp[n][i]) % Mod;
        }
        printf("%d\n", ans);
    }
    return 0;
}
