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
#define Done puts("Impossible!"), exit(0);
#define lson root << 1
#define rson root << 1 | 1
typedef long long LL;
  
const int maxn = 5010;
  
int n, a[maxn][maxn], ans[maxn][maxn], f[maxn], g[maxn];
vector<int> b[maxn];
struct node { int Max, lazy; } Tree[maxn << 2];
  
inline void PushTag(int root, int val) { Tree[root].Max += val; Tree[root].lazy += val; } 
  
inline void PushDown(int root)
{
    if ( !Tree[root].lazy ) return ;
    PushTag(lson, Tree[root].lazy);
    PushTag(rson, Tree[root].lazy);
    Tree[root].lazy = 0;
}
  
inline void Modify(int root, int l, int r, int L, int R, int val)
{
    if ( L <= l && r <= R ) { PushTag(root, val); return ; } 
    int Mid = l + r >> 1; // PushDown(root);
    if ( L <= Mid ) Modify(lson, l, Mid, L, R, val);
    if ( Mid < R ) Modify(rson, Mid + 1, r, L, R, val);
    Tree[root].Max = max(Tree[lson].Max, Tree[rson].Max) + Tree[root].lazy;
}
  
inline bool Query(int root, int l, int r, int pos, int val)
{
    if ( l == r ) return Tree[root].Max >= val;
    int Mid = l + r >> 1; val -= Tree[root].lazy;
    if ( Tree[lson].Max >= val ) return Query(lson, l, Mid, pos, val);    
    return Mid + 1 > pos ? false : Query(rson, Mid + 1, r, pos, val);
}
  
inline void Extend(int x, int n, int val)
{
    Modify(1, 1, n, x, x, x - 1);
    int sum = 0, m = b[n - 1 - x].size();
    for ( int i = m - 1; i >= 0; -- i )
    {
        int l = b[n - 1 - x][i], r = i == 0 ? n - 1 - x : b[n - 1 - x][i - 1] + 1;
        l -= n - 1 - x; r -= n - 1 - x;
        ++ sum; Modify(1, 1, n, r, l, sum);
    }
}
  
inline void Solve(int n)
{
    if ( n == 1 ) return ; 
    vector<int> p; REP(i, 1, n) if ( a[n][i] == 0 ) p.push_back(i);
    if ( !p.size() ) Done;  
    REP(i, 1, p[0] - 1) ans[n][i] = 3; REP(i, p.back() + 1, n) ans[n][i] = 1;       
  
    int now = 1; REP(i, 1, n * 4) Tree[i].Max = Tree[i].lazy = 0;
    for ( int o = 0; o + 1 < p.size(); ++ o ) 
    {
        int x = p[o], y = p[o + 1], pos = x;
        while ( now <= y - 1 ) 
        { 
            Extend(now, n, 1); 
            if ( Query(1, 1, n, x, now) ) pos = max(pos, now + 1);
            ++ now;
        } 
        if ( pos >= y ) Done;
        ans[n - 1][pos] = 2; a[n - 1][pos] = 0; b[n - 1 - pos].push_back(n - 1);
        Modify(1, 1, n, 1, pos, 1);
        REP(j, x + 1, pos) ans[n][j] = 1; REP(j, pos + 1, y - 1) ans[n][j] = 3;
    }
    REP(i, 0, n - 2) if ( b[i].size() && b[i].back() == n - 1 ) b[i].pop_back();
    Solve(n - 1);
}
  
inline void read(int &x)
{
    char c = getchar(); x = 0;
    while ( c < '0' || c > '9' ) c = getchar();
    x = c - '0';
}
  
int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &n);
    REP(i, 1, n) REP(j, 1, i) read(a[i][j]); 
    REP(i, 1, n - 1) REP(j, 1, i) if ( a[i][j] == 0 ) b[i - j].push_back(i);
    Solve(n);
    REP(i, 1, n) 
    {
        REP(j, 1, i) 
        {
            if ( ans[i][j] == 0 ) putchar('-');
            if ( ans[i][j] == 1 ) putchar('1');
            if ( ans[i][j] == 2 ) putchar('2');
            if ( ans[i][j] == 3 ) putchar('3');
        }
        puts("");
    }
    return 0;
}
