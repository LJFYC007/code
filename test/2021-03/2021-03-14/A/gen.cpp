/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2021年03月14日 星期日 09时13分47秒
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
	int n = 10000, k = 100; printf("%d %d\n", n, k); srand(time(0));
	REP(i, 1, n) printf("%d ", rand() % 1000000 + 1);  puts("");
    return 0;
}
