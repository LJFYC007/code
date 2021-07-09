/***************************************************************
	File name: string.cpp
	Author: ljfcnyali
	Create time: 2020年11月20日 星期五 14时22分52秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 6e5 + 10;
const int seed = 233;
const int Mod = 998244353;

int n, m, p[maxn], inv[maxn];
map<int, int> ans[maxn];
string s[maxn];
vector<int> Hash[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline int Get(int l, int r, int i)
{
    int val = Hash[i][r] - (l >= 1 ? Hash[i][l - 1] : 0);
    val = val * inv[l] % Mod;
    return (val + Mod) % Mod;
}

inline int Solve(int x, int y)
{
    int len1 = s[x].length(), len2 = s[y].length();
    for ( int i = min(len1, len2); i >= 1; -- i )
        if ( Get(len1 - i, len1 - 1, x) == Get(0, i - 1, y) ) return i;
    return 0;
}

signed main()
{
    freopen("string.in", "r", stdin);
    freopen("string.out", "w", stdout);
    scanf("%lld%lld", &n, &m);
    p[0] = inv[0] = 1; REP(i, 1, maxn - 10) { p[i] = p[i - 1] * seed % Mod; inv[i] = power(p[i], Mod - 2); }
    REP(i, 1, n) 
    {
        cin >> s[i]; int len = s[i].length(); Hash[i].resize(len);
        REP(j, 0, len - 1) Hash[i][j] = ((j >= 1 ? Hash[i][j - 1] : 0) + p[j] * (s[i][j] - 'a')) % Mod;
    }

    REP(i, 1, m)
    {
        int x, y; scanf("%lld%lld", &x, &y);
        if ( !ans[x].count(y) ) ans[x][y] = Solve(x, y);
        printf("%lld\n", ans[x][y]);
    }
    return 0;
}
