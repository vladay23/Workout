#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>

class GamePlatformer
{
    public:
    int calculating_position(std::string str); //calculating the value of the combination position
    void calculating_combinations(std::string str); //calculation of combinations and corresponding positions, 
                                                    //output of the number of unique values
    protected:
    std::string match;
};

int GamePlatformer::calculating_position(std::string str) 
{
    int position = 0;
    int direction = 0;
    for (int i = 0; i < str.size(); i++) {
        switch(str[i]) {
            case 'F': if (direction < 0) position--;
                      else position++;
                      break;
            case 'L': direction = -1; break;
            case 'R': direction = 1; break;
        }
    }
    return position;
}

void GamePlatformer::calculating_combinations(std::string str) 
{
    std::vector<int> results;
    char new_s1[100], new_s2[100], new_s3[100];
    
    for (int i = 0; i < str.size(); i++) {
        for (int j = 0; j < str.size(); j++) {
            if (i == j and j != 0) {
                new_s1[j] = 'R';
                new_s2[j] = 'L';
                new_s3[j] = 'F';
            }
            else {
                new_s1[j] = str[j];
                new_s2[j] = str[j];
                new_s3[j] = str[j];
            }
        }
        
        results.push_back(calculating_position(new_s1));
        results.push_back(calculating_position(new_s2));
        results.push_back(calculating_position(new_s3));
        //output for checking positions for combinations
        //cout << new_s1 << " " << res(new_s1) << endl;
        //cout << new_s2 << " " << res(new_s2) << endl;
        //cout << new_s3 << " " << res(new_s3) << endl;
    }
    
    sort(results.begin(), results.end());
    results.erase(unique(results.begin(), results.end()), results.end());
    //output of a vector of unique positions for verification
    //for (int i : results)
    //    cout << i << " ";
    
    std::cout << results.size();
}

int main()
{
    char str[1000];
    std::cout << " Platformer Game\n The player stands at position 0 at the beginning, when moving to the right,\n he moves to position (+1), and to the left — to (-1).\n Enter a combination of the letters F (making a move in a given direction), \n R (determining the direction to the right) and L (determining the direction to the left)\n to move the player. The catch is that according to the condition of the game,\n one of the entered commands will be read incorrectly. For example, if RLF is entered,\n the program will calculate the result of the move for each combination as LLF, RRF and other.\n The program will output the number of unique results of all possible combinations." << std::endl;
    std::cin >> str;
    GamePlatformer match_exmp;
    match_exmp.calculating_combinations(str);

    return 0;
}
