#include "../headers/TicTacToe.h"
#include "../headers/Matrix.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

TicTacToe::TicTacToe() : board(3, 3)
{
    // Inicializar el tablero y otros miembros según sea necesario

    currentPlayer = "X";
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            board.set(i, j, " ");
        }
    }
}

void TicTacToe::play()
{
    // Mostrar mensaje de bienvenida
    cout << "Welcome to the Tic-Tac-Toe game" << endl;

    string saveFileName;

    // Pedir al usuario el nombre del archivo de guardado

    cout << "Enter the name of file from which you want to load: ";
    cin >> saveFileName;
    // Cargar el juego si existe
    if (!loadGame(saveFileName))
    {
        return;
    }

    saveFileName = "saved_" + playerNames[0] + "_" + playerNames[1] + ".txt";

    while (true)
    {
        if (wantsToQuit())
        {
            break;
        }
        if (wantsToSave())
        {
            saveGame(saveFileName);
            break;
        }
        printBoard();
        cout << "Current player: " << playerNames[currentPlayer == "X" ? 0 : 1] << endl;
        int row, col;

        while (true)
        {
            cout << "Enter the coordinate (Example: A1): ";
            string move;
            cin >> move;

            if (move.length() == 2 && isalpha(move[0]) && isdigit(move[1]))
            {
                row = toupper(move[0]) - 'A';
                col = move[1] - '1';

                if (row >= 0 && row < 3 && col >= 0 && col < 3 && board.get(row, col) == " ")
                {
                    break;
                }
            }
            cout << "Invalid movement. Try again." << endl;
        }

        board.set(row, col, currentPlayer);

        if (checkWin())
        {
            printBoard();
            cout << playerNames[currentPlayer == "X" ? 0 : 1] << " has won!" << endl;
            break;
        }
        else if (checkDraw())
        {
            printBoard();
            cout << "Tie!" << endl;
            break;
        }

        currentPlayer = (currentPlayer == "X") ? "O" : "X";
    }

    // Guardar el juego al finalizar
    // saveGame(saveFileName);
}

void TicTacToe::printBoard()
{
    cout << "Board" << endl;
    cout << "- | 1 | 2 | 3 |" << endl;

    for (int i = 0; i < 3; i++)
    {
        cout << static_cast<char>('A' + i) << " |";
        for (int j = 0; j < 3; j++)
        {
            cout << " " << board.get(i, j) << " |";
        }
        cout << endl;
    }
}

bool TicTacToe::wantsToQuit()
{
    char choice;
    cout << "Do you want to exit the game? (Y/N): ";
    cin >> choice;
    return (choice == 'Y' || choice == 'y');
}

bool TicTacToe::wantsToSave()
{
    char choice;
    cout << "Do you want to save the game? (Y/N): ";
    cin >> choice;
    return (choice == 'Y' || choice == 'y');
}

bool TicTacToe::checkWin()
{
    // Comprobar filas, columnas y diagonales
    for (int i = 0; i < 3; i++)
    {
        if (board.get(i, 0) == currentPlayer && board.get(i, 1) == currentPlayer && board.get(i, 2) == currentPlayer)
        {
            return true; // Fila
        }
        if (board.get(0, i) == currentPlayer && board.get(1, i) == currentPlayer && board.get(2, i) == currentPlayer)
        {
            return true; // Columna
        }
    }
    if (board.get(0, 0) == currentPlayer && board.get(1, 1) == currentPlayer && board.get(2, 2) == currentPlayer)
    {
        return true; // Diagonal principal
    }
    if (board.get(0, 2) == currentPlayer && board.get(1, 1) == currentPlayer && board.get(2, 0) == currentPlayer)
    {
        return true; // Diagonal inversa
    }

    return false;
}

bool TicTacToe::checkDraw()
{
    // Comprobar si el tablero está lleno
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board.get(i, j) == " ")
            {
                return false;
            }
        }
    }
    return true;
}

