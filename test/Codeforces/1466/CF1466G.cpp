/***************************************************************
	File name: CF1466G.cpp
	Author: ljfcnyali
	Create time: 2021年01月02日 星期六 20时18分51秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 2e6 + 10;
const int Mod = 1e9 + 7;

int n, m, k, q, Next[maxn], fac[maxn], num[100010][26];
char s[maxn], t[maxn];
bool f[2][maxn];
string S;

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; } 

inline void GetNext()
{
    REP(i, 1, m) Next[i] = 0;
    for ( int i = 2, j = 0; i <= m; ++ i ) 
    {
        while ( j && s[i] != s[j + 1] ) j = Next[j];
        if ( s[i] == s[j + 1] ) ++ j;
        Next[i] = j;
    }
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld", &n, &q); fac[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * 2 % Mod;
    cin >> S; scanf("%s", t + 1);
    REP(i, 1, n)
    {
        REP(j, 0, 25) num[i][j] = num[i - 1][j] * 2 % Mod;
        ++ num[i][t[i] - 'a'];
    }
    while ( q -- ) 
    {
        scanf("%lld %s", &k, s + 1); m = str(s + 1);
        string now = S; int pos = 1;
        while ( now.length() < m && pos <= k ) { now = now + t[pos] + now; ++ pos; }
        if ( now.length() < m ) { puts("0"); continue ; } 

        GetNext();
        s[m + 1] = -1; int cnt = 0, len = now.length(), j;
        REP(i, 0, m) f[0][i] = f[1][i] = false; f[0][0] = f[1][0] = true;
        j = 0;
        for ( int i = 0; i < len; ++ i ) 
        {
            while ( j && now[i] != s[j + 1] ) j = Next[j];
            if ( now[i] == s[j + 1] ) ++ j;
            if ( j == m ) ++ cnt; 
        }
        while ( j ) { f[0][j] = true; j = Next[j]; } 
        reverse(s + 1, s + m + 1);
        GetNext(); j = 0;
        for ( int i = len - 1; i >= 0; -- i ) 
        {
            while ( j && now[i] != s[j + 1] ) j = Next[j];
            if ( now[i] == s[j + 1] ) ++ j;
        }
        while ( j ) { f[1][j] = true; j = Next[j]; } 
        reverse(s + 1, s + m + 1);

        // REP(i, 0, m) cout << f[0][i] << " "; cout << endl;
        // REP(i, 0, m) cout << f[1][i] << " "; cout << endl;

        int ans = cnt * fac[k - pos + 1] % Mod;
        REP(i, 1, m) if ( f[0][i - 1] && f[1][m - i] ) 
            ans = (ans + num[k][s[i] - 'a'] - num[pos - 1][s[i] - 'a'] * fac[k - pos + 1]) % Mod;

        printf("%lld\n", (ans + Mod) % Mod);
    }
    return 0;
}
