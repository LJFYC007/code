#include "rabbit.h"
#include <bits/stdc++.h>

using namespace std;

#define int long long
#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 

typedef long long ll;

void catch_rabbit(ll n, ll k)
{
    srand(time(0));
    int L = 1, R = n;
    while ( L <= R ) 
    {
        int Mid = L + R >> 1; 
        if ( (R - L + 1) / 2 + k + k + 1 >= R - L + 1 ) 
        {
            int x = rand() % (R - L + 1) + L;
            ask(x, x);
            L -= k; R += k;
        }
        else 
        {
            int x = rand() % 2;
            if ( x == 0 ) 
            {
                if ( ask(L, Mid) ) { R = Mid + k; L -= k; }
                else { L = Mid + 1 - k; R += k; }
            }
            else
            {
                if ( ask(Mid + 1, R) ) { L = Mid + 1 - k; R += k; }
                else { R = Mid + k; L -= k; }
            }
        }
    }
	return;
}
