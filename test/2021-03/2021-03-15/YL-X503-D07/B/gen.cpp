#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof(a) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>

const int maxn = 1e6 + 10;

int vis[maxn];

inline void print()
{
	int x = rand() % 1000000 + 1;
	while ( vis[x] ) x = rand() % 1000000 + 1;
	vis[x] = true; printf("%d ", x);
}

int main()
{
	freopen("input.txt", "w", stdout);
	int n = 5, m = 9999; printf("%d %d\n", n, m);
	srand(time(0));
	REP(i, 1, m) print(); puts("");
	REP(i, 1, n)
	{
		printf("0 ");
		REP(j, 1, m) print();
		puts("");
	}
	return 0;
}
