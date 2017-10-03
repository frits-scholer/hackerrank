#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

namespace euler {

class bigint {
public:
    typedef unsigned long long value_type;
private:
    typedef unsigned __int128 working_type; // to prevent overflows
    typedef std::vector<value_type> vector_type;
    static const size_t RADIX_SHIFT = 8*sizeof(value_type)-1;  // left or right bit shift to move between values
    static const value_type RADIX = ((value_type)1) << RADIX_SHIFT;  // last bit (sign bit in signed long int)
    static const value_type RADIX_MOD = ((value_type)(-1)) ^ RADIX;
    vector_type buff;
    char sign;

private:

    void _add_buff(const vector_type &a, const vector_type &b) {
        size_t na = a.size();
        size_t nb = b.size();

        const vector_type *p = &b;
        size_t minIdx = na;
        size_t maxIdx = nb;
        if (na > nb) {
            p = &a;
            minIdx = nb;
            maxIdx = na;
        }

        // maybe grow to fit
        buff.resize(maxIdx, 0);

        working_type overflow = 0;
        for (int i = 0; i < minIdx; ++i) {
            working_type c = a[i] + b[i] + overflow;
            buff[i] = (value_type) (c & RADIX_MOD);
            overflow = c >> RADIX_SHIFT;
        }

        // check if we have more digits to transfer
        for (size_t i = minIdx; i < maxIdx; ++i) {
            working_type c = (*p)[i] + overflow;
            buff[i] = (value_type) (c & RADIX_MOD);
            overflow = c >> RADIX_SHIFT;
        }

        // check final overflow
        while (overflow > 0) {
            working_type c = overflow & RADIX_MOD;
            buff.push_back((value_type) c);
            overflow = overflow >> RADIX_SHIFT;
        }
    }

    // requires a >= b
    void _sub_buff(const vector_type &a, const vector_type &b) {
        size_t na = a.size();
        size_t nb = b.size();

        buff.resize(na, 0);

        int steal = 0;
        for (int i = 0; i < nb; ++i) {
            working_type d = 0;
            if (a[i] < b[i] + steal) {
                d = a[i] + RADIX - b[i] - steal;
                steal = 1;
            } else {
                d = a[i] - b[i] - steal;
                steal = 0;
            }

            buff[i] = (value_type) d;
        }

        // check if we have more digits to transfer
        for (size_t i = nb; i < na; ++i) {
            working_type d = 0;
            if (a[i] < steal) {
                d = a[i] + RADIX - steal;
                steal = 1;
            } else {
                d = a[i] - steal;
                steal = 0;
            }
            buff[i] = (value_type) d;
        }

        // remove zeros at back
        while (buff.size() > 0 && buff.back() == 0) {
            buff.pop_back();
        }
    }

    void _inc_buff(value_type v) {

        size_t sb = buff.size();

        working_type overflow = v;
        size_t i = 0;
        while (i < sb && overflow > 0) {
            working_type c = buff[i] + overflow;
            buff[i] = (value_type) (c & RADIX_MOD);
            overflow = c >> RADIX_SHIFT;
            ++i;
        }

        if (overflow > 0) {
            buff.push_back((value_type) overflow);
        }

    }

    void _dec_buff(value_type v) {

        working_type steal = v;
        size_t i = 0;
        while (steal > 0) {
            if (buff[i] < steal) {
                working_type k = (steal - buff[i] + RADIX - 1) >> RADIX_SHIFT;
                working_type d = buff[i] + k << RADIX_SHIFT - steal;
                buff[i] = (value_type) d;
                steal = k;
            } else {
                buff[i] -= steal;
                steal = 0;
            }
            ++i;
        }

        // remove zeros at back
        while (buff.size() > 0 && buff.back() == 0) {
            buff.pop_back();
        }
    }

    // buff[boff,boff+1] += c*a, c < RADIX
    static void
    _mul_buff(vector_type &r, const vector_type &a, value_type c, size_t boff) {

        // maybe resize
        size_t an = a.size();
        if (r.size() < an + boff) {
            r.resize(an + boff, 0);
        }

        working_type overflow = 0;
        for (size_t i = 0; i < an; ++i) {
            size_t bidx = i + boff;
            // *should* fit and prevent integer overflow
            working_type d = ((working_type) c) * a[i] + r[bidx] + overflow;
            r[bidx] = (value_type) (d & RADIX_MOD);
            overflow = d >> RADIX_SHIFT;
        }

        // maybe add more digits
        while (overflow > 0) {
            value_type d = (value_type) (overflow & RADIX_MOD);
            r.push_back(d);
            overflow = overflow >> RADIX_SHIFT;
        }

    }

