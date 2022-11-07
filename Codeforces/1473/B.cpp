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

int T, n, m;
string s, t;

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &T);
	while ( T -- )
	{
		cin >> s >> t;
		if ( s.length() < t.length() ) swap(s, t);
		string f = "";
		REP(i, 1, 200) f = f + s;
		int now = 0;
		REP(i, 0, f.length() - 1)
		{
			if ( f[i] != t[now] ) { puts("-1"); goto Next; }
			++ now; if ( now == t.length() ) now = 0;
			if ( now == 0 && (i + 1) % s.length() == 0 )
			{
				REP(j, 0, i) printf("%c", f[j]);puts("");
				goto Next ;
			}
		}
		puts("-1");
		Next : ;
	}
    return 0;
}
