#ifndef INTC
#define INTC

#pragma once

#include <iostream>
#include <cstdint>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <type_traits>

struct intc16_t {
    private:
        static constexpr uint16_t MAXIMUM_SIZE16 = 65535;
        /*
        MAXIMUM_SIZE16 must be private because it can be changed if its public.
        */

        static int countOfIntc16; // count of each object of intc16_t.

    public:
        uint16_t val16 = 0; // public if it needs to be changed manually.

        intc16_t(uint16_t u) : val16(u) {countOfIntc16++;};
        intc16_t() {countOfIntc16++;};
        ~intc16_t() {countOfIntc16--;}

        uint16_t getValue() const;
        uint16_t getValueFromFile(const std::string& filename,
        size_t position) const;
        uint16_t getValueFromBinFile(const std::string& filename, size_t pos) const;
        uint16_t getValueFromHexFile(const std::string& filename, size_t pos) const;
        uint16_t m_highestBit() const;

        bool isZero() const;
        bool checkIfMax() const;
        bool isbitset(int pos) const;
        bool evenParity() const;
        bool isMin() const;
        bool equals(const intc16_t& other) const;
        bool m_equals(const intc16_t& other, const intc16_t& other2, char op) const;
        bool isOdd() const;
        bool isEven() const;
        bool isPalindromeH() const;
        bool isPalindromeB() const;
        bool hasBitPattern(uint16_t pattern) const;
        bool isPowerOfTwo() const;
        bool isPrime() const;

        void showMemAddress();
        void setbit(int pos);
        void clearbit(int pos);
        void togglebit(int pos);
        void appToFile(const std::string& filename) const;
        void overwriteFile(const std::string& filename) const;
        void swap(intc16_t& other);
        void appToBinFile(const std::string& filename) const;
        void appToHexFile(const std::string& filename) const;
        void delptr(intc16_t* other) const;
        void a_delptr(intc16_t* other[], size_t count) const;
        void swapBits(int pos1, int pos2);

        size_t countRecords(const std::string& filename) const;

        int toInt();
        int bitCount() const;
        int countsetbits() const;
        int highestbit() const;
        int lowestbit() const;
        int leadingZero() const;
        int trailingZero() const;
        int countUnsetBits() const;
        static int getCount();

        std::string toBin();
        std::string toHex();

        intc16_t rotateLeft(int n) const;
        intc16_t rotateRight(int n) const;
        intc16_t reverseBits() const;
        intc16_t pow(intc16_t base, unsigned int exp);
        intc16_t n_powerOfTwo() const;

        /* TEMPLATE FUNCTIONS */
        template<class A>
        bool inRange(const A& v1, const A& v2) const {
            if ((val16 > v1) && (val16 < v2)){
                return true;
            }

            return false;
        }

        template<class T>
        void add(T other) {
            int result = val16 + other;

            if (result > MAXIMUM_SIZE16) {
                val16 = MAXIMUM_SIZE16;
            }
            else {
                val16 = result;
            }
        }

        template<class T>
        void subtract(T other) {
            int result = val16 - other;

            if (result < 0) {
                val16 = 0;
            }
            else {
                val16 = result;
            }
        }

        template<class T>
        void multiply(T other) {
            int result = val16 * other;

            if (result > MAXIMUM_SIZE16) {
                val16 = MAXIMUM_SIZE16;
            }
            else {
                val16 = result;
            }
        }

        template<class T>
        void divide(T other) {
            if (other == 0) {
                throw std::invalid_argument("Cannot divide by zero.");
            }
            else {
                val16 = val16 / other;
            }
        }

        template<class S>
        S abs(S val){
            if (val < 0){
                return val;
            }
            else {
                return val;
            }
        }

        template<class S>
        S pow(S base, unsigned int exp){
            S result = 1;

            while (exp > 0){
                if (exp & 1){
                    result *= base;
                }

                base *= base;
                exp >>= 1;
            }

            return result;
        }

        template<class S>
        S gcd(S a, S b){
            while (b != 0){
                S temp = b;
                b = a % b;
                a = temp;
            }

            return a;
        }

        template<class S>
        S lcm(S a, S b){
            if (a == 0 || b == 0){
                return 0;
            }

            return (static_cast<S>(a) * b) / gcd(a, b);
        }

        template<class S, class = std::enable_if_t<std::is_integral<S>::value>>
        S i_sqrt(S num){
            // signed neg
            if constexpr(std::is_signed<S>::value){
                if (num < 0){
                    return static_cast<S>(-1);
                }
            }

            using unsigned_t = std::make_unsigned_t<S>;
            unsigned_t n = static_cast<unsigned_t>(num);
            unsigned_t lo = 0;
            unsigned_t hi = (n >= 1) ? std::min<unsigned_t>(n, static_cast<unsigned_t>(
                65535
            )) : 0; // safe bound
            unsigned_t ans = 0;

            while (lo <= hi){
                unsigned_t mid = (lo + hi) / 2;
                unsigned long long sq = static_cast<unsigned long long>(mid) * mid;

                if (sq == n){
                    ans = mid;

                    break;
                }
                else if (sq < n){
                    ans = mid;
                    lo = mid + 1;
                }
                else {
                    if (mid == 0){
                        break;
                    }

                    hi = mid - 1;
                }
            }

            return static_cast<S>(ans);
        }

        template<class S, class = std::enable_if_t<std::is_floating_point<S>::value>>
        S f_sqrt(S num){
            if (std::isnan(num)){
                return std::numeric_limits<S>::quiet_NaN();
            }

            if (num < 0){
                return static_cast<S>(-1);
            }

            if (num == 0){
                return static_cast<S>(0);
            }


            double guess = static_cast<double>(num) / 2.0;
            double eps = 1e-9;

            while (true){
                double new_guess = 0.5 * (guess + static_cast<double>(num) / guess);

                if (std::fabs(new_guess - guess) < eps){
                    return static_cast<S>(new_guess);
                }

                guess = new_guess;
            }
        }
        
        template<class T1, class T2, class T3>
        struct tpair {
            T1 first;
            T2 second;
            T3 third;

            tpair() {}
            tpair(T1 a, T2 b, T3 c) : first(a), second(b), third(c) {}

            void swap(tpair& other){
                std::swap(first, other.first);
                std::swap(second, other.second);
                std::swap(third, other.third);
            }
        };
};

#endif
