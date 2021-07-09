#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1010;

int main()
{
	for ( int i = 1; ; ++ i )
	{
		cerr << " The result of " << i << " is ";
		system("gen > tried.in");
		system("tried < tried.in > tried.out");
		system("1 < tried.in > tried1.out");
		if ( system("fc tried.out tried1.out") ) { cerr << "Wrong!" << endl; return 0; }
		else cerr << "Accepted." <<endl;
	}
	return 0;
}
