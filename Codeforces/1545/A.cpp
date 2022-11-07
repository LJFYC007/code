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

int T, n, a[maxn], b[maxn], c[maxn], m1, m2;

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &T);
	while ( T -- ) 
	{
		scanf("%d", &n); m1 = m2 = 0;
		REP(i, 1, n)
			if ( i & 1 ) scanf("%d", &a[++ m1]);
			else scanf("%d", &b[++ m2]);
		sort(a + 1, a + m1 + 1);
		sort(b + 1, b + m2 + 1);
		int x = 1, y = 1;
		REP(i, 1, n)
			if ( i & 1 ) c[i] = a[x ++];
			else c[i] = b[y ++];
		bool flag = true;
		REP(i, 1, n - 1) if ( c[i] > c[i + 1] ) flag = false;
		if ( flag ) puts("YES");
		else puts("NO");
	}

    return 0;
}