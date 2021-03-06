#include <curses.h>
#include <iostream>
#include <math.h>
#include <fstream>
#include <ctime>
#include <unistd.h>
#include <chrono>
#include <thread>
using namespace std;
string help = "q\t\t: to quit the game\n"
              "w|a|s|d\t\t: move cursor\n"
              "enter + [1-9]\t: insert number at cursor position\n"
              "v\t\t: validate\n"
              "c\t\t: clear current number\n"
              "p\t\t: print progress to file\n"
              "l\t\t: load sudoku from file\n"
              "k\t\t: to let the computer solve the Sodoku\n"
              "m\t\t: mode selection\n"
              "\nIf mode is set to easy you can see\nthree lists of numbers below the Sudoku.\nThese are the missing numbers for the current Row, Column and Cell.\n\n";
string error = "";
int matrix[9][9] = {{1, 0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 2, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 3, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 4, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 5, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 6, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 7, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 8, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0, 9}};
int cell[9][9];

int currX = 1;
int currY = 1;

enum mode {
    Easy = 1,
    Medium = 2,
    Hard = 3
};

mode m;




void initCurses() {
    initscr();
    cbreak();
    noecho();
    clear();
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    m = Easy;
}

void fillCell(int x, int y) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            cell[y + (x * 3)][(i * 3) + j] = matrix[(x * 3) + i][(y * 3) + j];
        }
    }
}

void fillCellArr() {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            fillCell(j, i);
        }
    }
}

string arrToString(int arr[]) {
    string arrString = "";
    return arrString;
}

int h[9], v[9], c[9];

void hRec(int i) {
    if (i < 9) {
        for (int j = 0; j < 9; ++j) {
            if (matrix[currX][j] == i + 1) {
                h[i] = 0;
                break;
            }
        }
        hRec(i + 1);
    }
}

void vRec(int i) {
    if (i < 9) {
        for (int j = 0; j < 9; ++j) {
            if (matrix[j][currY] == i + 1) {
                v[i] = 0;
                break;
            }
        }
        vRec(i + 1);
    }
}

void cRec(int i) {

    if (i < 9) {
        for (int j = 0; j < 9; ++j) {

            if (currY < 3) {
                if (currX < 3) {
                    if (cell[0][j] == i + 1) {
                        c[i] = 0;
                        break;
                    }
                } else if (currX < 6) {
                    if (cell[3][j] == i + 1) {
                        c[i] = 0;
                        break;
                    }
                } else if (currX < 9) {
                    if (cell[6][j] == i + 1) {
                        c[i] = 0;
                        break;
                    }
                }
            } else if (currY < 6) {
                if (currX < 3) {
                    if (cell[1][j] == i + 1) {
                        c[i] = 0;
                        break;
                    }
                } else if (currX < 6) {
                    if (cell[4][j] == i + 1) {
                        c[i] = 0;
                        break;
                    }
                } else if (currX < 9) {
                    if (cell[7][j] == i + 1) {
                        c[i] = 0;
                        break;
                    }
                }
            } else if (currY < 9) {
                if (currX < 3) {
                    if (cell[2][j] == i + 1) {
                        c[i] = 0;
                        break;
                    }
                } else if (currX < 6) {
                    if (cell[5][j] == i + 1) {
                        c[i] = 0;
                        break;
                    }
                } else if (currX < 9) {
                    if (cell[8][j] == i + 1) {
                        c[i] = 0;
                        break;
                    }
                }
            }
        }
        cRec(i + 1);
    }
}

