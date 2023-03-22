#include <iostream>
#include <string>

enum Color {
	black = '*',
	white = '-'
};

class Point {
private:
	int string;
	int column;
public: 
	Point (){}
	~Point() {}
};

class Cell {
private:
	Point coord = new Point();
	int hit = 0;
	bool chekHit = false;
	Color color;
public:
	Cell (Point point) : coord(point) {}
	~Cell () {}

	bool CheckEmpty(Cell* cell) {
		return cell->figure.type == 'Z';
	}

	friend std::ostream& operator << (std::ostream& out, Cell* cell) {
		std::cout << " ";
		if (CheckEmpty(cell)) {
			if (!cell->checkHit) {
				if (cell->color == white) {
					std::cout << "-";
				}
				else {
					std::cout << "*";
				}
			}
		}
		else {
			std::cout << cell->figure.type;
		}
	}
};

//Структура "Фигура" хранит данные о цвете, тип фигуры и отношение к другим фигурам
struct Figure {
	char type = 'Z';
	Color color;
};

//Структура координат фигуры
/*
struct Point {
	int x;
	int y;
};*/

//Структура "Клетка" хранит данные о координатах клетки, находиться ли клетка
//под боем и сколько раз её бьют, структуру данных "Фигура" и цвет клетки

/*?struct Cell {
	Point coord;
	bool checkHit = false;
	int hit = 0;
	Figure figure;
	Color color;
};
*/
//Стурктура "Шахматная доска" хранит массив ячеек

//
class Board{
private:
	int string;
	int column;
	Cell* board;
public:
	Board(int string_, int column_) : board(new Cell[string_][column_]), string(string_), column(column_) {}
	~Board () {
		delete[] board;
	}

	friend std::ostream & operator << (std::ostream & out, Board* board){
		std::cout << "  A B C D E F G H" << std::endl;
		for (int i = 7; i >= 0; i--) {
			std::cout << i + 1;
			for (int j = 0; j < 8; j++) {
				PrintCell(board->board[i][j]);

			}
			std::cout << " " << i + 1;
			std::cout << "\n";
		}
		std::cout << "  A B C D E F G H" << std::endl;
	}
}

/*struct ChessBoard {
	Cell* board[8][8];
};*/

//Функция для создания названий каждой клетки
std::string CreateCellName(int column, int _string) {
	std::string symbol = "ABCDEFGH";
	std::string name = symbol[column] + std::to_string(_string + 1);
	return name;
}

bool CheckEmpty(Cell *cell) {
	return cell->figure.type == 'Z';
}

//Функция для вывода состояния клетки
void PrintCell(Cell* cell) {
	std::cout << " ";
	if (CheckEmpty(cell)) {
		if (!cell->checkHit) {
			if (cell->color==white) {
				std::cout << "-";
			}
			else {
				std::cout << "*";
			}
		}
	}
	else {
		std::cout << cell->figure.type;
	}
}

//Функция для вывода шахматной доски
void PrintChessBoard(ChessBoard* board) {
	std::cout << "  A B C D E F G H" << std::endl;
	for (int i = 7; i >= 0; i--) {
		std::cout << i + 1;
		for (int j = 0; j < 8; j++) {
			PrintCell(board->board[i][j]);
		}
		std::cout << " " << i + 1;
		std::cout << "\n";
	}
	std::cout << "  A B C D E F G H" << std::endl;
}

//Функция для создания клетки с данными о координатах и цвете
Cell* CreateCell(int column, int string, Color color) {
	Cell* cell = new Cell;
	Point point;
	point.x = string;
	point.y = column;
	cell->coord = point;
	cell->color = color;
	return cell;
}

//Функция для замены цвета клетки
Color RelplaceColor(Color color) {
	if (color == white) {
		return black;
	}
	return white;
}

//Функция для создания шахматной доски
void CreateBoard(ChessBoard* board) {
	Color color = white;
	for (int i = 0; i < 8; i++) {
		color = RelplaceColor(color);
		for (int j = 0; j < 8; j++) {
			color = RelplaceColor(color);
			board->board[i][j] = CreateCell(i, j, color);
		}
	}
}

bool CheckHit(Cell* cell) {
	return !(cell->figure.type == 'Z');
}

