/***************************************************************
	File name: CF70D.cpp
	Author: ljfcnyali
	Create time: 2020年07月16日 星期四 20时00分33秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
#define pii pair<int, int>
#define x first
#define y second
typedef long long LL;

const int maxn = 1e5 + 10;
const double eps = 1e-12;

inline int cross(pii a, pii b) { return a.x * b.y - a.y * b.x; }
struct cmp 
{ 
    bool operator () (pii a, pii b) 
    { 
        double x = atan2(a.y, a.x);
        double y = atan2(b.y, b.x);
        if ( x - eps <= y && y <= x + eps ) return abs(a.x) < abs(b.x);
        return x < y;
    } 
} ;

int q;
set<pii, cmp> Set;
pii O;

inline pii Get(pii a, pii b) { return pii(b.x - a.x, b.y - a.y); }

inline bool Check(pii x, pii a, pii b) 
{ 
    return cross(a, x) >= 0 && cross(x, b) >= 0 && cross(Get(a, b), Get(a, x)) >= 0; 
}

inline auto Pre(auto it) { return it == Set.begin() ? -- Set.end() : -- it; }
inline auto Suf(auto it) { return it == Set.end() ? Set.begin() : it; }

pii a[4];

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld", &q);
    REP(i, 1, 3)
    {
        int t; pii x; scanf("%lld%lld%lld", &t, &x.x, &x.y);
        x.x *= 2; x.y *= 2; a[i] = x;
    }
    q -= 3;
    while ( 1 ) 
    {
        int 
    }
    REP(i, 1, 3) Set.insert(Get(O, a[i]));
    printf("%lld %lld\n", O.x, O.y);
    while ( q -- ) 
    {
        int t; pii x; scanf("%lld%lld%lld", &t, &x.x, &x.y);
        x.x *= 2; x.y *= 2; x = Get(O, x);
        auto it = Set.lower_bound(x);

        if ( t == 1 ) 
        {
            if ( Set.size() <= 2 ) { Set.insert(x); continue ; }
            auto a = Pre(it), b = it;
            while ( 1 ) 
            {
                b = Pre(a);
                if ( cross(Get(x, *a), Get(x, *b)) > 0 ) Set.erase(a);
                else break ;
                a = b;
            }

            a = Suf(it);
            while ( 1 )
            {
                b = a; ++ b; b = Suf(b);
                if ( cross(Get(x, *a), Get(x, *b)) < 0 ) Set.erase(a);
                else break ; 
                a = b;
            }

            a = Pre(it); b = Suf(it);
            if( !Check(x, *a, *b) ) Set.insert(x);
        }
        else
        {
            auto a = Pre(it), b = Suf(it);
            if ( Check(x, *a, *b) ) puts("YES");
            else puts("NO");
        }
    }
    return 0;
}
