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
		system("gen > input.txt");
		system("bf < input.txt > output.txt");
		system("capital_city < input.txt > output1.txt");
		if ( system("fc output1.txt output.txt") ) { cerr << "Wrong!" << endl; return 0; }
		else cerr << "Accepted." <<endl;
	}
	return 0;
}
