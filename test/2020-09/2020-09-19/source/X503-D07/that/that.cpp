/***************************************************************
	File name: that.cpp
	Author: ljfcnyali
	Create time: 2020年09月19日 星期六 11时51分31秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 4e4 + 10;

char s[maxn];
struct node { int Next[26], len, fa; } Tree[maxn];
int T, tot, last, n, m, k, Begin[maxn], Next[maxn], To[maxn], e, a[maxn], b[maxn], MinLen;
set<int> Set[maxn];
string ans;

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void Extand(int c, int pos)
{
    int cur = ++ tot, p = last; Tree[cur].len = Tree[last].len + 1; last = cur;
    Set[cur].insert(pos);
    while ( p && !Tree[p].Next[c] ) { Tree[p].Next[c] = cur; p = Tree[p].fa; }
    if ( !p ) { Tree[cur].fa = 1; return ; }
    int q = Tree[p].Next[c];
    if ( Tree[p].len + 1 == Tree[q].len ) { Tree[cur].fa = q; return ; }
    int clone = ++ tot; Tree[clone] = Tree[q]; Tree[clone].len = Tree[p].len + 1; 
    while ( p && Tree[p].Next[c] == q ) { Tree[p].Next[c] = clone; p = Tree[p].fa; }
    Tree[q].fa = Tree[cur].fa = clone;
}

inline int Check(int x)
{
    int pos = upper_bound(a + 1, a + m + 1, x) - a - 1;
    return b[pos] + (m - pos) * x;
}

inline void DFS(int u)
{
    for ( int i = Begin[u]; i; i = Next[i] )
    {
        int v = To[i]; DFS(v);
        if ( Set[v].size() > Set[u].size() ) swap(Set[u], Set[v]);
        for ( auto j : Set[v] ) Set[u].insert(j);
    }
    m = 0;
    auto it = Set[u].begin();
    while ( it != Set[u].end() ) 
    {
        ++ m; 
        if ( m == 1 ) a[m] = *it;
        else { auto x = it; -- x; a[m] = *it - *x; }
        ++ it;
    }
    sort(a + 1, a + m + 1);
    REP(i, 1, m) b[i] = b[i - 1] + a[i];
    int l = Tree[Tree[u].fa].len + 1, r = Tree[u].len, len = -1; 
    while ( l <= r ) 
    {
        int Mid = l + r >> 1;
        if ( Check(Mid) <= k ) { len = Mid; l = Mid + 1; }
        else r = Mid - 1;
    }
    if ( len != -1 && Check(len) == k ) 
    {
        if ( len < MinLen ) 
        {
            MinLen = len; 
            ans = ""; 
            int x = *Set[u].begin();
            for ( int i = x; i >= x - len + 1; -- i ) ans = ans + s[i];
        }
        else if ( len == MinLen ) 
        {
            int x = *Set[u].begin(), j = 0;
            for ( int i = x; i >= x - len + 1; -- i, ++ j )
            {
                if ( s[i] > ans[j] ) return ;
                if ( s[i] < ans[j] ) 
                {
                    for ( int o = i; o >= x - len + 1; -- o ) ans[j ++] = s[o];
                    return ;
                }
            }
        }
    }
}

int main()
{
    freopen("that.in", "r", stdin);
    freopen("that.out", "w", stdout);
    scanf("%d", &T);
    while ( T -- ) 
    {
        REP(i, 1, tot) Set[i].clear();
        tot = last = 1; mem(Tree); mem(Begin); e = 0;
        MinLen = 100000; 
        scanf("%s", s + 1); n = str(s + 1); scanf("%d", &k);
        reverse(s + 1, s + n + 1);
        REP(i, 1, n) Extand(s[i] - 'a', i);
        REP(i, 2, tot) add(Tree[i].fa, i);
        DFS(1);
        if ( MinLen == 100000 ) cout << "NOTFOUND!" << endl;
        else cout << ans << endl;
    }
    return 0;
}
