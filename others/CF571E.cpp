/***************************************************************
	File name: CF571E.cpp
	Author: ljfcnyali
	Create time: 2021年01月13日 星期三 21时26分48秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 110;
const int Mod = 1e9 + 7;

int n, a[maxn], b[maxn];
struct node 
{ 
    int x, a, b; 
    node ( int A = 0, int B = 0, int C = 0 ) { x = A; a = B; b = C; } 
    bool operator < (const node &p) const { return x < p.x || (x == p.x && a < p.a); }
} ;

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline node Get(int i, int a, int b)
{
    int num1 = 0; while ( a % i == 0 ) { ++ num1; a /= i; }
    int num2 = 0; while ( b % i == 0 ) { ++ num2; b /= i; }
    return node(i, num1, num2);
}

inline set<node> calc(int a, int b)
{
    set<node> Set; Set.clear();
    int x = a;
    for ( int i = 2; i * i <= x; ++ i ) if ( x % i == 0 ) 
    {
        Set.insert(Get(i, a, b));
        while ( x % i == 0 ) x /= i;
    }
    if ( x > 1 ) Set.insert(Get(x, a, b));
    x = b;
    for ( int i = 2; i * i <= x; ++ i ) if ( x % i == 0 ) 
    {
        Set.insert(Get(i, a, b));
        while ( x % i == 0 ) x /= i;
    }
    if ( x > 1 ) Set.insert(Get(x, a, b));
    return Set;
}

inline void exgcd(int a, int b, int &x, int &y)
{
    if ( !b ) { x = 1; y = 0; return ; } 
    exgcd(b, a % b, x, y); int t = x; x = y; y = t - a / b * y;
}

inline void Modify(set<node> &a, int x, int y)
{
    set<node> b; 
    for ( auto it : a ) b.insert(node(it.x, it.a + x * it.b, it.b * y));
    a = b;
}

inline set<node> Merge(set<node> a, set<node> b)
{
    set<node> t;  
    for ( auto it : a ) if ( (*b.lower_bound(node(it.x, -1, -1))).x != it.x ) b.insert(node(it.x, 0, 0));
    for ( auto it : b ) if ( (*a.lower_bound(node(it.x, -1, -1))).x != it.x ) a.insert(node(it.x, 0, 0));
    bool flag = false;
    while ( !a.empty() || !b.empty() ) 
    {
        node x = *a.begin(), y = *b.begin(); a.erase(a.begin()); b.erase(b.begin());    
        if ( x.a == y.a && x.b == y.b ) { t.insert(x); continue ; } 
        if ( !x.b && !y.b ) { puts("-1"); exit(0); }
        if ( flag ) 
        {
            int A = y.a - x.a, B = x.b - y.b;
            if ( !B ) 
            {
                if ( A ) { puts("-1"); exit(0); }
                t.insert(x); Modify(t, 0, 0); Modify(a, 0, 0); Modify(b, 0, 0); continue ; 
            }
            if ( A % B != 0 || (A / B) < 0 ) { puts("-1"); exit(0); }
            t.insert(x); Modify(t, A / B, 0); Modify(a, A / B, 0); Modify(b, A / B, 0);
            continue ; 
        }

        int A = x.b, B = -y.b, C = y.a - x.a, X, Y, d = __gcd(A, B); 
        if ( C % d != 0 ) { puts("-1"); exit(0); }
        A /= d; B /= d; C /= d; 
        exgcd(A, B, X, Y); X *= C; Y *= C;
        if ( B ) 
        { 
            if ( B > 0 ) X = (X % B + B) % B;
            else X = (X % (-B) - B) % (-B);
            Y = (C - A * X) / B;
        }
        else if ( X < 0 ) { puts("-1"); exit(0); } 
        if ( Y < 0 ) 
        {
            if ( !A ) { puts("-1"); exit(0); }
            if ( A > 0 ) Y = (Y % A + A) % A;
            else Y = (Y % (-A) - A) % (-A);
            X = (C - B * Y) / A;
        }
        int t1 = y.b / __gcd(x.b, y.b), t2 = x.b / __gcd(x.b, y.b);
        t.insert(x); Modify(t, X, t1); Modify(a, X, t1); Modify(b, Y, t2);
        flag = true;
    }
    return t;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld", &n);
    REP(i, 1, n) scanf("%lld%lld", &a[i], &b[i]);
    set<node> ans = calc(a[1], b[1]);      
    REP(i, 2, n) ans = Merge(ans, calc(a[i], b[i]));
    int ret = 1;
    for ( auto it : ans ) ret = ret * power(it.x, it.a) % Mod;
    printf("%lld\n", (ret + Mod) % Mod);
    return 0;
}
