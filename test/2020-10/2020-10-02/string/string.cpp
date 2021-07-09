/***************************************************************
	File name: string.cpp
	Author: ljfcnyali
	Create time: 2020年10月02日 星期五 08时24分22秒
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

const int maxn = 1e5 + 10;

int n, m, tot, op;
struct node { int lazy, len, sum; } Tree[26][maxn * 4];
char s[maxn];

inline void PushTag(int root, int val) { Tree[op][root].lazy = val; Tree[op][root].sum = Tree[op][root].len * val; }

inline void PushUp(int root) { Tree[op][root].sum = Tree[op][lson].sum + Tree[op][rson].sum; }

inline void PushDown(int root)
{
    if ( Tree[op][root].lazy == -1 ) return ; 
    PushTag(lson, Tree[op][root].lazy);
    PushTag(rson, Tree[op][root].lazy);
    Tree[op][root].lazy = -1;
}

inline void Modify(int root, int l, int r, int L, int R, int val)
{
    if ( L <= l && r <= R ) { PushTag(root, val); return ; }
    if ( Tree[op][root].sum == Tree[op][root].len * val ) return ;
    int Mid = l + r >> 1; PushDown(root);
    if ( L <= Mid ) Modify(lson, l, Mid, L, R, val);
    if ( Mid < R ) Modify(rson, Mid + 1, r, L, R, val);
    PushUp(root);
}

inline int Query(int root, int l, int r, int L, int R)
{
    if ( Tree[op][root].sum == 0 ) return 0;
    if ( L <= l && r <= R ) return Tree[op][root].sum;
    int Mid = l + r >> 1, ret = 0; PushDown(root);
    if ( L <= Mid ) ret += Query(lson, l, Mid, L, R);
    if ( Mid < R ) ret += Query(rson, Mid + 1, r, L, R);
    return ret;
}

inline void Build(int root, int l, int r)
{
    Tree[op][root].len = r - l + 1; Tree[op][root].lazy = -1;
    if ( l == r ) return ;
    int Mid = l + r >> 1; Build(lson, l, Mid); Build(rson, Mid + 1, r);
}

int main()
{
    freopen("string.in", "r", stdin);
    freopen("string.out", "w", stdout);
    scanf("%d%d", &n, &m);
    scanf("%s", s + 1);
    REP(i, 0, 25) { op = i; Build(1, 1, n); }
    REP(i, 1, n) { op = s[i] - 'a'; Modify(1, 1, n, i, i, 1); }
    while ( m -- ) 
    {
        int x, l, r; scanf("%d%d%d", &l, &r, &x);
        int now = l;
        if ( x == 1 ) 
        {
            REP(i, 0, 25)
            {
                op = i;
                int sum = Query(1, 1, n, l, r); if ( !sum ) continue ; 
                Modify(1, 1, n, l, r, 0); Modify(1, 1, n, now, now + sum - 1, 1); now += sum;
            }
        }
        else 
        {
            for ( int i = 25; i >= 0; -- i )
            {
                op = i;
                int sum = Query(1, 1, n, l, r); if ( !sum ) continue ; 
                Modify(1, 1, n, l, r, 0); Modify(1, 1, n, now, now + sum - 1, 1); now += sum;
            }
        }
    }
    REP(i, 1, n) 
    {
        int x = 0;
        REP(j, 1, 25) { op = j; if ( Query(1, 1, n, i, i) == 1 ) { x = j; break ; } }
        printf("%c", x + 'a');
    }
    puts("");
    return 0;
}
