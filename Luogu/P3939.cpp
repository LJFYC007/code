// luogu-judger-enable-o10
/***************************************************************
	File name: P3939.cpp
	Author: ljfcnyali
	Create time: 2019年06月30日 星期日 19时18分49秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 20000010;

struct node
{
    int lson, rson, sum;
} Tree[maxn];

int n, m, a[300010], Root[maxn], tot;

inline int Update(int root, int l, int r, int x, int val)
{
    if ( !root ) root = ++ tot;
    Tree[root].sum += val;
    if ( l == r ) return root;
    int Mid = l + r >> 1;
    if ( x <= Mid ) Tree[root].lson = Update(Tree[root].lson, l, Mid, x, val);
    else Tree[root].rson = Update(Tree[root].rson, Mid + 1, r, x, val);
    return root;
}

inline int Query(int root, int l, int r, int L, int R)
{
    if ( L <= l && r <= R ) return Tree[root].sum;
    int Mid = l + r >> 1, sum = 0;
    if ( L <= Mid ) sum += Query(Tree[root].lson, l, Mid, L, R);
    if ( Mid < R ) sum += Query(Tree[root].rson, Mid + 1, r, L, R);
    return sum;
}

inline void read(int &x)
{
    char c = getchar(); x = 0;
    while ( c < '0' || c > '9' ) c = getchar();
    while ( c >= '0' && c <= '9' ) { x = x * 10 + c - '0'; c = getchar(); }
}

/*inline void Update(int root, int l, int r, int x, int val)
{
    if ( l == r ) { Tree[root].sum += val; return ; }
    int Mid = l + r >> 1;
    if ( x <= Mid ) Update(Tree[root].lson, l, Mid, x, val);
    else Update(Tree[root].rson, Mid + 1, r, x, val);
    Tree[root].sum = Tree[Tree[root].lson].sum + Tree[Tree[root].rson].sum;
}*/

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    read(n); read(m);
    REP(i, 1, n) { read(a[i]); Root[a[i]] = Update(Root[a[i]], 1, n, i, 1); }
    int opt, l, r, c, x;
    REP(i, 1, m)
    {
        read(opt);
        if ( opt == 1 )
        {
            read(l); read(r); read(c);
            printf("%d\n", Query(Root[c], 1, n, l, r));
        }
        else
        {
            read(x);
            Update(Root[a[x]], 1, n, x, -1);
            Update(Root[a[x]], 1, n, x + 1, 1);
            Update(Root[a[x + 1]], 1, n, x, 1);
            Update(Root[a[x + 1]], 1, n, x + 1, -1);
            swap(a[x], a[x + 1]);
        }
    }
    return 0;
}
