/***************************************************************
	File name: sort.cpp
	Author: ljfcnyali
	Create time: 2021年02月17日 星期三 09时13分14秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int n, a[maxn], ans;
bitset<maxn> f, g;
bool b[maxn];

int main()
{
    freopen("sort.in", "r", stdin);
    freopen("sort.out", "w", stdout);
	scanf("%d", &n); REP(i, 1, n) scanf("%d", &a[i]);
	sort(a + 1, a + n + 1, [](const int &a, const int &b) { return a > b; });
	if ( n == 1 || a[n] != a[n - 1] ) { printf("%d\n", a[n]); return 0; } 
	REP(i, 1, n) b[a[i]] = true;
	for ( int i = a[1]; i >= 1; -- i ) 
	{
		if ( b[i] ) 
		{
			f[i] = 1;
			for ( int j = i; j <= a[1]; j += i ) g[j] = 1;
		}
		else if ( ((f >> i) & g).any() ) f[i] = 1;
	}
	REP(i, 0, a[1]) if ( f[i] ) ans = max(ans, i % a[n]);
	printf("%d\n", ans);
    return 0;
}
