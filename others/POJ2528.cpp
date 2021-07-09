#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset ( (a), 0, sizeof ( a ) )
#define str(a) strlen ( a ) 
typedef long long LL;
template<class T> int maxx(T a, T b) { return a > b ? a : b; }
template<class T> int minn(T a, T b) { return a < b ? a : b; }
template<class T> int abss(T a) { return a > 0 ? a : -a; }
#define max maxx
#define min minn
#define abs abss
#define lson root << 1
#define rson root << 1 | 1

const int maxn = 10000010;

struct node
{
    int l, r, color, lazy;
} Tree[maxn * 4];

int n;
bool vis[maxn];

inline void Build(int root, int l, int r)
{
    Tree[root].l = l; Tree[root].r = r; Tree[root].lazy = 0;
    if ( l == r ) 
    {
        Tree[root].color = 0; 
        return ;
    }
    int Mid = (l + r) >> 1;
    Build(lson, l, Mid);
    Build(rson, Mid + 1, r);
}

inline void add(int root, int l, int r, int L, int R, int x)
{
    if ( L <= l && r <= R ) 
    {
        Tree[root].lazy = x;
        return ;
    }
    int Mid = (l + r) >> 1;
    if ( Mid <= R ) add(lson, l, Mid, L, R, x);
    if ( Mid >= L ) add(rson, Mid + 1, r, L, R, x);
}

inline void solve(int root, int l, int r) 
{
    vis[Tree[root].lazy] = true;
    int Mid = (l + r) >> 1;
    solve(lson, l, Mid);
    solve(rson, Mid + 1, r);
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int T; scanf("%d", &T);
    while ( T -- )
    {
        scanf("%d", &n);
        mem(Tree); mem(vis);
        Build(1, 1, 10000000);
        REP(i, 1, n)
        {
            int L, R;
            scanf("%d%d", &L, &R);
            add(1, 1, n, L, R, i);
        }
        solve(1, 1, n);
        int ans = 0;
        REP(i, 1, n) if ( vis[i] ) ++ ans;
        printf("%d\n", ans);
    } 
    return 0;
}
