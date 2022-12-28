#include "minesweeper.h"

void minesweeper(string input, string output)
{
	ifstream commandfile;
	ofstream outputfile;
	char board[SIZE][SIZE];
	bool gameOver = false;
	int Spacestouched = 0, touchX, touchY;
	string line;

	commandfile.open(input);
	outputfile.open(output);

	while (!commandfile.eof() && gameOver == false) // command 파일을 한단어씩 읽고 없을 때까지 반복 
	{
		commandfile >> line;

		if (line == "load" && !commandfile.eof()) // load 명령
		{
			outputfile << "Command: " << line << " ";
			commandfile >> line;
			initBoard(board, line); // board 파일을 읽고 board 배열에 저장
			outputfile << line << endl;
		}
		else if (line == "display" && !commandfile.eof()) // display 명령
		{
			outputfile << "Command: " << line << endl;
			displayBoard(outputfile, board); // 현재 board 상황 표시
		}
		else if (line == "touch" && !commandfile.eof()) // touch 명령
		{
			outputfile << "Command: " << line << " ";
			commandfile >> touchX;
			commandfile >> touchY;
			outputfile << touchX << " " << touchY << endl;
			touchBoard(board, touchX, touchY, Spacestouched, gameOver); // 주어진 위치의 Board를 터치하고 그 결과를 Board 배열에 반영
		}
	}

	//Game Over, Final Board 표시
	outputfile << "Game Over" << endl;
	outputfile << "~~~~~~~~~" << endl;
	outputfile << "Final Board" << endl;
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			outputfile << board[i][j];
		}
		outputfile << endl;
	}
	outputfile << endl;

	outputfile << "Spaces touched: " << Spacestouched << endl; // 터치한 횟수 표시

	commandfile.close();
	outputfile.close();
}

void initBoard(char board[SIZE][SIZE], string file)
{
	// board 파일을 읽고 board 배열에 저장하는 함수
	ifstream boardfile;
	boardfile.open(file);
	char getmine;

	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			boardfile.get(getmine).skipws;
			if (getmine == '.') // 만약 빈 공간일 경우
			{
				board[i][j] = '.';
			}
			else if (getmine == '*') // 만약 지뢰일 경우
			{
				board[i][j] = '@';
			}
		}

		boardfile.get(getmine).skipws; // 개행문자 버리기
	}

	boardfile.close();
}

void displayBoard( ostream& out, char board[SIZE][SIZE] )
{
	// 현재 board 상황 표시하는 함수

	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (board[i][j] == '@') // 만약 지뢰일 경우 아직 터치하지 않은 공간(.)으로 표시
			{
				out << '.';
			}
			else // 아직 터치하지 않은 공간(.) 혹은 숫자일 경우
			{
				out << board[i][j];
			}
		}
		out << endl;
	}
	out << endl;
}

