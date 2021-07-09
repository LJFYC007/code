/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2020年06月18日 星期四 08时05分51秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2e5 + 10;

int n, m, f[2][2010], last = 1, tot = 1;
char s[maxn];
struct node { int Next[4], fa, len; } Tree[maxn];

inline void Extend(int c)
{
    int cur = ++ tot, p = last; last = cur; Tree[cur].len = Tree[p].len + 1;
    while ( p && !Tree[p].Next[c] ) { Tree[p].Next[c] = cur; p = Tree[p].fa; }
    if ( !p ) { Tree[cur].fa = 1; return ; }
    int q = Tree[p].Next[c];
    if ( Tree[p].len + 1 == Tree[q].len ) { Tree[cur].fa = q; return ; }
    int clone = ++ tot; Tree[clone] = Tree[q]; Tree[clone].len = Tree[p].len + 1;
    while ( p && Tree[p].Next[c] == q ) { Tree[p].Next[c] = clone; p = Tree[p].fa; }
    Tree[cur].fa = Tree[q].fa = clone;
}

namespace Subtask1
{
    const int maxn = 1e6 + 10;
    int Begin[maxn], Next[maxn], To[maxn], e, vis[4][4], ans, Root[4];

    inline void add(int u, int v) 
    { 
        if ( u == v ) ans = n;
        To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; 
    }   

    inline void DFS1(int u, int x)
    {
        vis[u][x] = true;
        for ( int i = Begin[u]; i; i = Next[i] ) 
            if ( To[i] && !vis[To[i]][x] ) DFS1(To[i], x);
    }

    inline void DFS2(int u, int x, int dep)
    {
        for ( int i = Begin[u]; i; i = Next[i] ) 
        {
            int v = To[i];
            REP(j, 0, 3) if ( v == Root[j] ) goto Next ; 
            if ( !v ) goto Next ;
            DFS2(v, x, dep + 1);
            Next : ; 
        }
        for ( int i = Begin[u]; i; i = Next[i] ) 
        {
            int v = To[i];
            REP(j, 0, 3) if ( v == Root[j] && vis[j][x] && v ) 
            {
                int len = dep;
                if ( j != x && vis[j][x] == 1 ) 
                {
                    ++ len;
                    int x = n % len; 
                    if ( x == 0 ) ans = max(ans, n / len * 2);
                    else if ( x == 1 ) ans = max(ans, n / len * 2 + 1);
                    else ans = max(ans, n / len * 2 + 2);
                }
                else if ( j == x ) 
                    ans = max(ans, 1 + (n - 1) / len);
                else { ++ len; ans = max(ans, 1 + n / len); }
            }
        }
    }

    inline int main()
    {
        scanf("%d", &n);
        scanf("%s", s + 1); m = str(s + 1);
        REP(i, 1, m) Extend(s[i] - 'A');

        REP(i, 0, 3) Root[i] = Tree[1].Next[i];
        REP(i, 1, tot) REP(j, 0, 3)
        {
            if ( Tree[i].Next[j] ) add(i, Tree[i].Next[j]);
            else add(i, Root[j]);
        }
        REP(i, 0, 3)
        {
            vis[i][i] = 1;
            REP(j, 0, 3) if ( !Tree[Root[i]].Next[j] ) vis[i][j] = 1;
            for ( int j = Begin[Root[i]]; j; j = Next[j] ) 
            {
                int v = To[j];
                REP(k, 0, 3) if ( !vis[i][k] && v == Root[k] ) vis[i][k] = 2;
            }
        }
    
        REP(i, 0, 3) DFS2(Root[i], i, 1);
        printf("%d\n", ans);
        return 0;
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("B.in", "r", stdin);
    freopen("B.out", "w", stdout);
#endif
    scanf("%d", &n);
    scanf("%s", s + 1); m = str(s + 1);
    REP(i, 1, m) Extend(s[i] - 'A');
    if ( m > 1000 ) return Subtask1 :: main();
    int now = 0;
    REP(i, 0, n - 1) 
    {
        REP(j, 1, tot) f[now ^ 1][j] = 0;
        REP(j, 1, tot) REP(c, 0, 3)
        {
            int p = j;
            if ( !Tree[p].Next[c] ) p = 1;
            if ( !Tree[p].Next[c] ) continue ;
            f[now ^ 1][Tree[p].Next[c]] = max(f[now ^ 1][Tree[p].Next[c]], f[now][j] + (p != j));
        }
        now ^= 1;
    }
    int ans = 0;
    REP(j, 1, tot) 
        ans = max(ans, f[now][j]);
    printf("%d\n", ans);
    return 0;
}
