#include "brackets.h"
#include<cstdio>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof(a) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>

void match(int n, int m, int s, int l) 
{
	if ( n & 1 ) return ; 
	if ( !m ) return ; 
		
	if ( n == 2 && m == 1 ) 
	{
		greater_equal(2, 0, 1);
		append(2);
		set(3, 1);
		bit_or(2, 2, 3);
		append(2);
		return ; 
	}
	if ( n == 2 ) 
	{
		plus(3, 0, 1);
		greater_equal(2, 0, 1);
		logical_or(2, 2, 3);

		append(2);
		set(3, 1);
		bit_or(2, 2, 3);
		append(2);
		return ; 
	}

	
}
