#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof(a) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>

const int maxn = 1e5 + 10;
const int N = 1e9;

int main()
{
	freopen("input.txt", "w", stdout);
	srand(time(0));
	int n = 5000, m = 5000; printf("%d %d\n", n, m);
	REP(i, 1, n) printf("%d %d\n", rand() % N + 1, rand() % N + 1);
	REP(i, 1, m) printf("%d\n", rand() % N + 1);
	return 0;
}
