/***************************************************************
	File name: HaHa
	Author: ljfcnyali
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset ( (a), 0, sizeof ( a ) )
#define str(a) strlen ( a )
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int T, n, a[maxn], m;

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &T);
	while ( T --  )
	{
		scanf("%d%d", &n, &m);
		REP(i, 1, n) scanf("%d", &a[i]);
		REP(i, 1, n)
		{
			m -= a[i];
			if ( !m ) swap(a[i], a[i + 1]); 
		}
		if ( !m ) puts("NO");
		else { puts("YES"); REP(i, 1, n) printf("%d ", a[i]); puts(""); }
	}
    return 0;
}
