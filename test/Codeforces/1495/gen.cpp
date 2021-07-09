/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2021年03月18日 星期四 21时59分26秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int a[maxn];

int main()
{
    freopen("input.txt", "w", stdout);
	int n = 20, q = 20; printf("%d %d\n", n, q);
	REP(i, 1, n) a[i] = i; srand(time(0)); random_shuffle(a + 1, a + n + 1);
	REP(i, 1, n) printf("%d ", a[i]); puts("");
	REP(i, 1, n) printf("%d ", rand() % 30); puts("");
	REP(i, 1, n) printf("%d ", rand() % 30); puts("");
	REP(i, 1, q) printf("%d ", rand() % n + 1); puts("");
    return 0;
}
