/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2020年07月13日 星期一 12时22分17秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2e6 + 10;
const int maxm = 1e5 + 10;
const int Mod = 998244353;

LL ans, n, tot = 1, last, f[maxn];
string s[maxm];
struct node { int len, fa, Next[26], val; } Tree[maxn];

inline void calc(string s)
{
    reverse(s.begin(), s.end());
    REP(i, 1, s.length() - 1)
    {
        int j = f[i - 1];
        while ( j > 0 && s[i] != s[j] ) j = f[j - 1];
        if ( s[i] == s[j] ) ++ j; f[i] = j;
    }
    reverse(s.begin(), s.end());
}

inline void Extend(int c)
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
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld", &n);
    REP(i, 1, n) { cin >> s[i]; last = 1; for ( auto j : s[i] ) Extend(j - 'a'); }
    REP(i, 1, n)
    {
        int p = 1;
        for ( auto j : s[i] ) 
        {
            p = Tree[p].Next[j - 'a'];
            ++ Tree[p].val;
        }
    }
    REP(i, 1, n)
    {
        int p = 1;
        calc(s[i]);
        for ( auto j : s[i] ) p = Tree[p].Next[j - 'a'];
        while ( p ) 
        {
            ans = (ans + (((LL)(Tree[p].len) * Tree[p].len % Mod) - (f[Tree[p].len - 1] * f[Tree[p].len - 1] % Mod)) * Tree[p].val) % Mod;
            p = Tree[p].fa;
        }
    }
    printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}
