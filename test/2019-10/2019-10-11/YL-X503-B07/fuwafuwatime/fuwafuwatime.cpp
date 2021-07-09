/***************************************************************
	File name: fuwafuwatime.cpp
	Author: ljfcnyali
	Create time: 2019年10月11日 星期五 08时50分23秒
***************************************************************/
#include<bits/stdc++.h>
#include<tr1/unordered_map>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 10000010;
const int MAX = 3e6;
const int Mod = 9990017;

int pow1[maxn], pow2[maxn], ans, sum[maxn], p[maxn];
LL n, m, B;
bool vis[maxn];

inline int power(LL a, int b)
{
    LL r = 1;
    while ( b ) { if ( b & 1 ) r = (r * a) % Mod; a = (a * a) % Mod; b >>= 1; }
    return r;
}

inline int C0(int a, int b)
{
    if ( a < b ) return 0;
    LL sum = ((LL) pow1[a] * pow2[a - b]) % Mod;
    sum = (sum * pow2[b]) % Mod;
    return sum;
}

inline int C(LL a, LL b) { return a < b ? 0 : ((a <= Mod ? 1 : (LL) C(a / Mod, b / Mod)) * C0(a % Mod, b % Mod)) % Mod; }

tr1::unordered_map<int, int> Map;

inline int S(LL n)
{
    if ( n <= MAX ) return sum[n];
    if ( Map.count(n) ) return Map[n];
    LL sum = C(n + 1, B + 1);
    for ( LL i = 2, j; i <= n; i = j + 1 ) 
    {
        j = n / (n / i);
        sum = (sum - ((LL) j - i + 1) * S(n / i)) % Mod;
    }
    Map[n] = sum; return sum;
}

signed main()
{
    freopen("fuwafuwatime.in", "r", stdin);
    freopen("fuwafuwatime.out", "w", stdout);
    scanf("%lld%lld%lld", &n, &m, &B);

    pow1[0] = 1; REP(i, 1, Mod) pow1[i] = ((LL) pow1[i - 1] * i) % Mod;
    pow2[Mod - 1] = power(pow1[Mod - 1], Mod - 2);
    for ( int i = Mod - 2; i >= 0; -- i ) pow2[i] = ((LL) pow2[i + 1] * (i + 1)) % Mod;
    REP(i, 1, MAX) sum[i] = C(i, B);

    REP(i, 1, MAX) 
        for ( int j = i + i; j <= MAX; j += i )
            sum[j] = ((LL) sum[j] - sum[i]) % Mod;
    REP(i, 2, MAX) sum[i] = ((LL) sum[i] + sum[i - 1]) % Mod;

    LL ans = 0;
    for ( LL i = 1, j; i <= min(n, m); i = j + 1 )
    {
        j = min(n / (n / i), m / (m / i));
        LL Sum = ((LL) n / i % Mod) * ((LL) m / i % Mod) % Mod;
       ans = (ans + Sum * ((LL) S(j) - S(i - 1))) % Mod;
    }
    printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}
