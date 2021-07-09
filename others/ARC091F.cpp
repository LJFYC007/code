/***************************************************************
	File name: ARC091F.cpp
	Author: ljfcnyali
	Create time: 2021年06月15日 星期二 11时02分21秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 210;

int n, a[maxn], k[maxn], ans;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &n);
	REP(i, 1, n) 
	{
		int k; scanf("%d%d", &a[i], &k);
		while ( a[i] >= k ) 
		{
			if ( a[i] % k == 0 ) { ans ^= (a[i] / k); break ; } 
			int t = a[i] / k + 1, pos = (a[i] / k) * k;
			while ( a[i] > pos ) a[i] -= t;
		}
	}
	if ( ans == 0 ) puts("Aoki"); else puts("Takahashi");
    return 0;
}
