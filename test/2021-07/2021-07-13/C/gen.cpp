/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2021年07月13日 星期二 08时33分10秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;
const int M = 1e9;

int main()
{
    freopen("input.txt", "w", stdout);
	int n = 3000; printf("%d\n", n);
	REP(i, 1, n) 
	{
		int x = rand() % (M + M + 1) - M;
		int y = rand() % (M + M + 1) - M;
		printf("%d %d\n", x, y);
	}
    return 0;
}
