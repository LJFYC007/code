/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2021年02月21日 星期日 14时17分49秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int n, x[maxn];

int main()
{
    freopen("input.txt", "w", stdout);
	srand(time(0));
	n = 1000; REP(i, 1, n) x[i] = rand() % 10000;
	sort(x + 1, x + n + 1); n = unique(x + 1, x + n + 1) - x - 1;
	printf("%d\n", n);
	REP(i, 1, n) printf("%d %d %d\n", x[i], rand() % 2000, rand() % 200);
    return 0;
}
