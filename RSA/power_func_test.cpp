#include <iostream>
using namespace std;

int pow_naive(int base, int power, int mod)
{
    int res = 1;
    int i = 1;
    while (i <= power)
    {
        res = (res * base) % mod;
        i++;
    }

    return res;
}

int pow_better(int base, int power, int mod)
{
    if (power == 0)
        return (1 % mod);

    if (power == 1)
        return (base % mod);

    int mid = (power / 2);

    int res = pow_better(base, mid, mod);

    res = ((res % mod) * (res % mod)) % mod;

    if (power & 1)
        res = ((res % mod) * (base % mod)) % mod;

    return (res % mod);
}

int main()
{
    while (true)
    {
        int base, power, mod;

        base = (int)rand() % 10000;
        power = (int)rand() % 13993;
        mod = (int)rand() % 1345 + 1;
        int res1 = pow_naive(base, power, mod);
        int res2 = pow_better(base, power, mod);
        if (res1 != res2)
        {
            cout << res1 << " " << res2 << endl;
            cout << base << " " << power << " " << mod << endl;
            break;
        }
        cout << "OK" << endl;
    }
    // int base = 5358, power = 1, mod = 900;
    // pow_better(base, power, mod);
}