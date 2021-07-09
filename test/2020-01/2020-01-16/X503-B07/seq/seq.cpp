/***************************************************************
	File name: seq.cpp
	Author: ljfcnyali
	Create time: 2020年01月16日 星期四 08时19分35秒
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

const int maxn = 6e5 + 10;

int n, a[maxn], Min[2][maxn][20], tot, Root;
pii p[maxn];
struct node { int son[3]; } Tree[maxn];
struct node1 
{
    int x; 
    bool operator < (const node1 b) const 
    {
        return p[x] > p[b.x];
    }
    node1 ( int X ) { x = X; }
} ;
priority_queue<node1> Q;

inline int GetMin(int opt, int L, int R)
{
    if ( opt == 1 && (L & 1) ) ++ L;
    if ( opt == 1 && (R & 1) ) ++ R;
    if ( opt == 0 && !(L & 1) ) ++ L;
    if ( opt == 0 && !(R & 1) ) ++ R;
    L /= 2; R /= 2;
    int x = log2(R - L + 1);
    return a[Min[opt][L][x]] < a[Min[opt][R - (1 << x) + 1][x]] ? Min[opt][L][x] : Min[opt][R - (1 << x) + 1][x];
}

inline int Solve(int l, int r)
{
    if ( l >= r ) return 0;
    if ( l + 1 == r )
    {
        p[++ tot] = pii(a[l], a[r]);
        return tot;
    }
    int opt = l & 1, posl = GetMin(opt, l, r), posr;
    if ( posl < r ) posr = GetMin(opt ^ 1, posl + 1, r);
    else posr = GetMin(opt ^ 1, l, posl - 1);
    if ( posl > posr ) swap(posl, posr);
    // cerr << l << " " << r << " " << opt << " " << posl << " " << posr << endl;
    int root = ++ tot; p[root] = pii(a[posl], a[posr]);  
    Tree[root].son[0] = Solve(l, posl - 1);
    Tree[root].son[1] = Solve(posl + 1, posr - 1);
    Tree[root].son[2] = Solve(posr + 1, r);
    return root;
}

int main()
{
    freopen("seq.in", "r", stdin);
    freopen("seq.out", "w", stdout);
    scanf("%d", &n);
    memset(a, 0x3f, sizeof(a));
    REP(i, 1, n) { scanf("%d", &a[i]); Min[i & 1][(i + 1) / 2][0] = i; }
    REP(i, 0, 1) REP(j, 1, 19) REP(k, 1, n / 2)
    {
        if ( a[Min[i][k][j - 1]] < a[Min[i][k + (1 << j - 1)][j - 1]] )
            Min[i][k][j] = Min[i][k][j - 1];
        else Min[i][k][j] = Min[i][k + (1 << j - 1)][j - 1];
    }
    Root = Solve(1, n); 
    Q.push(Root);
    while ( !Q.empty() )
    {
        node1 x = Q.top(); Q.pop();
        printf("%d %d ", p[x.x].first, p[x.x].second);
        REP(i, 0, 2) if ( Tree[x.x].son[i] ) Q.push(node1(Tree[x.x].son[i]));
    }
    puts("");
    return 0;
}
