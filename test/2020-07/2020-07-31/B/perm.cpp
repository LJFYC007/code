#include<bits/stdc++.h>
#include "perm.h"

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>

vector<int> unsure, lst, nxt;
int num[410];
vector<int> A, B;

inline pii Find(int n, int p, int q, pii a, pii b)
{
    for ( int i = -1; i <= 1; i += 2 ) for ( int j = -1; j <= 1; j += 2 ) 
    {
        int val1 = p + i * a.first;
        int val2 = q + j * a.second;
        if ( val1 < 1 || val1 > n || val2 < 1 || val2 > n ) continue ;
        if ( abs(q - val1) == b.first && abs(p - val2) == b.second ) return pii(val1, val2);
        if ( abs(q - val1) == b.second && abs(p - val2) == b.first ) return pii(val1, val2);
    }
    return pii(-1, -1);
}

inline pii Check(int n, int p, int q, vector<int> a)
{
    swap(a[p], a[q]); nxt = query(a); swap(a[p], a[q]);
    REP(i, 1, n) num[i] = 0;
    REP(i, 0, n - 1) { ++ num[lst[i]]; -- num[nxt[i]]; }
    A.clear(); B.clear();
    REP(i, 0, n) 
    {
        while ( num[i] > 0 ) { -- num[i]; A.push_back(i); }
        while ( num[i] < 0 ) { ++ num[i]; B.push_back(i); }
    }
    // for ( auto i : lst ) printf("%d ", i); puts("");
    // for ( auto i : nxt ) printf("%d ", i); puts("");
    for ( auto i : A ) printf("%d ", i); puts("");
    for ( auto i : B ) printf("%d ", i); puts("");
    if ( A.size() != 2 || B.size() != 2 ) return pii(-1, -1);

    pii x = Find(n, a[p], a[q], pii(A[0], A[1]), pii(B[0], B[1]));
    pii y = Find(n, a[p], a[q], pii(A[1], A[0]), pii(B[0], B[1]));

    cerr << x.first << " " << x.second << endl;
    cerr << y.first << " " << y.second << endl;
    if ( x.first != -1 ) return x;
    if ( y.first != -1 ) return y;
    return pii(-1, -1);
}

vector<int> guess(int n)
{
    // srand(time(0));
	vector<int> a; a.resize(n);
    REP(i, 0, n - 1) a[i] = i + 1;
    REP(i, 0, n - 1) unsure.push_back(i);

    lst = query(a);

    while ( unsure.size() > 1 ) 
    {
        int p = rand() % unsure.size(), q = rand() % unsure.size(); 
        while ( p == q ) q = rand() % unsure.size();

        p = unsure[p]; q = unsure[q];
        pii x = Check(n, p, q, a);
        if ( x.first != -1 )
        {
            a[p] = x.first; a[q] = x.second;
            cerr << x.first << " " << x.second << endl;
            unsure.erase(-- upper_bound(unsure.begin(), unsure.end(), p));
            unsure.erase(-- upper_bound(unsure.begin(), unsure.end(), q));
            lst = query(a);
        }
    }

	return a;
}
