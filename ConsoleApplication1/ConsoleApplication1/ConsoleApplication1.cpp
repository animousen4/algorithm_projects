#include <iostream>

const long long mod = 1000000007;

long long fact(long long num) {
    if (num > 1)
        return (num * fact(num - 1)) % mod;
    else
        return 1;

}

long long pow(long long num, long long s) {
    long long p = 1;

    while (s > 0) {
        if (s % 2 != 0)
            p = (p * num) % mod;

        num = (num * num) % mod;
        s = s / 2;
    }

    return p;
}

int main()
{
    long long n;
    long long k;
    long long t;
    long long zn;

    std::cin >> n >> k;

    t = fact(n);

    zn = (fact(k) * fact(n - k)) % mod;

    std::cout << (t * (pow(zn, mod - 2) % mod)) % mod;

}
