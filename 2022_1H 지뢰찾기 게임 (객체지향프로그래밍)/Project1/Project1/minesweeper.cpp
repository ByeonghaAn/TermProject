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

	while (!commandfile.eof() && gameOver == false) // command ������ �Ѵܾ �а� ���� ������ �ݺ� 
	{
		commandfile >> line;

		if (line == "load" && !commandfile.eof()) // load ���
		{
			outputfile << "Command: " << line << " ";
			commandfile >> line;
			initBoard(board, line); // board ������ �а� board �迭�� ����
			outputfile << line << endl;
		}
		else if (line == "display" && !commandfile.eof()) // display ���
		{
			outputfile << "Command: " << line << endl;
			displayBoard(outputfile, board); // ���� board ��Ȳ ǥ��
		}
		else if (line == "touch" && !commandfile.eof()) // touch ���
		{
			outputfile << "Command: " << line << " ";
			commandfile >> touchX;
			commandfile >> touchY;
			outputfile << touchX << " " << touchY << endl;
			touchBoard(board, touchX, touchY, Spacestouched, gameOver); // �־��� ��ġ�� Board�� ��ġ�ϰ� �� ����� Board �迭�� �ݿ�
		}
	}

	//Game Over, Final Board ǥ��
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

	outputfile << "Spaces touched: " << Spacestouched << endl; // ��ġ�� Ƚ�� ǥ��

	commandfile.close();
	outputfile.close();
}

void initBoard(char board[SIZE][SIZE], string file)
{
	// board ������ �а� board �迭�� �����ϴ� �Լ�
	ifstream boardfile;
	boardfile.open(file);
	char getmine;

	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			boardfile.get(getmine).skipws;
			if (getmine == '.') // ���� �� ������ ���
			{
				board[i][j] = '.';
			}
			else if (getmine == '*') // ���� ������ ���
			{
				board[i][j] = '@';
			}
		}

		boardfile.get(getmine).skipws; // ���๮�� ������
	}

	boardfile.close();
}

void displayBoard( ostream& out, char board[SIZE][SIZE] )
{
	// ���� board ��Ȳ ǥ���ϴ� �Լ�

	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (board[i][j] == '@') // ���� ������ ��� ���� ��ġ���� ���� ����(.)���� ǥ��
			{
				out << '.';
			}
			else // ���� ��ġ���� ���� ����(.) Ȥ�� ������ ���
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
	// �־��� x,y ��ġ�� Board�� ��ġ�ϰ� �� ����� Board �迭�� �ݿ��ϴ� �Լ�
	char bombs = '0';
	int x = touchX - 1, y = touchY - 1;
	
	if (board[x][y] == '@') // ���� ��ź�� ��ġ�� ��� gameOver�� true�� ����
	{
		board[x][y] = '*';
		gameOver = true;
		Spacestouched++; // ��ġ Ƚ�� ����
	}
	else if (board[x][y] == '.') // ���� ���� ��ġ���� ���� ����(.)�� ���
	{
		// ��ġ�� ��ġ �ֺ��� ��ź�� �ִ��� Ȯ��

		if (x == 0) // x = 0, y 0~7 (�� ����)
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
		else if (y == 0) // x 1~7, y = 0 (�� ������)
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
		else if (x == 7) // x = 7, y 1~7 (�� �Ʒ���)
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
		else if (y == 7) // x 1~6, y =7 (�� ��������)
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
		else // x 1~6, y 1~6 (�߰� �κ�)
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

		Spacestouched++; // ��ġ Ƚ�� ����
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