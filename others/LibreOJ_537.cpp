/***************************************************************
	File name: LibreOJ_537.cpp
	Author: ljfcnyali
	Create time: 2019年11月15日 星期五 09时41分28秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 5e6 + 10;
const int seed = 233;
const int Mod = 1e9 + 7;

char s[maxn];
int n, k, ans, inv[maxn], Hash[maxn];
map<int, int> Map;

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline int get(int l, int r) 
{ 
    return (Hash[r] - Hash[l - 1] + Mod) * inv[l] % Mod; 
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%s", s + 1); n = str(s + 1);
    int x = power(seed, Mod - 2);
    inv[n] = 1;
    for ( int i = n - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * x % Mod;
    REP(i, 1, n) Hash[i] = (Hash[i - 1] * seed + s[i]) % Mod;
    scanf("%lld", &k);
    REP(i, 1, n - k + 1) ++ Map[get(i, i + k - 1)];
    for ( auto i : Map ) ans = max(ans, i.second);
    printf("%lld\n", ans);
    return 0;
}
