#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof(a) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>

const int maxn = 1e5 + 10;

int s[maxn];

int main()
{
	freopen("A.in", "w", stdout);
	int n = 10; printf("%d\n", n);
	srand(time(0));
	int len1 = rand() % 5 + 1;
	REP(i, 1, len1) s[i] = 'A';
	REP(i, len1 + 1, n) s[i] = 'B';
	random_shuffle(s + 1, s + n + 1);
	int x = rand() % 5 + 1; s[x] = s[x + 1] = '_';
	REP(i, 1, n) printf("%c", s[i]); puts("");
	return 0;
}
