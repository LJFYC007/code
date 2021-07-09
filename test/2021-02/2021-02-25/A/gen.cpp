/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2021年02月25日 星期四 15时33分50秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;
const int N = 1e9;

int main()
{
    freopen("input.txt", "w", stdout);
	int n = 100000, q = 100000; printf("%d %d\n", n, q);
	REP(i, 1, n)
	{
		int x = rand() % N, y = rand() % N;
		int t = rand() % 10000, z = rand() % 10000;
		printf("%d %d %d %d\n", x, y , x + t, y + z);
	}
	REP(i, 1, q) printf("%d %d\n", rand() % N, rand() % N);
    return 0;
}
