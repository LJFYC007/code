/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2021年03月28日 星期日 10时34分08秒
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
	int n = 40000, M = 1000;
	srand(time(0));
	printf("%d\n", n);
	REP(i, 1, n) printf("%d ", rand() % M); puts("");
	REP(i, 1, n) printf("%d ", rand() % M); puts("");
    return 0;
}