string buildCheatString() {
    for (int i = 0; i < 9; ++i) {
        h[i] = i + 1;
        v[i] = i + 1;
        c[i] = i + 1;
    }
    hRec(0);
    vRec(0);
    cRec(0);
    string tmp = "h : [";
    for (int i = 0; i < 9; ++i) {
        if (h[i] != 0) { tmp.append(to_string(h[i])); }

    }
    tmp.append("] v : [");
    for (int i = 0; i < 9; ++i) {
        if (v[i] != 0) { tmp.append(to_string(v[i])); }
    }
    tmp.append("] c : [");
    for (int i = 0; i < 9; ++i) {
        if (c[i] != 0) { tmp.append(to_string(c[i])); }
    }
    tmp.append("]");
    return tmp;
}

string buildString() {
    string frameStr = "#####################################\n";
    for (int i = 0; i < 9; ++i) {
        frameStr.append("# ");
        for (int j = 0; j < 9; ++j) {
            if (j % 3 == 2) {
                if (matrix[i][j] != 0) {
                    frameStr.append(to_string(matrix[i][j]) + " # ");
                } else {
                    frameStr.append("_ # ");
                }

            } else {
                if (matrix[i][j] != 0) {
                    frameStr.append(to_string(matrix[i][j]) + "   ");
                } else {
                    frameStr.append("_   ");
                }
            }
        }
        if (i % 3 == 2) {
            frameStr.append("\n#####################################\n");
        } else {
            frameStr.append("\n#           #           #           #\n");
        }
    }

    frameStr.append("\nh : help\t");

    if (m == 1) {
        frameStr.append("mode : Easy\n" + buildCheatString());
    } else if (m == 2) { frameStr.append("mode : Medium\n"); }
    else if (m == 3) { frameStr.append("mode : Hard\n"); }

    return frameStr;
}

void printFrame() {
    clear();
    addstr(buildString().c_str());
    attron(COLOR_PAIR(1));
    mvaddch(1 + (currX * 2), 1 + (currY * 4), '>');
    mvaddch(1 + (currX * 2), 3 + (currY * 4), '<');
    attroff(COLOR_PAIR(1));
    move(23, 0);
    addstr(error.c_str());
}
//##############################################################################
// algorithm by Sharon Christine
//##############################################################################
bool isPresentInCol(int col, int num) {    //check whether num is present in col or not
    for (int row = 0; row < 9; row++)
        if (matrix[row][col] == num)
            return true;
    return false;
}

bool isPresentInRow(int row, int num) {    //check whether num is present in row or not
    for (int col = 0; col < 9; col++)
        if (matrix[row][col] == num)
            return true;
    return false;
}

bool isPresentInBox(int boxStartRow, int boxStartCol, int num) {    //check whether num is present in 3x3 box or not
    for (int row = 0; row < 3; row++)
        for (int col = 0; col < 3; col++)
            if (matrix[row + boxStartRow][col + boxStartCol] == num)
                return true;
    return false;
}


bool findEmptyPlace(int &row, int &col) {    //get empty location and update row and column
    for (row = 0; row < 9; row++)
        for (col = 0; col < 9; col++)
            if (matrix[row][col] == 0) //marked with 0 is empty
                return true;
    return false;
}

bool isValidPlace(int row, int col, int num) {
    //when item not found in col, row and current 3x3 box
    return !isPresentInRow(row, num) && !isPresentInCol(col, num) && !isPresentInBox(row - row % 3, col - col % 3, num);
}

bool solveSudoku() {
    usleep(1000);
    printFrame();
    refresh();
    int row, col;
    if (!findEmptyPlace(row, col))
        return true;     //when all places are filled
    for (int num = 1; num <= 9; num++) {
        if (isValidPlace(row, col, num)) {    //check validation, if yes, put the number in the matrix
            matrix[row][col] = num;
            if (solveSudoku())     //recursively go for other rooms in the matrix
                return true;
            matrix[row][col] = 0;    //turn to unassigned space when conditions are not satisfied
        }
    }
    return false;
}


