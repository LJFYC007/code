/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2020年06月15日 星期一 08时44分56秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int n, m, N;
multiset<int> num[maxn], g[maxn];
char s[maxn], t[maxn], f[51][51];

namespace SAM
{
    int last, tot = 1, Begin[maxn], Next[maxn], To[maxn], e;
    multiset<int> Set[maxn];
    struct node { int Next[26], fa, len; } Tree[maxn];

    inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

    inline void Extend(int c)
    {
        int cur = ++ tot, p = last; last = tot; Tree[cur].len = Tree[p].len + 1;
        while ( p && !Tree[p].Next[c] ) { Tree[p].Next[c] = cur; p = Tree[p].fa; }
        if ( !p ) { Tree[cur].fa = 1; return ; }
        int q = Tree[p].Next[c];
        if ( Tree[p].len + 1 == Tree[q].len ) { Tree[cur].fa = q; return ; }
        int clone = ++ tot; Tree[clone] = Tree[q]; Tree[clone].len = Tree[p].len + 1;
        while ( p && Tree[p].Next[c] == q ) { Tree[p].Next[c] = clone; p = Tree[p].fa; }
        Tree[q].fa = Tree[cur].fa = clone;
    }

    inline void DFS(int u)
    {
        for ( int i = Begin[u]; i; i = Next[i] ) 
        {
            int v = To[i];
            for ( auto j : Set[u] ) Set[v].insert(j);
            DFS(v);
        }
    }

    inline void INIT() 
    { 
        REP(i, 2, tot) add(Tree[i].fa, i);
        DFS(1);
        int p = 1, len = 0;
        REP(i, 1, str(s + 1))
        {
            int c = s[i] - 'a';
            while ( p && !Tree[p].Next[c] ) { p = Tree[p].fa; len = Tree[p].len; }
            if ( Tree[p].Next[c] ) { ++ len; p = Tree[p].Next[c]; }
            if ( !p ) { p = 1; len = 0; }
            num[i].clear();
            for ( auto j : SAM :: Set[p] ) if ( j <= len ) num[i].insert(j);
        }
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("B.in", "r", stdin);
    freopen("B.out", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    REP(i, 1, n)
    {
        scanf("%s", f[i] + 1); SAM :: last = 1;
        int len = str(f[i] + 1);
        REP(j, 1, len) SAM :: Extend(f[i][j] - 'a');
        N = max(N, len);
    }
    REP(i, 1, n)
    {
        int p = 1;
        REP(j, 1, str(f[i] + 1)) p = SAM :: Tree[p].Next[f[i][j] - 'a'];
        SAM :: Set[p].insert(str(f[i] + 1));
    }
    scanf("%s", s + 1); SAM :: INIT(); n = str(s + 1);
    while ( m -- ) 
    {
        int op, l, r; scanf("%d%d%d", &op, &l, &r);
        if ( op == 1 ) 
        {
            scanf("%s", t + 1);
            int len = str(t + 1), ll = len;
            while ( ll <= N + len ) 
            { 
                REP(i, ll + 1, ll + len) t[i] = t[i - ll];
                ll += len;
            }
        
            int L = max(1, l - N), R = min(n, l + N), x = N;
            N = max(N, len); 
            REP(i, l, min(r, R)) s[i] = t[(i - l) % len + 1];
            int p = 1, Len = 0;
            REP(i, L, R)
            {
                int c = s[i] - 'a';
                while ( p && !SAM :: Tree[p].Next[c] ) { p = SAM :: Tree[p].fa; Len = SAM :: Tree[p].len; }
                if ( SAM :: Tree[p].Next[c] ) { p = SAM :: Tree[p].Next[c]; ++ Len; }
                if ( !p ) { p = 1; Len = 0; }
                if ( i >= l ) 
                {
                    num[i].clear();
                    for ( auto j : SAM :: Set[p] ) if ( j <= Len ) num[i].insert(j);
                }
            }

            L = max(1, r - N), R = min(n, r + N); p = 1; Len = 0;
            REP(i, max(l, L), r) s[i] = t[(i - l) % len + 1];
            REP(i, L, R)
            {
                int c = s[i] - 'a';
                while ( p && !SAM :: Tree[p].Next[c] ) { p = SAM :: Tree[p].fa; Len = SAM :: Tree[p].len; }
                if ( SAM :: Tree[p].Next[c] ) { p = SAM :: Tree[p].Next[c]; ++ Len; }
                if ( !p ) { p = 1; Len = 0; }
                if ( i > r ) 
                {
                    num[i].clear();
                    for ( auto j : SAM :: Set[p] ) if ( j <= Len ) num[i].insert(j);
                }
            }

            p = 1; Len = 0;
            REP(i, 1, ll)
            {
                int c = t[i] - 'a';
                while ( p && !SAM :: Tree[p].Next[c] ) { p = SAM :: Tree[p].fa; Len = SAM :: Tree[p].len; }
                if ( SAM :: Tree[p].Next[c] ) { p = SAM :: Tree[p].Next[c]; ++ Len; }
                if ( !p ) { p = 1; Len = 0; }
                if ( i > N ) 
                {
                    g[(i - 1) % len + 1].clear();
                    for ( auto j : SAM :: Set[p] ) if ( j <= Len ) g[(i - 1) % len + 1].insert(j);
                }
            }

            REP(i, l + N + 1, r)
            {
                s[i] = t[(i - l) % len + 1];
                num[i] = g[(i - l) % len + 1];
            }
            N = x;
        }
        else 
        {
            int ans = 0;
            REP(i, l, min(r, l + N)) for ( auto j : num[i] ) if ( j <= i - l + 1 ) ++ ans;
            REP(i, min(r, l + N) + 1, r) ans += num[i].size();
            printf("%d\n", ans);
        }
    }
    return 0;
}
