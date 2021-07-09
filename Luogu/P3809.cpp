/***************************************************************
	File name: CF1043G.cpp
	Author: ljfcnyali
	Create time: 2020年12月30日 星期三 11时36分14秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e6 + 10;
const int Mod = 1e9 + 7;
const int seed = 233;

int n, m, sa[maxn], rk[maxn];
char s[maxn];

inline void SA()
{
    int x[maxn], y[maxn], c[maxn], m = 128; 
    REP(i, 1, n) { x[i] = s[i]; ++ c[x[i]]; } REP(i, 1, m) c[i] += c[i - 1];
    for ( int i = n; i >= 1; -- i ) sa[c[x[i]] --] = i;
    REP(i, 1, n) y[i] = i;
    for ( int k = 1; k <= n; k <<= 1 ) 
    {
        mem(c); int tot = 0;
        REP(i, n - k + 1, n) y[++ tot] = i; REP(i, 1, n) if ( sa[i] > k ) y[++ tot] = sa[i] - k;
        REP(i, 1, n) ++ c[x[y[i]]]; REP(i, 1, m) c[i] += c[i - 1];
        for ( int i = n; i >= 1; -- i ) sa[c[x[y[i]]] --] = y[i];
        swap(x, y); x[sa[1]] = tot = 1;
        REP(i, 2, n) x[sa[i]] = (y[sa[i]] == y[sa[i - 1]] && y[sa[i] + k] == y[sa[i - 1] + k]) ? tot : ++ tot;
        m = tot;
    }
    REP(i, 1, n) rk[sa[i]] = i;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%s", s + 1); n = str(s + 1); SA();
    REP(i, 1, n) cout << sa[i] << " "; cout << endl;
    return 0;
}
