/***************************************************************
	File name: game.cpp
	Author: ljfcnyali
	Create time: 2020年04月22日 星期三 19时40分48秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int INF = 1e18;
const int maxn = 1e6 + 10;

int P, n, A, B, C, D, g, block, Inv[maxn];
vector<int> a;
vector<pii> Shit;

inline int power(int a, int b, int Mod) 
{ 
    int r = 1; b = (b % (Mod - 1) + (Mod - 1)) % (Mod - 1);
    while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } 
    return r; 
}

inline int get(int x) 
{
    int pos = lower_bound(Shit.begin(), Shit.end(), pii(x, 0)) - Shit.begin();
    if ( pos == Shit.size() || Shit[pos].first != x ) return INF;
    return Shit[pos].second;
}

inline int BSGS(int a, int b, int p)
{
    int x = p;
    REP(i, 0, P / block + 1) 
    {
        x = min(x, i * block + get(b * Inv[i] % p));
        if ( x != p ) return x;
    }
}

inline void exgcd(int a, int b, int &x, int &y)
{
    if ( b == 0 ) { x = 1; y = 0; return ; }
    exgcd(b, a % b, y, x); y -= a / b * x;
}

inline int GetInv(int a, int p)
{
    int x, y; exgcd(a, p, x, y);
    return (x % p + p) % p;
}

inline int F(int x, int C, int D, int E) { return (C * x + D) / E; }

inline int f(int L, int R, int A, int B, int C, int D, int E)
{
//    cerr << L << " " << R << " " << A << " " << B << " " << C << " " << D << " " << E << endl;
    if ( L > R ) return INF;
    if ( C >= E ) return f(L, R, A + B * (C / E), B, C % E, D, E);
    if ( A >= 0 ) 
    {
        int ans1 = A * L + B * F(L, C, D, E);
        int l = F(L, C, D, E), r = F(R, C, D, E);
        int ans2 = f(l + 1, r, B, A, E, C - D - 1, C);
        return min(ans1, ans2);
    }
    else
    {
        int ans1 = A * R + B * F(R, C, D, E);
        int l = F(L, C, D, E), r = F(R, C, D, E);
        int ans2 = f(l, r - 1, B, A, E, E - D - 1, C);
        return min(ans1, ans2);
    }
}

signed main()
{
    freopen("game.in", "r", stdin);
    freopen("game.out", "w", stdout);
    srand(time(0));
    scanf("%lld%lld", &P, &n); 
    int x = P - 1;
    for ( int i = 2; i * i <= x; ++ i ) 
        if ( x % i == 0 ) { a.push_back(i); while ( x % i == 0 ) x /= i; }
    if ( x ) a.push_back(x);
    while ( 1 ) 
    {
        g = rand() % P; if ( g <= 1 ) continue ;
        bool flag = true;
        for ( auto i : a ) if ( power(g, (P - 1) / i, P) == 1 ) { flag = false; break ; }
        if ( flag == true ) break ; 
    }

    block = sqrt(n * P) + 1; 
    for ( int i = 0, j = 1; i < block; ++ i, j = j * g % P ) Shit.push_back(pii(j, i));
    REP(i, 0, P / block + 1) Inv[i] = power(g, - i * block, P) % P;
    sort(Shit.begin(), Shit.end());
    
    REP(o, 1, n)
    {
        scanf("%lld%lld%lld%lld", &A, &B, &C, &D); C %= P; D %= P;
        if ( !C || !D ) { puts("Damn it"); continue ; }
        C = BSGS(g, C, P); D = BSGS(g, D, P);
        int p = P - 1, d; 
        if ( C == 0 && D == 0 ) { puts("0"); continue ; }
        if ( C == 0 ) { printf("%lld\n", B * p / __gcd(p, D) + A); continue ; } 
        if ( D == 0 ) { printf("%lld\n", A * p / __gcd(p, C) + B); continue ; } 
//        printf("%lld %lld\n", C, D);
        d = __gcd(__gcd(C, D), p); C /= d; D /= d; p /= d;
        d = __gcd(C, p); C = C / d; p = p / d; B = B * d; D = D * GetInv(C, p) % p;
        d = __gcd(D, p); D = D / d; p = p / d; A = A * d;
        printf("%lld\n", min((A + B) * p, f(1, p - 1, B + A * D, - A * p, D, 0, p)));
    }
    return 0;
}
