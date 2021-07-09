/***************************************************************
	File name: P1886.cpp
	Author: ljfcnyali
	Create time: 2019年06月26日 星期三 19时49分56秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 1000010;

struct node
{
    int val, x;
} p;

deque<node> Q;
int n, k, a[maxn];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &k);
    REP(i, 1, n) scanf("%d", &a[i]);
    REP(i, 1, n)
    {
        while ( !Q.empty() )
        {
            p = Q.back(); if ( p.val >= a[i] ) Q.pop_back(); else break ; 
        }
        p.val = a[i]; p.x = i; Q.push_back(p);
        while ( !Q.empty() )
        {
            p = Q.front(); if ( p.x <= i - k ) Q.pop_front(); else break ; 
        }
        p = Q.front();
        if ( i >= k ) printf("%d ", p.val);
    }
    puts("");
    while ( !Q.empty() ) Q.pop_front();
    REP(i, 1, n)
    {
        while ( !Q.empty() )
        {
            p = Q.back(); if ( p.val <= a[i] ) Q.pop_back(); else break ; 
        }
        p.val = a[i]; p.x = i; Q.push_back(p);
        while ( !Q.empty() )
        {
            p = Q.front(); if ( p.x <= i - k ) Q.pop_front(); else break ; 
        }
        p = Q.front();
        if ( i >= k ) printf("%d ", p.val);
    }
    puts("");
    return 0;
}
