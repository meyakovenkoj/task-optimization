#include <stddef.h>
#include <stdint.h>


uint64_t mul64_hi(uint64_t a, uint64_t b);

#define MUL64(a, b, r0_, r1_) \
    { \
        r0_ = a * b; \
        r1_ = mul64_hi(a, b); \
    }

#define ADC(a, b, r, c) \
    { \
        uint64_t ta = a, tb = b, tc = c; \
        uint64_t s = ta + tb; \
        r = s + tc; \
        c = (s < ta) || (tc != 0ul && s == 0xFFFFFFFFFFFFFFFFul); \
    }

// alpha = { 0, 1 } - множитель для вычисления значения magic
void reduction(uint64_t *x, const uint64_t *n, size_t len, uint64_t rho, uint64_t alpha, uint64_t *magic)
{
    long n_size = len;
    *magic = 0;

    for (long i = 0; i < n_size; ++i) {
        uint64_t mu = x[i] * rho;
        uint64_t c0 = 0, c1 = 0;

        uint64_t prev = 0;
        for (long j = 0; j < n_size; ++j) {
            uint64_t r0, r1;
            MUL64(n[j], mu, r0, r1)
            ADC(x[i + j], r0, r0, c0)
            ADC(prev, r0, x[i + j], c1)
            *magic += alpha * r1;
            prev = r1;
        }
        prev += c0;
        ADC(x[i + n_size], prev, x[i + n_size], c1)

        long tix = i + n_size + 1;
        while (c1 && tix < 2 * n_size + 1) {
            uint64_t tx = x[tix];
            ADC(tx, 0, x[tix], c1);
	    ++tix;
	}
    }
}
