#include <iostream>

class TicTacToe
{
    public:
    bool checkWin(char board[3][3], char player);
    int  count(char board[3][3], int row, int col);
    bool checkWinO(char board[3][3], char player);
    char selectQueue();
    
    void drawBoard(char board[3][3]);
    void realizGame();
    void checkCross(char board[3][3], int row, int col);
    
    protected:
    char board[3][3] = { { ' ', ' ', ' ' }, 
					     { ' ', ' ', ' ' }, 
					     { ' ', ' ', ' ' } }; 
	char player = 'X'; 
	int row, col;
	int turn;
};
 
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

bool TicTacToe::checkWinO(char board[3][3], char player)
{
    
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

void TicTacToe::checkCross(char board[3][3], int row, int col)
{
    int col_i  = 0;
    int row_i  = 0;
    int diag_1 = 0;
    int diag_2 = 0;
    
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
    
    if (col_i == 2) {
        for (int i = 0; i < 3; i++) {
            if (board[i][col] == ' ') {
                board[i][col] = 'O';
                break;
            }
        }
    } else
    if (row_i == 2) {
        for (int i = 0; i < 3; i++) {
            if (board[row][i] == ' ') {
                board[row][i] = 'O';
                break;
            }
        }
    } else 
    if (diag_1 == 2) {
        for (int i = 0; i < 3; i++) {
            if (board[i][i] == ' ') {
                board[i][i] = 'O';
                break;
            }
        }
    } else
    if (diag_2 == 2) {
        for (int i = 0; i < 3; i++) {
            for (int t = 0; t < 3; t++) {
                if ((t + i == 2) && (board[i][t] == ' ')) {
                    board[i][t] = 'O';
                    break;
                }
            }
        }
    }
    else {
        int l = 0;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (l == 0) {
                    if (board[i][j] == ' ') {
                        board[i][j] = 'O';
                        l++;
                    }
                }
            }
        }
    }
}

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

void TicTacToe::realizGame()
{
    std::cout << "Welcome to Tic-Tac-Toe!\n";
    
    player = selectQueue();
    
    for (turn = 0; turn < 9; turn++) { 
		
		if (player == 'X') {
		//if (turn%2 == 0) {
		    
		    drawBoard(board);
		    
		    while (true) {
			    std::cout << "Player " << player 
				    << ", enter row (0-2) and column (0-2): "; 
			    std::cin >> row >> col; 
			    
			    if (board[row][col] != ' ' || row < 0 || row > 2 
				    || col < 0 || col > 2) { 
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
		        checkCross(board, row, col);
		    }
	    }
	    
	    player = (player == 'X') ? 'O' : 'X'; 
	    
	    if (turn == 9 && !checkWin(board, 'X') 
		    && !checkWin(board, 'O')) { 
		    std::cout << "It's a draw!\n";
		}
	}
}

int main() 
{
	TicTacToe match_exmpl;
	match_exmpl.realizGame();

	return 0; 
}
