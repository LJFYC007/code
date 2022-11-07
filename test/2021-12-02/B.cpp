#include<bits/stdc++.h>
#include "integer.h"

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset ( (a), 0, sizeof ( a ) )
#define str(a) strlen ( a )
#define pii pair<int, int>
typedef long long LL;


namespace Std
{

const int maxn = 1e5 + 10;
int p[maxn], n, num, cnt;

inline int Get(int x) { int ret = 0; while ( x & 1 ) { ++ ret; x >>= 1; } return ret; }

inline void Solve()
{
	vector<int> a, b; REP(i, 0, n - 1) if ( p[i] == -1 ) a.push_back(i); else b.push_back(i);
	if ( !a.size() ) return ;
	random_shuffle(a.begin(), a.end());
	int sum = operate(a[0]), x = n + Get(cnt) - (num - sum + 1); 
	//cerr << endl << num << " ";
	num = sum;
	p[a[0]] = x; int lst = a[0];
	//cerr << a[0] << " " << x << endl;
	for ( int i = 1; i < a.size(); ++ i ) 
	{
		sum = operate(a[i]); 
		if ( sum == num + 1 ) { ++ num; continue ; }
		else
		{
			x = x - (num - sum + 1);
			p[a[i]] = x; lst = a[i];
			//cerr << endl  << "Fuck " << a[i] << " " << x << endl;
			num = sum;
		}
	}
	operate(lst); ++ num; ++ cnt; 
	for ( auto it : b ) if ( p[it] > p[lst] ) num = operate(it);
	Solve();
}

}

vector<int> findPermutation (int N) 
{
	Std :: n = Std :: num = N; REP(i, 0, N - 1) { Std :: p[i] = -1; operate(i); }
	Std :: Solve();
	vector<int> ans; REP(i, 0, N - 1) ans.push_back(Std :: p[i]);
	return ans;
}