    // multiplies in place
    static void _inplace_mul_buff(vector_type &a, value_type c) {

        // maybe resize
        size_t an = a.size();

        working_type overflow = 0;
        for (auto &b : a) {
            // *should* fit and prevent integer overflow
            working_type d = ((working_type) c) * b + overflow;
            b = (value_type) (d & RADIX_MOD);
            overflow = d >> RADIX_SHIFT;
        }

        // maybe add more digits
        while (overflow > 0) {
            value_type d = (value_type) (overflow & RADIX_MOD);
            a.push_back(d);
            overflow = overflow >> RADIX_SHIFT;
        }

    }

    void _mul_buff(const vector_type &m) {
        // long multiplication
        size_t nm = m.size();
        size_t nb = buff.size();
        vector_type r;
        r.reserve(nm + nb);

        const vector_type *v;
        const vector_type *x;
        size_t nv;
        if (nm > nb) {
            v = &buff;
            x = &m;
            nv = nb;
        } else {
            v = &m;
            x = &buff;
            nv = nm;
        }

        for (size_t i = 0; i < nv; ++i) {
            _mul_buff(r, *x, (*v)[i], i);
        }

        buff = std::move(r);
    }

    void _shift_left_buff(size_t d) {

        size_t k = d / RADIX_SHIFT;
        d = d & RADIX_MOD;

        // shift by d
        working_type overflow = 0;
        for (auto &a : buff) {
            working_type b = (((working_type) a) << d) + overflow;
            a = (value_type) (b & RADIX_MOD);
            overflow = (b >> RADIX_SHIFT);
        }

        while (overflow > 0) {
            value_type v = (value_type) (overflow & RADIX_MOD);
            buff.push_back(v);
            overflow = overflow >> RADIX_SHIFT;
        }

        // insert zeros at front
        buff.insert(buff.begin(), k, 0);
    }

    void _shift_right_buff(size_t d) {

        size_t k = d / RADIX_SHIFT;
        // delete elements at back
        buff.erase(buff.begin(), buff.begin() + k);

        d = d & RADIX_MOD;

        // shift by d
        size_t sb = buff.size();
        for (size_t i = 0; i < sb - 1; ++i) {
            working_type a = buff[i] + ((working_type) buff[i] << RADIX_SHIFT);
            buff[i] = (value_type) ((a >> d) & RADIX_MOD);
        }
        buff[sb - 1] = buff[sb - 1] >> d;

        while (buff.size() > 0 && buff.back() == 0) {
            buff.pop_back();
        }
    }

    int _compare_buff(const vector_type &a, const vector_type &b) const {
        if (b.size() > a.size()) {
            return -1;
        } else if (b.size() < a.size()) {
            return 1;
        }

        size_t s = a.size();
        for (size_t i = s; i-- > 0;) {
            if (a[i] < b[i]) {
                return -1;
            } else if (a[i] > b[i]) {
                return 1;
            }
        }

        return 0;
    }

    // in-place buffer division
    static value_type _inplace_div_buff(vector_type &n, value_type v) {
        working_type r = 0;

        std::for_each(n.rbegin(), n.rend(), [&](value_type &i) {
            r = (r << RADIX_SHIFT) + i;
            working_type d = r / v;
            i = ((value_type) d);
            r -= d * v;
        });

        // remove leading zeros
        while (n.size() > 0 && n.back() == 0) {
            n.pop_back();
        }

        return (value_type) r;
    }

