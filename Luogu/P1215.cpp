/***************************************************************
	File name: P1215.cpp
	Author: ljfcnyali
	Create time: 2019年05月06日 星期一 14时07分23秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

int A, B, C, ans[50], sum;
bool vis[30][30][30];

inline void DFS(int a, int b, int c)
{
	if ( vis[a][b][c] ) return ; 
	vis[a][b][c] = true;
	cerr << a << " " << b << " " << c << endl;
	if ( ans[c] == 0 && a == 0 ) { ans[c] = 1; ++ sum; }
	int x = a, y = b, z = c;
	a = x; b = y; c = z;
	if ( a != 0 && b != B ) { b += a; a = 0; if ( b > B ) { a = (b - B); b = B; } DFS(a, b, c); }
	a = x; b = y; c = z;
	if ( a != 0 && c != C ) { c += a; a = 0; if ( c > C ) { a = (c - C); c = C; } DFS(a, b, c); }
	a = x; b = y; c = z;
	if ( b != 0 && c != C ) { c += b; b = 0; if ( c > C ) { b = (c - C); c = C; } DFS(a, b, c); }
	a = x; b = y; c = z;
	if ( b != 0 && a != A ) { a += b; b = 0; if ( a > A ) { b = (a - A); a = A; } DFS(a, b, c); }
	a = x; b = y; c = z;
	if ( c != 0 && a != A ) { a += c; c = 0; if ( a > A ) { c = (a - A); a = A; } DFS(a, b, c); }
	a = x; b = y; c = z;
	if ( c != 0 && b != B ) { b += c; c = 0; if ( b > B ) { c = (b - B); b = B; } DFS(a, b, c); }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d%d", &A, &B, &C);
	DFS(8, 2, 0); cerr << endl;
	DFS(0, 0, C);
	REP(i, 0, 20) if ( ans[i] == 1 ) printf("%d ", i);
	puts("");
    return 0;
}
