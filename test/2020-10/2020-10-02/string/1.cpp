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
#define ls(x) Tree[x].lson
#define rs(x) Tree[x].rson
typedef long long LL;

const int maxn = 1e5 + 10;

int n, m, Root[26], tot;
struct node { int lson, rson, lazy, sum; } Tree[maxn * 26 * 4];
char s[maxn];

inline void PushTag(int root, int l, int r, int val)
{
    Tree[root].lazy = val; Tree[root].sum = (r - l + 1) * val;
}

inline void PushUp(int root) { Tree[root].sum = Tree[ls(root)].sum + Tree[rs(root)].sum; }

inline void PushDown(int root, int l, int r)
{
    if ( Tree[root].lazy == -1 ) return ; 
    int Mid = l + r >> 1;
    if ( !ls(root) ) ls(root) = ++ tot; PushTag(ls(root), l, Mid, Tree[root].lazy);
    if ( !rs(root) ) rs(root) = ++ tot; PushTag(rs(root), Mid + 1, r, Tree[root].lazy);
    Tree[root].lazy = -1;
}

inline void Modify(int &root, int l, int r, int L, int R, int val)
{
    if ( !root ) root = ++ tot;
    if ( L <= l && r <= R ) { PushTag(root, l, r, val); return ; }
    int Mid = l + r >> 1; PushDown(root, l, r);
    if ( L <= Mid ) Modify(ls(root), l, Mid, L, R, val);
    if ( Mid < R ) Modify(rs(root), Mid + 1, r, L, R, val);
    PushUp(root);
}

inline int Query(int root, int l, int r, int L, int R)
{
    if ( !root ) return 0;
    if ( L <= l && r <= R ) return Tree[root].sum;
    int Mid = l + r >> 1, ret = 0; PushDown(root, l, r);
    if ( L <= Mid ) ret += Query(ls(root), l, Mid, L, R);
    if ( Mid < R ) ret += Query(rs(root), Mid + 1, r, L, R);
    return ret;
}

int main()
{
    freopen("string.in", "r", stdin);
    freopen("string.out", "w", stdout);
    scanf("%d%d", &n, &m);
    scanf("%s", s + 1);
    REP(i, 1, n) Modify(Root[s[i] - 'a'], 1, n, i, i, 1);
    while ( m -- ) 
    {
        int x, l, r; scanf("%d%d%d", &l, &r, &x);
        int now = l;
        if ( x == 1 ) 
        {
            REP(i, 0, 25)
            {
                int sum = Query(Root[i], 1, n, l, r); Modify(Root[i], 1, n, l, r, 0);
                Modify(Root[i], 1, n, now, now + sum - 1, 1); now += sum;
            }
        }
        else 
        {
            for ( int i = 25; i >= 0; -- i )
            {
                int sum = Query(Root[i], 1, n, l, r); Modify(Root[i], 1, n, l, r, 0);
                Modify(Root[i], 1, n, now, now + sum - 1, 1); now += sum;
            }
        }
    }
    REP(i, 1, n) 
    {
        int x = 0;
        REP(j, 1, 25) if ( Query(Root[j], 1, n, i, i) == 1 ) x = j;
        printf("%c", x + 'a');
    }
    puts("");
    return 0;
}
