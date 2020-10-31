#include <iostream>
#include <climits>
#include <stdio.h>
#include <bitset>
#include <vector>
#include <algorithm>
#include <math.h>
#include <sstream>
#include <unordered_map>

using namespace std;

#define uint28_t bitset<28>
#define MOD_ENCRYPT 0
#define MOD_DECRYPT 1

int p_box_perm[32] = {16, 7, 20, 21,
                      29, 12, 28, 17,
                      1, 15, 23, 26,
                      5, 18, 31, 10,
                      2, 8, 24, 14,
                      32, 27, 3, 9,
                      19, 13, 30, 6,
                      22, 11, 4, 25};

int exp_perm[48] = {32, 1, 2, 3, 4, 5, 4, 5,
                    6, 7, 8, 9, 8, 9, 10, 11,
                    12, 13, 12, 13, 14, 15, 16, 17,
                    16, 17, 18, 19, 20, 21, 20, 21,
                    22, 23, 24, 25, 24, 25, 26, 27,
                    28, 29, 28, 29, 30, 31, 32, 1};

///////////////////////////////////////////////////////////////////////////////

// not working
string bin_to_hex(string s)
{
    // binary to hexadecimal conversion
    unordered_map<string, string> mp;
    mp["0000"] = "0";
    mp["0001"] = "1";
    mp["0010"] = "2";
    mp["0011"] = "3";
    mp["0100"] = "4";
    mp["0101"] = "5";
    mp["0110"] = "6";
    mp["0111"] = "7";
    mp["1000"] = "8";
    mp["1001"] = "9";
    mp["1010"] = "A";
    mp["1011"] = "B";
    mp["1100"] = "C";
    mp["1101"] = "D";
    mp["1110"] = "E";
    mp["1111"] = "F";
    string hex = "";
    for (int i = 0; i < s.length(); i += 4)
    {
        string ch = "";
        ch += s[i];
        ch += s[i + 1];
        ch += s[i + 2];
        ch += s[i + 3];
        hex += mp[ch];
    }
    return hex;
}

string hex_to_bin(string hex_str)
{
    unordered_map<char, string> mp;
    mp['0'] = "0000";
    mp['1'] = "0001";
    mp['2'] = "0010";
    mp['3'] = "0011";
    mp['4'] = "0100";
    mp['5'] = "0101";
    mp['6'] = "0110";
    mp['7'] = "0111";
    mp['8'] = "1000";
    mp['9'] = "1001";
    mp['A'] = "1010";
    mp['B'] = "1011";
    mp['C'] = "1100";
    mp['D'] = "1101";
    mp['E'] = "1110";
    mp['F'] = "1111";
    string bin = "";
    for (int i = 0; i < hex_str.size(); i++)
    {
        bin += mp[hex_str[i]];
    }
    return bin;
}

int s_box_perm[8][4][16] = {{14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
                             0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
                             4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
                             15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13},
                            {15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,
                             3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
                             0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
                             13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9},

                            {10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,
                             13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
                             13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,
                             1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12},
                            {7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,
                             13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
                             10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,
                             3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14},
                            {2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,
                             14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,
                             4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,
                             11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3},
                            {12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,
                             10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
                             9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,
                             4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13},
                            {4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,
                             13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
                             1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,
                             6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12},
                            {13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7,
                             1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,
                             7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,
                             2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}};

// Fix the bug in this function
string apply_s_box_perm(string input)
{

    string output = "";

    for (int n_group = 0; n_group < 8; n_group++)
    {
        string cur_group_op = "";
        int start_idx = n_group * 6;

        string cur_str = input.substr(start_idx, 6);

        int s_table_row = (cur_str[0] - '0') * 2 + (cur_str[5] - '0');
        int s_table_col = bitset<4>(cur_str.substr(1, 4)).to_ulong();

        cur_group_op += bitset<4>(s_box_perm[n_group][s_table_row][s_table_col]).to_string();

        output += cur_group_op;

        // cout << n_group << " --> " << cur_str << " " << cur_group_op << endl;
    }

    return output;
}

string apply_perm(int *arr, string input, size_t output_len)
{
    string output;

    output.resize(output_len);

    for (size_t i = 0; i < output_len; i++)
    {
        output[i] = input[arr[i] - 1];
    }

    return output;
}

int initial_perm[64] = {58, 50, 42, 34, 26, 18, 10, 2,
                        60, 52, 44, 36, 28, 20, 12, 4,
                        62, 54, 46, 38, 30, 22, 14, 6,
                        64, 56, 48, 40, 32, 24, 16, 8,
                        57, 49, 41, 33, 25, 17, 9, 1,
                        59, 51, 43, 35, 27, 19, 11, 3,
                        61, 53, 45, 37, 29, 21, 13, 5,
                        63, 55, 47, 39, 31, 23, 15, 7};
// encrypts data using this key

int pc2[48] = {14, 17, 11, 24, 1, 5,
               3, 28, 15, 6, 21, 10,
               23, 19, 12, 4, 26, 8,
               16, 7, 27, 20, 13, 2,
               41, 52, 31, 37, 47, 55,
               30, 40, 51, 45, 33, 48,
               44, 49, 39, 56, 34, 53,
               46, 42, 50, 36, 29, 32};

