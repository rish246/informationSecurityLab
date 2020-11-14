#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <algorithm>
#include <sstream>
#include <unordered_map>
#include <queue>
using namespace std;
#define PUBLIC_KEY 65537
#define BLOCK_SIZE 3

int64_t plain_text = 688232789878879879;

int64_t p = 65479, q = 23833;

vector<int64_t> generate_blocks(int64_t plain_text, int size_block)
{
    vector<int64_t> output;
    int dividend = pow(10, size_block);

    while (plain_text)
    {
        int rem = plain_text % dividend;
        output.push_back(rem);
        plain_text /= dividend;
    }

    reverse(output.begin(), output.end());

    return output;
}

/*
    Implement a recursive algorithm to calculate
*/

int64_t calc_mod(int64_t base, int64_t power, int64_t mod)
{
    if (power == 0)
        return (1 % mod);

    if (power == 1)
        return (base % mod);

    int mid = (power / 2);

    int res = calc_mod(base, mid, mod);

    res = ((res % mod) * (res % mod)) % mod;

    if (power & 1)
        res = ((res % mod) * (base % mod)) % mod;

    return (res % mod);
}

vector<int64_t> encrypt(vector<int64_t> plaintext_blocks, int64_t p, int64_t q)
{
    int64_t n = (p * q);

    // public key
    int64_t e = PUBLIC_KEY;
    // blocks generate kar leta
    vector<int64_t> output_blocks;

    for (int64_t block : plaintext_blocks)
    {

        // encrypt block
        int64_t encrypted_block = calc_mod(block, e, n);
        // convert it into a single number
        output_blocks.push_back(encrypted_block);
    }

    return output_blocks;
}
/* 
    Euclid's algorithm code for finding modulo inverse
*/
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

    unordered_map<int64_t, vector<int64_t>> expansion = generate_map(A, x, B, y, d);
    unordered_map<int64_t, int64_t> consonent;
    queue<int64_t> q;

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

int64_t mod_inverse_euclid(int64_t e, int64_t t)
{

    // compute A, x, B, y and d

    int64_t A = t;
    int64_t B = e;
    int64_t x = 1;
    int64_t y = t / e;
    int64_t d = (A * x) - (B * y);

    pair<int64_t, int64_t> result = extended_euclid_algo(A, x, B, y, d);

    int64_t y_res = result.second;

    return (y_res < 0 ? (y_res + t) : y_res);
}

vector<int64_t> decrypt(vector<int64_t> cipher_blocks, int64_t p, int64_t q)
{
    int64_t n = (p * q);

    int64_t t = (p - 1) * (q - 1);

    int64_t e = PUBLIC_KEY;

    /*
    @TODO --> use extended euclid's algo to improve the performance
    */
    int64_t d = mod_inverse_euclid(e, t);

    d %= t;
    cout << d << endl;

    vector<int64_t> original_blocks;
    for (int64_t cipher_block : cipher_blocks)
    {
        int64_t original_block = calc_mod(cipher_block, d, n);
        original_blocks.push_back(original_block);
    }
    return original_blocks;
}

void print_vector(vector<int64_t> v)
{
    for (int64_t e : v)
        cout << e << " ";
    cout << endl;
}
int main()
{

    vector<int64_t> plaintext_blocks = generate_blocks(plain_text, BLOCK_SIZE);
    print_vector(plaintext_blocks);

    // encrypt in block of 3
    vector<int64_t> cipher_blocks = encrypt(plaintext_blocks, p, q);
    print_vector(cipher_blocks);

    vector<int64_t> original_blocks = decrypt(cipher_blocks, p, q);
    print_vector(original_blocks);
}

// inverse modulo cacl : 65537 mod 1560471696
// 1143906209