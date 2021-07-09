/***************************************************************
	File name: P2032.cpp
	Author: ljfcnyali
	Create time: 2019年06月27日 星期四 09时14分51秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 2000010;

int a[maxn], n, k;
struct node
{
    int x, val;
} p;
deque<node> Q;

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
            p = Q.back(); 
            if ( p.val < a[i] ) Q.pop_back();
            else break ; 
        }
        p.x = i; p.val = a[i];
        Q.push_back(p);
        while ( !Q.empty() ) 
        {
            p = Q.front();
            if ( p.x + k <= i ) Q.pop_front();
            else break ; 
        }
        p = Q.front();
        if ( i >= k ) printf("%d\n", p.val);
    }
    return 0;
}
