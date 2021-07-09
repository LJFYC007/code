#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof(a) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>

const int maxn = 1e5 + 10;
const int N = 1e9;

map<int, int> Map1, Map2;

inline int Get1()
{
	int x = -(rand() % N + 1);
	while ( Map1.count(x) ) x = -(rand() % N + 1);
	Map1[x] = true; return x;
}

inline int Get2()
{
	int x = (rand() % N + 1);
	while ( Map1.count(x) ) x = (rand() % N + 1);
	Map1[x] = true; return x;
}

inline int Get3()
{
	int x = (rand() % N + 1);
	while ( Map2.count(x) ) x = (rand() % N + 1);
	Map2[x] = true; return x;
}

int main()
{
	freopen("input.txt", "w", stdout);
	int n = 50000, q = n; printf("%d\n", n);
	srand(time(0));
	REP(i, 1, n)
	{
		int x = Get1(), y = Get3();
		printf("%d %d %d\n", x, y, rand() % N + 1);
	}
	REP(i, 1, n)
	{
		int x = Get2(), y = Get3();
		printf("%d %d %d\n", x, y, rand() % N + 1);
	}
	printf("%d\n", q);
	REP(i, 1, q)
	{
		int x = Get1(), y = Get2();
		printf("%d %d\n", x, y);
	}
	return 0;
}
