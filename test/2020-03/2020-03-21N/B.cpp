#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e6 + 10;

int n, a[maxn];
char s[maxn];
set<pii> Set;

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &n); scanf("%s", s + 1);
	REP(i, 1, n - 1) a[i] = abs((int)s[i] - s[i + 1]);

	int L = 1, R = n;
	while ( L <= n && a[L] == 0 ) { Set.insert(pii(L, a[L])); ++ L; }
	while ( R >= 1 && a[R] == 0 ) -- R;
	REP(i, L, R) if ( a[i] != 0 ) Set.insert(pii(i, a[i]));
	REP(i, R + 1, n) Set.insert(pii(i, a[i]));
	if ( L > n ) { puts("0"); return 0; }

	while ( Set.size() != 1 )
	{
		n = Set.size();
		set<pii> :: iterator it = Set.begin();
		REP(i, 1, n) { a[i] = (*it).second; ++ it; }
		REP(i, 1, n - 1) a[i] = abs(a[i] - a[i + 1]);

		Set.clear();
		-- n;
		L = 1; R = n;
		while ( L <= n && a[L] == 0 ) { Set.insert(pii(L, a[L])); ++ L; }
		if ( L > n ) { puts("0"); return 0; }
		while ( R >= 1 && a[R] == 0 ) -- R;
		REP(i, L, R) if ( a[i] != 0 ) Set.insert(pii(i, a[i]));
		REP(i, R + 1, n) Set.insert(pii(i, a[i]));
	}
	printf("%d\n", (*Set.begin()).second);
	return 0;
}
