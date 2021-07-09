#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof(a) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>

const int maxn = 5e5 + 10;

int n, k, a[maxn];

int main()
{
#ifndef ONLINE_JUDGE
	freopen("decrypt.in", "r", stdin);
	freopen("decrypt1.out", "w", stdout);
#endif
	scanf("%d%d", &n, &k);
	REP(i, 1, n) scanf("%d", &a[i]);
	REP(o, 1, k)
	{
		REP(i, 1, n - 1) if ( a[i] == 0 && a[i + 1] == 1 ) { swap(a[i], a[i + 1]); ++ i; } 
	}
	REP(i, 1, n) printf("%d ", a[i]); puts("");
	return 0;
}
