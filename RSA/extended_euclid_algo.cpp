#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <utility>
#include <math.h>

using namespace std;
int64_t p1 = 41023, p2 = 37699;
int64_t e = 65537;

int64_t mod_inverse_naive(int64_t e, int64_t p, int64_t q)
{
    int64_t t = (p - 1) * (q - 1);

    /*

    @TODO --> use extended euclid's algo to improve the performance

    */
    int64_t d = ceil((double)t / e);

    while ((e * d) % t != 1)
        d++;

    return d;
}

unordered_map<int64_t, vector<int64_t>> generate_map(int64_t A, int64_t x, int64_t B, int64_t y, int64_t d)
{
    unordered_map<int64_t, vector<int64_t>> result;
    while (d > 0)
    {
        result[d] = {A, x, B, y};
        A = B;
        B = d;
        y = (A / B);
        d = (A * x - B * y);
    }
    return result;
}

pair<int64_t, int64_t> extended_euclid_algo(int64_t A, int64_t x, int64_t B, int64_t y, int64_t d)
{
    // no map is being generated for this case

    unordered_map<int64_t, vector<int64_t>> expansion = generate_map(A, x, B, y, d);
    unordered_map<int64_t, int64_t> consonent;
    queue<int64_t> q;

    // cout << "Map == " << endl;
    // for (auto entry : expansion)
    // {
    //     cout << entry.first << " : ";
    //     for (auto val : entry.second)
    //     {
    //         cout << val << " ";
    //     }
    //     cout << endl;
    // }

    q.push(1);
    consonent[1] = 1;

    while (!q.empty())
    {
        int64_t cur_d = q.front();
        q.pop();

        int64_t first_val = expansion[cur_d][0], first_val_consonent = expansion[cur_d][1];

        int64_t second_val = expansion[cur_d][2], second_val_consonent = expansion[cur_d][3];

        consonent[first_val] += (consonent[cur_d] * first_val_consonent);

        consonent[second_val] -= (consonent[cur_d] * second_val_consonent);

        consonent[cur_d] = 0;

        if (expansion[second_val].size())
            q.push(second_val);
        if (expansion[first_val].size())
            q.push(first_val);
    }

    return {consonent[A], consonent[B]};
}

int64_t mod_inverse_euclid(int64_t e, int64_t p1, int64_t p2)
{

    int64_t t = (p1 - 1) * (p2 - 1);

    // compute A, x, B, y and d

    int64_t A = t;
    int64_t B = e;
    int64_t x = 1;
    int64_t y = t / e;
    int64_t d = (A * x) - (B * y);
    if (d == 0)
        return -1;
    // found the bug
    pair<int64_t, int64_t> result = extended_euclid_algo(A, x, B, y, d);

    int64_t y_res = result.second;

    return (y_res < 0 ? (y_res + t) : y_res);
}
int main()
{
    // int64_t mod_inv_e = mod_inverse_naive(e, p1, p2);

    // cout << mod_inv_e << endl;

    // int64_t mod_inv_e_better = mod_inverse_euclid(e, p1, p2);

    // cout << mod_inv_e_better << endl;
    vector<int> hundred_primes = {2,
                                  3,
                                  5,
                                  7,
                                  11,
                                  13,
                                  17,
                                  19,
                                  23,
                                  29,
                                  31,
                                  37,
                                  41,
                                  43,
                                  47,
                                  53,
                                  59,
                                  61,
                                  67,
                                  71,
                                  73,
                                  79,
                                  83,
                                  89,
                                  97,
                                  101,
                                  103,
                                  107,
                                  109,
                                  113,
                                  127,
                                  131,
                                  137,
                                  139,
                                  149,
                                  151,
                                  157,
                                  163,
                                  167,
                                  173,
                                  179,
                                  181,
                                  191,
                                  193,
                                  197,
                                  199,
                                  211,
                                  223,
                                  227,
                                  229,
                                  233,
                                  239,
                                  241,
                                  251,
                                  257,
                                  263,
                                  269,
                                  271,
                                  277,
                                  281,
                                  283,
                                  293,
                                  307,
                                  311,
                                  313,
                                  317,
                                  331,
                                  337,
                                  347,
                                  349,
                                  353,
                                  359,
                                  367,
                                  373,
                                  379,
                                  383,
                                  389,
                                  397,
                                  401,
                                  409,
                                  419,
                                  421,
                                  431,
                                  433,
                                  439,
                                  443,
                                  449,
                                  457,
                                  461,
                                  463,
                                  467,
                                  479,
                                  487,
                                  491,
                                  499,
                                  503,
                                  509,
                                  521,
                                  523,
                                  541};

    // // generate e, p, p such that e and p are coPrime numbers
    while (true)
    {
        // 3 prime numbers
        int e_idx = rand() % 50;
        int p_idx = rand() % 50 + 50;
        int q_idx = rand() % 50 + 50;
        if (e_idx != p_idx && p_idx != q_idx)
        {
            // run test
            int e = hundred_primes[e_idx];
            int p = hundred_primes[p_idx];
            int q = hundred_primes[q_idx];
            cout << e_idx << " " << p_idx << " " << q_idx << endl;

            int res1 = mod_inverse_euclid(e, p, q);
            if (res1 == -1)
                continue;
            int res2 = mod_inverse_naive(e, p, q);

            if (res1 != res2 && res1 != -1)
            {
                cout << e << " " << p << " " << q << endl;
                cout << res1 << " " << res2 << endl;
                break;
            }

            cout << "OK" << endl;
        }
    }
    // int e = 17, p = 373, q = 307;
    // int res = mod_inverse_euclid(e, p, q);
    // cout << res << endl;
    // int64_t t = (p1 - 1) * (p2 - 1);

    // pair<int, int> res = extended_euclid_algo(t, 1, e, )
}
// 17 373 307 --> 3 variables