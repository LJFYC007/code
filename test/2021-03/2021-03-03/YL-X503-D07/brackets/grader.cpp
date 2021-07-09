#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "brackets.h"

int n_impl_, m_impl_, s_impl_, l_impl_, x_impl_;
int mat_impl_[65536];
bool e_impl_;
bool vis_impl_[65536];
uint16_t a_impl_[65536];

const char *inc_impl_ = "Matching incomplete.";
const char *err_impl_ = "Matching incorrect.";
const char *opt_impl_ = "Too many operations.";
const char *sub_impl_ = "Subscripting exceeds.";

void assert_impl_(bool cond, const char *mes) {
  if (!cond) {
    printf("Unaccpeted! %s\n", mes);
    exit(0);
  }
}

#define UU(op, ap) \
void op(int p, int x) noexcept { \
  assert_impl_(l_impl_--, opt_impl_); \
  assert_impl_(p >= n_impl_ && p < n_impl_ + s_impl_, sub_impl_); \
  assert_impl_(x >= 0 && x < 65536, sub_impl_); \
  a_impl_[p] = ap a_impl_[x]; \
}
#define BU(op, ap) \
void op(int p, int x, int y) noexcept { \
  assert_impl_(l_impl_--, opt_impl_); \
  assert_impl_(p >= n_impl_ && p < n_impl_ + s_impl_, sub_impl_); \
  assert_impl_(x >= 0 && x < 65536, sub_impl_); \
  assert_impl_(y >= 0 && y < 65536, sub_impl_); \
  a_impl_[p] = a_impl_[x] ap a_impl_[y]; \
}
#define UB(op, ap) \
void op(int p, int x) noexcept { \
  assert_impl_(l_impl_--, opt_impl_); \
  assert_impl_(p >= n_impl_ && p < n_impl_ + s_impl_, sub_impl_); \
  assert_impl_(x >= 0 && x < 65536, sub_impl_); \
  a_impl_[p] = -(ap a_impl_[x]); \
}
#define BB(op, ap) \
void op(int p, int x, int y) noexcept { \
  assert_impl_(l_impl_--, opt_impl_); \
  assert_impl_(p >= n_impl_ && p < n_impl_ + s_impl_, sub_impl_); \
  assert_impl_(x >= 0 && x < 65536, sub_impl_); \
  assert_impl_(y >= 0 && y < 65536, sub_impl_); \
  a_impl_[p] = -(a_impl_[x] ap a_impl_[y]); \
}

BU(plus, +)BU(minus, -)BU(multiplies, *)BU(divides, /)BU(modulus, %)
UU(negate, -)BB(equal_to, ==)BB(not_equal_to, !=)BB(greater, >)BB(less, <)
BB(greater_equal, >=)BB(less_equal, <=)BB(logical_and, &&)BB(logical_or, ||)
UB(logical_not, !)BU(bit_and, &)BU(bit_or, |)BU(bit_xor, ^)UU(bit_not, ~)
BU(left_shift, <<)BU(right_shift, >>)UU(assign, )

#undef UU
#undef BU
#undef UB
#undef BB

void subscript(int p, int x) noexcept {
  assert_impl_(l_impl_--, opt_impl_);
  assert_impl_(p >= n_impl_ && p < n_impl_ + s_impl_, sub_impl_);
  assert_impl_(x >= 0 && x < 65536, sub_impl_);
  a_impl_[p] = a_impl_[a_impl_[x]];
}
void subscript_assign(int p, int x) noexcept {
  assert_impl_(l_impl_--, opt_impl_);
  assert_impl_(p >= 0 && p < 65536, sub_impl_);
  assert_impl_(x >= 0 && x < 65536, sub_impl_);
  assert_impl_(a_impl_[p] >= n_impl_ && a_impl_[p] < n_impl_ + s_impl_, sub_impl_);
  a_impl_[a_impl_[p]] = a_impl_[x];
}
void set(int p, uint16_t v) noexcept {
  assert_impl_(l_impl_--, opt_impl_);
  assert_impl_(p >= n_impl_ && p < n_impl_ + s_impl_, sub_impl_);
  a_impl_[p] = v;
}

void append(int y) noexcept {
printf("%d ", a_impl_[y]);
  assert_impl_(l_impl_--, opt_impl_);
  y = a_impl_[y];
  if (!~x_impl_) {
    x_impl_ = y;
    return;
  }
  if (e_impl_) {
    assert_impl_(x_impl_ < n_impl_ && y < n_impl_ && mat_impl_[x_impl_] == y, err_impl_);
    vis_impl_[x_impl_] = true;
    vis_impl_[y] = true;
  } else {
    assert_impl_(x_impl_ == 65535 && y == 65535, err_impl_);
  }
  x_impl_ = -1;
}

int main() {
freopen("brackets1.in", "r", stdin);
  int T;
  scanf("%d", &T);
  while (T--) {
    scanf("%d%d%d%d", &n_impl_, &m_impl_, &s_impl_, &l_impl_);
    x_impl_ = -1;
    for (int i = 0; i < n_impl_; ++i) {
      unsigned x;
      scanf("%u", &x);
      a_impl_[i] = x;
    }
    for (int i = n_impl_; i < 65536; ++i) {
      a_impl_[i] = 0;
    }
    static int stk[65536];
    int top = 0;
    e_impl_ = true;
    for (int i = 0; i < n_impl_; ++i) {
      vis_impl_[i] = false;
      if (a_impl_[i] < 32768) {
        stk[top++] = i;
      } else {
        if (!top || uint16_t(a_impl_[stk[--top]] + a_impl_[i]) != 0) {
          e_impl_ = false;
          break;
        }
        mat_impl_[stk[top]] = i;
        mat_impl_[i] = stk[top];
      }
    }
    if (top) e_impl_ = false;
    match(n_impl_, m_impl_, s_impl_, l_impl_);
    if (e_impl_) {
      for (int i = 0; i < n_impl_; ++i) {
        assert_impl_(vis_impl_[i], inc_impl_);
      }
    }
  }
  puts("Accepted!");
  return 0;
}
