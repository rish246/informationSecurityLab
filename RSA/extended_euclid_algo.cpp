#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <utility>
#include <math.h>

using namespace std;
uint64_t p1 = 41023, p2 = 37699;
uint64_t e = 65537;

uint64_t mod_inverse_naive(uint64_t e, uint64_t p, uint64_t q)
{
    uint64_t t = (p - 1) * (q - 1);

    /*

    @TODO --> use extended euclid's algo to improve the performance

    */
    uint64_t d = ceil((double)t / e);

    while ((e * d) % t != 1)
        d++;

    return d;
}

unordered_map<uint64_t, vector<uint64_t>> generate_map(uint64_t A, uint64_t x, uint64_t B, uint64_t y, uint64_t d)
{
    unordered_map<uint64_t, vector<uint64_t>> result;
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

pair<uint64_t, uint64_t> extended_euclid_algo(uint64_t A, uint64_t x, uint64_t B, uint64_t y, uint64_t d)
{

    unordered_map<uint64_t, vector<uint64_t>> expansion = generate_map(A, x, B, y, d);
    unordered_map<uint64_t, uint64_t> consonent;
    queue<uint64_t> q;

    q.push(1);
    consonent[1] = 1;

    while (!q.empty())
    {
        uint64_t cur_d = q.front();
        q.pop();

        uint64_t first_val = expansion[cur_d][0], first_val_consonent = expansion[cur_d][1];

        uint64_t second_val = expansion[cur_d][2], second_val_consonent = expansion[cur_d][3];

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

uint64_t mod_inverse_euclid(uint64_t e, uint64_t p1, uint64_t p2)
{
    uint64_t n = (p1 * p2);

    uint64_t t = (p1 - 1) * (p2 - 1);

    // compute A, x, B, y and d

    uint64_t A = t;
    uint64_t B = e;
    uint64_t x = 1;
    uint64_t y = t / e;
    uint64_t d = (A * x) - (B * y);

    pair<uint64_t, uint64_t> result = extended_euclid_algo(A, x, B, y, d);

    uint64_t x_res = result.first;
    uint64_t y_res = result.second;

    return y_res;
}
int main()
{
    uint64_t mod_inv_e = mod_inverse_naive(e, p1, p2);

    cout << mod_inv_e << endl;

    uint64_t mod_inv_e_better = mod_inverse_euclid(e, p1, p2);

    cout << mod_inv_e_better << endl;

    // uint64_t t = (p1 - 1) * (p2 - 1);

    // pair<int, int> res = extended_euclid_algo(t, 1, e, )
}