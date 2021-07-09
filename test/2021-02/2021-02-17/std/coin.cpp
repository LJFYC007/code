#include "coin.h"
#include <string>

void guess(){
	srand(23333);
	std::string s = "";
	int cnt, ncnt, x;
	for (x = 0; x < 100; ++x) {
		s += (rand() & 1) + '0';
	}
	cnt = ask(s);
	for (x = 0; x < 100; ++x) {
		while (true) {
			s[x] ^= 1;
			ncnt = ask(s);
			if (cnt > ncnt) break;
			cnt = ncnt;
		}
		cnt = ncnt;
	}
	for (x = 0; x < 100; ++x) {
		s[x] ^= 1;
	}
	ask(s);
}

