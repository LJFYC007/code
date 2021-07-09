/***************************************************************
	File name: P1110.cpp
	Author: ljfcnyali
	Create time: 2019年06月27日 星期四 20时42分16秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define ls(x) Tree[x].l
#define rs(x) Tree[x].r

const int maxn = 5000010;

struct node
{
    int l, r, size, val, rank;
} Tree[maxn];

int n, m, Heap[maxn][2], len[2], cnt, Min = 0x3f3f3f3f;
vector<int> a[maxn];

inline void Push_up(int root) { Tree[root].size = Tree[ls(root)].size + Tree[rs(root)].size + 1; }

inline void Merge(int &root, int a, int b)
{
    if ( !a || !b ) { root = a + b; return ; }
    if ( Tree[a].rank < Tree[b].rank ) { root = a; Merge(rs(a), rs(a), b); }
    else { root = b; Merge(ls(b), a, ls(b)); }
    Push_up(root);
}

inline void Split(int root, int &a, int &b, int val)
{
    if ( !root ) { a = b = 0; return ; }
    if ( Tree[root].val <= val ) { a = root; Split(rs(a), rs(a), b, val); }
    else { b = root; Split(ls(b), a, ls(b), val); }
    Push_up(root);
}

inline void New_Node(int val)
{
    ++ cnt; ls(cnt) = rs(cnt) = 0;
    Tree[cnt].val = val;
    Tree[cnt].size = 1;
    Tree[cnt].rank = rand();
}

inline void Update(int root, int val)
{
    int a, b, c, x; 
    Split(root, a, b, val); Split(a, a, c, val - 1);
    if ( Tree[c].size > 1 ) Min = 0;
    Merge(a, a, c); Merge(root, a, b);
    Split(root, a, b, val - 1);
    x = a;
    while ( rs(x) ) x = rs(x);
    if ( x ) Min = min(Min, abs(val - Tree[x].val));
    Merge(root, a, b);
    Split(root, a, b, val);
    x = b;
    while ( ls(x) ) x = ls(x);
    if ( x ) Min = min(Min, abs(val - Tree[x].val));
    Merge(root, a, b);
}

inline void Insert(int val, int opt)
{
    Heap[++ len[opt]][opt] = val;
    int x = len[opt];
    while ( x > 1 && Heap[x / 2][opt] > Heap[x][opt] ) { swap(Heap[x][opt], Heap[x / 2][opt]); x /= 2; }
}

inline void Delete(int opt)
{
    Heap[1][opt] = Heap[len[opt] -- ][opt];
    int x = 1, l = len[opt];
    while ( (x * 2 <= l && Heap[x][opt] > Heap[x * 2][opt]) || (x * 2 < l && Heap[x][opt] > Heap[x * 2 + 1][opt]) )
    {
        int m = x * 2;
        if ( m < l && Heap[m][opt] > Heap[m + 1][opt] ) ++ m;
        swap(Heap[x][opt], Heap[m][opt]);
        x = m;
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    int root = 0;
    REP(i, 1, n)
    {
        int x; scanf("%d", &x); a[i].push_back(x);
        New_Node(x);
        if ( i == 1 ) { Merge(root, root, cnt); continue ; }
        Insert(abs(a[i - 1][0] - x), 0);
        int b, c; Split(root, b, c, x); Merge(b, b, cnt); Merge(root, b, c);
        Update(root, x);
    }
    while ( m -- )
    {
        char s[100]; scanf("%s", s);
        if ( s[0] == 'I' ) 
        {
            int pos, val; scanf("%d%d", &pos, &val);
            if ( pos < n ) Insert(abs(a[pos][a[pos].size() - 1] - a[pos + 1][0]), 1);
            a[pos].push_back(val);
            New_Node(val);
            int b, c; Split(root, b, c, val); Merge(b, b, cnt); Merge(root, b, c);
            Update(root, val);
            if ( pos < n ) Insert(abs(a[pos][a[pos].size() - 1] - a[pos + 1][0]), 0);
            Insert(abs(a[pos][a[pos].size() - 1] - a[pos][a[pos].size() - 2]), 0);
        }
        else if ( s[0] == 'M' && s[4] == 'G' ) 
        {
            while ( Heap[1][0] == Heap[1][1] ) { Delete(0); Delete(1); }
            printf("%d\n", Heap[1][0]);
        }
        else printf("%d\n", Min);
    }
    return 0;
}