int pc1[56] = {57, 49, 41, 33, 25, 17, 9,
               1, 58, 50, 42, 34, 26, 18,
               10, 2, 59, 51, 43, 35, 27,
               19, 11, 3, 60, 52, 44, 36,
               63, 55, 47, 39, 31, 23, 15,
               7, 62, 54, 46, 38, 30, 22,
               14, 6, 61, 53, 45, 37, 29,
               21, 13, 5, 28, 20, 12, 4};

int final_perm[64] = {40, 8, 48, 16, 56, 24, 64, 32,
                      39, 7, 47, 15, 55, 23, 63, 31,
                      38, 6, 46, 14, 54, 22, 62, 30,
                      37, 5, 45, 13, 53, 21, 61, 29,
                      36, 4, 44, 12, 52, 20, 60, 28,
                      35, 3, 43, 11, 51, 19, 59, 27,
                      34, 2, 42, 10, 50, 18, 58, 26,
                      33, 1, 41, 9, 49, 17, 57, 25};

// keys will be same for each block
/*
    CODE FOR ENCRYPTION
*/
string encrypt_block(bitset<64> data_bts, vector<string> compressed_keys)
{
    // bitset<64> data_bts(data);
    // apply initial perm on data
    string data_block = apply_perm(initial_perm, data_bts.to_string(), 64);

    string l_data = data_block.substr(0, 32);
    string r_data = data_block.substr(32, 32);

    for (int i_round = 0; i_round < 16; i_round++)
    {
        // L_shift
        // compression
        string compressed_key = compressed_keys[i_round];

        string r_data_copy = r_data;

        // data operations start
        string r_data_exp = apply_perm(exp_perm, r_data, 48);

        r_data_exp = (bitset<48>(r_data_exp) ^ bitset<48>(compressed_key)).to_string();

        string r_data_s_box = apply_s_box_perm(r_data_exp);

        string r_data_p_box = apply_perm(p_box_perm, r_data_s_box, 32);

        r_data_p_box = (bitset<32>(r_data_p_box) ^ bitset<32>(l_data)).to_string();

        if (i_round != 15)
        {
            r_data = r_data_p_box;

            l_data = r_data_copy;
        }
        else
        {
            l_data = r_data_p_box;
        }
        cout << "Round " << (i_round + 1) << " " << bin_to_hex(l_data) << " " << bin_to_hex(r_data) << " " << bin_to_hex(compressed_key) << endl;
    }

    // apply final permute
    string cipher_block = apply_perm(final_perm, (l_data + r_data), 64);

    return bin_to_hex(cipher_block);
}

string encrypt(string data, vector<string> &compressed_keys)
{
    string data_bin = hex_to_bin(data);

    int size_block = 16;

    int total_blocks = (data.size() / size_block);

    string cipher_text = "";

    for (int n_block = 0; n_block < total_blocks; n_block++)
    {
        int starting_idx = n_block * size_block;

        string cur_block = data_bin.substr(starting_idx, size_block * 4);

        // cout << cur_block << endl;

        // encrypt cur block
        string res = encrypt_block(bitset<64>(cur_block), compressed_keys);

        cipher_text += res;
    }

    return cipher_text;
}

string decrypt(const string &data, vector<string> compressed_keys)
{
    reverse(compressed_keys.begin(), compressed_keys.end());

    return encrypt(data, compressed_keys);
}

/*********************************************
 * 
 * CODE FOR PREPARING KEYS (K1 -> K16)
 * 
 * 
 * ********************************************/
int l_shift_table[16] = {1, 1, 2, 2,
                         2, 2, 2, 2,
                         1, 2, 2, 2,
                         2, 2, 2, 1};

string L_shift(string input, int num_steps)
{

    string append_end = input.substr(0, num_steps);

    // remove
    input.erase(input.begin(), input.begin() + num_steps);

    input += append_end;

    return input;
}

vector<string> prepare_compressed_keys(const string &key)
{
    // apply pc1
    vector<string> compressed_keys(16);

    string key_final = apply_perm(pc1, key, 56);

    string l_key = key_final.substr(0, 28);

    string r_key = key_final.substr(28, 28);

    for (int i_round = 0; i_round < 16; i_round++)
    {
        l_key = L_shift(l_key, l_shift_table[i_round]);
        r_key = L_shift(r_key, l_shift_table[i_round]);

        // compression
        string compressed_key = apply_perm(pc2, l_key + r_key, 48);
        compressed_keys[i_round] = compressed_key;
    }

    return compressed_keys;
}

///////////////////////////////////////////////////////////////////////////////
int main()
{
    // key same
    string key = "AABB09182736CCDD";

    string data = "123456ABCD132536";

    string key_bin = hex_to_bin(key);

    vector<string> compressed_keys = prepare_compressed_keys(key_bin);

    string cipher_text = encrypt(data, compressed_keys);
    cout << "Cipher text = " << cipher_text << endl;

    string original_text = decrypt(cipher_text, compressed_keys);

    cout << "Original Text = " << original_text << endl;
}
