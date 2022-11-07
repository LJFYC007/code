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

int T, n; double Max, Min, Ave;

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &T);
	while ( T -- ) 
	{
		scanf("%d%lf%lf%lf", &n, &Max, &Min, &Ave);
		if ( Max < Max || Ave < Min || Ave > Max || (n <= 2 && (Max + Min) / 2 != Ave) || (n == 1 && Max != Min) 
			|| Min + Max * (n - 1) < n * Ave || Max + Min * (n - 1) > n * Ave 	
		) 
			puts("no");
		else 
			puts("yes");
	}

    return 0;
}
