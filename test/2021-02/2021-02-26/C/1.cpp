/***************************************************************
    File name: C.cpp
    Author: ljfcnyali
    Create time: 2021年02月26日 星期五 16时14分43秒
***************************************************************/
#include<bits/stdc++.h>
 
using namespace std;
 
#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define lson root << 1
#define rson root << 1 | 1
#define Done puts("Impossible!"), exit(0);
typedef long long LL;
 
const int maxn = 5010;
 
int n, a[maxn][maxn], ans[maxn][maxn], f[maxn], g[maxn];
vector<int> b[maxn];
struct node { int Max, lazy; } Tree[maxn << 2];
 
inline void PushTag(int root, int val) { Tree[root].Max += val; Tree[root].lazy += val; } 
 
inline void PushDown(int root)
{
    if ( !Tree[root].lazy ) return ;
    PushTag(lson, Tree[root].lazy); PushTag(rson, Tree[root].lazy);
    Tree[root].lazy = 0;
}
 
inline void Modify(int root, int l, int r, int L, int R, int val)
{
    if ( L <= l && r <= R ) { PushTag(root, val); return ; } 
    int Mid = l + r >> 1; PushDown(root);
    if ( L <= Mid ) Modify(lson, l, Mid, L, R, val);
    if ( Mid < R ) Modify(rson, Mid + 1, r, L, R, val);
    Tree[root].Max = max(Tree[lson].Max, Tree[rson].Max);
}
 
inline int Query(int root, int l, int r, int pos)
{
    if ( l == r ) return Tree[root].Max;
    int Mid = l + r >> 1; PushDown(root);
    if ( pos <= Mid ) return Query(lson, l, Mid, pos);
    return Query(rson, Mid + 1, r, pos);
}
 
inline void Extend(int x, int n, int val)
{
    g[x] = x - 1; int sum = 0, m = b[n - 1 - x].size();
    for ( int i = m - 1; i >= 0; -- i )
    {
        int l = b[n - 1 - x][i], r = i == 0 ? n - 1 - x : b[n - 1 - x][i - 1] + 1;
        l -= n - 1 - x; r -= n - 1 - x;
        ++ sum; REP(j, r, l) g[j] += sum * val;
    }
}
 
inline int ask(int pos)
{
    REP(i, 1, pos) if ( Query(1, 1, n, i == pos ) return i;
    return pos + 1;
}
 
inline void Solve(int n)
{
    if ( n == 1 ) return ; 
    vector<int> p; REP(i, 1, n) if ( a[n][i] == 0 ) p.push_back(i);
    if ( !p.size() ) Done;  
    REP(i, 1, p[0] - 1) ans[n][i] = 3; REP(i, p.back() + 1, n) ans[n][i] = 1;       
 
    int now = 1;
    for ( int o = 0; o + 1 < p.size(); ++ o ) 
    {
        int x = p[o], y = p[o + 1], pos = x;
        while ( now <= y - 1 ) 
        { 
            Extend(now, n, 1); 
            if ( ask(now) <= x ) pos = max(pos, now + 1);
            ++ now; 
        } 
        if ( pos >= y ) Done;
        while ( now > pos ) { Extend(now - 1, n, -1); -- now; } 
        ans[n - 1][pos] = 2; a[n - 1][pos] = 0; b[n - 1 - pos].push_back(n - 1);
        while ( now <= y - 1 ) { Extend(now, n, 1); ++ now; } 
        REP(j, x + 1, pos) ans[n][j] = 1; REP(j, pos + 1, y - 1) ans[n][j] = 3;
    }
    REP(i, 0, n - 2) if ( b[i].size() && b[i].back() == n - 1 ) b[i].pop_back();
    Solve(n - 1);
}
 
int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &n);
    REP(i, 1, n) REP(j, 1, i) scanf("%1d", &a[i][j]);
    REP(i, 1, n - 1) REP(j, 1, i) if ( a[i][j] == 0 ) b[i - j].push_back(i);
    Solve(n);
//  puts("Yes"); return 0; 
    REP(i, 1, n) 
    {
        REP(j, 1, i) 
        {
            if ( ans[i][j] == 0 ) printf("-");
            else printf("%d", ans[i][j]);
        }
        puts("");
    }
    return 0;
}
