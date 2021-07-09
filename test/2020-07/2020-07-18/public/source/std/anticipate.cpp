#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5 + 5;
const double eps = 1e-14;
typedef long long ll;
template <typename T> void read(T &x) {
	x = 0; int f = 1;
	char c = getchar();
	for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
	for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
	x *= f;
}
struct info {
	double l, r;
	int pos;
}; int n;
vector <info> L, R;
double l, r, ans[MAXN];
double x[MAXN], y[MAXN];
double slopeL(int a, int b) {
	return (y[b] - y[a]) / (x[a] - x[b]);
}
void workL() {
	L.push_back((info) {l, x[1], 0});
	static int q[MAXN], top = 1;
	double cur = x[1]; int nxt = 2; q[1] = 1;
	while (true) {
		if (top == 1 || (r - l) / (x[nxt] - l) > slopeL(q[top], q[top - 1])) {
			L.push_back((info) {cur, x[nxt], q[top]}), cur = x[nxt];
			while (top >= 1 && y[nxt] >= y[q[top]]) top--;
			while (top >= 2 && slopeL(nxt, q[top]) < slopeL(q[top], q[top - 1])) top--;
			if (top == 0 || (r - l) / (x[nxt] - l) > slopeL(nxt, q[top])) q[++top] = nxt;
			nxt++; if (nxt > n + 1) break;
		} else {
			double tmp = l + (r - l) / slopeL(q[top], q[top - 1]);
			L.push_back((info) {cur, tmp, q[top]});
			top--, cur = tmp;
		}
	}
}
double slopeR(int a, int b) {
	return (y[b] - y[a]) / (x[b] - x[a]);
}
void workR() {
	R.push_back((info) {x[n], r, 0});
	static int q[MAXN], top = 1;
	double cur = x[n]; int nxt = n - 1; q[1] = n;
	while (true) {
		if (top == 1 || (r - l) / (r - x[nxt]) > slopeR(q[top], q[top - 1])) {
			R.push_back((info) {x[nxt], cur, q[top]}), cur = x[nxt];
			while (top >= 1 && y[nxt] >= y[q[top]]) top--;
			while (top >= 2 && slopeR(nxt, q[top]) < slopeR(q[top], q[top - 1])) top--;
			if (top == 0 || (r - l) / (r - x[nxt]) > slopeR(nxt, q[top])) q[++top] = nxt;
			nxt--; if (nxt < 0) break;
		} else {
			double tmp = r - (r - l) / slopeR(q[top], q[top - 1]);
			R.push_back((info) {tmp, cur, q[top]});
			top--, cur = tmp;
		}
	}
	reverse(R.begin(), R.end());
}
void debug() {
	for (auto x : L)
		cerr << x.l << ' ' << x.r << ' ' << x.pos << endl;
	cerr << endl;
	for (auto x : R)
		cerr << x.l << ' ' << x.r << ' ' << x.pos << endl;
	cerr << endl;
}
double health(double mid, int pos) {
	if (pos == 0) return -1;
	if (abs(x[pos] - mid) <= eps) return y[pos] + (r - l);
	else if (x[pos] < mid) return y[pos] + (r - l) / (mid - l) * (x[pos] - l);
	else return y[pos] + (r - l) / (r - mid) * (r - x[pos]);
}
void work(double vl, double vr, int p, int q) {
	if (vr - vl <= eps) return;
	double ql = vl, qr = vr;
	for (int i = 1; i <= 70; i++) {
		double mid = (ql + qr) / 2;
		if (health(mid, p) > health(mid, q)) ql = mid;
		else qr = mid;
	}
	ans[p] += ql - vl;
	ans[q] += vr - qr;
}
void workM() {
	unsigned pl = 0, pr = 0; double cur = l;
	while (pl < L.size() && pr < R.size()) {
		if (L[pl].r < R[pr].r) {
			work(cur, L[pl].r, L[pl].pos, R[pr].pos);
			cur = L[pl].r, pl++;
		} else {
			work(cur, R[pr].r, L[pl].pos, R[pr].pos);
			cur = R[pr].r, pr++;
		}
	}
}
int main() {
	freopen("anticipate.in", "r", stdin);
	freopen("anticipate.out", "w", stdout);
	int num; read(num);
	read(n), read(l), read(r);
	x[n + 1] = r, y[0] = l;
	for (int i = 1; i <= n; i++)
		read(x[i]);
	for (int i = 1; i <= n; i++)
		read(y[i]);
	workL(), workR(), workM();
	for (int i = 1; i <= n; i++)
		printf("%.12lf\n", ans[i] / (r - l));
	return 0;
}