#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof(a) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>

const int maxn = 1e5 + 10;

int main()
{
	freopen("gear.in", "w", stdout);
	srand(time(0));
//	int n = 10, q = 10;
 	int n = 1000 + rand() % 3000, q = 1000 + rand() % 3000;
	printf("%d %d\n", n, q);
	REP(i, 2, n) printf("%d ", rand() % (i - 1) + 1); puts("");
	REP(i, 1, q)
	{
		int op = rand() % 2;
		if ( op == 0 ) printf("1 %d %d\n", rand() % n + 1, rand() % 360);
		else printf("2 %d %d\n", rand() % n + 1, rand() % n + 1);
	}
	return 0;
}
