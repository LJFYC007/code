#include "testlib.h"

int main() {
	registerValidation();
	int n = inf.readInt(1, 166, "n"); inf.readSpace();
	int m = inf.readInt(1, 1e6, "m"); inf.readSpace();
	int q = inf.readInt(1, 166, "q"); inf.readEoln();
	for(int i = 1;i <= m;++i) {
		int x = inf.readInt(1, n, "x_i"); inf.readSpace();
		int y = inf.readInt(1, n, "y_i"); inf.readSpace();
		int v = inf.readInt(1, 500, "v_i"); inf.readEoln();
		ensuref(x != y, " x == y ");
	}
	for(int i = 1;i <= q;++i) {
		int x = inf.readInt(1, n, "x_i"); inf.readSpace();
		int y = inf.readInt(1, n, "y_i"); inf.readSpace();
		int a = inf.readInt(1, 1e6, "a_i"); inf.readSpace();
		int k = inf.readInt(1, 15, "k_i"); inf.readEoln();
	}
	inf.readEof();
}
