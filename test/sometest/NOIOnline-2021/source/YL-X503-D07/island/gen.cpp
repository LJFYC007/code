/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2021年03月27日 星期六 11时50分32秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int main()
{
    freopen("island.in", "w", stdout);
	int n = 100000, m = (1 << 24) - 1, q = n;
	srand(time(0));
	cout << n << " " << q << endl;
	REP(i, 1, n) printf("%d %d\n", rand() % m + 1, rand() % m + 1);
	REP(i, 1, q)
	{
		int l = rand() % n + 1, r = rand() % n + 1;
		if ( l > r ) swap(l, r);
		printf("%d %d %d %d\n", l, r, rand() % m + 1, rand() % m + 1);
	}

    return 0;
}
