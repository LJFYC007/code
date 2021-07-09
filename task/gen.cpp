/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2020年07月28日 星期二 19时25分55秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

map<int, int> Map[maxn];

int main()
{
    freopen("input.txt", "w", stdout);
    srand(time(0));
	int n = 10, m = 100000; printf("%d %d\n", n, m);
	REP(i, 2, n) printf("%d %d %d\n", i, rand() % (i - 1) + 1, rand() % 10 + 1);
	REP(i, 1, m) printf("%d %d\n", rand() % n + 1, rand() % n + 1);
    return 0;
}
