/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2021年04月08日 星期四 09时37分06秒
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
	int n = rand() % 100 + 3, px = rand() % 20 + 1, py = rand() % 20 + 1;
	printf("%d %d %d %d %d %d %d %d %d\n", rand() % px, rand() % py, rand() % px, rand() % py, rand() % px, rand() % py, px, py, n);
    return 0;
}
