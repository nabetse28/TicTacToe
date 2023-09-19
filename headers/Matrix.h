#ifndef MATRIX_H
#define MATRIX_H

#include "LinkedList.h"
#include <iostream>

using namespace std;

template <class T>
class Matrix
{
private:
    LinkedList<LinkedList<T> *> rows;
    int numRows;
    int numCols;

public:
    Matrix() {}
    Matrix(int rows, int cols) : numRows(rows), numCols(cols)
    {
        for (int i = 0; i < rows; i++)
        {
            LinkedList<T> *row = new LinkedList<T>;
            for (int j = 0; j < cols; j++)
            {
                row->insert(T()); // Insert default-initialized elements
            }
            this->rows.insert(row);
        }
    }

    void set(int row, int col, T data)
    {
        if (row < 0 || row >= numRows || col < 0 || col >= numCols)
        {
            throw out_of_range("Index out of bounds.");
        }
        LinkedList<T> *targetRow = rows.get(row);
        targetRow->set(col, data);
    }

    T get(int row, int col)
    {
        if (row < 0 || row >= numRows || col < 0 || col >= numCols)
        {
            throw out_of_range("Index out of bounds.");
        }
        LinkedList<T> *targetRow = rows.get(row);
        return targetRow->get(col);
    }
    void printMatrix()
    {

        for (int i = 0; i < numRows; i++)
        {
            cout << "[";
            LinkedList<T> *row = rows.get(i);
            for (int j = 0; j < numCols; j++)
            {
                if (j + 1 == numCols)
                {
                    cout << row->get(j) << "]\n";
                }
                else
                {
                    cout << row->get(j) << ", ";
                }
            }
        }
    }
    ~Matrix()
    {
        for (int i = 0; i < numRows; i++)
        {
            delete rows.get(i);
        }
    }
};

#endif // MATRIX_H