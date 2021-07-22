/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2021年07月21日 星期三 08时34分05秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int n, T, a[maxn];
bool vis[maxn], flag;
int ans[51][51] = {{},{},{},{54,36,18},{72,48,18,6},{90,60,20,9,1},{108,81,54,36,27,18},{126,84,28,7,4,2,1},{144,108,72,54,48,3,2,1},{162,108,18,12,9,6,4,3,2},{180,144,120,90,80,72,24,6,3,1},{196,147,98,84,28,14,7,6,4,3,1},{216,180,135,120,108,90,72,60,54,40,4,1},{225,180,150,100,90,75,50,15,5,4,3,2,1},{252,210,180,140,126,105,90,84,45,18,4,3,2,1},{270,216,180,135,120,108,12,10,8,6,5,4,3,2,1},{288,240,180,160,144,120,96,90,80,18,9,5,4,3,2,1},{300,240,200,150,120,100,24,15,12,10,8,6,5,4,3,2,1},{324,270,180,162,135,108,90,81,60,54,45,36,30,27,12,3,2,1},{336,288,252,224,168,144,126,112,96,84,72,63,28,7,6,4,3,2,1},{360,315,280,252,210,180,168,140,126,120,105,90,84,63,12,5,4,3,2,1},{378,315,270,210,189,135,126,105,45,27,18,15,14,10,9,7,6,5,3,2,1},{384,320,240,192,160,128,120,96,80,64,40,30,15,12,10,8,6,5,4,3,2,1},{405,324,270,135,108,81,54,45,36,30,27,20,18,15,12,10,9,6,5,4,3,2,1},{432,378,336,252,216,189,168,144,126,112,108,84,72,63,56,54,48,42,36,28,27,24,21,8},{450,360,300,225,75,72,50,40,36,30,25,24,20,18,15,12,10,9,8,6,5,4,3,2,1},{450,360,300,180,75,72,50,45,40,36,30,25,24,20,18,15,12,10,9,8,6,5,4,3,2,1},{480,420,336,280,240,224,210,168,160,140,120,112,105,96,84,80,42,15,12,8,7,6,5,4,3,2,1},{504,432,378,336,252,216,189,168,144,72,63,56,42,27,24,21,18,16,14,12,9,8,7,6,4,3,2,1},{504,432,378,336,252,216,189,168,126,63,56,54,42,36,27,24,21,18,16,14,12,9,8,7,6,4,3,2,1},{540,480,432,360,288,270,240,216,180,160,144,135,120,108,96,90,80,72,60,54,48,45,40,36,10,6,4,3,2,1},{540,480,432,360,288,270,240,216,180,160,144,135,120,108,96,90,80,72,60,54,48,45,40,32,9,6,5,4,3,2,1},{576,504,448,336,288,252,224,192,168,144,126,112,96,84,72,64,63,56,48,42,36,28,21,12,9,8,7,6,4,3,2,1},{576,504,448,336,288,252,224,192,168,144,126,112,96,84,72,64,63,56,48,42,32,21,18,14,12,9,8,7,6,4,3,2,1},{600,525,420,350,300,280,210,200,175,168,150,140,120,105,100,84,56,40,25,24,21,20,15,14,12,10,8,7,6,5,4,3,2,1},{630,560,504,420,360,336,315,280,252,240,210,180,168,144,140,72,30,28,21,20,18,16,15,14,12,10,9,8,7,6,5,4,3,2,1},{630,560,504,420,360,336,315,280,252,240,210,180,168,144,140,48,30,28,24,21,20,18,16,15,14,12,10,9,8,7,6,5,4,3,2,1},{630,560,504,420,360,336,315,280,252,240,210,180,168,144,112,40,36,30,28,24,21,20,18,16,15,14,12,10,9,8,7,6,5,4,3,2,1},{672,560,280,224,210,168,160,112,105,96,84,80,70,60,56,48,42,40,35,32,30,28,24,21,20,16,15,14,12,10,8,7,6,5,4,3,2,1},{700,600,525,300,280,210,175,168,150,140,105,100,84,75,70,60,56,50,42,40,35,30,28,25,24,21,20,15,14,12,10,8,7,6,5,4,3,2,1},{720,640,576,480,384,360,320,288,240,192,180,160,144,128,120,96,90,80,72,64,60,48,45,40,36,32,30,24,20,18,16,15,12,9,6,5,4,3,2,1},{720,640,576,480,384,360,320,288,240,192,180,160,144,128,120,96,90,80,72,64,60,48,45,40,36,32,30,24,20,16,15,12,10,9,8,6,5,4,3,2,1},{720,630,560,504,420,360,336,315,180,105,90,72,70,63,60,56,48,45,42,40,36,35,30,28,24,21,20,18,16,15,14,12,10,9,8,7,6,5,4,3,2,1},{720,630,560,504,420,360,336,280,126,120,84,80,72,70,63,60,56,48,45,42,40,36,35,30,28,24,21,20,18,16,15,14,12,10,9,8,7,6,5,4,3,2,1},{720,630,560,504,420,360,336,180,144,112,90,84,80,72,70,63,60,56,48,45,42,40,36,35,30,28,24,21,20,18,16,15,14,12,10,9,8,7,6,5,4,3,2,1},{720,630,560,504,420,360,210,180,144,126,112,90,84,80,72,70,63,60,56,48,45,42,40,36,35,30,28,24,21,20,18,16,15,14,12,10,9,8,7,6,5,4,3,2,1},{720,630,560,504,420,315,210,144,126,120,112,105,90,84,80,72,70,63,60,56,48,45,42,40,36,35,30,28,24,21,20,18,16,15,14,12,10,9,8,7,6,5,4,3,2,1},{840,756,630,540,504,420,378,360,315,280,270,252,216,210,189,180,168,140,135,126,120,60,54,42,40,36,35,30,28,27,24,21,20,18,15,14,12,10,9,8,7,6,5,4,3,2,1},{840,756,630,540,504,420,378,360,315,280,270,252,216,210,189,180,168,140,135,126,72,63,54,45,42,40,36,35,30,28,27,24,21,20,18,15,14,12,10,9,8,7,6,5,4,3,2,1},{840,756,630,540,504,420,378,360,315,280,270,252,216,210,189,180,168,140,135,72,70,63,56,54,45,42,40,36,35,30,28,27,24,21,20,18,15,14,12,10,9,8,7,6,5,4,3,2,1},{840,756,630,540,504,420,378,360,315,280,270,252,216,210,189,180,140,135,108,72,70,63,60,56,54,45,42,40,36,35,30,28,27,24,21,20,18,15,14,12,10,9,8,7,6,5,4,3,2,1}};

