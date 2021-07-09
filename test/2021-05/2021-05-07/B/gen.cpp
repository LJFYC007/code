/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2021年05月07日 星期五 09时21分54秒
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
	int n = 20; printf("%d\n", n);
	REP(i, 1, n)
	{
		int len = 100000 / n;
		REP(i, 1, len) printf("%c" ,rand() % 5 + 'a'); puts("");
	}
    return 0;
}
