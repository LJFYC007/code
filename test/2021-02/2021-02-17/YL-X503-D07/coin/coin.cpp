/***************************************************************
	File name: coin.cpp
	Author: ljfcnyali
	Create time: 2021年02月17日 星期三 11时02分23秒
***************************************************************/
#include<bits/stdc++.h>
#include "coin.h"

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

vector<int> p;

inline char rev(char c) { return c == '0' ? '1' : '0'; }

void guess()
{
	srand(time(0)); p.clear();
	std::string s = ""; REP(i, 1, 100) s += rand() % 2 ? '1' : '0'; 
	REP(i, 0, 99) p.push_back(i);	
	int lst = ask(s);
	while ( p.size() ) 
	{
		random_shuffle(p.begin(), p.end());
		int pos = p.back(), num = 0;	
		while ( 1 ) 
		{
			s[pos] = rev(s[pos]);
			int now = ask(s); ++ num;
			if ( now == 0 ) goto Finish; 
			if ( now < lst ) { p.pop_back(); lst = now; break ; }
			lst = now;
		}
	}
Finish : ;
	REP(i, 0, 99) s[i] = rev(s[i]);
	ask(s);
}
