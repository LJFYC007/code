#include "testlib.h"
#include <bitset>
#include <libgen.h>
#ifdef FY
#include <ctime>
#endif
#define EB emplace_back
#define SRZ (valid_identifier_char[(u8)token.front()] && !is_reserved_word(token))
#define DAK error_info(in).c_str()
using std::vector;
using std::pair;
using std::map;
using std::string;

typedef unsigned char u8;
typedef unsigned int u32;
typedef unsigned long long u64;
const int N = 100054, IMPLIES = -1, NOT = -2;

struct expression : vector <int> {
	expression () {}
	expression (const std::initializer_list <int> &il) : vector <int> (il) {}
	inline u64 hash() const {
		u64 ret = 0;
		for (int x : *this)
			ret ^= ret << 11,
			ret ^= ret >> 45,
			ret ^= ret << 14,
			ret ^= 1027341528ull * 1473200830ull,
			ret += 417288081ull * x;
		return ret;
	}
	expression substitute(const vector <expression> &) const;
};

// use Reverse Polish notation to storage
struct function {
	int n;
	vector <expression> A, C;
	function () {}
	function (int n_arguments, const vector <expression> &assumptions, const vector <expression> &conclusions) :
		n(n_arguments), A(assumptions), C(conclusions) {}
	inline void clear() {n = 0, A.clear(), C.clear();}
	inline string describe() const {
		switch (n) {
			case 1: return " A ";
			case 2: return " A, B ";
			case 3: return " A, B, C ";
			default: return " <" + vtos(n) + " variables> ";
		}
	}
} f[N], g[N];

u64 LENGTH_TOTAL;
int n_functions, m_functions, n_args;
map <string, int> name_map, arg_map;
vector <expression> apply_args;
string I[N];
 
bool valid_identifier_char[256];

string error_info(InStream &in) {
	int L = in.name.size();
	char *p = new char[L + 5]; memcpy(p, in.name.c_str(), L), p[L] = 0;
	string info = "[ERROR]\n" + string(basename(p)) + ":" + vtos(in.reader->getLine()) + ": error: ";
	return delete [] p, info;
}

expression expression::substitute(const vector <expression> &args) const {
	expression ret;
	for (int x : *this)
		if (x >= 0) ret.insert(ret.end(), args[x].begin(), args[x].end());
		else ret.EB(x);
	return ret;
}

namespace logistic {
	const int P = 2003731;

	map <string, expression> macros;
	vector <expression> truths[P];
	std::bitset <P> used;

	void init() {
		macros.clear();
		for (int i = used._Find_first(); i != P; i = used._Find_next(i)) truths[i].clear();
		used.reset();
	}

	inline bool check_truth(const expression &expr) {
#ifdef FY
		LENGTH_TOTAL += expr.size();
#endif
		int pos = expr.hash() % P;
		for (const expression &truth : truths[pos])
			if (expr == truth) return true;
		return false;
	}

	inline void add_truth(const expression &expr) {
		if (check_truth(expr)) return;
		int pos = expr.hash() % P;
		truths[pos].EB(expr), used.set(pos);
	}

	inline void init_assumptions() {for (const expression &expr : f[n_functions - 1].A) add_truth(expr);}

	void apply(int id, const vector <expression> &args, const string &fn, InStream &in) {
		int i = 0, n = f[id].n;
		if ((int)args.size() < n)
			in.quitf(_pe, "%stoo few arguments to apply theorem '%s [%s]'", DAK, fn.c_str(), f[id].describe().c_str());
		if ((int)args.size() > n)
			in.quitf(_pe, "%stoo many arguments to apply theorem '%s [%s]'", DAK, fn.c_str(), f[id].describe().c_str());
		for (const expression &assumption : f[id].A)
			if (++i, !check_truth(assumption.substitute(args)))
				in.quitf(_wa, "%sassumption #%d of applying theorem '%s [%s]' is not deduced", DAK, i, fn.c_str(), f[id].describe().c_str());
		for (const expression &conclusion : f[id].C)
			add_truth(conclusion.substitute(args));
	}