//##############################################################################
void runLoop() {
    char c;
    while (true) {

        printFrame();
        refresh();
        switch (c = getch()) {
            case 'q': {
                while (true) {
                    error = "You sure bro? All progress will be lost!!\ny : yes";
                    printFrame();
                    if (getch() == 'y') {
                        return;
                    } else {
                        break;
                    }
                }
                break;
            }
            case 'a': {
                if (currY > 0) {
                    currY = currY - 1;
                }
                error = "";
                break;
            }
            case 'w': {
                if (currX > 0) {
                    currX = currX - 1;
                }
                error = "";
                break;
            }
            case 's': {
                if (currX < 8) {
                    currX = currX + 1;
                }
                error = "";
                break;
            }
            case 'd': {
                if (currY < 8) {
                    currY = currY + 1;
                }
                error = "";
                break;
            }
            case '\n': {
                if ((c = getch()) > 48 && c < 58) {
                    matrix[currX][currY] = c - 48;
                    fillCellArr();
                }
                error = "";
                break;
            }
            case 'h': {
                clear();
                addstr(help.c_str());
                refresh();
                if (getch()) {
                    break;
                }

                error = "";
                break;
            }
            case 'm': {
                if (m == Easy) {
                    m = Medium;
                } else if (m == Medium) {
                    m = Hard;
                } else { m = Easy; }
                error = "";
                break;
            }
            case 'c': {
                matrix[currX][currY] = 0;
                fillCellArr();
                error = "";
                break;
            }
            case 'k': {
                if (solveSudoku()) {
                    error = "finished";
                } else
                    error = "No solution exists";
                break;
            }
            case 'l': {
                bool corrFormat = true;
                int tmp_matrix[9][9] = {{0, 0, 0, 0, 0, 0, 0, 0, 0},
                                        {0, 0, 0, 0, 0, 0, 0, 0, 0},
                                        {0, 0, 0, 0, 0, 0, 0, 0, 0},
                                        {0, 0, 0, 0, 0, 0, 0, 0, 0},
                                        {0, 0, 0, 0, 0, 0, 0, 0, 0},
                                        {0, 0, 0, 0, 0, 0, 0, 0, 0},
                                        {0, 0, 0, 0, 0, 0, 0, 0, 0},
                                        {0, 0, 0, 0, 0, 0, 0, 0, 0},
                                        {0, 0, 0, 0, 0, 0, 0, 0, 0},};
                char str[80];
                clear();
                error = "input the location of the sudoku file";
                printFrame();
                nocbreak();
                echo();
                move(24, 0);
                //mvprintw(10,0,get_current_dir_name());
                getstr(str);
                string line;
                ifstream file(str, ios::in);
                if (file.is_open()) {
                    int count = 0;
                    while (getline(file, line)) {
                        for (int i = 0; i < 9; ++i) {
                            if (isdigit(line[i])) {
                                tmp_matrix[count][i] = line[i] - 48;

                            } else {
                                error = "wrong format";
                                corrFormat = false;
                                break;
                            }
                        }
                        count = count + 1;
                    }
                    file.close();
                    if (corrFormat) {
                        for (int i = 0; i < 9; ++i) {
                            for (int j = 0; j < 9; ++j) {
                                matrix[i][j] = tmp_matrix[i][j];
                            }
                        }
                        error = "Sudoku loaded successfully";
                    }

                } else { error = "file not found."; }
                noecho();
                cbreak();
                break;
            }
            case 'p':
                string filename = "sudoku";
                fstream outfile;
                outfile.open(filename, ios::out);
                if (!outfile) {
                    error = "File not created!";
                } else {
                    error = "File created successfully!";
                    for (int i = 0; i < 9; ++i) {
                        for (int j = 0; j < 9; ++j) {
                            if (matrix[i][j] != 0) {
                                outfile << matrix[i][j];
                            } else {
                                outfile << "0";
                            }
                        }
                        outfile << "\n";
                    }
                    outfile.close();
                }
                break;


        }
    }
}

int main(void) {

    initCurses();
    fillCellArr();

    runLoop();
    return 0;
}