    static bigint divide(const bigint& a, const bigint& b,
                         bigint& r) {
        if (b.is_zero()) {
            throw "arithmetic exception: divison by zero";
        }

        // absolute value
        bigint target = a;
        if (target.sign < 0) {
            target.sign = 1;
        }
        bigint denom = b;
        if (denom.sign < 0) {
            denom.sign = 1;
        }
        if (target < denom) {
            r = a;
            return bigint(0LL);
        }

        bigint upper = target;
        ++upper;  // upper is ABOVE result
        bigint lower = bigint(0LL);
        bigint out;
        bigint m;

        do {
            out = upper;
            out += lower;
            out >>= 1;
            m = out*denom;

            if (m == target) {
                r = 0;
                // determine sign
                out.sign = (a.sign == b.sign ? 1 : -1);
                return out;
            } else if (m < target) {
                lower = out;
                ++lower;
            } else {
                upper = out; // upper stays above
            }
        } while (upper > lower);
        // rounding down, one below position found
        --lower;

        // handle signs
        out = lower;
        out.sign = (a.sign == b.sign ? 1 : -1);
        m = out*b;
        r = a-m;

        return out;
    }
public:
    bigint() : buff(0), sign(0) {} // default 0

    bigint(long long v) {
        set(v);
    }

    bigint(const bigint &other) : buff(other.buff), sign(other.sign) {}

    bigint(bigint &&other) : buff(std::move(other.buff)), sign(other.sign) {
        other.buff.clear();
        other.sign = 0;
    }

    bigint &operator=(const bigint &other) {
        bigint tmp(other);
        *this = std::move(tmp);
        return *this;
    }

    void set(long long v) {
        buff.clear();
        if (v < 0) {
            sign = -1;
            v = -v;
        } else if (v > 0) {
            sign = 1;
        } else {
            sign = 0;
            v = 0;
            return;
        }

        while (v > 0) {
            value_type d = (value_type) (v & RADIX_MOD);
            buff.push_back(d);
            v = v >> RADIX_SHIFT;
        }
    }

    bigint &operator=(long long v) {
        set(v);
        return *this;
    }

    bigint &operator=(bigint &&other) noexcept {
        buff = std::move(other.buff);
        sign = other.sign;
        other.buff.clear();
        other.sign = 0;
        return *this;
    }

    // standard math operations
    bigint &add(const bigint &a) {
        if (a.sign == 0) {
            return *this;
        } else if (sign == 0) {
            buff = a.buff;
            sign = a.sign;
        } else if (a.sign == sign) { // same sign, add digits
            _add_buff(buff, a.buff);
        } else {
            // check which one is greater, and if sign should switch
            int cmp = _compare_buff(buff, a.buff);
            if (cmp == 0) {
                // cancel out
                buff.clear();
                sign = 0;
            } else if (cmp < 0) {
                _sub_buff(a.buff, buff);
                sign = -sign; // flip sign
            } else {
                _sub_buff(buff, a.buff);
            }
        }
        return *this;
    }

    bigint &subtract(const bigint &a) {
        if (a.sign == 0) {
            return *this;
        } else if (sign == 0) {
            buff = a.buff;
            sign = -a.sign;
        } else if (a.sign != sign) { // same sign, add digits
            _add_buff(buff, a.buff);
        } else {
            // check which one is greater, and if sign should switch
            int cmp = _compare_buff(buff, a.buff);
            if (cmp == 0) {
                // cancel out
                buff.clear();
                sign = 0;
            } else if (cmp < 0) {
                _sub_buff(a.buff, buff);
                sign = -sign; // flip sign
            } else {
                _sub_buff(buff, a.buff);
            }
        }

        return *this;
    }

    bigint &add(value_type v) {
        if (v == 0) {
            return *this;
        }

        if (sign == 0) {
            sign = 1;
            buff.push_back(v);
        } else if (sign < 0) {
            _dec_buff(v);
            if (buff.size() == 0) {
                sign = 0;
            }
        } else {
            _inc_buff(v);
        }

        return *this;
    }

    bigint &subtract(value_type v) {

        if (v == 0) {
            return *this;
        }

        if (sign == 0) {
            sign = -1;
            buff.push_back(v);
        } else if (sign > 0) {
            _dec_buff(v);
            if (buff.size() == 0) {
                sign = 0;
            }
        } else {
            _inc_buff(v);
        }
        return *this;
    }

    bigint &multiply(const bigint &b) {
        if (sign == 0 || b.sign == 0) {
            sign = 0;
            buff.clear();
        } else {
            sign *= b.sign;
            _mul_buff(b.buff);
        }

        return *this;
    }

