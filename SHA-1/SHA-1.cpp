#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <math.h>
#include <bitset>
#include <vector>

using namespace std;

/* */
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
    for (int i = 0; i < (int)s.length(); i += 4)
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
    for (int i = 0; i < (int)hex_str.size(); i++)
    {
        bin += mp[hex_str[i]];
    }
    return bin;
}

void pad_message(string &hex_string)
{
    string bin_string = hex_to_bin(hex_string);
    int len_bin_string = bin_string.size();
    bin_string += '1';

    // append zeros to the string
    int n_zeros = 512 - 64 - bin_string.size();
    bin_string += string(n_zeros, '0');

    // pad the string with the length of the original message in 64 bits form
    bin_string += bitset<64>(len_bin_string).to_string();

    hex_string = bin_to_hex(bin_string);
}

string L_shift(string input, int num_steps)
{

    string append_end = input.substr(0, num_steps);

    input.erase(input.begin(), input.begin() + num_steps);

    input += append_end;

    return input;
}

string expansion_func(string bin_X, string bin_Y, string bin_Z, int i_operation)
{
    i_operation /= 20;

    bitset<32> X_bts(bin_X);
    bitset<32> Y_bts(bin_Y);
    bitset<32> Z_bts(bin_Z);
    switch (i_operation)
    {
    case 0:
        return ((X_bts & Y_bts) | ((~X_bts) & Z_bts)).to_string();
        break;
    case 1:
        return (X_bts ^ Y_bts ^ Z_bts).to_string();
        break;
    case 2:
        return ((X_bts & Y_bts) | (X_bts & Z_bts) | (Y_bts & Z_bts)).to_string();
        break;
    case 3:
        return ((X_bts ^ Y_bts ^ Z_bts)).to_string();
        break;
    default:
        return "";
    }
}

vector<string> message_blocks(16);

void generate_message_blocks(string message)
{
    int n_blocks = 16;

    for (int i_block = 0; i_block < n_blocks; i_block++)
    {
        int starting_idx = i_block * 32;

        message_blocks.push_back(message.substr(starting_idx, 32));
    }
}

vector<string> cache_w_outputs(80);
string get_w(int i_operation)
{
    if (i_operation <= 15)
        return message_blocks[i_operation];

    if (cache_w_outputs[i_operation] != "")
        return cache_w_outputs[i_operation];
    cache_w_outputs[i_operation] = L_shift((bitset<32>(get_w(i_operation - 3)) ^ bitset<32>(get_w(i_operation - 8)) ^ bitset<32>(get_w(i_operation - 14)) ^ bitset<32>(get_w(i_operation - 16))).to_string(), 1);
    return cache_w_outputs[i_operation];
}

string get_k(int i_operation)
{
    i_operation /= 20;

    switch (i_operation)
    {
    case 0:
        return hex_to_bin("5A827999");
        break;
    case 1:
        return hex_to_bin("6ED9EBA1");
        break;
    case 2:
        return hex_to_bin("8F1BBCDC");
        break;
    case 3:
        return hex_to_bin("CA62C1D6");
        break;

    default:
        break;
    }
}

int main()
{
    string message = "ABEE3454345543455434543DDEE5456432245667432456677443213456643224566ABBBBAEBFBDBBCCD123";

    // pad message
    pad_message(message);

    generate_message_blocks(message);

    /* declare the variables */
    string A = "67452301";
    string B = "efcdab89";
    string C = "98badcfe";
    string D = "10325476";
    string E = "c3d2e1f0";

    /* total operations performed in SHA */
    int n_operations = 80;

    string a = hex_to_bin(A);
    string b = hex_to_bin(B);
    string c = hex_to_bin(C);
    string d = hex_to_bin(D);
    string e = hex_to_bin(E);

    for (int i_operation = 0; i_operation < n_operations; i_operation++)
    {
        uint64_t temp = bitset<32>(L_shift(a, 5)).to_ulong() + bitset<32>(expansion_func(b, c, d, i_operation)).to_ulong() + bitset<32>(e).to_ulong() + bitset<32>(get_w(i_operation)).to_ulong() + bitset<32>(get_k(i_operation)).to_ulong();

        e = d;

        d = c;

        c = L_shift(b, 30);

        b = a;

        a = bitset<32>(temp).to_string();
    }

    cout << bin_to_hex(a) << " " << bin_to_hex(b) << " " << bin_to_hex(c) << " " << bin_to_hex(d) << " " << bin_to_hex(e) << endl;
}