void touchBoard( char board[SIZE][SIZE], int touchX, int touchY, int& Spacestouched, bool& gameOver )
{
	// 주어진 x,y 위치의 Board를 터치하고 그 결과를 Board 배열에 반영하는 함수
	char bombs = '0';
	int x = touchX - 1, y = touchY - 1;
	
	if (board[x][y] == '@') // 만약 폭탄을 터치한 경우 gameOver를 true로 저장
	{
		board[x][y] = '*';
		gameOver = true;
		Spacestouched++; // 터치 횟수 증가
	}
	else if (board[x][y] == '.') // 만약 아직 터치하지 않은 공간(.)인 경우
	{
		// 터치한 위치 주변에 폭탄이 있는지 확인

		if (x == 0) // x = 0, y 0~7 (맨 윗줄)
		{
			if (y == 0) // x = 0, y = 0
			{
				if (board[x][y + 1] == '@')
					bombs++;
				if (board[x + 1][y] == '@')
					bombs++;
				if (board[x + 1][y + 1] == '@')
					bombs++;
				board[x][y] = bombs;
			}
			else if (y == SIZE - 1) // x = 0, y = 7
			{
				if (board[x][y - 1] == '@')
					bombs++;
				if (board[x + 1][y] == '@')
					bombs++;
				if (board[x + 1][y - 1] == '@')
					bombs++;
				board[x][y] = bombs;
			}
			else  // x = 0, y 1~6
			{
				if (board[x][y - 1] == '@')
					bombs++;
				if (board[x][y + 1] == '@')
					bombs++;
				if (board[x + 1][y - 1] == '@')
					bombs++;
				if (board[x + 1][y] == '@')
					bombs++;
				if (board[x + 1][y + 1] == '@')
					bombs++;
				board[x][y] = bombs;
			}
		}
		else if (y == 0) // x 1~7, y = 0 (맨 왼쪽줄)
		{
			if (x == 7) // x = 7, y = 0
			{
				if (board[x][y + 1] == '@')
					bombs++;
				if (board[x - 1][y] == '@')
					bombs++;
				if (board[x - 1][y + 1] == '@')
					bombs++;
				board[x][y] = bombs;
			}
			else // x 1~6, y = 0
			{
				if (board[x - 1][y] == '@')
					bombs++;
				if (board[x - 1][y + 1] == '@')
					bombs++;
				if (board[x][y + 1] == '@')
					bombs++;
				if (board[x + 1][y] == '@')
					bombs++;
				if (board[x + 1][y + 1] == '@')
					bombs++;
				board[x][y] = bombs;
			}
		}
		else if (x == 7) // x = 7, y 1~7 (맨 아랫줄)
		{
			if (y == 7) // x = 7, y = 7
			{
				if (board[x - 1][y - 1] == '@')
					bombs++;
				if (board[x - 1][y] == '@')
					bombs++;
				if (board[x][y - 1] == '@')
					bombs++;
				board[x][y] = bombs;
			}
			else // x = 7, y 1~6
			{
				if (board[x - 1][y - 1] == '@')
					bombs++;
				if (board[x - 1][y] == '@')
					bombs++;
				if (board[x - 1][y + 1] == '@')
					bombs++;
				if (board[x][y - 1] == '@')
					bombs++;
				if (board[x][y + 1] == '@')
					bombs++;
				board[x][y] = bombs;
			}
		}
		else if (y == 7) // x 1~6, y =7 (맨 오른쪽줄)
		{
			if (board[x - 1][y - 1] == '@')
				bombs++;
			if (board[x - 1][y] == '@')
				bombs++;
			if (board[x][y - 1] == '@')
				bombs++;
			if (board[x + 1][y] == '@')
				bombs++;
			if (board[x + 1][y - 1] == '@')
				bombs++;
			board[x][y] = bombs;
		}
		else // x 1~6, y 1~6 (중간 부분)
		{
			if (board[x - 1][y - 1] == '@')
				bombs++;
			if (board[x - 1][y] == '@')
				bombs++;
			if (board[x - 1][y + 1] == '@')
				bombs++;
			if (board[x][y - 1] == '@')
				bombs++;
			if (board[x][y + 1] == '@')
				bombs++;
			if (board[x + 1][y - 1] == '@')
				bombs++;
			if (board[x + 1][y] == '@')
				bombs++;
			if (board[x + 1][y + 1] == '@')
				bombs++;
			board[x][y] = bombs;
		}

		Spacestouched++; // 터치 횟수 증가
	}
}

int main() {
	cout << "Testing minesweeper" << endl;
	minesweeper(".\\test1commands.txt", "test1_output_mine.txt");
	minesweeper(".\\test2commands.txt", "test2_output_mine.txt");
	minesweeper(".\\test3commands.txt", "test3_output_mine.txt");
	minesweeper(".\\test4commands.txt", "test4_output_mine.txt");
	minesweeper(".\\test5commands.txt", "test5_output_mine.txt");
	minesweeper(".\\test6commands.txt", "test6_output_mine.txt");
	minesweeper(".\\test7commands.txt", "test7_output_mine.txt");
	minesweeper(".\\test8commands.txt", "test8_output_mine.txt");
	minesweeper(".\\test9commands.txt", "test9_output_mine.txt");
	minesweeper(".\\test10commands.txt", "test10_output_mine.txt");

	return 0;
}