#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset ( (a), 0, sizeof ( a ) )
#define str(a) strlen ( a )
typedef long long LL;

const int maxn = 60;

int n, l, r, a[maxn];
char s[maxn], t[maxn], ask[9][2], p[4][2], f[8][4];

inline bool check(char c) { return c == 'C' || c == 'H' || c == 'T'; }

inline char get(int c)
{
	if ( c == 1 ) return 'C';
	if ( c == 0 ) return 'H';
	if ( c == 2 ) return 'T';
}

inline bool Check()
{
	REP(i, 2, n) if ( check(s[i - 1]) && check(s[i]) ) { l = i - 1; r = i; return true; }
	return false;
}

inline void Query()
{
	printf("? %c%c\n", t[1], t[2]); fflush(stdout);
	int k; scanf("%d", &k);
	REP(j, 1, k) { int x; scanf("%d", &x); s[x] = t[1]; s[x + 1] = t[2]; }
}

int main()
{
	srand(time(0));
	ask[0][0] = ask[0][1] = ask[3][0] = ask[4][0] = ask[5][1] = ask[8][1] = 'C';
	ask[1][0] = ask[1][1] = ask[3][1] = ask[5][0] = ask[6][0] = ask[7][1] = 'H';
	ask[2][0] = ask[2][1] = ask[4][1] = ask[6][1] = ask[7][0] = ask[8][0] = 'T';
	p[0][0] = p[0][1] = p[1][0] = p[2][0] = 'T'; p[1][1] = p[3][0] = 'C'; p[2][1] = p[3][1] = 'H';
	int T; scanf("%d", &T);
	while ( T -- )
	{
	 	mem(s); scanf("%d", &n);

		if ( n > 4 )
		{
			t[1] = 'C'; t[2] = 'C'; Query();
			t[1] = 'C'; t[2] = 'H'; Query();
			t[1] = 'C'; t[2] = 'T'; Query();
			t[1] = 'H'; t[2] = 'H'; Query();
			t[1] = 'T'; t[2] = 'H'; Query();
			REP(i, 2, n - 1) if ( !check(s[i]) ) s[i] = 'T';

			if ( !check(s[1]) )
			{
				s[1] = 'T';
				printf("? "); REP(i, 1, n - 1) printf("%c", s[i]); puts(""); fflush(stdout);
				int k; scanf("%d", &k);
				REP(j, 1, k) { int x; scanf("%d", &x); }
				if ( !k ) s[1] = 'H';
			}

			if ( !check(s[n]) )
			{
				s[n] = 'T';
				printf("? "); REP(i, 1, n) printf("%c", s[i]); puts(""); fflush(stdout);
				int k; scanf("%d", &k);
				REP(j, 1, k) { int x; scanf("%d", &x); }
				if ( !k ) s[n] = 'C';
			}
			printf("! "); REP(i, 1, n) printf("%c", s[i]); puts("");
			goto Finish;
		}

	 	if ( n == 4 )
	 	{
	 		REP(i, 0, 3)
	 		{
	 			printf("? %c%c\n", p[i][0], p[i][1]);
				fflush(stdout);
				int k; scanf("%d", &k);
				REP(j, 1, k)
				{
					int x; scanf("%d", &x);
					s[x] = p[i][0]; s[x + 1] = p[i][1];
				}
				if ( Check() ) break ;
			}
	 		if ( !Check() )
	 		{
	 			printf("? HH\n"); fflush(stdout);
				int k; scanf("%d", &k);
				REP(j, 1, k) scanf("%d", &a[j]);

				if ( k == 3 ) { printf("! HHHH\n"); goto Finish; }

				if ( k == 2 )
				{
					printf("? HHHT\n"); fflush(stdout);
	 				scanf("%d", &k);
	 				if ( k ) { int x; scanf("%d", &x); printf("! HHHT\n"); goto Finish; }

	 				printf("! HHHC\n"); goto Finish;
				}

				if ( k == 1 )
				{
					printf("? HHCC\n"); fflush(stdout);
	 				scanf("%d", &k);
	 				if ( k ) { int x; scanf("%d", &x); printf("! HHCC\n"); goto Finish; }

	 				printf("! HHCT\n"); goto Finish;
				}

	 			printf("? CCC\n"); fflush(stdout);
				scanf("%d", &k);
				REP(j, 1, k) scanf("%d", &a[j]);

				if ( k == 2 ) { printf("! CCCC\n"); goto Finish; }

				if ( k == 1 && a[1] == 1 ) { printf("! CCCT\n"); goto Finish; }

				if ( k == 1 && a[1] == 2 ) { printf("! HCCC\n"); goto Finish; }

				printf("! HCCT\n"); goto Finish;
	 		}
	 	}
	 	else
	 	{
	 		REP(i, 0, 2)
	 		{
	 			int len = 6; REP(j, 1, 6) t[j] = get(i);
	 			printf("? "); REP(j, 1, len) printf("%c", t[j]); puts("");
				fflush(stdout);
				int k; scanf("%d", &k);
				REP(j, 1, k)
				{
					int x; scanf("%d", &x);
					REP(k, 1, len) s[x + k - 1] = t[k];
				}
				if ( Check() ) break ;
			}

	 		random_shuffle(ask + 3, ask + 9);
			REP(i, 3, 8)
			{
				printf("? %c%c\n", ask[i][0], ask[i][1]);
				fflush(stdout);
				int k; scanf("%d", &k);
				REP(j, 1, k)
				{
					int x; scanf("%d", &x);
					s[x] = ask[i][0]; s[x + 1] = ask[i][1];
				}
				if ( Check() ) break ;
			}
		}
		while ( l > 1 )
		{
			if ( check(s[l - 1]) ) { -- l; continue ; }
			REP(i, 0, 1)
			{
				int len = 1; t[1] = get(i); REP(j, l, r) t[++ len] = s[j];
				printf("? "); REP(j, 1, len) printf("%c", t[j]); puts("");
				fflush(stdout);
				int k; scanf("%d", &k);
				REP(j, 1, k)
				{
					int x; scanf("%d", &x);
					REP(k, 1, len) s[x + k - 1] = t[k];
				}
				if ( check(s[l - 1]) ) { -- l; goto Next2; }
			}
			s[l - 1] = get(2); -- l;
			Next2 : ;
		}
		while ( r < n )
		{
			if ( check(s[r + 1]) ) { ++ r; continue ; }
			REP(i, 0, 1)
			{
				int len = 0; REP(j, l, r) t[++ len] = s[j]; t[++ len] = get(i);
				printf("? "); REP(j, 1, len) printf("%c", t[j]); puts("");
				fflush(stdout);
				int k; scanf("%d", &k);
				REP(j, 1, k)
				{
					int x; scanf("%d", &x);
					REP(k, 1, len) s[x + k - 1] = t[k];
				}
				if ( check(s[r + 1]) ) { ++ r; goto Next1; }
			}
			s[r + 1] = get(2); ++ r;
			Next1 : ;
		}
		printf("! "); REP(i, 1, n) printf("%c", s[i]); puts("");
		Finish : ;
		fflush(stdout);
		int p; scanf("%d", &p);
	}
	return 0;
}



