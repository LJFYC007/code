#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 2e5 + 5;
int num, n; double a[MAXN];
int main(int argc, char *argv[]) {
	freopen(argv[1], "r" ,stdin);
	freopen(argv[5], "w" ,stdout);
	scanf("%d%d", &num, &n);
	freopen(argv[3], "r" ,stdin);
	for (int i = 1; i <= n; i++)
		scanf("%lf", &a[i]);
	freopen(argv[2], "r", stdin);
	for (int i = 1; i <= n; i++) {
		double x = 0; scanf("%lf", &x);
		if (abs(x - a[i]) > 1e-9) {
			printf("%d\n", 0);
			freopen(argv[6], "w" ,stdout);
			printf("Wrong Answer. Line %d Expected %.9lf, Found %.9lf.", i, a[i], x);
			return 0;
		}
	}
	int score = atoi(argv[4]);
	printf("%d\n", score);
	freopen(argv[6], "w" ,stdout);
	printf("Correct Answer.");
	return 0;
}
