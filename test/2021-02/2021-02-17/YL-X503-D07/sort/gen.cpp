/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2021年02月17日 星期三 09时15分56秒
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
    freopen("sort.in", "w", stdout);
	srand(time(0));
	int n = 10; printf("%d\n", n);
	int x = rand() % 30 + 1; printf("%d %d ", x, x);
	REP(i, 3, n) printf("%d ", x + rand() % 100); puts("");
    return 0;
}