	void check(const string &fn, InStream &in) {
		int id = 0;
		for (const expression &expr : f[n_functions - 1].C)
			if (++id, !check_truth(expr))
				in.quitf(_wa, "%sconclusion #%d of theorem '%s [%s]' is not deduced", DAK, id, fn.c_str(), f[n_functions - 1].describe().c_str());
	}

}

namespace tokenizer {
	string next_token(InStream &in) {
		string ret; int c;
		for (; ; ) {
			if (in.eof()) return ret;
			c = in.nextChar();
			if (c == 9 || c == 10 || c == 13 || c == 32) {
				if (ret.empty()) continue;
				else return ret;
			} else if (32 < c && c < 127) {
				if (valid_identifier_char[c]) ret.push_back(c);
				else if (ret.empty()) return string(1, c);
				else return in.unreadChar(c), ret;
			} else
				in.quitf(_pe, "%sstray '\\%03o' in program", DAK, c & 255);
		}
	}
}

namespace parser {
	enum type {
		LB,
		IMPLIES,
		NOT
	};

	int top, nlb;
	type stack[N];
	expression result;

	inline bool empty() {return !top && result.empty();}
	inline bool complete() {return !nlb;}
	inline void clear() {top = nlb = 0, result.clear();}
	void forward() {
		for (; top; )
			switch (stack[--top]) {
				case LB:	  __testlib_fail("error code 1");	break;
				case IMPLIES: result.EB(::IMPLIES); 			break;
				case NOT:	  result.EB(::NOT);					break;
			}
		if (top) __testlib_fail("error code 2");
/*
		fputs("expr = [", stderr);
		for (int x : result)
			if (x == -1) fputs("-> ", stderr);
			else if (x == -2) fputs("! ", stderr);
			else fprintf(stderr, "%d ", x);
		fprintf(stderr, "], hash = %016llx\n", result.hash());
*/
	}

	inline void push_left_bracket() {stack[top++] = LB, ++nlb;}
	inline bool push_right_bracket() {
		bool found = false;
		for (; top && !found; )
			switch (stack[--top]) {
				case LB:	  found = true, --nlb;	break;
				case IMPLIES: result.EB(::IMPLIES); break;
				case NOT:	  result.EB(::NOT);		break;
			}
		return found;
	}
	inline void push_not() {stack[top++] = NOT;}
	inline void push_var(int x) {result.EB(x);}
	inline void push_macro(const expression &expr) {result.insert(result.end(), expr.begin(), expr.end());}
	inline void push_implies() {
		for (; top && stack[top - 1] == NOT; --top) result.EB(::NOT);
		stack[top++] = IMPLIES;
	}
}

namespace processor {
	enum State {
		MAIN,
		WAITING_LBRACK,
		WAITING_LBRACK2,
		WAITING_LBRACE,
		NAME,
		ARGUMENT,
		COMMA,

		ASSUMPTIONS_HEADER,
		PROOF_CASUAL,
		EQUAL_OR_LBRACK,

		ASSUMPTIONS_COLON,
		CONCLUSIONS_COLON,
		PROOF_COLON,

		EXPECTED_VAR,
		EXPECTED_SYMBOL
	};

	enum Substate {
		ASSUMPTIONS,
		CONCLUSIONS,
		MACRO,
		APPLY,
	};

	inline bool is_reserved_word(const string &s) {return s == "assumptions" || s == "conclusions" || s == "proof";}

