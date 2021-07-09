/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2020年05月31日 星期日 19时11分10秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int Mod = 998244353;
const int maxn = 1e7 + 10;

int Q, n, ans;

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

signed main()
{
    freopen("a.in", "r", stdin);
    freopen("a.out", "w", stdout);
    scanf("%lld", &Q);
    while ( Q -- ) 
    {
        scanf("%lld", &n); 
        int x = power(n, Mod - 2);
        ans = 0; 
        int last = 1;
        REP(i, 1, n) 
        {
            int now = (n - i + 1) * x % Mod;
            ans = (ans + (i * last % Mod) * (1 - now)) % Mod;
            last = last * now % Mod;
        }
        ans = (ans + last * (n + 1)) % Mod;
        printf("%lld\n", (ans + Mod) % Mod);
    }
    return 0;
}
