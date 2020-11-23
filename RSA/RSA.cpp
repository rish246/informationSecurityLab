#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <algorithm>
#include <sstream>
#include <unordered_map>
#include <queue>
#include <iomanip>
using namespace std;
#define PUBLIC_KEY 65537
#define BLOCK_SIZE 3

int64_t plain_text = 688232789878879879;

int64_t p = 63743, q = 23833;

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
    Computes the value of { (base ^ power) % mod }

    Time complexity = O(log(power))
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
/*
Main function for encrypting the plaintext blocks
@params:-> plaintext blocks, prime numbers p, q
@return:-> list of encrypted blocks

@Formula to encrypt a block:->
        encrypted_block = (original_block ^ e) % (p * q)
                        where, e = public key
*/

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
//////////////////////////// CODE FOR DECRYPTION OF FUNCTION ///////////////////////////////////////
/* 
    Extended euclid's algorithm for calculating modulo inverse of a number  
*/

/*
    @params:-> integers: A, x, B, y, d
    @return:-> map of equations

    @description:-> 
        Calculate the given set of euations such that A*x + B*y = 1
        Convert the set of equations in form of a map

        Eg: for equation of the form:
            A*x + B*y = d
        Output:
            {
                d: [A, x, B, y]
            }
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

/*
Main algorithm for computing modulo inverse using Euclid's algorithm
*/
pair<int64_t, int64_t> extended_euclid_algo(int64_t A, int64_t x, int64_t B, int64_t y, int64_t d)
{
    /* 
        Reprentation of equations are stored in the variable "expansion"
        eg: Equation:-> 3 * 7 - 5 * 4 = 1
            Entry in map = { 1 : [3, 7, 5, 4] } 

        **Used for implementing backward induction   
    */
    unordered_map<int64_t, vector<int64_t>> expansion = generate_map(A, x, B, y, d);

    /* 
        store the values of consonents of the variables in an equation 
        eg: Eqn:-> 3 * x - 4 * y = 7
            Entry in consonent :-> {x : 3}, {y : 4}
    */
    unordered_map<int64_t, int64_t> consonent;

    /* keeps track of the next number to be substituted in the main equation */
    queue<int64_t> q;

    /* push the value 1 to the queue: (as the remainder of the last eqn in euclid algo == 1) */
    q.push(1);
    consonent[1] = 1;

    while (!q.empty())
    {
        int64_t cur_d = q.front();
        q.pop();

        /* take the value of x, y, A, B from the eqn */
        int64_t first_val = expansion[cur_d][0], first_val_consonent = expansion[cur_d][1];

        int64_t second_val = expansion[cur_d][2], second_val_consonent = expansion[cur_d][3];

        /* substitute the values and compute consonants */
        consonent[first_val] += (consonent[cur_d] * first_val_consonent);

        consonent[second_val] -= (consonent[cur_d] * second_val_consonent);

        consonent[cur_d] = 0;

        /* Add the values to the queue */
        if (expansion[second_val].size())
            q.push(second_val);
        if (expansion[first_val].size())
            q.push(first_val);
    }

    return {consonent[A], consonent[B]};
}

/*
    Computes (e ^ -1) % t
*/
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

/*
    Main function for decryption
    @params:->  ciphertext block, prime numbers p and q
    @return:-> original text blocks

    @Formula for decrypting a block:
    original_block = { (cipher_block ^ d) % (p * q) }
                    where, d = (e ^ -1) % (p-1 * q-1)
*/
vector<int64_t> decrypt(vector<int64_t> cipher_blocks, int64_t p, int64_t q)
{
    int64_t n = (p * q);

    int64_t t = (p - 1) * (q - 1);

    int64_t e = PUBLIC_KEY;

    int64_t d = mod_inverse_euclid(e, t);

    d %= t;

    vector<int64_t> original_blocks;
    for (int64_t cipher_block : cipher_blocks)
    {
        /* decrypt each block */
        int64_t original_block = calc_mod(cipher_block, d, n);

        /* add the decrypted block to original blocks array*/
        original_blocks.push_back(original_block);
    }
    return original_blocks;
}

void print_vector(vector<int64_t> v, const string &message)
{
    cout << "-------------------------------------------------------------------------------------------------------" << endl;
    cout << setw(60) << message << endl;
    cout << "-------------------------------------------------------------------------------------------------------" << endl;

    for (int64_t e : v)
        cout << setw(15) << e << " ";
    cout << endl;
    cout << "-------------------------------------------------------------------------------------------------------" << endl
         << endl;
}
int main()
{
    cout << "-------------------------------------------------------------------------------------------------------" << endl;
    cout << setw(60) << "Original plaintext" << endl;
    cout << "-------------------------------------------------------------------------------------------------------" << endl;

    cout << setw(60) << plain_text << endl;
    cout << "-------------------------------------------------------------------------------------------------------" << endl;

    vector<int64_t> plaintext_blocks = generate_blocks(plain_text, BLOCK_SIZE);
    print_vector(plaintext_blocks, "Original plaintext blocks(size = 3)");

    // encrypt in block of 3
    vector<int64_t> cipher_blocks = encrypt(plaintext_blocks, p, q);
    print_vector(cipher_blocks, "Encrypted cipher blocks");

    vector<int64_t> original_blocks = decrypt(cipher_blocks, p, q);
    print_vector(original_blocks, "Decrypted plaintext blocks");
}