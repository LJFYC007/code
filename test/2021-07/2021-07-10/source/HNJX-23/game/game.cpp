#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define pii pair<int, int>
#define mem(a) memset((a), 0, sizeof(a))

const int maxn = 1e5 + 10;
const int Mod = 998244353;

int a[8], tot, Edge[50][2], f[maxn][200]; bool g[20][2]; 
struct node { int len, a[20]; } dot[200];
char s[maxn];

inline int get(vector<int> c)
{
    while ( c.size() > 1 ) 
    {
        int w = 0;
        REP(i, 0, 2) { w = w * 2 + c.back(); c.pop_back(); }
        w = a[w]; c.push_back(w);
    }
    return c[0];
}

inline pii Solve(node x)
{
    mem(g); g[1][x.a[1]] = true;
    for ( int i = 3; i <= x.len; i += 2 ) for ( int j = 1; j < i; j += 2 ) REP(o, 0, 1) if ( g[j][o] ) 
    {
        vector<int> a; a.push_back(o);
        REP(k, j + 1, i) a.push_back(x.a[k]);
        g[i][get(a)] = true;
    }
    return pii(g[x.len][0], g[x.len][1]);
}

inline bool Check(node a, node b)
{
    if ( a.len % 2 != b.len % 2 ) return false;
    REP(len, 0, 7) if ( (a.len + len) % 2 == 1 )
        REP(i, 0, (1 << len) - 1) 
        {
            node c = a, d = b;
            REP(j, 1, len)
            {
                c.a[++ c.len] = (i >> j - 1) & 1;
                d.a[++ d.len] = (i >> j - 1) & 1;
            }
            if ( Solve(c) != Solve(d) ) return false;
        }
    return true;
}

inline void Build()
{
    tot = 1; queue<int> Q; Q.push(1);
    while ( !Q.empty() ) 
    {
        int id = Q.front(); node x = dot[Q.front()]; Q.pop();
        REP(i, 0, 1)
        {
            node y = x; y.a[++ y.len] = i;
            bool flag = false;
            REP(j, 1, tot) if ( Check(dot[j], y) ) { Edge[id][i] = j; flag = true; break ; }
            if ( !flag ) { dot[++ tot] = y; Edge[id][i] = tot; Q.push(tot); }
        }
    }
}

int main()
{
    freopen("game.in", "r", stdin);
    freopen("game.out", "w", stdout);
    int T; scanf("%d", &T);
    while ( T -- ) 
    {
        mem(Edge); mem(f);
        REP(i, 0, 7) scanf("%1d", &a[i]);
        Build();
        scanf("%s", s + 1); int n = strlen(s + 1);
        f[0][1] = 1; 
        REP(i, 1, n) REP(j, 1, tot) if ( f[i - 1][j] ) 
        {
            if ( s[i] != '?' ) f[i][Edge[j][s[i] - '0']] = (f[i][Edge[j][s[i] - '0']] + f[i - 1][j]) % Mod;
            else REP(k, 0, 1) f[i][Edge[j][k]] = (f[i][Edge[j][k]] + f[i - 1][j]) % Mod;
        }
        int ans = 0; REP(i, 1, tot) if ( Solve(dot[i]).second == 1 ) ans = (ans + f[n][i]) % Mod;
        printf("%d\n", ans);
    }
    return 0;
}