/**************************************************************
	File name: pair.cpp
	Author: ljfcnyali
	Create time: 2019年09月17日 星期二 20时00分07秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
typedef long long LL;

const int maxn = 500010;
const int Mod = 998244353;

char L[maxn], R[maxn];
int l, r, T, opt, p[maxn], A[maxn], C[maxn][11];

inline int Solve(char *s, int n)
{
    int ans = 0, x = 0;
    mem(C);
    REP(i, 1, n) { p[i] = (p[i - 1] * 10) % Mod; A[i] = (A[i - 1] * 10 + s[i] - '0') % Mod; }
    for ( int i = n; i >= 1; -- i )
    {
        REP(j, 0, 9)
        {
            C[i][j] = (C[i + 1][j] + (((s[i] - '0') * (n - i)) % Mod) * p[n - i - 1]) % Mod;
            if ( s[i] - '0' == j ) C[i][j] = (C[i][j] + x + 1) % Mod;
            if ( j < s[i] - '0' ) C[i][j] = (C[i][j] + p[n - i]) % Mod;
        }
        x = (x + (s[i] - '0') * p[n - i]) % Mod;
    }
    REP(i, 1, n) REP(j, 1, 9) C[i][j] = (C[i][j] + C[i][j - 1]) % Mod;
    REP(i, 1, n)
        REP(j, 0, 9)
        {
            int x = (((j * (n - i)) % Mod) * p[n - i - 1]) % Mod;
            ans = (ans + (A[i - 1] + (j < s[i] - '0')) * x) % Mod;
            if ( j == s[i] - '0' && j ) ans = (ans + C[i + 1][j - 1]) % Mod;
        }
    cerr << ans << endl;
    return ans;
}

signed main()
{
    freopen("pair.in", "r", stdin);
    freopen("pair.out", "w", stdout);
    scanf("%lld%lld", &T, &opt);
    p[0] = 1;
    while ( T -- )
    {
        scanf("%s%s", L + 1, R + 1);
        l = str(L + 1); r = str(R + 1);
        int x = l; 
        while ( L[x] == '0' ) L[x --] = '9';
        -- L[x]; 
        printf("%lld\n", ((Solve(R, r) - Solve(L, l)) % Mod + Mod) % Mod;
    }
    return 0;
}
