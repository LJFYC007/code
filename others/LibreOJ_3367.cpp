#include<bits/stdc++.h>
#include "biscuits.h"

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1e5 + 10;

int f[maxn];

int count_tastiness(int x, vector<int> a) 
{
    while ( a.size() < 62 ) a.push_back(0);
    int k = 62;
    REP(i, 0, k) f[i] = 0; f[k] = 1;
    for ( int i = k - 1; i >= 0; -- i ) 
        REP(j, i + 1, k)
        {
            int L = 0, R = (1ll << j - i) - 1, sum = 0;
            for ( int o = j - 1; o >= i; -- o ) 
            {
                sum = sum * 2 + a[o];
                int val = (sum / x + 1) << (o - i);
                if ( o > i ) L = max(L, val);
                else R = min(R, val - 1);
            }
            if ( L <= R ) f[i] += f[j] * (R - L + 1);
        }
	return f[0];
}
