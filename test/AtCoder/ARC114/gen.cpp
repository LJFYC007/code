/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2021年03月24日 星期三 22时18分58秒
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
	int n = 10; srand(time(0));
	REP(i, 1, n) a[i] = i;
	random_shuffle(a + 1, a + n + 1);
	printf("%d %d\n", n, rand() % n + 1);
	REP(i, 1, n) printf("%d ", a[i]); puts("");
    return 0;
}