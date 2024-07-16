#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>

int main()
{
    int n, q, k;
    std::string word;
    std::vector<std::pair<std::string, int>> mas;
    std::pair<std::string, int> p;
    
    std::cin >> n >> q;
    
    //filling out the dictionary and the frequency of use of the word
    for (int i = 0; i < n; i++) {
        std::cin >> word >> k;
        p = std::make_pair(word, k);
        mas.push_back(p);
    }
    
    std::vector<std::string> combs;
    std::vector<std::string>::iterator c;
    std::string str = "";
    char s;
    
    //filling in the prefix vector, after sequential execution of commands
    for (int i = 0; i < q; i++) {
        std::cin >> s;
        if (s == '+') {
            std::cin >> s;
            str += s;
        }
        else if (s == '-' and str != "") str.pop_back();
        combs.push_back(str);
    }
    
    for (c = combs.begin(); c != combs.end(); c++) {
        std::vector<int> kol;
        int max_kol = 0;
        int res_kol = 0;
        
        /*if the word obtained from the commands is a prefix of a word 
        from the dictionary, then the number of matches is considered and 
        the filling of the vector with the number of frequency of use of the word*/
        for (const auto& pair : mas) {
            //if (pair.first.find(*c, 0) != std::string::npos) {
            if (std::string(pair.first).find(*c) == 0) {
                kol.push_back(pair.second);
                res_kol++;
            }
        }
        
        //which corresponds to the most frequently used
        max_kol = *max_element(begin(kol), end(kol));
        
        //search for a word in the dictionary by key — frequency of use
        int i = 0;
        for (const auto& pair : mas) {
            i++;
            if (pair.second == max_kol) {
                std::cout << " Word: " << pair.first << ", the number of words containing this prefix " 
                << res_kol << ", the line number of the syllable " << i << std::endl;
                break;
            }
        }
        //clearing the vector
        kol.clear();
    }
    //clearing the vector
    mas.clear();
    
    return 0;
}
