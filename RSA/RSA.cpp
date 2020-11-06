#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <algorithm>
#include <sstream>
using namespace std;
#define PUBLIC_KEY 79
#define BLOCK_SIZE 3

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

uint64_t encrypt_block(uint64_t block, uint64_t p, uint64_t q)
{
    uint64_t n = (p * q);

    // public key
    uint64_t e = PUBLIC_KEY;

    // private key+;
    return calc_mod(block, e, n);

    // encrypt formula
}

vector<uint64_t> encrypt(vector<uint64_t> plaintext_blocks, uint64_t p, uint64_t q)
{
    // blocks generate kar leta
    vector<uint64_t> output_blocks;
    for (uint64_t block : plaintext_blocks)
    {

        // encrypt block
        uint64_t encrypted_block = encrypt_block(block, p, q);
        // convert it into a single number
        output_blocks.push_back(encrypted_block);
    }

    return output_blocks;
}

int decrypt_block(uint64_t cipher_block, uint64_t p, uint64_t q)
{
    uint64_t n = (p * q);

    uint64_t t = (p - 1) * (q - 1);

    uint64_t e = PUBLIC_KEY;

    uint64_t d = ceil((double)t / e);

    while ((e * d) % t != 1)
        d++;
    // cout << d << endl;
    cout << d << endl;

    return calc_mod(cipher_block, d, n);
}

vector<uint64_t> decrypt(vector<uint64_t> cipher_blocks, uint64_t p, uint64_t q)
{

    vector<uint64_t> original_blocks;
    for (uint64_t cipher_block : cipher_blocks)
    {
        uint64_t original_block = decrypt_block(cipher_block, p, q);
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
    uint64_t plain_text = 688232;

    uint64_t p = 47, q = 71;

    vector<uint64_t> plaintext_blocks = generate_blocks(plain_text, BLOCK_SIZE);
    print_vector(plaintext_blocks);

    // encrypt in block of 3
    vector<uint64_t> cipher_blocks = encrypt(plaintext_blocks, p, q);

    print_vector(cipher_blocks);

    // uint64_t original_text =

    vector<uint64_t> original_blocks = decrypt(cipher_blocks, p, q);

    print_vector(original_blocks);
}