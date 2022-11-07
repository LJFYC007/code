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

int T, n; pii a[maxn];

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &T);
	while ( T -- ) 
	{
		int op; scanf("%d", &op);
		if ( op == 1 ) 
		{
			int x, y; scanf("%d%d", &x, &y);
			a[++ n] = pii(x, y);
			sort(a + 1, a + n + 1);
		}
		else 
		{
			int d, sum = 0, num = 1; scanf("%d", &d);
			while ( 1 ) 
			{
				bool flag = false; int val = 0;
				REP(i, 1, n) if ( sum < a[i].first && a[i].first <= sum + d )
				{
					flag = true;
					val += a[i].second;
				}
				if ( !flag ) break ; 
				++ num; sum += d; d -= val; 
			}
			printf("%d\n", num);
		}
	}

    return 0;
}
