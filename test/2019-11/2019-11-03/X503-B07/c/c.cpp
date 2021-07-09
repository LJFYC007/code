/***************************************************************
	File name: c.cpp
	Author: ljfcnyali
	Create time: 2019年11月03日 星期日 09时22分44秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define x first
#define y second
#define ls(x) Tree[x].lson
#define rs(x) Tree[x].rson
typedef long long LL;

const int maxn = 1000010;

int n, Root, tot, N;
struct node
{
    int lson, rson, Max;
} Tree[maxn << 2];
pii a[200010];
vector<pii> p;

inline void PushUp(int root) { Tree[root].Max = max(Tree[ls(root)].Max, Tree[rs(root)].Max); }

inline void Modify(int &root, int l, int r, int pos, int val)
{
    if ( !root ) root = ++ tot;
    if ( l == r ) { Tree[root].Max = val; return ; }
    int Mid = ((LL)(l) + r) >> 1;
    if ( pos <= Mid ) Modify(ls(root), l, Mid, pos, val);
    else Modify(rs(root), Mid + 1, r, pos, val);
    PushUp(root);
}

inline int Query(int root, int l, int r, int L, int R)
{
    if ( L <= l && r <= R ) return Tree[root].Max;
    int Mid = ((LL)(l) + r) >> 1, ret = 0;
    if ( L <= Mid ) ret = max(ret, Query(ls(root), l, Mid, L, R));
    if ( Mid < R ) ret = max(ret, Query(rs(root), Mid + 1, r, L, R));
    return ret; 
}

int main()
{
    freopen("c.in", "r", stdin);
    freopen("c.out", "w", stdout);
    scanf("%d", &n);
    REP(i, 1, n) { scanf("%d%d", &a[i].x, &a[i].y); N = max(N, a[i].y); }
    sort(a + 1, a + n + 1);
    for ( int i = 1; i <= n; ++ i )
    {
        p.clear(); int j = i;
        while ( a[j].x == a[i].x ) 
        {
            p.push_back(pii(a[j].y, Query(Root, 0, N, 0, a[j].y - 1) + 1));
            ++ j;
        }
        i = j - 1;
        for ( auto j : p ) Modify(Root, 0, N, j.first, j.second);
    }
    printf("%d\n", Tree[1].Max);
    return 0;
}
