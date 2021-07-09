#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof(a) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>

const int maxn = 1e5 + 10;

int n, a[maxn], m;
pii b[maxn];

int main()
{
	freopen("one.in", "r", stdin);
	freopen("one.out", "w", stdout);
	scanf("%d", &n); REP(i, 0, n) scanf("%d", &a[i]);
	int cnt = 0;
	while ( cnt <= 10000 ) 
	{
		++ cnt;
		m = 0; int sum = 0; bool flag = false;
		for ( int i = 0; i < n; i += 2)  
		{
			sum += a[i];
			if ( sum <= a[i + 1] ) 
			{
				b[m ++] = pii(a[i], 0);
				b[m ++] = pii(sum, 1);
				b[m ++] = pii(a[i + 1] - sum, 0);
				sum = 0;
			}
			else
			{
				b[m ++] = pii(a[i], 0);
				b[m ++] = pii(a[i + 1], 1);
				sum -= a[i + 1];
			}
		}
		if ( cnt == 10000 ) { for ( int i = 0; i <= n; i += 2 ) printf("%d ", a[i]); puts(""); return 0; } 
		sum += a[n]; b[m ++] = pii(a[n], 0); b[m ++] = pii(sum, 1);

		n = 0;
		for ( int i = 1, j; i < m; i = j + 1 )
		{
			j = i; int num = b[j].first;
			while ( j + 1 < m && b[j + 1].second == b[j].second ) { ++ j; num += b[j].first; } 
			a[n ++] = num;
		}

		-- n;
	}
	return 0;
}