//Функция для счёта ударов по клетке 
void FigureHit(Cell* cell) {
	if (CheckHit(cell)) {
		cell->hit += 1;
		cell->checkHit = true;
	}
	else {
		cell->hit -= 1;
		if (cell->hit == 0) {
			cell->checkHit = false;
		}
	}
}

//Функция для королевы, которая бьёт все клетки по горизонтали
void HorizonMovingQueen(ChessBoard* board, Cell* cell) {
	for (int i = 0; i < 8; i++) {
		if (board->board[cell->coord.y][i] != board->board[cell->coord.y][cell->coord.x]) {
			FigureHit(board->board[cell->coord.y][i]);
		}
	}
}

//Функция для королевы, которая бьёт все клетки по вертикали
void VerticalMovingQueen(ChessBoard* board, Cell* cell) {
	for (int i = 0; i < 8; i++) {
		if (board->board[i][cell->coord.x] != board->board[cell->coord.y][cell->coord.x]) {
			FigureHit(board->board[i][cell->coord.x]);
		}
	}
}

//Функция для королевы, которая бьёт все клетки по диагонали
void DiagonalMovingQueen(ChessBoard* board, Cell* cell) {
	for (int i = 0; i < 8; i++) {
		if (cell->coord.x + i < 8 && cell->coord.y + i < 8) {
			FigureHit(board->board[cell->coord.y + i][cell->coord.x + i]);
		}
		if (cell->coord.x - i >= 0 && cell->coord.y - i >= 0) {
			FigureHit(board->board[cell->coord.y - i][cell->coord.x - i]);
		}
		if (cell->coord.x - i >= 0 && cell->coord.y + i < 8) {
			FigureHit(board->board[cell->coord.y + i][cell->coord.x - i]);
		}
		if (cell->coord.x + i < 8 && cell->coord.y - i >= 0) {
			FigureHit(board->board[cell->coord.y - i][cell->coord.x + i]);
		}
	}
}

//Функция, которая решает какую королеву надо изменить и возвращает индекс этой королевы
int ReturnPreviousQueen(ChessBoard* board, Cell* QueensInCell[8], int numPlacedQueens) {
	Point point;
	do {
		point = QueensInCell[numPlacedQueens]->coord;
		numPlacedQueens -= 1;
	} while (point.x > 8); 
	return numPlacedQueens;
}

//Функция для клетки доски, которая ставит королеву на неё и бьёт все клетки по горизонтали, вертикали и диагонали
void MoveQueen(ChessBoard* board, Cell* cellQueen,char type) {
	cellQueen->figure.type = type;
	HorizonMovingQueen(board, cellQueen);
	VerticalMovingQueen(board, cellQueen);
	DiagonalMovingQueen(board, cellQueen);
}

//Функция для проверки количества королев на доске
int CheckBoard(ChessBoard* board) {
	int numQueen = 0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (board->board[i][j]->figure.type == 'Q') {
				numQueen += 1;
			}
		}
	}
	return numQueen;
}

Cell* GetCell(Cell* cell,int string,int column) {
	cell->coord.x = string;
	cell->coord.y = column;
}

//Рекурсивная функция, которая ставит королеву и вызывает функцию для постановки следующей королевы
ChessBoard* PartingQueen(ChessBoard* board, int numPlacedQueens, int numQueen, int column, int string, Cell* QueensInCell[8]) {
	if (CheckBoard(board) == 8) {
		return board;
	}
	for (int i = 0; i < 8; i++) {
		if (CheckEmpty(board->board[string][i]) && board->board[string][i]->checkHit == false) {
			MoveQueen(board, board->board[string][i],'Q');
			Cell* cell = new Cell;
			GetCell(cell, string, i);
			QueensInCell[numQueen] = cell;
			if (string < 8) {
				board = PartingQueen(board, numPlacedQueens, numQueen, 0, string + 1, QueensInCell);
				if (CheckBoard(board) == 8) {
					return board;
				}
				MoveQueen(board, board->board[string][i],'Z');
			}
		}
	}
	return board;
}

//Функция, вызывающая реурсивную функцию. Возвращает доску с расставленными королевами
ChessBoard* CallPartingQueen(ChessBoard* board, int numPlacedQueens) {
	Cell* QueensInCell[8];
	board = PartingQueen(board, numPlacedQueens, 0, 0, 0, QueensInCell);
	return board;
}

