/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2020年07月24日 星期五 11时17分20秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define ls(x) Tree[x].lson
#define rs(x) Tree[x].rson
typedef long long LL;

const int maxn = 2000010;

struct node { int lson, rson, sum; } Tree[maxn << 2];
int n, w, q, type, Root[maxn], tot, ans;

inline int Modify(int now, int l, int r, int x)
{
    int root = ++ tot; Tree[root] = Tree[now]; ++ Tree[root].sum;
    if ( l == r ) return root; 
    int Mid = l + r >> 1;
    if ( x <= Mid ) ls(root) = Modify(ls(root), l, Mid, x);
    else rs(root) = Modify(rs(root), Mid + 1, r, x);
    return root;
}

inline int Query(int p, int q, int l, int r, int k)
{
    if ( l == r ) return l;
    int Mid = l + r >> 1;
    int sum = Tree[ls(q)].sum - Tree[ls(p)].sum;
    if ( k <= sum ) return Query(ls(p), ls(q), l, Mid, k);
    else return Query(rs(p), rs(q), Mid + 1, r, k - sum);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("A.in", "r", stdin);
    freopen("A.out", "w", stdout);
#endif
    scanf("%d%d%d%d", &n, &w, &q, &type);
    REP(i, 1, n) { int x; scanf("%d", &x); Root[i] = Modify(Root[i - 1], 0, n - 1, x); }
    while ( q -- ) 
    {
        int l, r, k; scanf("%d%d%d", &l, &r, &k);
        l ^= ans * type; r ^= ans * type; k ^= ans * type;
        ans = Query(Root[l - 1], Root[r], 0, n - 1, k);
        printf("%d\n", ans);
    }
    return 0;
}
