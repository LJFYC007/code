#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
typedef long long LL;

const int maxn = 5e4 + 10;

int n, f[maxn];
char s[maxn];
vector<int> a[10];

int main()
{
	freopen("delete.in", "r", stdin);
	freopen("delete.out", "w", stdout);
	scanf("%d", &n); scanf("%s", s + 1);
	REP(i, 1, n) a[s[i] - 'a'].push_back(i);
	memset(f, 0x3f, sizeof(f)); f[1] = 0;
	REP(i, 1, n - 1)
	{
		if ( s[i] == 'a' ) continue ;

	}
	return 0;
}
