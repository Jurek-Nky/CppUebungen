#include <curses.h>
#include <iostream>
#include <math.h>
#include <fstream>
#include <ctime>

using namespace std;
string help = "q\t\t: to quit the game\n"
              "w|a|s|d\t\t: move cursor\n"
              "enter + [1-9]\t: insert number at cursor position\n"
              "v\t\t: validate\n"
              "m\t\t: mode selection\n"
              "p\t\t: print progress to file\n"
              "l\t\t: load sudoku from file\n";
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
    move(23,0);
    addstr(error.c_str());
}

void runLoop() {
    char c;
    while (true) {

        printFrame();
        refresh();
        switch (c = getch()) {
            case 'q':
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

            case 'a':
                if (currY > 0) {
                    currY = currY - 1;
                }
                error = "";
                break;

            case 'w':
                if (currX > 0) {
                    currX = currX - 1;
                }
                error = "";
                break;

            case 's':
                if (currX < 8) {
                    currX = currX + 1;
                }
                error = "";
                break;

            case 'd':
                if (currY < 8) {
                    currY = currY + 1;
                }
                error = "";
                break;

            case '\n':
                if ((c = getch()) > 48 && c < 58) {
                    matrix[currX][currY] = c - 48;
                    fillCellArr();
                }
                error = "";
                break;

            case 'h':
                while (true) {
                    clear();
                    addstr(help.c_str());
                    refresh();
                    if (getch()) {
                        break;
                    }
                }
                error = "";
                break;
            case 'm':
                if (m == Easy) {
                    m = Medium;
                } else if (m == Medium) {
                    m = Hard;
                } else { m = Easy; }
                error = "";
                break;
            case 'c':
                matrix[currX][currY] = 0;
                fillCellArr();
                error = "";
                break;
            case 'l':
                while (true) {
                    char str[80];
                    string Filestring;
                    clear();
                    mvaddstr(9, 0, "input the location of the sudoku file\n");
                    addstr(":$");
                    refresh();
                    nocbreak();
                    echo();
                    getstr(str);
                    fstream infile;
                    infile.open(str, ios::in);
                    if (!infile) {
                        error = "file not found";
                    } else {
                        while (true) {
                            infile >> Filestring;
                            if (infile.eof()) {
                                break;
                            }
                        }
                    }
                    error = Filestring;

                    noecho();
                    cbreak();
                    break;

                }

                break;

            case 'p':
                string filename = "sudoku";
                fstream outfile;
                outfile.open(filename, ios::out);
                if (!outfile) {
                    error=  "File not created!";
                } else {
                    error = "File created successfully!";
                    for (int i = 0; i < 9; ++i) {
                        for (int j = 0; j < 9; ++j) {
                            if (matrix[i][j] != 0) {
                                outfile << matrix[i][j] << ",";
                            } else {
                                outfile << ",";
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
