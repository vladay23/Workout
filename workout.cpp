#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>

//fills the vector dictionary with words and frequency of use
void input(int n, int q, std::vector<std::pair<std::string, int>>& vocabulary, 
            std::vector<std::string>& combs)
{
    std::pair<std::string, int> p;
    std::string word;
    int rate;
    
    for (int i = 0; i < n; i++) {
        std::cin >> word >> rate;
        p = std::make_pair(word, rate);
        vocabulary.push_back(p);
    }
    
    std::string str = "";
    char s;
    
    for (int i = 0; i < q; i++) {
        std::cin >> s;
        if (s == '+') {
            std::cin >> s;
            str += s;
        }
        else if (s == '-' and str != "") str.pop_back();
        combs.push_back(str);
    }
}

//iterates through the prefixes and the corresponding words, 
//outputs the ordinal numbers of the words 
//with the highest frequency of use corresponding to the prefix
void output_words_appropriate_prefixes(std::vector<std::pair<std::string, int>>& vocabulary, 
                                       std::vector<std::string>& combs)
{
    std::vector<std::string>::iterator it;
    
    for (it = combs.begin(); it != combs.end(); it++) {
        std::vector<int> rate;
        int max_rate = 0;
        int res_rate = 0;
        
        for (const auto& pair : vocabulary) {
            if (std::string(pair.first).find(*it) == 0) {
                rate.push_back(pair.second);
                res_rate++;
            }
        }
        
        max_rate = *max_element(begin(rate), end(rate));
        
        int pos = 0;
        for (const auto& pair : vocabulary) {
            pos++;
            if (pair.second == max_rate) {
                std::cout << " Word: " << pair.first 
                << ", the number of words containing this prefix " << res_rate 
                << ", the line number of the syllable " << pos << std::endl;
                break;
            }
        }
        
        rate.clear();
    }
}

int main()
{
    int N, Q;
    std::cin >> N >> Q;
    
    std::vector<std::pair<std::string, int>> vocabulary;
    std::vector<std::string> combs;
    
    input(N, Q, vocabulary, combs);
    output_words_appropriate_prefixes(vocabulary, combs);
    
    combs.clear();
    vocabulary.clear();
    
    return 0;
}
