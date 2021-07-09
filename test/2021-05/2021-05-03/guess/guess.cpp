#include<bits/stdc++.h>
using namespace std;
#include "guess.h"

#define ull unsigned long long 
#define pii pair<ull, ull>
#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
const ull N = 14;

inline bool Check(ull l, ull r) { vector<pii> p; p.push_back(pii(l, r)); return Query(p); }

int p[4];

inline ull Solve(ull L, ull R)
{
	while ( L < R ) 
	{
		ull Mid = R - (R - L) / 2 - 1; int num = 0;
        while ( 1 ) 
        {
            if ( num < 0 || (num == 0 && rand() % 2 == 0) )
            {
				ull x = Mid; if ( (R - L) % 2 == 0 ) ++ x;
                if ( Check(L, x) ) { R = x; break ; } 
                ++ num; 
            }
            else
            {
                if ( Check(Mid + 1, R) ) { L = Mid + 1; break ; }
                -- num;
            }
        }
	}
	return L;
}

inline ull Get(ull L, ull R); 
inline ull solve(ull L, ull R, int num)
{
	if ( num == 3 ) return Check(L, R) ? Get(L, R) : 0;
	if ( rand() & 1 ) 
	{
		ull Mid = L + (R - L) / 2;
		return Check(L, Mid) ? Get(L, Mid) : solve(Mid + 1, R, num + 1);
	}
	else
	{
		ull Mid = R - (R - L) / 2;
		return Check(Mid, R) ? Get(Mid, R) : solve(L, Mid - 1, num + 1);
	}
}

inline ull Get(ull L, ull R)
{
	if ( R - L + 1 <= N ) return Solve(L, R);
	ull x = 0; while ( !x ) x = solve(L, R, 0); return x;
}

ull Guess()
{
	ull L = 10, R = -11; srand(time(0));
	return Get(L, R);
}

