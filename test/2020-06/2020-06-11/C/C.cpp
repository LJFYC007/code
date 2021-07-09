/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2020年06月11日 星期四 10时33分56秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;
const int maxn = 6e5 + 10;

int n, last = 1, tot = 1, f[maxn], anc[maxn][21], p[maxn], q[maxn], g[maxn];
LL ans;
struct node { int Next[26], len, fa; } Tree[maxn];
bool vis[maxn];
char s[maxn], t[maxn];

inline void Extand(int c)
{
    int cur = ++ tot, p = last; last = cur; Tree[cur].len = Tree[p].len + 1;
    while ( p && !Tree[p].Next[c] ) { Tree[p].Next[c] = cur; p = Tree[p].fa; }
    if ( !p ) { Tree[cur].fa = 1; return ; }
    int q = Tree[p].Next[c];
    if ( Tree[p].len + 1 == Tree[q].len ) { Tree[cur].fa = q; return ; }
    int clone = ++ tot; Tree[clone] = Tree[q]; Tree[clone].len = Tree[p].len + 1;
    while ( p && Tree[p].Next[c] == q ) { Tree[p].Next[c] = clone; p = Tree[p].fa; }
    Tree[q].fa = Tree[cur].fa = clone;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("C.in", "r", stdin);
    freopen("C.out", "w", stdout);
#endif
    scanf("%d", &n); scanf("%s", s + 1);
    reverse(s + 1, s + n + 1);
    REP(i, 1, n) { Extand(s[i] - 'a'); f[i] = last; }
    REP(i, 1, tot) anc[i][0] = Tree[i].fa;
    REP(j, 1, 20) REP(i, 1, tot) anc[i][j] = anc[anc[i][j - 1]][j - 1];
    
    int len = 0; REP(i, 1, n) { t[len ++] = '#'; t[len ++] = s[i]; } t[len ++] = '#';
    int pos = 0, MaxRight = 0;
    REP(i, 0, len - 1)
    {
        if ( i < MaxRight ) p[i] = min(p[2 * pos - i], MaxRight - i);
        else p[i] = 1;
        while ( 0 <= i - p[i] && i + p[i] < len && t[i - p[i]] == t[i + p[i]] ) ++ p[i];
        if ( i + p[i] > MaxRight )
        {
            pos = i; MaxRight = i + p[i];
        }
    }
    REP(i, 0, len - 1)
    {
        int pos = (i - p[i] + 1) / 2 + 1;
        q[pos] = max(q[pos], p[i] - 1);
    }
    REP(i, 2, n) q[i] = max(q[i], q[i - 1] - 2);
    REP(i, 1, tot) g[i] = Tree[anc[i][0]].len;

    for ( int i = n; i >= 1; -- i )
    {
        int x = f[i + q[i] - 1];
        for ( int j = 20; j >= 0; -- j ) if ( Tree[anc[x][j]].len >= q[i] ) x = anc[x][j];
        if ( !vis[x] ) 
        {
            if ( g[x] <= q[i] ) { ans += q[i] - g[x]; g[x] = q[i]; }
            if ( g[x] == Tree[x].len ) vis[x] = true;
        }
        x = anc[x][0];
        while ( !vis[x] && x ) { vis[x] = true; ans += Tree[x].len - g[x]; g[x] = Tree[x].len; x = Tree[x].fa; }
        printf("%lld\n", ans);
    }
    return 0;
}