	void read(InStream &in, bool is_input = false) {
		State state = MAIN;
		Substate substate = ASSUMPTIONS;
		string token, key, fn;
		expression expr;
		int apply_id = -1;
		map<string, int>::iterator it;
		map<string, expression>::iterator jt;
		bool ret;
		for (; ; ) {
			token = tokenizer::next_token(in);
			if (token == "/") {
				for (in.readChar('/'); ; ) {
					if (in.eof()) break;
					int ch = in.nextChar();
					if (ch == LF) break;
				}
				continue;
			}
			switch (state) {
				case MAIN: {
					if (token.empty()) return;
					if (token != "`") in.quitf(_pe, "%sexpected '`' before '%s' token", DAK, token.c_str());
					logistic::init(), state = NAME;
					break;
				}
				case WAITING_LBRACK: {
					if (token.empty()) in.quitf(_pe, "%sexpected '[' at end of input", DAK);
					if (token != "[") in.quitf(_pe, "%sexpected '[' before '%s' token", DAK, token.c_str());
					state = ARGUMENT;
					break;
				}
				case WAITING_LBRACE: {
					if (token.empty()) in.quitf(_pe, "%sexpected '{' at end of input", DAK);
					if (token != "{") in.quitf(_pe, "%sexpected '{' before '%s' token", DAK, token.c_str());
					state = ASSUMPTIONS_HEADER;
					break;
				}
				case EQUAL_OR_LBRACK: {
					if (token.empty()) in.quitf(_pe, "%sexpected '=' or '[' at end of input", DAK);
					if (token == "=") {
						if (name_map.count(key) || arg_map.count(key) || logistic::macros.count(key))
							in.quitf(_pe, "%smacro '%s' redeclared as different kind of symbol", DAK, key.c_str());
						parser::clear(), state = EXPECTED_VAR, substate = MACRO;
					} else if (token == "[") {
						it = name_map.find(key);
						if (it == name_map.end() || it->second == n_functions - 1 || key == fn) in.quitf(_pe, "%s'%s' is not declared in this scope", DAK, key.c_str());
						apply_id = it->second, apply_args.clear();

						parser::clear(), state = EXPECTED_VAR, substate = APPLY;
					} else in.quitf(_pe, "%sexpected '=' or '[' before '%s' token", DAK, token.c_str());
					break;
				}
				case NAME:
				case ARGUMENT:
				case PROOF_CASUAL: {
					if (state == PROOF_CASUAL && token == "}") {logistic::check(fn, in), state = MAIN; continue;}
					if (token.empty()) in.quitf(_pe, "%sexpected %s at end of input", DAK, state == PROOF_CASUAL ? "'}'" : "identifier");
					if (!SRZ) in.quitf(_pe, "%sexpected identifier before '%s' token", DAK, token.c_str());
					switch (state) {
						case NAME:
							std::tie(it, ret) = name_map.emplace(fn = token, n_functions++);
							if (!ret) in.quitf(_pe, "%sredefinition of theorem '%s [%s]'", DAK, token.c_str(), f[it->second].describe().c_str());
							f[n_functions - 1].clear(), arg_map.clear(), state = WAITING_LBRACK;
							break;
						case ARGUMENT:
							if (name_map.count(token)) in.quitf(_pe, "%sargument '%s' redeclared as different kind of symbol", DAK, token.c_str());
							std::tie(it, ret) = arg_map.emplace(token, f[n_functions - 1].n++);
							if (!ret) in.quitf(_pe, "%sredefinition of argument '%s'", DAK, token.c_str());
							state = COMMA;
							break;
						case PROOF_CASUAL:
							key = token, state = EQUAL_OR_LBRACK;
							break;
					}
					break;
				}
				case COMMA: {
					if (token.empty()) in.quitf(_pe, "%sexpected ',' or ']' at end of input", DAK);
					if (token == ",") state = ARGUMENT;
					else if (token == "]") state = WAITING_LBRACE;
					else in.quitf(_pe, "%sexpected ',' or ']' before '%s' token", DAK, token.c_str());
					break;
				}
				case ASSUMPTIONS_HEADER: {
					if (token.empty()) in.quitf(_pe, "%sexpected 'assumptions' at end of input", DAK);
					if (token != "assumptions") in.quitf(_pe, "%sexpected 'assumptions' before '%s' token", DAK, token.c_str());
					state = ASSUMPTIONS_COLON;
					break;
				}
				case ASSUMPTIONS_COLON:
				case CONCLUSIONS_COLON:
				case PROOF_COLON: {
					if (token.empty()) in.quitf(_pe, "%sexpected ':' at end of input", DAK);
					if (token != ":") in.quitf(_pe, "%sexpected ':' before '%s' token", DAK, token.c_str());
					if (state == ASSUMPTIONS_COLON)
						parser::clear(), state = EXPECTED_VAR, substate = ASSUMPTIONS;
					else if (state == CONCLUSIONS_COLON)
						parser::clear(), state = EXPECTED_VAR, substate = CONCLUSIONS;
					else
						parser::clear(), state = PROOF_CASUAL, logistic::init_assumptions();
					break;
				}
				case EXPECTED_VAR: {
					if (token == "(")
						parser::push_left_bracket();
					else if (token == "!")
						parser::push_not();
					else if (SRZ) {
						it = arg_map.find(token);
						if (it != arg_map.end()) parser::push_var(it->second);
						else {
							jt = logistic::macros.find(token);
							if (jt != logistic::macros.end()) parser::push_macro(jt->second);
							else in.quitf(_pe, "%s'%s' is not declared in this scope", DAK, token.c_str());
						}
						state = EXPECTED_SYMBOL;
					} else {
						if (parser::empty()) {
							if (substate == MACRO || substate == APPLY) {
								if (token.empty()) in.quitf(_pe, "%sexpected primary-expression at end of input", DAK);
								in.quitf(_pe, "%sexpected primary-expression before '%s' token", DAK, token.c_str());
							}
#define SRZ_TRANSFORM		switch (substate) {																				\
								case ASSUMPTIONS:																			\
									if (token == "conclusions") {															\
										state = CONCLUSIONS_COLON; continue;												\
									} else if (token == "}" || is_reserved_word(token))										\
										in.quitf(_pe, "%sexpected 'conclusions' before '%s' token", DAK, token.c_str());	\
									else if (token.empty())																	\
										in.quitf(_pe, "%sexpected 'conclusions' at end of input", DAK); 					\
									break;																					\
								case CONCLUSIONS:																			\
									if (is_input) {																			\
										if (token == "}") {																	\
											state = MAIN; continue; 														\
										} else if (is_reserved_word(token))													\
											in.quitf(_pe, "%sexpected '}' before '%s' token", DAK, token.c_str());			\
										else if (token.empty())																\
											in.quitf(_pe, "%sexpected '}' at end of input", DAK);							\
									} else {																				\
										if (token == "proof") {																\
											state = PROOF_COLON; continue;													\
										} else if (token == "}" || is_reserved_word(token))									\
											in.quitf(_pe, "%sexpected 'proof' before '%s' token", DAK, token.c_str());		\
										else if (token.empty())																\
											in.quitf(_pe, "%sexpected 'proof' at end of input", DAK);						\
									}																						\
									break;																					\
							}

							SRZ_TRANSFORM;
							in.quitf(_pe, "%sexpected primary-expression before '%s' token", DAK, token.c_str());
						} else {
							if (token.empty()) in.quitf(_pe, "%sexpected primary-expression at end of input", DAK);
							in.quitf(_pe, "%sexpected primary-expression before '%s' token", DAK, token.c_str());
						}
					}
					break;
				}
				case EXPECTED_SYMBOL: {
					if (token == ")") {
						if (!parser::push_right_bracket())
							in.quitf(_pe, "%sexpected operator before ')' token", DAK);
					} else if (token == "-")
						in.readChar('>'), parser::push_implies(), state = EXPECTED_VAR;
					else {
						if (parser::complete()) {
							parser::forward(), expr.swap(parser::result), parser::clear();
							switch (substate) {
								case ASSUMPTIONS:
									f[n_functions - 1].A.EB(std::move(expr));
									break;
								case CONCLUSIONS:
									f[n_functions - 1].C.EB(std::move(expr));
									break;
								case MACRO:
									logistic::macros.emplace(key, std::move(expr));
									if (token == "}") {logistic::check(fn, in), state = MAIN; continue;}
									if (token.empty()) in.quitf(_pe, "%sexpected '}' at end of input", DAK);
									if (!SRZ) in.quitf(_pe, "%sexpected identifier before '%s' token", DAK, token.c_str());
									key = token, state = EQUAL_OR_LBRACK;
									continue;
									break;
								case APPLY:
									apply_args.EB(std::move(expr));
									if (token.empty()) in.quitf(_pe, "%sexpected ',' or ']' at end of input", DAK);
									if (token == ",") state = EXPECTED_VAR;
									else if (token == "]") logistic::apply(apply_id, apply_args, key, in), state = PROOF_CASUAL;
									else in.quitf(_pe, "%sexpected ',' or ']' before '%s' token", DAK, token.c_str());
									continue;
									break;
							}

							SRZ_TRANSFORM;
							if (token == "(")
								parser::push_left_bracket(), state = EXPECTED_VAR;
							else if (token == "!") parser::push_not(),
								state = EXPECTED_VAR;
							else if (SRZ) {
								it = arg_map.find(token);
								if (it == arg_map.end()) in.quitf(_pe, "%s'%s' is not declared in this scope", DAK, token.c_str());
								parser::push_var(it->second);
							} else in.quitf(_pe, "%sexpected primary-expression before '%s' token", DAK, token.c_str());
						} else {
							if (token.empty()) in.quitf(_pe, "%sexpected ')' at end of input", DAK);
							in.quitf(_pe, "%sexpected ')' before '%s' token", DAK, token.c_str());
						}
					}
					break;
				}
			}
		}
	}
}

