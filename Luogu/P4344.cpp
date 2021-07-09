/***************************************************************
	File name: P4344.cpp
	Author: ljfcnyali
	Create time: 2019年10月30日 星期三 19时52分11秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

int n, m;
struct node 
{ 
    int l, r, val; 
    node(const int &L, const int &R, const int &v) { l = L; r = R; val = v; }
    bool operator < (const node &a) const { return l < a.l; } 
} ;
set<node> Set;

inline auto Split(int x)
{
    if ( x > n ) return Set.end();
    auto it = -- Set.upper_bound(node(x, 0, 0));
    if ( it -> l == x ) return it;
    int l = it -> l, r = it -> r, v = it -> val;
    Set.erase(it);
    Set.insert(node(l, x - 1, v)); Set.insert(node(x, r, v));
    return Set.lower_bound(node(x, 0, 0));
}

inline void Assign(int l, int r, int val)
{
    if ( l > r ) return ;
    auto itr = Split(r + 1), itl = Split(l);
    Set.erase(itl, itr);
    Set.insert(node(l, r, val));
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);    
    Set.insert(node(1, n, 1));
    while ( m -- ) 
    {
        int opt, l, r; scanf("%d%d%d", &opt, &l, &r);
        // for ( auto i : Set ) printf("%d %d %d\n", i.l, i.r, i.val);
        // puts("");
        if ( opt == 0 ) Assign(l, r, 0);
        else if ( opt == 1 ) 
        { 
            int sum = r - l + 1;
            auto itr = Split(r + 1), itl = Split(l);
            for ( ; itl != itr; ++ itl ) if ( !itl -> val ) sum -= itl -> r - itl -> l + 1;
            Assign(l, r, 0);
            scanf("%d%d", &l, &r);
            itr = Split(r + 1); itl = Split(l);
            for ( ; itl != itr; ++ itl ) 
            {
                if ( itl -> val ) continue ;
                int ret = itl -> r - itl -> l + 1;
                if ( ret <= sum ) { sum -= ret; continue ; }
                int L = itl -> l + sum - 1, R = itl -> r;
                Assign(l, L, 1); Assign(L + 1, R , 0); sum = -1;
                break ; 
            }
            if ( sum != -1 ) Assign(l, r, 1);
        }
        else 
        {
            auto itr = Split(r + 1), itl = Split(l);
            int ans = 0, ret = 0;
            for ( ; itl != itr; ++ itl ) 
                if ( !itl -> val ) ret += itl -> r - itl -> l + 1;
                else ans = max(ans, ret), ret = 0;
            ans = max(ans, ret);
            printf("%d\n", ans);
        }
    }
    return 0;
}
