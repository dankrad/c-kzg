/*
 * Copyright 2021 Benjamin Edgington
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "poly.h"

static void poly_factor_div(blst_fr *out, const blst_fr *a, const blst_fr *b) {
    blst_fr_eucl_inverse(out, b);
    blst_fr_mul(out, out, a);
}

// Call this to find out how much space to allocate for the result
uint64_t poly_long_div_length(const uint64_t len_dividend, const uint64_t len_divisor) {
    return len_dividend - len_divisor + 1;
}

// `out` must have been pre-allocated to the correct size, and the length is provided
// as a check
C_KZG_RET poly_long_div(blst_fr *out, const uint64_t len_out, const blst_fr *dividend, const uint64_t len_dividend, const blst_fr *divisor, const uint64_t len_divisor) {
    uint64_t a_pos = len_dividend - 1;
    uint64_t b_pos = len_divisor - 1;
    uint64_t diff = a_pos - b_pos;
    blst_fr a[len_dividend];

    ASSERT(len_out == diff + 1, C_KZG_BADARGS);

    for (uint64_t i = 0; i < len_dividend; i++) {
        a[i] = dividend[i];
    }

    while (true) {
        poly_factor_div(&out[diff], &a[a_pos], &divisor[b_pos]);
        for (uint64_t i = 0; i <= b_pos; i++) {
            blst_fr tmp;
            // a[diff + i] -= b[i] * quot
            blst_fr_mul(&tmp, &out[diff], &divisor[i]);
            blst_fr_sub(&a[diff + i], &a[diff + i], &tmp);
        }
        if (diff == 0) break;
        --diff;
        --a_pos;
    }

    return C_KZG_SUCCESS;
}