bool TicTacToe::saveGame(const string &fileName)
{
    ofstream outputFile(fileName); // Nombre del archivo de guardado
    if (outputFile.is_open())
    {
        outputFile << "Name player1: " << endl
                   << playerNames[0] << endl;
        outputFile << "Name player2: " << endl
                   << playerNames[1] << endl;
        if (currentPlayer == "X")
        {
            outputFile << "Player: " << playerNames[0] << endl;
        }
        else
        {
            outputFile << "Player: " << playerNames[1] << endl;
        }
        // outputFile << "Player: " << playerNames[currentPlayer == "X" ? 0 : 1] << endl; // ?: Esto es un operario ternatio, como un if.
        outputFile << "Board" << endl;
        outputFile << "- | 1 | 2 | 3 |" << endl;

        for (int i = 0; i < 3; i++)
        {
            outputFile << static_cast<char>('A' + i) << " |";
            for (int j = 0; j < 3; j++)
            {
                outputFile << " " << board.get(i, j) << " |";
            }
            outputFile << endl;
        }

        outputFile << "Current turn: " << endl
                   << playerNames[currentPlayer == "X" ? 0 : 1] << endl;

        outputFile.close();
        cout << "Game saved successfully to "
             << fileName;
        return true;
    }
    else
    {
        cout << "Failed to save the game state." << endl;
        return false;
    }
}

bool TicTacToe::loadGame(const string &fileName)
{
    ifstream inputFile(fileName); // Nombre del archivo de guardado

    if (inputFile.is_open())
    {
        // Variables para almacenar los datos cargados
        string line;
        string currentPlayerName;
        string player1Name, player2Name;
        string boardHeader;
        Matrix<string> loadedBoard(3, 3);

        // Leer datos desde el archivo
        // Leer el nombre del jugador 1
        getline(inputFile, line);
        if (line.find("Name player1") != std::string::npos)
        {
            getline(inputFile, player1Name);
        }
        getline(inputFile, line);
        if (line.find("Name player2") != std::string::npos)
        {
            getline(inputFile, player2Name);
        }

        getline(inputFile, line); // Leer el nombre del jugador actual

        if (line.find(player1Name) != std::string::npos)
        {
            currentPlayerName = player1Name;
        }
        else
        {
            currentPlayerName = player2Name;
        }

        // Asignar los nombres de los jugadores al arreglo
        playerNames[0] = player1Name;
        playerNames[1] = player2Name;

        if (currentPlayerName == playerNames[0])
        {
            currentPlayer = "X";
        }
        else if (currentPlayerName == playerNames[1])
        {
            currentPlayer = "O";
        }
        else
        {
            // En caso de un error en los datos del archivo
            cout << "Error: Unable to determine the current player." << endl;
            inputFile.close();
            return false;
        }

        // Leer el encabezado del tablero desde el archivo
        getline(inputFile, line);
        // cout << line << endl;
        getline(inputFile, boardHeader);
        // cout << boardHeader << endl;

        // Leer el estado del tablero desde el archivo
        if (line.find("Board") != std::string::npos)
        {
            for (int i = 0; i < 3; i++)
            {
                getline(inputFile, line);

                for (int j = 0; j < 3; j++)
                {
                    string s(1, line[4 * j + 4]);
                    loadedBoard.set(i, j, s);
                }
            }
        }
        else
        {
            // En caso de un error en los datos del archivo
            cout << "Error: The save file doesn't match the correct format." << endl;
            inputFile.close();
            return false;
        }

        // Copiar el estado cargado al tablero del juego
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                board.set(i, j, loadedBoard.get(i, j));
            }
        }

        inputFile.close();
        cout << "Game loaded successfully from "
             << fileName << endl;
        return true;
    }
    else
    {
        // El archivo no existe, mostramos un mensaje y comenzamos un nuevo juego
        cout << "No saved game found. Please specify a file name to load." << endl;
        return false;
    }
}
