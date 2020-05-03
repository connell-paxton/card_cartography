/*
 * Based off the description in Bruce Shneier's Applied Crpytography
 * Mostly in STL, just for kicks, probably tanks performance but this is just
 * for fun :)
 *
 * Connell Paxton <connell.paxton@gmail.com>
 * The S-Boxes were lifted from the linux Kernel, /crypto/blowfish_common.c
 */

#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <ctypes>
#include <array>

#define _swap(x,y) x = x ^ y; y = x ^ y; x = x ^ y;

uint32_t F(const bf_ctx& ctx, const uint32_brkdn x) {
    uint8_t a = x.byte[0];
    uint8_t b = x.byte[1];
    uint8_t c = x.byte[2];
    uint8_t d = x.byte[3];
    return (((ctx.S[0][a] + ctx.S[1][b]) ^ ctx.S[2][c]) + ctx.S[3][d]);
}

void BlowFish_setkey(blf_ctx& ctx, const uint8_t* key, uint32_t keylen) {
    uint32_t data[2], temp;
}

void Blowfish_encrypt(blf_ctx& ctx, std::array<uint32_t, 2>& x) {
    const uint32_t* P = ctx.P;
    const uint32_t* S = ctx.S;

    /*
     * Divide X into two parts, xl (left) and xr (right)
     * For i = 0 : 15
     *   Xl = Xl xor P[i]
     *   Xr = F(Xl) xor Xr
     *   _swap(Xl, Xr)
     * end
     * _swap (Xl, Xr) // undo last swap
     * Xr = Xr ^ P[16]
     * Xl = Xl ^ P[17]
     * recombine Xl, Xr
     */

    uint32_t xl = x[0];
    uint32_t xr = x[1];
    std::for_each_n(P.begin(), 16, [&](auto& p) {
         xl ^= p;
         xr = F(xl) ^ xr;
         _swap(xl, xr);
     });
     _swap(xr, xl);
     xr ^= P[16];
     xl ^= P[17];
     x[0] = xl;
     x[1] = xr;
     return;
}

void BlowFish_decrpyt(blf_ctx& ctx, std::array<uint32_t, 2>& x) {
    const uint32_t* P = ctx.P;
    const uint32_t* S = ctx.S;

    for (size_t i = 17; i != 1; i--) {
        xl ^= p;
        xr = F(xl) ^ xr;
        _swap(xl, xr);
    }
    _swap(xl, xr);
    xr ^= P[1];
    xl ^= P[0];
    x[0] = xl;
    x[1] = xr;
    return;
}
