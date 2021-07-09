#ifndef BRACKETS_H_
#define BRACKETS_H_

#include <cstdint>

void plus(int, int, int) noexcept;
void minus(int, int, int) noexcept;
void multiplies(int, int, int) noexcept;
void divides(int, int, int) noexcept;
void modulus(int, int, int) noexcept;
void negate(int, int) noexcept;
void equal_to(int, int, int) noexcept;
void not_equal_to(int, int, int) noexcept;
void greater(int, int, int) noexcept;
void less(int, int, int) noexcept;
void greater_equal(int, int, int) noexcept;
void less_equal(int, int, int) noexcept;
void logical_and(int, int, int) noexcept;
void logical_or(int, int, int) noexcept;
void logical_not(int, int) noexcept;
void bit_and(int, int, int) noexcept;
void bit_or(int, int, int) noexcept;
void bit_xor(int, int, int) noexcept;
void bit_not(int, int) noexcept;
void left_shift(int, int, int) noexcept;
void right_shift(int, int, int) noexcept;
void subscript(int, int) noexcept;
void subscript_assign(int, int) noexcept;
void assign(int, int) noexcept;
void set(int, uint16_t) noexcept;
void append(int) noexcept;
void match(int, int, int, int);

#endif
