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
        return 1;

    if (power == 1)
        return base;

    int mid = (power / 2);

    int res = pow_better(base, mid, mod);

    res = (res * res) % mod;

    if (power & 1)
        res = (res * base) % mod;

    return (res);
}

int main()
{
    int base, power, mod;

    while (true)
    {
        base = rand() % 20;
        power = rand() % 50;
        mod = rand() % 40;

        int res1 = pow_naive(base, power, mod);

        int res2 = pow_better(base, power, mod);

        if (res1 == res2)
            cout << "YES" << endl;

        else
            break;
    }
}