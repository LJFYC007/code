/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2020年06月09日 星期二 08时14分57秒
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

const int maxn = 5e5 + 10;
const int INF = 0x3f3f3f3f;

int n, a[maxn], b[maxn];
vector<int> pos1[maxn], pos2[maxn];
set<int> Set1, Set2, Set3, Set4;
struct HAHA
{
    struct node { int lazy, Min; } Tree[maxn << 2];

    inline void PushUp(int root) 
    { 
        Tree[root].Min = min(Tree[lson].Min, Tree[rson].Min); 
    }

    inline void PushTag(int root, int val) 
    { 
        Tree[root].Min += val; 
        Tree[root].lazy += val; 
    }

    inline void PushDown(int root)
    {
        if ( !Tree[root].lazy ) return ;
        PushTag(lson, Tree[root].lazy);
        PushTag(rson, Tree[root].lazy);
        Tree[root].lazy = 0;
    }

    inline int Query1(int root, int l, int r, int pos)
    {
        if ( l == r ) return Tree[root].Min;
        int Mid = l + r >> 1; PushDown(root);
        if ( pos <= Mid ) return Query1(lson, l, Mid, pos);
        return Query1(rson, Mid + 1, r, pos);
    }

    inline int Query2(int root, int l, int r, int L, int R)
    {
        if ( Tree[root].Min > 0 ) return n + 1;
        if ( l == r ) return l;
        int Mid = l + r >> 1, x = n + 1; PushDown(root);
        if ( L <= Mid ) x = min(x, Query2(lson, l, Mid, L, R));
        if ( Mid < R ) x = min(x, Query2(rson, Mid + 1, r, L, R));
        return x;
    }

    inline void Modify1(int root, int l, int r, int pos, int val)
    {
        if ( l == r ) { Tree[root].Min = val; return ; }
        int Mid = l + r >> 1; PushDown(root);
        if ( pos <= Mid ) Modify1(lson, l, Mid, pos, val);
        else Modify1(rson, Mid + 1, r, pos, val);
        PushUp(root);
    }

    inline void Modify2(int root, int l, int r, int L, int R, int val)
    {
        if ( L <= l && r <= R ) { PushTag(root, val); return ; }
        int Mid = l + r >> 1; PushDown(root);
        if ( L <= Mid ) Modify2(lson, l, Mid, L, R, val);
        if ( Mid < R ) Modify2(rson, Mid + 1, r, L, R, val);
        PushUp(root);
    }
} A, B;

namespace Subtask
{
    int a[maxn];
    int main()
    {
        REP(i, 1, n) scanf("%d", &a[i]);
        REP(m, 1, n)
        {
            sort(a + 1, a + m + 1);
            int x = 0;
            REP(i, 1, m) 
            {
                if ( a[i] > x ) ++ x;
                else if ( a[i] < x ) -- x;
            }
            printf("%d\n", x);
        }   
        return 0;
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("B.in", "r", stdin);
    freopen("B.out", "w", stdout);
#endif
    scanf("%d", &n);
    // if ( n <= 3000 ) return Subtask :: main();
    REP(i, 1, n) { scanf("%d", &a[i]); b[i] = a[i]; }
    sort(b + 1, b + n + 1);
    for ( int i = n; i >= 1; -- i ) 
    {
        if ( b[i] >= 0 ) pos1[b[i]].push_back(i);
        else pos2[-b[i]].push_back(i);
    }
    REP(i, 1, n * 4) A.Tree[i].Min = B.Tree[i].Min = INF;
    Set1.insert(0); Set2.insert(0); Set3.insert(n + 1); Set4.insert(n + 1);
    REP(i, 1, n)
    {
        if ( a[i] >= 0 ) 
        {
            int lst = 0, x = pos1[a[i]].back(), t = *(-- Set1.upper_bound(x)); 
            pos1[a[i]].pop_back();
            if ( t > 0 ) lst = b[t] - A.Query1(1, 1, n, t);
            if ( t == 0 ) 
            {
                t = *(-- Set2.end());
                if ( t > 0 ) lst = B.Query1(1, 1, n, t) + b[t];
            }
            A.Modify1(1, 1, n, x, a[i] - lst);
            Set1.insert(x); Set3.insert(x);
            if ( lst < a[i] ) 
            {
                int R = A.Query2(1, 1, n, x, n);
                Set3.erase(x); Set3.insert(R);
                A.Modify2(1, 1, n, x, R - 1, -1);
            }
        }
        else
        {
            int lst = 0, x = pos2[-a[i]].back(), t = *(-- Set2.upper_bound(x));
            pos2[-a[i]].pop_back();
            if ( t > 0 ) lst = B.Query1(1, 1, n, t) + b[t];
            B.Modify1(1, 1, n, x, lst - a[i]);
            Set2.insert(x); Set4.insert(x);
            printf("%d ",lst);
            if ( lst > a[i] ) 
            {
                Set4.erase(x); int R = *Set4.upper_bound(x);
                B.Modify2(1, 1, n, x, R - 1, -1);
                printf("%d ", R);
                if ( R <= n ) Set4.erase(R);
                if ( R > n ) 
                {
                    R = *Set3.begin(); 
                    if ( R <= n ) Set3.erase(R);
                    A.Modify2(1, 1, n, 1, R - 1, 1);
                }
            }
            else if ( lst < a[i] ) 
            { 
                int R = A.Query2(1, 1, n, 1, n); Set4.erase(R);
                B.Modify2(1, 1, n, x, n, 1); 
                Set3.insert(R); A.Modify2(1, 1, n, 1, R - 1, -1); 
            }
        }
        int t = *(-- Set1.end());
        if ( !t ) 
        {
            t = *(-- Set2.end());
            printf("%d\n", B.Query1(1, 1, n, t) + b[t]);
        }
        else printf("%d\n", b[t] - A.Query1(1, 1, n, t));
    }
    return 0;
}
