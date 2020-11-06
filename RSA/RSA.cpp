#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <algorithm>
#include <sstream>
using namespace std;

vector<int> generate_blocks(uint64_t plain_text, int size_block)
{
    vector<int> output;
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

int calc_mod(int base, int power, int mod)
{
    int i = 1;
    int res = 1;
    while (i <= power)
    {
        res = (res * base) % mod;
        i++;
    }
    return res;
}

int encrypt_block(int block, uint64_t p, uint64_t q)
{
    int n = (p * q);

    // public key
    int e = 79;

    // private key+;
    return calc_mod(block, e, n);

    // encrypt formula
}

vector<int> encrypt(vector<int> plaintext_blocks, uint64_t p, uint64_t q)
{
    // blocks generate kar leta
    vector<int> output_blocks;
    for (int block : plaintext_blocks)
    {

        // encrypt block
        int encrypted_block = encrypt_block(block, p, q);
        // convert it into a single number
        output_blocks.push_back(encrypted_block);
    }

    return output_blocks;
}

int decrypt_block(int cipher_block, uint64_t p, uint64_t q)
{
    int n = (p * q);

    int t = (p - 1) * (q - 1);

    int e = 79;

    int d = ceil((double)t / e);

    while ((e * d) % t != 1)
        d++;
    // cout << d << endl;

    return calc_mod(cipher_block, d, n);
}

vector<int> decrypt(vector<int> cipher_blocks, uint64_t p, uint64_t q)
{

    vector<int> original_blocks;
    for (int cipher_block : cipher_blocks)
    {
        int original_block = decrypt_block(cipher_block, p, q);
        original_blocks.push_back(original_block);
    }
    return original_blocks;
}

void print_vector(vector<int> v)
{
    for (int e : v)
        cout << e << " ";
    cout << endl;
}
int main()
{
    uint64_t plain_text = 688232;

    uint64_t p = 47, q = 71;

    vector<int> plaintext_blocks = generate_blocks(plain_text, 3);

    // encrypt in block of 3
    vector<int> cipher_blocks = encrypt(plaintext_blocks, p, q);

    print_vector(cipher_blocks);

    // uint64_t original_text =

    vector<int> original_blocks = decrypt(cipher_blocks, p, q);

    print_vector(original_blocks);
}