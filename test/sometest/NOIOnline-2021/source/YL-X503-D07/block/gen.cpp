/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2021年03月27日 星期六 09时40分24秒
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
    freopen("block.in", "w", stdout);
	int n = 3000; printf("%d\n", n);
	REP(i, 1, n) printf("%c", rand() % 3 + 'a'); puts("");
	REP(i, 1, n) printf("%c", rand() % 3 + 'a'); puts("");
    return 0;
}