/*

#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset ( (a), 0, sizeof ( a ) )
#define str(a) strlen ( a )
typedef long long LL;

const int maxn = 60;

int n, l, r, m;
char s[maxn], t[maxn], ask[9][2], p[maxn][3];

inline bool check(char c) { return c == 'C' || c == 'H' || c == 'T'; }

inline char get(int c)
{
	if ( c == 0 ) return 'C';
	if ( c == 1 ) return 'H';
	if ( c == 2 ) return 'T';
}

inline bool Check()
{
	REP(i, 3, n) if ( check(s[i - 2]) && check(s[i - 1]) && check(s[i]) ) { l = i - 2; r = i; return true; }
	return false;
}

int main()
{
	srand(time(0));
	ask[0][0] = ask[0][1] = ask[3][0] = ask[4][0] = ask[5][1] = ask[8][1] = 'C';
	ask[1][0] = ask[1][1] = ask[3][1] = ask[5][0] = ask[6][0] = ask[7][1] = 'H';
	ask[2][0] = ask[2][1] = ask[4][1] = ask[6][1] = ask[7][0] = ask[8][0] = 'T';
	m = 0;
	REP(i, 0, 2) REP(j, 0, 2) REP(k, 0, 2)
	{
		if ( i == j ) continue ;
		if ( j == k ) continue ;
		++ m;
		p[m][1] = get(k); p[m][2] = get(j); p[m][3] = get(i);
	}
	int T; scanf("%d", &T);
	while ( T -- )
	{
	 	mem(s); scanf("%d", &n);
		if ( n != 4 )
		{
			REP(i, 0, 8)
			{
				printf("? %c%c\n", ask[i][0], ask[i][1]);
				fflush(stdout);
				int k; scanf("%d", &k);
				REP(j, 1, k)
				{
					int x; scanf("%d", &x);
					s[x] = ask[i][0]; s[x + 1] = ask[i][1];
				}
				if ( Check() ) break ;
			}
		}
		else
		{
			bool flag = false;
			REP(i, 0, 2)
			{
				int len = 2; t[1] = get(i); t[2] = get(i);
				printf("? "); REP(j, 1, len) printf("%c", t[j]); puts("");
				fflush(stdout);
				int k; scanf("%d", &k);
				REP(j, 1, k)
				{
					flag = true;
					int x; scanf("%d", &x);
					REP(k, 1, len) s[x + k - 1] = t[k];
				}
				if ( Check() ) goto Next;
			}
			if ( flag == true )
			{
				REP(i, 1, n - 1) if ( check(s[i]) && check(s[i + 1]) )
				{
					l = i; r = i + 1;
					goto Next;
				}
			}
			if ( !Check() )
			{
				REP(i, 1, m)
				{
					printf("? "); REP(j, 1, 3) printf("%c", p[i][j]); puts("");
					fflush(stdout);
					int k; scanf("%d", &k);
					if ( k )
					{
						int x; scanf("%d", &x);
						REP(j, 1, 3) s[x + j - 1] = p[i][j];
					}
					if ( Check() ) break ;
				}
			}
		}
		Next : ;
		while ( l > 1 )
		{
			if ( check(s[l - 1]) ) { -- l; continue ; }
			REP(i, 0, 1)
			{
				int len = 1; t[1] = get(i); REP(j, l, r) t[++ len] = s[j];
				printf("? "); REP(j, 1, len) printf("%c", t[j]); puts("");
				fflush(stdout);
				int k; scanf("%d", &k);
				REP(j, 1, k)
				{
					int x; scanf("%d", &x);
					REP(k, 1, len) s[x + k - 1] = t[k];
				}
				if ( check(s[l - 1]) ) { -- l; goto Next2; }
			}
			s[l - 1] = get(2); -- l;
			Next2 : ;
		}
		while ( r < n )
		{
			if ( check(s[r + 1]) ) { ++ r; continue ; }
			REP(i, 0, 1)
			{
				int len = 0; REP(j, l, r) t[++ len] = s[j]; t[++ len] = get(i);
				printf("? "); REP(j, 1, len) printf("%c", t[j]); puts("");
				fflush(stdout);
				int k; scanf("%d", &k);
				REP(j, 1, k)
				{
					int x; scanf("%d", &x);
					REP(k, 1, len) s[x + k - 1] = t[k];
				}
				if ( check(s[r + 1]) ) { ++ r; goto Next1; }
			}
			s[r + 1] = get(2); ++ r;
			Next1 : ;
		}
		printf("! "); REP(i, 1, n) printf("%c", s[i]); puts("");
		fflush(stdout);
		int p; scanf("%d", &p);
	}
	return 0;
}

*/
