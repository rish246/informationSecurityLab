#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <algorithm>
#include <sstream>
#include <unordered_map>
#include <queue>
using namespace std;
#define PUBLIC_KEY 79
#define BLOCK_SIZE 3

uint64_t plain_text = 688232789878879879;

uint64_t p = 47, q = 97;

vector<uint64_t> generate_blocks(uint64_t plain_text, int size_block)
{
    vector<uint64_t> output;
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

uint64_t calc_mod(uint64_t base, uint64_t power, uint64_t mod)
{
    if (power == 0)
        return 1;

    if (power == 1)
        return base;

    int mid = (power / 2);

    int res = calc_mod(base, mid, mod);

    res = (res * res) % mod;

    if (power & 1)
        res = (res * base) % mod;

    return (res);
}

vector<uint64_t> encrypt(vector<uint64_t> plaintext_blocks, uint64_t p, uint64_t q)
{
    uint64_t n = (p * q);

    // public key
    uint64_t e = PUBLIC_KEY;
    // blocks generate kar leta
    vector<uint64_t> output_blocks;

    for (uint64_t block : plaintext_blocks)
    {

        // encrypt block
        uint64_t encrypted_block = calc_mod(block, e, n);
        // convert it into a single number
        output_blocks.push_back(encrypted_block);
    }

    return output_blocks;
}
/* 
    Euclid's algorithm code for finding modulo inverse
*/
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

uint64_t mod_inverse_euclid(uint64_t e, uint64_t t)
{

    // compute A, x, B, y and d

    uint64_t A = t;
    uint64_t B = e;
    uint64_t x = 1;
    uint64_t y = t / e;
    uint64_t d = (A * x) - (B * y);

    pair<uint64_t, uint64_t> result = extended_euclid_algo(A, x, B, y, d);

    return result.second;
}

vector<uint64_t> decrypt(vector<uint64_t> cipher_blocks, uint64_t p, uint64_t q)
{
    uint64_t n = (p * q);

    uint64_t t = (p - 1) * (q - 1);

    uint64_t e = PUBLIC_KEY;

    /*

    @TODO --> use extended euclid's algo to improve the performance

    */
    uint64_t d = mod_inverse_euclid(e, t);

    cout << d << endl;

    vector<uint64_t> original_blocks;
    for (uint64_t cipher_block : cipher_blocks)
    {
        uint64_t original_block = calc_mod(cipher_block, d, n);
        original_blocks.push_back(original_block);
    }
    return original_blocks;
}

void print_vector(vector<uint64_t> v)
{
    for (uint64_t e : v)
        cout << e << " ";
    cout << endl;
}
int main()
{

    vector<uint64_t> plaintext_blocks = generate_blocks(plain_text, BLOCK_SIZE);
    print_vector(plaintext_blocks);

    // encrypt in block of 3
    vector<uint64_t> cipher_blocks = encrypt(plaintext_blocks, p, q);

    print_vector(cipher_blocks);

    // uint64_t original_text =

    vector<uint64_t> original_blocks = decrypt(cipher_blocks, p, q);

    print_vector(original_blocks);
}