#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

int main()
{
    freopen("input.txt", "w", stdout);
	srand(time(0));
	int n = 1000, m = 1000; printf("%d %d\n", n, m);
	REP(i, 1, n)
	{
		int x1 = rand() % m, x2 = rand() % m, y1 = rand() % m, y2 = rand() % m;
		if ( x1 > x2 ) swap(x1, x2);
		if ( y1 > y2 ) swap(y1, y2);
		printf("%d %d %d %d\n", x1, y1, x2, y2);
	}
    return 0;
}
