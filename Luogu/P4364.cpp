/***************************************************************
	File name: P4364.cpp
	Author: ljfcnyali
	Create time: 2020年06月04日 星期四 08时53分58秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define lson root << 1
#define rson root << 1 | 1
typedef long long LL;

const int maxn = 5e5 + 10;

int n, d[maxn], ans[maxn], size[maxn];
struct node { int Min, lazy, num; } Tree[maxn << 2];
vector<int> Edge[maxn];
double k;

inline void PushUp(int root) 
{ 
    Tree[root].Min = min(Tree[lson].Min, Tree[rson].Min); 
    Tree[root].num = min(Tree[lson].num, Tree[rson].num);
}

inline void Build(int root, int l, int r)
{
    if ( l == r ) { Tree[root].Min = l; Tree[root].num = d[l]; return ; }
    int Mid = l + r >> 1;
    Build(lson, l, Mid); Build(rson, Mid + 1, r);
    PushUp(root);
}

inline int Query(int root, int l, int r, int k)
{
    return l;
    int Mid = l + r >> 1;
    if ( Tree[rson].Min > k ) return Query(lson, l, Mid, k);
    return Query(rson, Mid + 1, r, k);
}

inline void DFS1(int u)
{
    size[u] = 1;
    for ( auto v : Edge[u] ) { DFS1(v); size[u] += size[v]; }
}

inline void DFS(int u)
{
    for ( auto v : Edge[u] ) 
    {
        int pos = Query(1, 1, n, size[v]); 
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%lf", &n, &k);
    REP(i, 1, n) scanf("%d", &d[i]);
    REP(i, 1, n) Edge[(int)floor(i / k)].push_back(i);
    sort(d + 1, d + n + 1); reverse(d + 1, d + n + 1); Build(1, 1, n);
    DFS1(0); DFS(0);
    REP(i, 1, n) printf("%d ", ans[i]); puts("");
    return 0;
}