//Функция, проверяющая вводимые значения
bool CheckHVD(std::string isTestMoving, char HVD) {
	for (int i = 0; i < isTestMoving.length(); i++) {
		if (isTestMoving[i] == HVD) {
			return true;
		}
	}
	return false;
}

//Проверка по горизонтали
bool TestHorizontal(ChessBoard* board, Point pointQueen, Point pointQueenHorizontal) {
	board->board[pointQueen.x][pointQueen.y]->figure.type = 'Q';
	HorizonMovingQueen(board, board->board[pointQueen.x][pointQueen.y]);
	PrintChessBoard(board);
	std::cout << CreateCellName(pointQueenHorizontal.y, pointQueenHorizontal.x) << '\n';
	if (board->board[pointQueenHorizontal.x][pointQueenHorizontal.y]->checkHit == false) {
		return true;
	}
	return false;
}

//Проверка по вертикали
bool TestVertical(ChessBoard* board, Point pointQueen, Point pointQueenVertical) {
	board->board[pointQueen.x][pointQueen.y]->figure.type = 'Q';
	VerticalMovingQueen(board, board->board[pointQueen.x][pointQueen.y]);
	PrintChessBoard(board);
	std::cout << CreateCellName(pointQueenVertical.y, pointQueenVertical.x) << '\n';
	if (board->board[pointQueenVertical.x][pointQueenVertical.y]->checkHit == false) {
		return true;
	}
	return false;
}

//Проверка по диагонали
bool TestDiagonal(ChessBoard* board, Point pointQueen, Point pointQueenDiagonal) {
	board->board[pointQueen.x][pointQueen.y]->figure.type = 'Q';
	DiagonalMovingQueen(board, board->board[pointQueen.x][pointQueen.y]);
	PrintChessBoard(board);
	std::cout << CreateCellName(pointQueenDiagonal.y, pointQueenDiagonal.x) << '\n';
	if (board->board[pointQueenDiagonal.x][pointQueenDiagonal.y]->checkHit == false) {
		std::cout << true << std::endl;
		return true;
	}
	return false;
}

//Функция для задания координат двух проверяемых королев
bool TestQueenMoving(ChessBoard* board) {
	bool isTestTrue = true;
	Point pointQueen;
	std::cin >> pointQueen.x >> pointQueen.y;
	std::string isTestMoving;
	std::cout << "Start test? H or V or D: ";
	std::cin >> isTestMoving;
	if (CheckHVD(isTestMoving, 'H') or CheckHVD(isTestMoving, 'h')) {
		Point pointQueenHorizontal;
		std::cin >> pointQueenHorizontal.x >> pointQueenHorizontal.y;
		bool expectedResult;
		std::cin >> expectedResult;
		if (TestHorizontal(board, pointQueen, pointQueenHorizontal) != expectedResult) {
			return false;
		}
	}
	if (CheckHVD(isTestMoving, 'V') or CheckHVD(isTestMoving, 'v')) {
		Point pointQueenVertical;
		std::cin >> pointQueenVertical.x >> pointQueenVertical.y;
		bool expectedResult;
		std::cin >> expectedResult;
		std::cout << expectedResult;
		if (TestVertical(board, pointQueen, pointQueenVertical) != expectedResult) {
			return false;
		}
	}
	if (CheckHVD(isTestMoving, 'D') or CheckHVD(isTestMoving, 'd')) {
		Point pointQueenDiagonal;
		std::cin >> pointQueenDiagonal.x >> pointQueenDiagonal.y;
		bool expectedResult;
		std::cin >> expectedResult;
		if (TestDiagonal(board, pointQueen, pointQueenDiagonal) != expectedResult) {
			return false;
		}
	}
	return isTestTrue;
}

int main() {
	char isTest;
	ChessBoard* board = new ChessBoard;
	CreateBoard(board);
	std::cout << "Start test? Y or N: ";
	std::cin >> isTest;
	if (isTest == 'Y' || isTest == 'y') {
		bool test = TestQueenMoving(board);
		if (test) {
			std::cout << "Test passed successfully" << std::endl;
		}
		else {
			std::cout << "Test failed" << std::endl;
		}
	}
	else {
		int numPlacedQueens;
		std::cin >> numPlacedQueens;
		board = CallPartingQueen(board, numPlacedQueens);
		PrintChessBoard(board);
		int a;
		std::cin >> a;
	}
	return 0;
}


