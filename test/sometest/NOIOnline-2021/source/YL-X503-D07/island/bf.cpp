/***************************************************************
	File name: bf.cpp
	Author: ljfcnyali
	Create time: 2021年03月27日 星期六 11时48分39秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int n, m, a[maxn], b[maxn];

int main()
{
    freopen("island.in", "r", stdin);
    freopen("island1.out", "w", stdout);
	scanf("%d%d", &n, &m); REP(i, 1, n) scanf("%d%d", &a[i], &b[i]);
	REP(i, 1, m) 
	{
		int l, r, c, d; scanf("%d%d%d%d", &l, &r, &c, &d);
		int ans = 0;
		REP(j, l, r) if ( (a[j] ^ c) <= min(b[j], d)) ++ ans;
		cout << ans << endl;
	}

    return 0;
}