inline int Get(int l, int r) { return (l + r) * (r - l + 1) / 2; }

inline void DFS(int lst, int x, int val, int sum)
{
	if ( flag ) return ; 
	if ( Get(lst - n + x - 1, lst) + sum < val ) return ;
	if ( x > 5 && Get(1, n - x + 1) + sum > val ) return ;
	if ( x == n + 1 ) 
	{
		if ( val != sum ) return ; 
		printf("{");
		REP(i, 1, n - 1) printf("%d,", a[i]);
		printf("%d},", a[n]);
		flag = true; return ;
	}
	for ( int i = lst; i >= 1; -- i ) if ( !vis[i] ) 
	{
		a[x] = i;
		DFS(i - 1, x + 1, val * i / __gcd(val, i), sum + i);
	}
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d", &n, &T);	
	if ( n == 1 ) { puts("1"); return 0; } 
	if ( n == 2 ) { puts("-1"); return 0; } 
	if ( T == 1 ) 
	{
		if ( n % 2 == 1 ) 
		{
			printf("%d 2 ", n);
			REP(i, 1, n - 2) printf("1 "); puts("");
		}
		else
		{
			printf("%d %d 1 ", n, n - 1);
			REP(i, 1, n - 3) printf("%d ", n); puts("");
		}
		return 0;
	}

	/*
	REP(i, 11, 1000) if ( !vis[i] ) 
	{
		vis[i] = true;
		for ( int j = 2; j * j <= i; ++ j ) if ( i % j == 0 ) vis[i] = false;
		if ( vis[i] ) { for ( int j = i; j <= 1000; j += i ) vis[j] = true; }
	}
	REP(m, 3, 50)
	{
		n = m; flag = false;
		cerr << n << endl;
		DFS(n * 18, 1, 1, 0);
	}
	*/
	REP(i, 0, n - 1) printf("%d ", ans[n][i]); puts("");
	/*
	REP(m, 3, 50)
	{
		int sum = 0, val = 1;
		REP(j, 0, m - 1) { sum += ans[m][j]; val = val * ans[m][j] / __gcd(val, ans[m][j]); }
		assert(sum == val);
	}
	*/
    return 0;
}
