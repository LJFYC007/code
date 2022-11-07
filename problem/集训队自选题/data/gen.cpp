/***************************************************************
	File name: HaHa
	Author: ljfcnyali
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset ( (a), 0, sizeof ( a ) )
#define str(a) strlen ( a )
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int n = 100000, M = sqrt(n) * 5;

int Rand()
{
	unsigned int x = rand();
	x = x ^ (rand() << 10);
	x = x ^ (rand() << 20);
	x = x ^ (rand() << 30);
	return x % 2147483648;
}

map<int, int> Map[maxn];

inline int Get()
{
	int x = rand() % M;
	int y = rand() % M;
	while ( Map[x].count(y) ) { x = rand() % M; y = rand() % M; }
	Map[x][y] = true;
	printf("%d %d\n", x, y);
}

int main()
{
	freopen("7.in", "w", stdout);
	srand(time(0));
	printf("%d\n", n);
	REP(i, 1, n) Get();
    return 0;
}