    bigint &multiply(value_type b) {
        if (sign == 0 || b == 0) {
            sign = 0;
            buff.clear();
        } else {
            // first shift
            size_t nshifts = b >> RADIX_SHIFT;
            buff.insert(buff.begin(), nshifts, 0);
            b = b & RADIX_MOD;
            if (b > 0) {
                _inplace_mul_buff(buff, b);
            }
        }

        return *this;
    }

    bigint &divide(value_type v, value_type &r) {
        r = _inplace_div_buff(buff, v);
        if (buff.size() == 0) {
            sign = 0;
        }
        return *this;
    }

    bigint &divide(value_type v) {
        value_type r;
        return divide(v, r);
    }

    bigint &divide(const bigint& v, bigint &r) {
        bigint d = divide(*this, v, r);
        *this = d;
        return *this;
    }

    bigint &divide(const bigint &v) {
        bigint r;
        return divide(v, r);
    }

    int compare_to(const bigint &b) const {
        if (sign < b.sign) {
            return -1;
        } else if (sign > b.sign) {
            return 1;
        }

        return _compare_buff(buff, b.buff);
    }

    bool is_zero() const {
        return sign == 0;
    }

    bool is_negative() const {
        return sign < 0;
    }

    bool is_positive() const {
        return sign > 0;
    }

    value_type long_value() const {
        if (buff.size() == 0) {
            return 0;
        }
        return sign*buff[0];
    }

    void shift_left(size_t d) {
        if (sign != 0) {
            _shift_left_buff(d);
        }
    }

    bigint operator-() const {
        bigint out = *this;
        out.sign *= -1;
        return out;
    }

    bigint &operator <<=(size_t d) {
        shift_left(d);
        return *this;
    }

    bigint &operator >>=(size_t d) {
        shift_right(d);
        return *this;
    }

    void shift_right(size_t d) {
        if (sign != 0) {
            _shift_right_buff(d);
            if (buff.size() == 0) {
                sign = 0;
            }
        }
    }

    size_t num_binary_digits() const {
        size_t sb = buff.size();
        if (sb == 0) {
            return 0;
        }
        size_t nd = (sb - 1) * RADIX;

        // length of last digit
        value_type l = buff.back();
        while (l > 0) {
            ++nd;
            l = l >> 1;
        }
        return nd;
    }

    size_t num_decimal_digits() const {
        size_t nb = num_binary_digits();
        // approximate
        return (size_t) floor((nb + 1) * log10(2)) + 1;
    }

    std::string to_hex_string() const {
        static const char HEX_CHARS[] = {'0', '1', '2', '3', '4', '5', '6', '7',
                                         '8', '9',
                                         'A', 'B', 'C', 'D', 'E', 'F'};
        static const int HEX_BITS = 4;
        if (sign == 0) {
            return "0";
        }

        std::string s;

        // reverse characters
        size_t nb = buff.size();

        size_t b = 0;
        size_t bits_available = 0;
        working_type w = 0;

        // 16 bits at a time
        while (b < nb || w != 0) {
            if (bits_available < HEX_BITS) {
                // reload
                w = ((working_type) buff[b] << bits_available) | w;
                bits_available += RADIX_SHIFT;
                ++b;
            }

            int c = (int) (w & 0xF);
            s.push_back(HEX_CHARS[c]);
            w = w >> HEX_BITS;
            bits_available -= HEX_BITS;
        }

        if (sign < 0) {
            s.append("-");
        }
        std::reverse(s.begin(), s.end());

        return s;
    }

    std::string to_string() const {
        if (sign == 0) {
            return "0";
        }

        // reverse characters
        vector_type bcopy(buff);

        // keep dividing in blocks
        static const value_type BLOCK = 1000000000;
        static const size_t BLOCK_DIGITS = 9;
        std::string s;
        while (bcopy.size() > 0) {
            value_type a = _inplace_div_buff(bcopy, BLOCK);

            for (int i = 0; i < BLOCK_DIGITS; ++i) {
                char d = (char) (a % 10 + '0');
                a = a / 10;
                s.push_back(d);
            }
        }

        // remove zeros
        while ((s.length() > 0) && (s.back() == '0')) {
            s.pop_back();
        }

        if (sign < 0) {
            s.append("-");
        }
        std::reverse(s.begin(), s.end());

        return s;
    }

    bigint &operator+=(const bigint &b) {
        add(b);
        return *this;
    }

    bigint &operator-=(const bigint &b) {
        subtract(b);
        return *this;
    }

