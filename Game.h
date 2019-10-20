#ifndef __GAME_2019__
#define __GAME_2019__
#include "Table.h"
#include <random>
#include <time.h>
#include <Windows.h>


class Game {
	Table gameField; 
	unsigned long long iteration; 
	bool clearConsole; 
public:
	Game() : iteration(0), clearConsole(true) {
		setlocale(0, "Russian");
		srand(time(NULL));
		int rows, cols; 
		int mode;
		bool** inputField; 
		int tmp1;
		std::cout << "\t\t ========== Добро пожаловать в игру 'Жизнь' ==========" << std::endl;
		std::cout << "\t\t ====== Для начала, введем необходимые данные ========" << std::endl;
		std::cout << "\t | Введите '1', если хотите, чтобы консоль очищалась на каждой итерации Жизни |\n";
		std::cout << "\t | Введите '2', если хотите, чтобы каждая итерация Жизни оставалась на экране |\n";
		std::cout << "\t |> Ввод: ";
		std::cin >> tmp1;
	
		if (tmp1 == 2) clearConsole = false;
		else clearConsole = true;

		std::cout << "\t | Введите '1' для начала игры со случайной конфигурацией                     |\n";
		std::cout << "\t | Введите '2' для начала игры со своей конфигурацией                         |\n";
		std::cout << "\t |> Ввод: ";
		std::cin >> mode;
		if (mode == 2) {   // Create custom field configuration
			do { 
				std::cout << "\t |> Введите количество рядов(0 < x < 1001 ): ";
				std::cin >> rows;
			} while (rows > 1000 || rows < 1);

			do { 
				std::cout << "\t |> Введите количество столбцов( 0 < y < 1001 ): ";
				std::cin >> cols; 
			} while (cols > 1000 || cols < 1);

			inputField = new bool*[rows];
			for (int i = 0; i < rows; ++i)
				inputField[i] = new bool[cols];
			std::cout << std::endl;
			std::cout << "\t\t =================== Игровое поле ====================" << std::endl;
			std::cout << "\t| 0 0 0 0 0 0 0 |\n";
			std::cout << "\t| 0 0 0 1 0 0 0 |\n";
			std::cout << "\t| 0 0 0 0 1 0 0 |              - пример игрвого поля, где 0 - мертвая, 1 - живая \n";
			std::cout << "\t| 0 0 1 1 1 0 0 |\n";
			std::cout << "\t| 0 0 0 0 0 0 0 |\n";
			std::cout << "\t =====================================================" << std::endl;
			std::cout << "\t|> Введите игрвое поле (поле должно состоять только из 0 и 1, разделяемых пробелами): \n";
			for (int i = 0; i < rows; ++i) {
				std::cout << "\t|> ";
				for (int j = 0; j < cols; ++j)
					std::cin >> inputField[i][j];
			}
		}
		else { // Random configuration of field
			rows = rand() % 16 + 5, cols = rand() % 16 + 5;
			inputField = new bool*[rows];
			for (int i = 0; i < rows; ++i)
				inputField[i] = new bool[cols];
			for (int i = 0; i < rows; ++i)
				for (int j = 0; j < cols; ++j)
					inputField[i][j] = rand() % 2;
		}
		gameField = Table(cols, rows, inputField);
		 
		for (int i = 0; i < rows; ++i)
			delete[] inputField[i];
		delete[] inputField;
	}

	void playGame() {
		do {
			Sleep(1000); // Slowing down generations (once per second)
			if(clearConsole)
				system("cls"); // Clear console
			++iteration;
			std::cout << "\t ======= " << iteration << " ======="<< std::endl;
			std::cout << "======= Количество живых клеток: " << gameField.countOfAlive() << " =======" << std::endl;
			gameField.printField();
			if (iteration == 1) {
				char p;
				std::cout << "\nВведите '1', чтобы начать: ";
				std::cin >> p;
			}
		} while (gameField.countOfAlive() > 0 && !gameField.nextGeneration()); // While exist at least one living element
																			   // and previous generation is not equal to the current
	}
};

#endif