void init_logistic() {
	bool *const v = valid_identifier_char;
	memset(v + 34, true, 93),
	v['`'] = v['{'] = v['}'] = v['['] = v[']'] = v[':'] = v['-'] =
	v['>'] = v['!'] = v[','] = v['('] = v[')'] = v['='] = v['/'] = false;
}

void init_proof_environment() {
	n_functions = 4,
	name_map.clear(),
	name_map["P1"] = 0,
	name_map["P2"] = 1,
	name_map["P3"] = 2,
	name_map["MP"] = 3,
	f[0] = function(2, {}, {{0, 1, 0, -1, -1}}),
	f[1] = function(3, {}, {{0, 1, 2, -1, -1, 0, 1, -1, 0, 2, -1, -1, -1}}),
	f[2] = function(2, {}, {{0, -2, 1, -2, -1, 1, 0, -1, -1}}),
	f[3] = function(2, {{0, 1, -1}, {0}}, {{1}});
}

int main(int argc, char *argv[]) {
	registerTestlibCmd(argc, argv);

	int i, alpha = 0, beta = 0, p = 0;
	init_logistic(),
	processor::read(inf, true);

	m_functions = n_functions;
	for (i = 0; i < m_functions; ++i) std::swap(f[i], g[i]), beta += g[i].C.size();
	for (const pair <string, int> &e : name_map) I[e.second] = e.first;
#ifdef FY
	fprintf(stderr, "[%ld] input read finished.\n", clock());
#endif
	init_proof_environment();
	processor::read(ouf, false);
#ifdef FY
	fprintf(stderr, "[%ld] output read finished, total length = %llu.\n", clock(), LENGTH_TOTAL);
#endif
	for (i = 0; i < m_functions; ++i) {
		map<string, int>::iterator it = name_map.find(I[i]);
		if (it != name_map.end()) {
			function &F = f[it->second];
			if (g[i].n == F.n && g[i].A == F.A && g[i].C == F.C) alpha += F.C.size(), ++p;
		}
	}

	string info = format("%d/%d theorem%s proved, points = %.2lf", p, m_functions, p == 1 ? " is" : "s are", 10. * alpha / beta);
	if (alpha == beta) quit(_ok, info);
	else if (alpha) quitp(10 * alpha / beta * .1, info);
	else quit(_wa, info);

	return 0;
}
