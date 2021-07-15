/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2021年07月15日 星期四 11时45分51秒
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
	int n = 200000;
	printf("%d\n", n);
	REP(i, 1, n) printf("%c", rand() % 1 + 'a');
	puts("");
    return 0;
}
