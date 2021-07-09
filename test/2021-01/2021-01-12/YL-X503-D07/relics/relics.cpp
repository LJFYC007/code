/***************************************************************
	File name: relics.cpp
	Author: ljfcnyali
	Create time: 2021年01月12日 星期二 08时53分00秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int n, m, h[maxn], ans[maxn], Stack1[maxn], Stack2[maxn], tot1, tot2, c[maxn];
struct node 
{ 
    int l, r, id; 
    node ( int a = 0, int b = 0, int c = 0 ) { l = a; r = b; id = c; } 
} ;

inline int lowbit(int x) { return x & -x; }

inline void add(int pos, int val) { for ( int i = pos; i <= n; i += lowbit(i) ) c[i] = max(c[i], val); }

inline int get(int pos) { int sum = 0; for ( int i = pos; i > 0; i -= lowbit(i) ) sum = max(sum, c[i]); return sum; } 

inline void Calc(int l, int r, int Mid, vector<node> p)
{
    Stack1[tot1 = 1] = Mid; for ( int i = Mid - 1; i >= l; -- i ) if ( h[i] < h[Stack1[tot1]] ) Stack1[++ tot1] = i;
    Stack2[tot2 = 1] = Mid + 1; REP(i, Mid + 2, r) if ( h[i] < h[Stack2[tot2]] ) Stack2[++ tot2] = i;
    Stack2[tot2 + 1] = r + 1; int X = h[r + 1]; h[r + 1] = 0;
    sort(p.begin(), p.end(), [](node &a, node &b) { return a.l > b.l; });
    // cout << l << " " << r << endl;
    // for ( auto it : p ) printf("(%d, %d, %d), ", it.l, it.r, it.id); puts("");

    int now1 = 1, now2 = 1, now = 0, nxt = 1; mem(c); 
    while ( h[Stack2[nxt]] >= h[Stack1[now1]] && nxt <= tot2 ) ++ nxt;
    for ( int i = Mid; i >= l; -- i ) 
    {
        if ( now1 + 1 <= tot1 && i == Stack1[now1 + 1] ) 
        {
            while ( h[Stack2[now2]] >= h[Stack1[now1]] && now2 <= tot2 )
            {
                ++ now2; add(Stack2[now2] - 1, h[Stack1[now1]] * (Stack2[now2] - i - 1));
            }
            ++ now1;
            while ( h[Stack2[nxt]] >= h[Stack1[now1]] && nxt <= tot2 ) ++ nxt;
        }
        while ( now < p.size() && p[now].l == i ) 
        {
            auto it = p[now]; 
            cout << it.l << " " << it.r << " " << it.id << " " << endl;
            ans[it.id] = max(ans[it.id], get(it.r));
            ans[it.id] = max(ans[it.id], h[Stack1[now1]] * (min(it.r, Stack2[nxt] - 1) - it.l + 1));
            ++ now;    
        }
    }
    h[r + 1] = X;
}

inline void Solve(int l, int r, vector<node> p)
{
    if ( !p.size() || l > r ) return ; 
    if ( l == r ) 
    {
        for ( auto it : p ) ans[it.id] = max(ans[it.id], h[l]);
        return ;
    }
    int Mid = l + r >> 1; vector<node> A, B, C;
    for ( auto it : p ) 
    {
        if ( it.l <= Mid ) A.push_back(node(it.l, min(it.r, Mid), it.id));
        if ( Mid < it.r ) B.push_back(node(max(it.l, Mid + 1), it.r, it.id));
        if ( it.l <= Mid && Mid < it.r ) C.push_back(it);
    }
    // Solve(l, Mid, A); Solve(Mid + 1, r, B); p = C;

    Calc(l, r, Mid, p);  
    return ;
    reverse(h + l, h + r + 1); 
    for ( int i = 0; i < p.size(); ++ i ) { p[i].l = r + l - p[i].l; p[i].r = r + l - p[i].r; swap(p[i].l, p[i].r); }
    Calc(l, r, r + l - Mid - 1, p); 
    reverse(h + l, h + r + 1); 
}

int main()
{
    freopen("relics.in", "r", stdin);
    freopen("relics.out", "w", stdout);
    scanf("%d%d", &n, &m); REP(i, 1, n) scanf("%d", &h[i]);
    vector<node> Q; REP(i, 1, m) { int x, y; scanf("%d%d", &x, &y); Q.push_back(node(x, y, i)); }
    Solve(1, n, Q);
    REP(i, 1, m) printf("%d\n", ans[i]);
    return 0;
}
