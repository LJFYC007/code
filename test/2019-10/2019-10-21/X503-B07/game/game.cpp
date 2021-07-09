/***************************************************************
	File name: game.cpp
	Author: ljfcnyali
	Create time: 2019年10月21日 星期一 14时23分14秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
#define lson root << 1
#define rson root << 1 | 1
#define pii pair<int, int>
typedef long long LL;

const int maxn = 100010;
const int N = 100000;

int n, a[maxn], b[maxn], sum;
struct node { int sum, a, b; } Tree[maxn << 2];
multiset<int> Set;

inline void PushUp(int root) 
{ 
    int x = min(Tree[lson].a, Tree[rson].b);
    Tree[root].a = Tree[lson].a + Tree[rson].a - x;
    Tree[root].b = Tree[lson].b + Tree[rson].b - x;
    Tree[root].sum = Tree[lson].sum + Tree[rson].sum + x; 
}

inline void Modify(int root, int l, int r, int pos, int val, int opt)
{
    if ( l == r )
    {
        if ( opt == 0 ) Tree[root].a += val;
        else Tree[root].b += val;
        return ;
    }
    int Mid = l + r >> 1;
    if ( pos <= Mid ) Modify(lson, l, Mid, pos, val, opt);
    else Modify(rson, Mid + 1, r, pos, val, opt);
    PushUp(root);
}

signed main()
{
    freopen("game.in", "r", stdin);
    freopen("game.out", "w", stdout);
    scanf("%lld", &n);
    REP(i, 1, n) scanf("%lld", &a[i]);
    REP(i, 1, n) { scanf("%lld", &b[i]); Set.insert(b[i]); }
    REP(i, 1, n)
    {
        Modify(1, 1, N, a[i], 1, 0);
        Modify(1, 1, N, b[i], 1, 1);
    }
    sum = Tree[1].sum;
    REP(i, 1, n)
    {
        Modify(1, 1, N, a[i], -1, 0);
        auto it = -- Set.end();
        int L = a[i] + 1, R = *it, x = -1;
        while ( L <= R ) 
        {
            int Mid = L + R >> 1;
            Modify(1, 1, N, Mid, -1, 1);
            if ( Tree[1].sum == sum - 1 ) { x = Mid; L = Mid + 1; }
            else R = Mid - 1;
            Modify(1, 1, N, Mid, 1, 1);
        }
        if ( x == -1 )
        {
            L = 1; R = a[i];
            while ( L <= R )
            {
                int Mid = L + R >> 1;
                Modify(1, 1, N, Mid, -1, 1);
                if ( Tree[1].sum == sum ) { x = Mid; L = Mid + 1; }
                else R = Mid - 1;
                Modify(1, 1, N, Mid, 1, 1);
            }
        }
        else -- sum;
        Modify(1, 1, N, x, -1, 1);
        Set.erase(Set.lower_bound(x));
        printf("%lld ", x);
    }
    puts("");
    return 0;
}
