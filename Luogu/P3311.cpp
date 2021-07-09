/***************************************************************
	File name: P3311.cpp
	Author: ljfcnyali
	Create time: 2019年11月04日 星期一 15时33分45秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 5010;
const int Mod = 1e9 + 7;

int n, tmp[maxn], m, f[maxn][maxn][2], tot, Next[maxn * 10];
struct node { int Next[10], val; } Tree[maxn * 10];
char s[maxn];

inline void Insert()
{
    int len = str(s + 1), p = 0;
    REP(i, 1, len)
    {
        int c = s[i] - '0';
        if ( !Tree[p].Next[c] ) Tree[p].Next[c] = ++ tot;
        p = Tree[p].Next[c];
    }
    Tree[p].val = 1;
}

inline void Build()
{
    queue<int> Q;
    REP(i, 0, 9) if ( Tree[0].Next[i] ) Q.push(Tree[0].Next[i]);
    while ( !Q.empty() ) 
    {
        int u = Q.front(); Q.pop();
        REP(c, 0, 9)
        {
            if ( !Tree[u].Next[c] ) { Tree[u].Next[c] = Tree[Next[u]].Next[c]; continue ; }
            Next[Tree[u].Next[c]] = Tree[Next[u]].Next[c];
            Q.push(Tree[u].Next[c]);
        }
    }
    Tree[0].Next[0] = 0;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%s", s + 1); n = str(s + 1);
    REP(i, 1, n) tmp[i] = s[i] - '0';
    scanf("%lld", &m);
    REP(i, 1, m) { scanf("%s", s + 1); Insert(); }
    Build();
    f[0][0][1] = 1;
    REP(i, 0, n - 1)
        REP(j, 0, tot)
            REP(o, 0, 1)
            {
                if ( !f[i][j][o] ) continue ;
                int dim = o ? tmp[i + 1] : 9;
                REP(k, 0, dim) 
                {
                    int u = Tree[j].Next[k];
                    if ( Tree[u].val ) continue ;
                    f[i + 1][u][o & (k == dim)] = (f[i + 1][u][o & (k == dim)] + f[i][j][o]) % Mod;
                }
            }
    int ans = -1;
    REP(i, 0, tot) ans = (ans + f[n][i][0] + f[n][i][1]) % Mod;
    printf("%lld\n", ans);
    return 0;
}
