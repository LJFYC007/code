/***************************************************************
	File name: P1552.cpp
	Author: ljfcnyali
	Create time: 2019年07月05日 星期五 08时49分53秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define ls(x) Tree[x].l
#define rs(x) Tree[x].r
typedef long long LL;

const int maxn = 100010;

struct node
{
    LL l, r, val, dis;
} Tree[maxn];

LL n, m, l[maxn], ans, Root[maxn], sum[maxn], cnt[maxn];
vector<LL> son[maxn];

inline int Merge(int x, int y)
{
    if ( !x || !y ) return x + y;
    if ( Tree[x].val < Tree[y].val ) swap(x, y);
    rs(x) = Merge(rs(x), y);
    if ( Tree[ls(x)].dis < Tree[rs(x)].dis ) swap(ls(x), rs(x));
    Tree[x].dis = Tree[rs(x)].dis + 1;
    return x;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    Tree[0].dis = -1;
    REP(i, 1, n)
    {
        int x; scanf("%d%lld%lld", &x, &sum[i], &l[i]);
        Root[i] = i;
        Tree[i].val = sum[i]; 
        cnt[i] = 1;
        son[x].push_back(i);
        Tree[i].dis = ls(i) = rs(i) = 0;
    }
    for ( int i = n; i >= 1; -- i )
    {
        REP(j, 0, son[i].size() - 1)
        {
            Root[i] = Merge(Root[i], Root[son[i][j]]);
            sum[i] += sum[son[i][j]]; cnt[i] += cnt[son[i][j]];
        }
        while ( sum[i] > m )
        {
            sum[i] -= Tree[Root[i]].val; -- cnt[i];
            Root[i] = Merge(ls(Root[i]), rs(Root[i]));
        }
        ans = max(ans, cnt[i] * l[i]);
    }
    printf("%lld\n", ans);
    return 0;
}
