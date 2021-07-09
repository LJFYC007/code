/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2021年02月21日 星期日 13时52分13秒
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
    freopen("input.txt", "w", stdout);
	srand(time(0));
	int n = 5, m = 5; printf("%d %d\n", n, m);
	REP(i, 1, m) printf("%d ", rand() % 100); puts("");
	REP(i, 1, n) printf("%d %d\n", rand() % 10, rand() % m + 1); puts("");
    return 0;
}
