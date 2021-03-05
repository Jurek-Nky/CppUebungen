#include <curses.h>
#include <iostream>

using namespace std;
string help = "q\t\t: to quit the game\n"
"w|a|s|d\t\t: move cursor\n"
"enter + [1-9]\t: insert number at cursor position\n"
"v\t\t: validate\n"
"m\t\t: mode selection\n";
int matrix[9][9] = { { 1, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 2, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 3, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 4, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 5, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 6, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 7, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 8, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 9 } };

int currX = 1;
int currY = 4;
enum mode { Easy = 1,
		Medium = 2,
		Hard = 3 };

mode m;
//const char sz[] = "########################################\n#   1   2   3 # 4   5   6 # 7   8   9   #\n#				#			#			  #\n#	 1	 2	 3 # 4	 5	 6 # 7	 8	 9	 #\n#			  #			  #				#\n#   1   2   3 # 4   5   6 # 7   8   9   #\n#########################################\n#	 1	 2	 3 # 4	 5	 6 # 7	 8	 9	 #\n#			  #			  #				#\n#   1   2   3 # 4   5   6 # 7   8   9   #\n#				#			#			  #\n#	 1	 2	 3 # 4	 5	 6 # 7	 8	 9	 #\n#########################################\n#   1   2   3 # 4   5   6 # 7   8   9   #\n#				#			#			  #\n#	 1	 2	 3 # 4	 5	 6 # 7	 8	 9	 #\n#			  #			  #				#\n#   1   2   3 # 4   5   6 # 7   8   9   #\n#########################################";
void initCurses(){
		initscr();
		cbreak();
		noecho();
		clear();
		m = Easy;
}
string buildCheatString()
{
		string tmp = "h:[] v:[] c:[]................";
		return tmp;
}
string buildString()
{
		string tmp = "#####################################\n";
		for (int i = 0; i < 9; ++i) {
				tmp.append("# ");
				for (int j = 0; j < 9; ++j) {
						if (j % 3 == 2) {
								if (matrix[i][j] != 0) {
										tmp.append(to_string(matrix[i][j]) + " # ");
								} else {
										tmp.append("_ # ");
								}

						} else {
								if (matrix[i][j] != 0) {
										tmp.append(to_string(matrix[i][j]) + "   ");
								} else {
										tmp.append("_   ");
								}
						}
				}
				if (i % 3 == 2) {
						tmp.append("\n#####################################\n");
				} else {
						tmp.append("\n#           #           #           #\n");
				}
		}

		tmp.append("\nh : help\t");
		if (m == 1){
				tmp.append("mode : Easy\n"+buildCheatString());
		}
		else if (m == 2){tmp.append("mode : Medium\n");}
		else if (m == 3){tmp.append("mode : Hard\n");}
		return tmp;
}

void printFrame()
{
		clear();
		addstr(buildString().c_str());
		mvaddch(1 + (currX * 2), 1 + (currY * 4), '>');
}

void runLoop()
{
		char c;
		while (true) {

				printFrame();
				refresh();
				switch (c = getch()) {
						case 'q':
								while (true) {
										clear();
										mvaddstr(9, 0, "You sure bro? All progress will be lost!!");
										mvaddstr(10, 16, "y : yes");
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
								break;

						case 'w':
								if (currX > 0) {
										currX = currX - 1;
								}
								break;

						case 's':
								if (currX < 8) {
										currX = currX + 1;
								}
								break;

						case 'd':
								if (currY < 8) {
										currY = currY + 1;
								}
								break;

						case '\n':
								if ((c = getch()) > 48 && c < 58) {
										matrix[currX][currY] = c - 48;
								}
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
								break;
						case 'm':
								if (m ==Easy){
										m = Medium;
								}
								else if (m == Medium){
										m = Hard;
								}
								else{m = Easy;}
				}
		}
}

int main(void)
{
		initCurses();
		runLoop();
		return 0;
}
