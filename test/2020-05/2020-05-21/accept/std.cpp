/***************************************************************
	File name: std.cpp
	Author: ljfcnyali
	Create time: 2020年05月21日 星期四 19时22分14秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int __int128
typedef long long LL;

const int maxn = 1e5 + 10;
const int INF = 1e18;

LL n;
long double r;

struct node 
{
    int x, y;
    node ( int a = 0, int b = 0 ) { x = a; y = b; }
} X = node(0, 1), Y = node(1, 0);

node operator + (node x, node y) { return node(x.x + y.x, x.y + y.y); }
node operator * (node x, int y) { return node(x.x * y, x.y * y); }
bool operator < (node x, node y) { return x.x * y.y < x.y * y.x; } 
bool operator > (node x, node y) { return x.x * y.y > x.y * y.x; } 
bool operator == (node x, node y) { return x.x * y.y == x.y * y.x; }

inline void print(node x) { cerr << (LL)x.x << "/" << (LL)x.y << " "; }

inline int Check(node l, node r, node now, node x)
{
    if ( x < l || x > r ) return -1;
    if ( x < now ) return 0;
    else return 1;
}

inline void Jump(node &l, node &r, node &now, int pos, node L, node R)
{
    if ( pos == 0 ) 
    {
        node x = now + l * 1;
        node New = now;
        if ( L < l || R > New ) return ;
        now = x; r = New;
    }
    else
    {
        node x = now + r * 1;
        node New = now;
        if ( L < New || R > r ) return ;
        now = x; l = New;
    }
    for ( int i = 30; i >= 0; -- i ) 
        if ( pos == 0 ) 
        {
            node x = now + l * (1 << i);
            node New = now + l * ((1 << i) - 1);
            if ( L < l || L == l || R == New || R > New ) continue ;
            int p = Check(l, New, x, L), q = Check(l, New, x, R);     
            if ( p != pos && q != pos ) continue ;
            now = x; r = New;
        }
        else
        {
            node x = now + r * (1 << i);
            node New = now + r * ((1 << i) - 1);
            if ( L < New || L == New || R == r || R > r ) continue ;
            int p = Check(New, r, x, L), q = Check(New, r, x, R);     
            if ( p != pos && q != pos ) continue ;
            now = x; l = New;
        }
}

inline LL Solve(node l, node r, node now, node L, node R) 
{
    // print(l); print(r); print(now); print(L); print(R); cerr << endl;
    if ( L == now || R == now ) return now.y / __gcd(now.x, now.y);
    int p = Check(l, r, now, L), q = Check(l, r, now, R);     
    if ( p != q ) return now.y / __gcd(now.x, now.y);
    // print(l); print(r); print(now); print(L); print(R); cerr << endl;
    // cerr << (LL) p << endl;
    Jump(l, r, now, p, L, R);
    // print(l); print(r); print(now); print(L); print(R); cerr << endl;
    return Solve(l, r, now, L, R);
}

signed main()
{
    freopen("accept.in", "r", stdin);
    freopen("accept.out", "w", stdout);
    while ( ~scanf("%lld%Lf", &n, &r) )
    {
        int num = 1; REP(i, 1, n) num *= 10; 
        node L = node(round(r * num * 10) - 5, num * 10);                
        node R = node(round(r * num * 10) + 5, num * 10);
        if ( n <= 12 ) R = node(round(r * num * 10000) + 4999, num * 10000);
        printf("%lld\n", Solve(X, Y, node(1, 1), L, R));
        // return 0;
    }
    return 0;
}

