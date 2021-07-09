/***************************************************************
	File name: 5.cpp
	Author: ljfcnyali
	Create time: 2020年07月21日 星期二 15时52分54秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define x first
#define y second
typedef long long LL;

const int maxn = 1e5 + 10;
const int Mod = 1e9 + 9;

int T, n, m, k, fac[maxn], inv[maxn];

pii operator + (pii a, pii b) { return pii((a.x + b.x) % Mod, (a.y + b.y) % Mod); }
pii operator - (pii a, pii b) { return pii((a.x - b.x) % Mod, (a.y - b.y) % Mod); }
pii operator * (pii a, pii b) { return pii((a.x * b.x + a.y * b.y) % Mod, (a.x * b.y + a.y * b.x) % Mod); }
inline pii inv(pii a) { return pii(, (a.y * a.y - a.x * a.x) % Mod * power(a.y * a.y % Mod, Mod - 2) % Mod); }
pii operator / (pii a, pii b) { return 

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    n = maxn - 10; fac[0] = inv[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;    
    inv[n] = power(n, Mod - 2); for ( int i = n - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;

    return 0;
}
