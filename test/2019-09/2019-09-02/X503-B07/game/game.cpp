/***************************************************************
	File name: game.cpp
	Author: ljfcnyali
	Create time: 2019年09月02日 星期一 19时20分11秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
typedef long long LL;

const int maxn = 1000010;
const int Mod = 1e9 + 7;

int n, m, k, A[maxn], B[maxn], sum, ans;
char s[3];

signed main()
{
    freopen("game.in", "r", stdin);
    freopen("game.out", "w", stdout);
    scanf("%lld%lld%lld", &n, &m, &k);
    REP(i, 1, n) A[i] = 1; REP(i, 1, m) B[i] = 1;
    REP(i, 1, k)
    {
        scanf("%s", s);
        int pos, val; scanf("%lld%lld", &pos, &val); 
        if ( s[0] == 'R' ) A[pos] = (A[pos] * val) % Mod;
        else B[pos] = (B[pos] * val) % Mod;
    }
    REP(i, 1, m) sum = (sum + B[i]) % Mod;
    REP(i, 1, m) B[i] = (B[i - 1] + B[i] * i) % Mod;
    REP(i, 1, n)
    {
        int Sum = ((((i - 1) * m) % Mod) * sum + B[m]) % Mod;
        ans = (ans + ((Sum * A[i]) % Mod)) % Mod;
    }
    printf("%lld\n", ans);
    return 0;
}
