#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof(a) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>

const int maxn = 1e5 + 10;

int main()
{
	freopen("input.txt", "w", stdout);
	srand(time(0));
	int n = 3 + rand() % 3;
	int m = 3 + rand() % 3;
	REP(i, 1, n) printf("%c", rand() % 3 + 'a'); puts("");
	REP(i, 1, m) printf("%c", rand() % 3 + 'a'); puts("");
	return 0;
}
