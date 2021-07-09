/***************************************************************
	File name: CF674G.cpp
	Author: ljfcnyali
	Create time: 2021年01月13日 星期三 14时42分44秒
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

const int maxn = 3e5 + 10;

int n, m, p, a[maxn];
struct node { vector<pii> Set; int tag; } Tree[maxn << 2];
vector<pii> ans;

inline void PushTag(int root, int l, int r, int val)
{
    Tree[root].Set.clear(); 
    Tree[root].Set.push_back(pii(r - l + 1, val)); 
    Tree[root].tag = val;
}

inline void PushDown(int root, int l, int r)
{
    if ( !Tree[root].tag ) return ;
    int Mid = l + r >> 1;
    PushTag(lson, l, Mid, Tree[root].tag);
    PushTag(rson, Mid + 1, r, Tree[root].tag);
    Tree[root].tag = 0;
}

inline void Delete(vector<pii> &a, int x) { for ( int i = 0; i < a.size(); ++ i ) a[i].first -= x; } 

inline vector<pii> Merge(vector<pii> a, vector<pii> b)
{
    sort(a.begin(), a.end());
    for ( auto it : b ) 
    {
        for ( int i = 0; i < a.size(); ++ i ) if ( a[i].second == it.second ) { a[i].first += it.first; sort(a.begin(), a.end()); goto Next ; } 
        if ( a.size() < p ) { a.push_back(it); sort(a.begin(), a.end()); goto Next ; }
        if ( a[0].first < it.first )
        {
            int x = a[0].first; Delete(a, x);
            a[0] = pii(it.first - x, it.second);
            sort(a.begin(), a.end());
        }
        else Delete(a, it.first);
Next : ;
    }
    return a;
}

inline void Modify(int root, int l, int r, int L, int R, int val)
{
    if ( L <= l && r <= R ) { PushTag(root, l, r, val); return ; }
    int Mid = l + r >> 1; PushDown(root, l, r);     
    if ( L <= Mid ) Modify(lson, l, Mid, L, R, val);
    if ( Mid < R ) Modify(rson, Mid + 1, r, L, R, val);
    Tree[root].Set = Merge(Tree[lson].Set, Tree[rson].Set);
}

inline void Query(int root, int l, int r, int L, int R)
{
    if ( L <= l && r <= R ) { ans = Merge(ans, Tree[root].Set); return ; } 
    int Mid = l + r >> 1; PushDown(root, l, r);
    if ( L <= Mid ) Query(lson, l, Mid, L, R);
    if ( Mid < R ) Query(rson, Mid + 1, r, L, R);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d%d", &n, &m, &p); p = 100 / p;
    REP(i, 1, n) { scanf("%d", &a[i]); Modify(1, 1, n, i, i, a[i]); }
    while ( m -- )
    {
        int op, l, r, x; scanf("%d%d%d", &op, &l, &r);
        if ( op == 1 ) { scanf("%d", &x); Modify(1, 1, n, l, r, x); }
        if ( op == 2 ) 
        {
            ans.clear(); Query(1, 1, n, l, r);
            printf("%d ", ans.size()); for ( auto it : ans ) printf("%d ", it.second); puts(""); 
        }
    }
    return 0;
}
