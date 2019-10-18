#ifndef __TABLE_2019__
#define __TABLE_2019__

class Table {
	bool** field; // Игровое поле, каждый элемент которого 0 или 1
	int cols, rows;

public:
	Table(): cols(0), rows(0), field(nullptr) {}

	Table(int col, int row, bool** f): cols(col), rows(row) {
		setlocale(0, "Russian");
		rows += 2;
		cols += 2;

		//Array allocation
		field = new bool*[rows];
		for (int i = 0; i < rows; ++i)
			field[i] = new bool[cols];

		//Fill the borders to make the field endless (conditionally)
		for (int i = 1; i < rows - 1; ++i) { field[i][0] = f[i - 1][cols - 3]; field[i][cols - 1] = f[i - 1][0]; }
		for (int i = 1; i < cols - 1; ++i) { field[0][i] = f[rows - 3][i - 1]; field[rows - 1][i] = f[0][i - 1]; }
		field[0][0] = f[rows - 3][cols - 3]; field[0][cols - 1] = f[rows - 3][0];
		field[rows - 1][0] = f[0][cols - 3]; field[rows - 1][cols - 1] = f[0][0];
		//----------------------------------------------------------

		//Copy entered field to the array 'field'
		for (int i = 1; i < rows - 1; ++i)
			for (int j = 1; j < cols - 1; ++j)
				field[i][j] = f[i - 1][j - 1];
		//----------------
	}

	void operator=(const Table& table){

		for (int i = 0; i < rows; ++i)
			delete[] field[i];
		delete[] field;

		this->cols = table.cols;
		this->rows = table.rows;

		field = new bool*[rows];
		for (int i = 0; i < rows; ++i)
			field[i] = new bool[cols];
		
		for (int i = 0; i < rows; ++i)
			for (int j = 0; j < cols; ++j)
				this->field[i][j] = table.field[i][j];
	}

	~Table() {
		//Memory cleaning
		for (int i = 0; i < rows; ++i)
			delete[] field[i];
		delete[] field;
	}

	const void printField() const{
		for (int i = 1; i < rows - 1; ++i) {
			std::cout << "\t";
			for (int j = 1; j < cols - 1; ++j) {
				if (field[i][j] == 0) std::cout << '_';
				else std::cout << 'O';
			}
			std::cout << std::endl;
		}
	}

	// The transition to the next generation, we run through all the cells, we consider neighbors
	// and depending on their number change the field (the old field is stored in the cloneField array)
	// The function also checks if the previous generation matches the new generation, if so, returns True
	bool nextGeneration() {
		bool** cloneField = new bool*[rows];
		bool theEnd = true;
		for (int i = 0; i < rows; ++i) cloneField[i] = new bool[cols];
		for (int i = 0; i < rows; ++i)
			for (int j = 0; j < cols; ++j)
				cloneField[i][j] = field[i][j];

		//The main cycle over all elements of the array
		for(int i = 1; i < rows - 1; ++i) {
			for (int j = 1; j < cols - 1; ++j) {
				int neighbors = cloneField[i - 1][j - 1] + cloneField[i - 1][j] + cloneField[i - 1][j + 1]
								+ cloneField[i][j - 1] + cloneField[i][j + 1]
								+ cloneField[i + 1][j - 1] + cloneField[i + 1][j] + cloneField[i + 1][j + 1];
				if (neighbors == 3 && cloneField[i][j] == 0) { // If the cell is dead and has three living neighbors,
					field[i][j] = 1;						   // we revive the cell
					theEnd = false; // If at least something has changed, then the generations are different and the game continues
				}
				if (cloneField[i][j] == 1 && (neighbors < 2 || neighbors > 3)) { // Extinction of a living cell
					field[i][j] = 0;											
					theEnd = false; // If at least something has changed, then the generations are different and the game continues
				}
			}
		}
		//--------------------------------------

		//Change field boundaries for the new generation
		for (int i = 1; i < rows - 1; ++i) { field[i][0] = field[i][cols - 2]; field[i][cols - 1] = field[i][1]; }
		for (int i = 1; i < cols - 1; ++i) { field[0][i] = field[rows - 2][i]; field[rows - 1][i] = field[1][i]; }
		field[0][0] = field[rows - 2][cols - 2]; field[0][cols - 1] = field[rows - 2][1];
		field[rows - 1][0] = field[1][cols - 2]; field[rows - 1][cols - 1] = field[1][1];
		//------------------------------------------

		return theEnd;
	}

	// Function of counting living cells
	int countOfAlive() {
		int cnt = 0;
		for (int i = 1; i < rows - 1; ++i) {
			for (int j = 1; j < cols - 1; ++j) {
				if (field[i][j]) ++cnt;
			}
		}
		return cnt;
	}
};

#endif