    bigint &operator*=(const bigint &b) {
        multiply(b);
        return *this;
    }

    bigint &operator*=(const value_type &b) {
        multiply(b);
        return *this;
    }

    bigint &operator/=(const bigint &b) {
        divide(b);
        return *this;
    }

    bigint &operator/=(const value_type &v) {
        divide(v);
        return *this;
    }

    bigint &operator%=(const value_type &v) {
        value_type r;
        divide(v, r);
        *this = r;
        return *this;
    }

    bigint &operator%=(const bigint &v) {
        bigint r;
        divide(v, r);
        *this = r;
        return *this;
    }

    bigint &operator++() {
        add(1);
        return *this;
    }

    bigint &operator--() {
        subtract(1);
        return *this;
    }

    bigint operator++(int) {
        bigint tmp(*this);
        add(1);
        return tmp;
    }

    bigint operator--(int) {
        bigint tmp(*this);
        subtract(1);
        return tmp;
    }

    void ensure_capacity(size_t nbits) {
        size_t blocks = nbits / RADIX_SHIFT;
        buff.reserve(blocks);
    }

    friend std::ostream &operator<<(std::ostream &os, const bigint &bi) {
        // os << "0x" << bi.to_hex_string();
        os << bi.to_string();
        return os;
    }

    friend bigint operator+(const bigint &bi1, const bigint &bi2) {
        bigint out(bi1);
        out.add(bi2);
        return out;
    }

    friend bigint operator-(const bigint &bi1, const bigint &bi2) {
        bigint out(bi1);
        out.subtract(bi2);
        return out;
    }

    friend bigint operator*(const bigint &bi1, const bigint &bi2) {
        bigint out(bi1);
        out.multiply(bi2);
        return out;
    }

    friend bigint operator*(const bigint &bi1, const bigint::value_type &v) {
        bigint out(bi1);
        out.multiply(v);
        return out;
    }

    friend bigint operator/(const bigint &bi1, const value_type &bi2) {
        bigint out(bi1);
        out.divide(bi2);
        return out;
    }

    friend value_type operator%(const bigint &bi1, const value_type &bi2) {
        bigint out(bi1);
        value_type r;
        out.divide(bi2, r);
        return r;
    }

    friend bigint operator/(const bigint &bi1, const bigint &bi2) {
        bigint out(bi1);
        out.divide(bi2);
        return out;
    }

    friend bigint operator%(const bigint &bi1, const bigint &bi2) {
        bigint out(bi1);
        bigint r;
        out.divide(bi2, r);
        return r;
    }

    friend bigint operator<<(const bigint &bi, size_t d) {
        bigint out = bi;
        out.shift_left(d);
        return out;
    }

    friend bigint operator>>(const bigint &bi, size_t d) {
        bigint out = bi;
        out.shift_right(d);
        return out;
    }

    friend bool operator>(const bigint &bi1, const bigint &bi2) {
        int cmp = bi1.compare_to(bi2);
        return cmp > 0;
    }

    friend bool operator>=(const bigint &bi1, const bigint &bi2) {
        int cmp = bi1.compare_to(bi2);
        return cmp >= 0;
    }

    friend bool operator<(const bigint &bi1, const bigint &bi2) {
        int cmp = bi1.compare_to(bi2);
        return cmp < 0;
    }

    friend bool operator<=(const bigint &bi1, const bigint &bi2) {
        int cmp = bi1.compare_to(bi2);
        return cmp <= 0;
    }

    friend bool operator ==(const bigint &bi1, const bigint &bi2) {
        int cmp = bi1.compare_to(bi2);
        return cmp == 0;
    }

    friend bool operator !=(const bigint &bi1, const bigint &bi2) {
        int cmp = bi1.compare_to(bi2);
        return cmp != 0;
    }

};
} // euler

int main() {
    
   size_t t1, t2, n;
   std::cin >> t1 >> t2 >> n;
   
   // incremental fibonacci
   euler::bigint b1 = t1;
   euler::bigint b2 = t2;
   euler::bigint out = b2*b2+b1;
   for (int i=3; i<n; ++i) {
      b1 = std::move(b2);
      b2 = std::move(out);
      out = b2*b2+b1;
   }
   std::cout << out << std::endl;
    return 0;
}
