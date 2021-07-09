/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2021年03月28日 星期日 09时21分37秒
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
	int n = 100, m = 1000; printf("%d %d\n", n, m);
	int N = 100000;
	srand(time(0));
	REP(i, 1, n) printf("%d %d\n", rand() % N, rand() % N);
	REP(i, 1, m) printf("%d %d\n", rand() % N, rand() % N);
    return 0;
}
