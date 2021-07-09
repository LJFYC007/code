/***************************************************************
	File name: P4070.cpp
	Author: ljfcnyali
	Create time: 2019年11月24日 星期日 21时27分08秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 2e5 + 10;

struct node { map<int, int> Next; int len, fa; } Tree[maxn];
int tot = 1, last = 1, n, ans;

inline int Extand(int c)
{
    int cur = ++ tot;
    Tree[cur].len = Tree[last].len + 1;
    int p = last; last = cur;
    while ( p && !Tree[p].Next[c] ) { Tree[p].Next[c] = cur; p = Tree[p].fa; }
    if ( !p ) { Tree[cur].fa = 1; return cur; }
    int q = Tree[p].Next[c];
    if ( Tree[p].len + 1 == Tree[q].len ) { Tree[cur].fa = q; return cur; }
    int clone = ++ tot;
    Tree[clone] = Tree[q]; Tree[clone].len = Tree[p].len + 1;
    while ( p && Tree[p].Next[c] == q ) { Tree[p].Next[c] = clone; p = Tree[p].fa; }
    Tree[q].fa = Tree[cur].fa = clone;
    return cur;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld", &n);
    REP(i, 1, n) { int x; scanf("%lld", &x); x = Extand(x); ans += Tree[x].len - Tree[Tree[x].fa].len; printf("%lld\n", ans); }
    return 0;
}
