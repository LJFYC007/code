/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2021年02月15日 星期一 12时25分25秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1e5 + 10;

signed main()
{
    freopen("input.txt", "w", stdout);
	int n = 7, K = 3; printf("%lld %lld\n", n, K);
	int lst = 0; srand(time(0));
	REP(i, 1, K)
	{
		lst += rand() + 1;
		printf("%lld ", lst);
	}
	puts("");
    return 0;
}
