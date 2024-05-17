#include <stdint.h>


enum
{
    LOW_32_BITS_MASK = 0xffffffffull,
};


uint64_t mul64_hi(uint64_t a, uint64_t b)
{
    uint64_t    a_lo = a & LOW_32_BITS_MASK;
    uint64_t    a_hi = a >> 32;
    uint64_t    b_lo = b & LOW_32_BITS_MASK;
    uint64_t    b_hi = b >> 32;

    uint64_t    a_x_b_hi =  a_hi * b_hi;
    uint64_t    a_x_b_mid = a_hi * b_lo;
    uint64_t    b_x_a_mid = b_hi * a_lo;
    uint64_t    a_x_b_lo =  a_lo * b_lo;

    uint64_t    carry_bit = ((a_x_b_mid & LOW_32_BITS_MASK) +
                            (b_x_a_mid & LOW_32_BITS_MASK) +
                            (a_x_b_lo >> 32) ) >> 32;

    uint64_t    multhi = a_x_b_hi +
                        (a_x_b_mid >> 32) + (b_x_a_mid >> 32) +
                        carry_bit;

    return multhi;
}
