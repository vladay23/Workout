//    the implementation of the game tic tac toe in C++ 
//    by a user with a computer in such 
//    a way that the computer strives to win or play a draw 
//    (additions are needed to implement a draw, 
//    the difficulty level and the symbol for playing on the board)
//    LovDay 21.07.24
#include <iostream>
#include <random>

class TicTacToe
{
    public:
    bool checkWin(char board[3][3], char player);
    bool checkWinO(char board[3][3], char player);
    char selectQueue();
    
    void drawBoard(char board[3][3]);
    void realizeGame();
    void checkMoves(char board[3][3], int row, int col);
    void generateRandPosition(char board[3][3]);
    protected:
    char board[3][3] = { { ' ', ' ', ' ' }, 
					     { ' ', ' ', ' ' }, 
					     { ' ', ' ', ' ' } }; 
	char player = 'X'; 
	int row, col;
	int turn;
};

//    draw a board with zeros and crosses
void TicTacToe::drawBoard(char board[3][3]) 
{ 
    std::cout << "—————————————\n"; 
	for (int i = 0; i < 3; i++) { 
		std::cout << "| "; 
		for (int j = 0; j < 3; j++) { 
			std::cout << board[i][j] << " | "; 
		} 
		std::cout << "\n—————————————\n"; 
	} 
}

//    checking for a combination of three characters
bool TicTacToe::checkWin(char board[3][3], char player)
{
	for (int i = 0; i < 3; i++) { 
		if (board[i][0] == player && board[i][1] == player && board[i][2] == player) {
			return true;
		}
		if (board[0][i] == player && board[1][i] == player && board[2][i] == player) {
			return true;
		}
	} 
	if (board[0][0] == player && board[1][1] == player && board[2][2] == player) {
		return true;
	}
	if (board[0][2] == player && board[1][1] == player && board[2][0] == player) {
		return true;
	}
	return false; 
}

//    checking for a possible victory with the next move of the computer
bool TicTacToe::checkWinO(char board[3][3], char player)
{
    //sorting through possible combinations vertically and horizontally
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = 'O';
                if (checkWin(board, player)) {
                    return true;
                } else {
                    board[i][j] = ' ';
                }
            }
        }
        for (int j = 0; j < 3; j++) {
            if (board[j][i] == ' ') {
                board[j][i] = 'O';
                if (checkWin(board, player)) {
                    return true;
                } else {
                    board[j][i] = ' ';
                }
            }
        }
    }
    
    //sorting through possible combinations diagonally 
    //from left to right from top to bottom 
    //and from right to left from top to bottom
    for (int i = 0; i < 3; i++) {
        if (board[i][i] == ' ') {
            board[i][i] = 'O';
            if (checkWin(board, player)) {
                return true;
            } else {
                board[i][i] = ' ';
            }
        }
        for (int j = 0; j < 3; j++) {
            if ((board[j][i] == ' ') && (i + j == 2)) {
                board[j][i] = 'O';
                if (checkWin(board, player)) {
                    return true;
                } else {
                    board[j][i] = ' ';
                }
            }
        }
    }
    
    return false;
}

//    checking for a possible victory of the user 
//    and determining a possible position for the computer's move
void TicTacToe::checkMoves(char board[3][3], int row, int col)
{
    int col_i  = 0;
    int row_i  = 0;
    int diag_1 = 0;
    int diag_2 = 0;
    
    //count the number of user moves on each line
    for (int i = 0; i < 3; i++) {
        if (board[i][col] == 'X') {
            col_i++;
        }
        if (board[row][i] == 'X') {
            row_i++;
        }
    }
    
    for (int i = 0; i < 3; i++) {
        if (board[i][i] == 'X') {
            diag_1++;
        }
    }
    
    for (int i = 0; i < 3; i++) {
        for (int t = 0; t < 3; t++) {
            if ((i + t == 2) && (board[i][t] == 'X')) {
                diag_2++;
            }
        }
    }
    
    //if there are two user moves on at least one line 
    //and there is an empty cell, 
    //then the move is determined on it
    int moves = 0;
    
    if (col_i == 2) {
        for (int i = 0; i < 3; i++) {
            if (board[i][col] == ' ' && moves == 0) {
                board[i][col] = 'O';
                moves++;
            }
        }
    }
    
    if (row_i == 2 && moves == 0) {
        for (int i = 0; i < 3; i++) {
            if (board[row][i] == ' ' && moves == 0) {
                board[row][i] = 'O';
                moves++;
            }
        }
    }
    
    if (diag_1 == 2 && moves == 0) {
        for (int i = 0; i < 3; i++) {
            if (board[i][i] == ' ' && moves == 0) {
                board[i][i] = 'O';
                moves++;
            }
        }
    }
    
    if (diag_2 == 2 && moves == 0) {
        for (int i = 0; i < 3; i++) {
            for (int t = 0; t < 3; t++) {
                if ((t + i == 2) && (board[i][t] == ' ') && moves == 0) {
                    board[i][t] = 'O';
                    moves++;
                }
            }
        }
    }
    
    //if the number of user moves is less than two, 
    //then the computer's move is determined by a random combination
    if (moves == 0) {
        generateRandPosition(board);
    }
}

//    generating a random computer move
void TicTacToe::generateRandPosition(char board[3][3])
{
    int stop = 1;
    //the cycle repeats until 
    //a randomly empty board cell is found
    while(stop)
    {
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> dist2(0,2);
        
        int x = dist2(rng);
        int y = dist2(rng);
        
        if (board[x][y] == ' ') {
            board[x][y] = 'O';
            stop = 0;
        }
    }
}

//    determining the order of the user and computer's progress
char TicTacToe::selectQueue()
{
    std::cout << "Enter 1 if you want to be first and 2 if you want to be second: " << std::endl;
    int queue;
    std::cin >> queue;
    
    if (queue == 1) {
        return 'X';
    } else if (queue == 2) {
        return 'O';
    }
}

//    the implementation of the game of tic tac toe with a computer
void TicTacToe::realizeGame()
{
    std::cout << "Welcome to Tic-Tac-Toe!\n";
    
    player = selectQueue();
    
    for (turn = 1; turn <= 9; turn++) { 
		
		if (player == 'X') {
		    
		    drawBoard(board);
		    
		    while (true) {
			    std::cout << "Player " << player << ", enter row (0-2) and column (0-2): "; 
			    std::cin >> row >> col; 
			    
			    if (board[row][col] != ' ' || row < 0 || row > 2 || col < 0 || col > 2) {
				std::cout << "Invalid move. Try again.\n"; 
			    } else { 
				    break;
			    }
		    }
		    
		    board[row][col] = player; 
		    
		    if (checkWin(board, player)) { 
			drawBoard(board); 
			std::cout << "Player " << player << " wins!\n"; 
			break;
		    }
		} else {
		    if (checkWinO(board, player)) {
		        drawBoard(board); 
			std::cout << "Player " << player << " wins!\n"; 
			break;
		    } else {
		        if (turn == 1) {
		            generateRandPosition(board);
		        } else {
		            checkMoves(board, row, col);
		        }
		    }
	    }
	    
	    player = (player == 'X') ? 'O' : 'X'; 
	    
	    if (turn >= 8 && !checkWin(board, 'X') && !checkWin(board, 'O')) { 
		    std::cout << "It's a draw!\n";
		}
	}
}

int main() 
{
    //creating a game class variable 
    //and accessing the game implementation function
	TicTacToe match_exmpl;
	match_exmpl.realizeGame();

	return 0; 
}
