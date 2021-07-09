/***************************************************************
	File name: H.cpp
	Author: ljfcnyali
	Create time: 2020年12月12日 星期六 15时25分47秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1e5 + 10;
const int Mod = 1e9 + 7;

int T, n, ans;
struct node { int x, y, z; node(int a = 0, int b = 0, int c = 0 ) { x = a; y = b; z = c; } };
map<int, node> Map;

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline node Solve(int n)
{
    if ( n == 1 ) { return node(1, 1, 1); }
    if ( Map.count(n) ) return Map[n];
    int x = n / 2, y = n - x;
    node sum, X = Solve(x), Y = Solve(y); 
    sum.x = (X.x + Y.x) % Mod;
    sum.x = (sum.x + X.z * (y % Mod)) % Mod;
    sum.x = (sum.x + (x % Mod) * Y.y) % Mod;

    sum.y = (X.y + Y.y + (y % Mod) * ((2 * x % Mod) - 1)) % Mod;
    sum.z = (Y.z + X.z + (x % Mod) * ((2 * y % Mod) - 1)) % Mod;
    ++ sum.x; ++ sum.y; ++ sum.z;
    Map[n] = sum; return sum;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld", &T);
    while ( T -- ) 
    {
        scanf("%lld", &n);
        int N = n % Mod, x = (2 + N) % Mod;
        x = x * (N + 1) % Mod;
        x = x * N % Mod;
        ans = x * power(6, Mod - 2) % Mod;

        ans = ans * 2 % Mod;
        ans = (ans - Solve(n).x) % Mod;
        printf("%lld\n", (ans + Mod) % Mod);
    }
    return 0;
}
