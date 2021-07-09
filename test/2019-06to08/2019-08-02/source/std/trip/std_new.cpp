int solve(int at, int k) {
	if (at == n - 1) return k == 0 ? 1 : 0;
	int& ret = dp[at][k];
	if (ret >= 0) return ret;
	ret = 0;
	if (at == s) {
		// add left
		if (a[s] != 'L') add(ret, solve(at + 1, k));
		// add left and connect a component
		if (k > 0 && a[s] != 'R') add(ret, (int64)k * solve(at + 1, k - 1) % MOD);
		return ret;
	}
	if (at == t) {
		// add right
		add(ret, solve(at + 1, k));
		// add right and connect a component
		if (k > 0) add(ret, (int64)k * solve(at + 1, k - 1) % MOD);
		return ret;
	}
	// add a new component
	if (a[at] != 'L') add(ret, solve(at + 1, k + 1));
	// connect two components, or connect end and components
	if (a[at] != 'R') {
		if (k >= 2) add(ret, (int64)k * (k - 1) * solve(at + 1, k - 1) % MOD);
		if (k > 0 && at > t) add(ret, (int64)k * solve(at + 1, k - 1) % MOD);
		if (k > 0 && at > s) add(ret, (int64)k * solve(at + 1, k - 1) % MOD);
	}
	// touch a component from left
	if (k > 0 && a[at] != 'R') add(ret, (int64)k * solve(at + 1, k) % MOD);
	// touch a component from right
	if (k > 0 && a[at] != 'L') add(ret, (int64)k * solve(at + 1, k) % MOD);
	// touch left end
	if (at > s && a[at] != 'L') add(ret, solve(at + 1, k) % MOD);
	// touch right end
	if (at > t && a[at] != 'R') add(ret, solve(at + 1, k) % MOD);

	return ret;
}
