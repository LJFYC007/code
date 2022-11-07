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

int main()
{
	freopen("input.txt", "w", stdout);

	int n = 1000; printf("%d %d\n", n, n);
	srand(time(0));
	REP(i, 1, n - 1)
	{
		int op = rand() % 3 + 1;
		int l = rand() % n + 1, r = rand() % n + 1;
		if ( op <= 2 ) 
			printf("%d %d %d %d\n", op, min(l, r), max(l, r), rand() % n + 1);
		if ( op == 3 ) 
			printf("%d %d %d %d\n", op, min(l, r), max(l, r) , rand() % 100);
	}
	puts("4 1 1000");

    return 0;
}
