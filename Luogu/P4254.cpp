/***************************************************************
	File name: P4254.cpp
	Author: ljfcnyali
	Create time: 2019年10月14日 星期一 21时16分45秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define lson root << 1
#define rson root << 1 | 1
#define int long long
typedef long long LL;

const int maxn = 200010;
const int N = 50000;

struct Line { double b, k; } ;
struct node { Line x; bool flag; } Tree[maxn << 2];

int n;
char s[20];

inline int f(Line x, int pos) { return x.k * pos + x.b; }

inline void Modify(int root, int l, int r, Line x)
{
    if ( !Tree[root].flag ) { Tree[root].flag = true; Tree[root].x = x; return ; }
    if ( l == r ) 
    {
        if ( f(Tree[root].x, l) < f(x, l) ) Tree[root].x = x;
        return ;
    }
    int Mid = l + r >> 1;
    if ( x.k > Tree[root].x.k ) 
        if ( f(x, Mid) > f(Tree[root].x, Mid) )
        {
            Modify(lson, l, Mid, Tree[root].x);
            Tree[root].x = x;
        }
        else Modify(rson, Mid + 1, r, x);
    if ( x.k <= Tree[root].x.k )
        if ( f(x, Mid) > f(Tree[root].x, Mid) )
        {
            Modify(rson, Mid + 1, r, Tree[root].x);
            Tree[root].x = x;
        }
        else Modify(lson, l, Mid, x);
}

inline int Query(int root, int l, int r, int pos)
{
    if ( !Tree[root].flag ) return 0;
    if ( l == r ) return f(Tree[root].x, pos);
    int Mid = l + r >> 1, ans = f(Tree[root].x, pos);
    if ( pos <= Mid ) ans = max(ans, Query(lson, l, Mid, pos));
    else ans = max(ans, Query(rson, Mid + 1, r, pos));
    return ans;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld", &n);
    REP(i, 1, n)
    {
        scanf("%s", s + 1);
        if ( s[1] == 'P' ) 
        {
            Line x; scanf("%lf%lf", &x.b, &x.k);
            x.b -= x.k;
            Modify(1, 1, N, x);
            continue ;
        }
        int x; scanf("%lld", &x);
        printf("%lld\n", Query(1, 1, N, x) / 100);
    }
    return 0;
}
