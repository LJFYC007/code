/***************************************************************
	File name: bf.cpp
	Author: ljfcnyali
	Create time: 2021年04月02日 星期五 08时45分01秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 310;

int n, m, a[maxn][maxn];
char s[maxn];
map<vector<int>, bool> Map1, Map2;

inline bool Solve2(vector<int> p);

inline bool Solve1(vector<int> p)
{
	sort(p.begin(), p.end());
	if ( Map1.count(p) ) return Map1[p];
	bool flag = false; int t = -1;
	for ( int i = 0; i < p.size(); ++ i ) if ( s[p[i]] == 'W' )
	{
		int it = p[i];
		vector<int> q; for ( int j = 0; j < p.size(); ++ j ) if ( i != j ) q.push_back(p[j]);
		REP(i, 1, n) if ( a[it][i] )
		{
			q.push_back(i);
			flag |= Solve2(q) ^ 1;
			if ( !Solve2(q) ) t = it;
			q.pop_back();
		}
	}
	// cout << t << " ";
	// if ( flag ) cout << "YES "; else cout << "NO ";
	// for ( auto it : p ) cout << it << " "; cout << endl;
	Map1[p] = flag ; return flag;
}

inline bool Solve2(vector<int> p)
{
	sort(p.begin(), p.end());
	if ( Map2.count(p) ) return Map2[p];
	bool flag = false;
	for ( int i = 0; i < p.size(); ++ i ) if ( s[p[i]] == 'B' )
	{
		int it = p[i];
		vector<int> q; for ( int j = 0; j < p.size(); ++ j ) if ( i != j ) q.push_back(p[j]);
		REP(i, 1, n) if ( a[it][i] )
		{
			q.push_back(i);
			flag |= Solve1(q) ^ 1;
			q.pop_back();
		}
	}
	Map2[p] = flag ; return flag;
}

int main()
{
    freopen("gametwice.in", "r", stdin);
    freopen("gametwice1.out", "w", stdout);
	scanf("%d%d", &n, &m); scanf("%s", s + 1);
	REP(i, 1, m) { int u, v; scanf("%d%d", &u, &v); a[u][v] = true; } 

	int ans = 0;
	REP(i, 0, (1 << n) - 1)
	{
		vector<int> p; REP(j, 1, n) if ( (i >> j - 1) & 1 ) p.push_back(j);
		// bool x = Solve1(p);
		// if ( x ) { for ( auto it : p ) cout << it << " "; cout << endl; } 
		ans += Solve1(p);
	}
	printf("%d\n", ans);
    return 0;
}
