#include <cmath>
#include <iostream>
#include <string>
#include <vector>

using std::pow;
using std::string;
using std::vector;
typedef unsigned long long ull;


struct Data {
    string pattern, text;
};

Data read_input() {
    Data data;
    std::cin >> data.pattern >> data.text;
    return data;
}

void print_occurrences(const std::vector<int>& output) {
    for (size_t i = 0; i < output.size(); ++i)
        std::cout << output[i] << " ";
    std::cout << "\n";
}

std::vector<int> get_occurrences(const Data& input) {
    const string& s = input.pattern, t = input.text;
    std::vector<int> ans;
    for (size_t i = 0; i + s.size() <= t.size(); ++i)
        if (t.substr(i, s.size()) == s)
            ans.push_back(i);
    return ans;
}


long long polyhash(const string& s, int index, int length, int prime, int mult)
{
    long long hash { 0 };
    
    for (int i { index + length - 1 }; i >= index; --i)
    {
        hash = (mult * hash + s[i]) % prime;
    }
    
    return hash;
}

vector<long long> precompute_hashes(const string& text, const string& pattern, int prime, int mult)
{
    auto t_len = text.length();
    auto p_len = pattern.length();
    
    vector<long long> hashes(t_len - p_len + 1);
    
    long long y { 1 };
    for (int i { 1 }; i <= p_len; ++i)
    {
        y = y * mult % prime;
    }
    
    hashes.back() = polyhash(text, hashes.size() - 1, p_len, prime, mult);
    for (int i { static_cast<int>(hashes.size() - 2) }; i >= 0; --i)
    {
        hashes[i] = (mult * hashes[i + 1] + text[i] - y * text[i + p_len]) % prime;
        if (hashes[i] < 0)
        {
            hashes[i] += prime;
        }
    }
    
    return hashes;
}


vector<int> rabinkarp(const Data& input)
{
    int prime = 102191;
    int mult = rand() % prime + 1;
    vector<int> result;
    
    auto p_hash = polyhash(input.pattern, 0, input.pattern.length(), prime, mult);
    auto hashes = precompute_hashes(input.text, input.pattern, prime, mult);
    
    for (int h { 0 }; h < hashes.size(); ++h)
    {
        if (hashes[h] == p_hash)
        {
            if (input.text.substr(h, input.pattern.size()) == input.pattern)
            {
                result.push_back(h);
            }
        }
    }
    
    return result;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    print_occurrences(rabinkarp(read_input()));
    
    return 0;
}
