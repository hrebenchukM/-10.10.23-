#include <iostream>
#include <string>
using namespace std;


class Exception {

public:
    string m_message;
    Exception() { m_message = " "; }
    Exception(const char* message) { m_message = message; }
    virtual const string& GetMessage() const { return m_message; }
};

class ArraySizeException : public Exception {

public:
    ArraySizeException(const char* mes) : Exception(mes) {}
    virtual const string& GetMessage() const { return m_message; }

};





class ArrayDataException : public Exception {
    int row;
    int col;

public:
    ArrayDataException(int r, int c) : row(r), col(c) {}
    virtual const string& GetMessage() const {
        return "Data exception at row:" + to_string(row) + ", col:" + to_string(col);
    }
};



class ArrayValueCalculator
{
    string** array;
    int rows;
    int cols;
public:
    ArrayValueCalculator() {
        array = nullptr;
        rows = 0;
        cols = 0;
    }
    ArrayValueCalculator(ArrayValueCalculator& obj) {
        this->rows = obj.rows;
        this->cols = obj.cols;
        array = new string * [rows];
        for (int i = 0; i < rows; i++) {
            array[i] = new string[cols];
        }
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                this->array[i][j] = obj.array[i][j];
            }
        }
    }
    ArrayValueCalculator(string** arr, int r, int c) {
        this->array = arr;
        this->rows = r;
        this->cols = c;

        if (rows != 4 || cols != 4) {
            throw  ArraySizeException("Invalid array size");
        }
    }
    int doCalc()
    {
        int result = 0;


        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                try {
                    int value = stoi(array[i][j]);

                    result = result + value;
                }

                catch (...) {
                    throw ArrayDataException(i, j);
                }
            }
        }

        return result;
    }


    ~ArrayValueCalculator() {
        for (int i = 0; i < rows; ++i) {
            delete[] array[i];
        }
        delete[] array;
    }
};











int main() {
    string** inputArray = new string * [4];
    for (int i = 0; i < 4; ++i) {
        inputArray[i] = new string[4];
    }


    string inputArrayValues[4][4] = {
           {"0", "1", "2", "k"},
           {"4", "5", "6", "7"},
           {"8", "9", "8", "7"},
           {"6", "5", "4", "3"}
    };
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            inputArray[i][j] = inputArrayValues[i][j];
        }
    }
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            cout << inputArray[i][j] << " ";
        }
        cout << endl;
    }
    try {
        ArrayValueCalculator calculator(inputArray, 4, 5);
        int result = calculator.doCalc();
        cout << "Result: " << result << endl;
    }

    catch (ArraySizeException& e) {
        cout << "Error of size: " << e.GetMessage() << endl;
    }
    catch (ArrayDataException& e) {
        cout << "Error of data: " << e.GetMessage() << endl;
    }

    for (int i = 0; i < 4; ++i) {
        delete[] inputArray[i];
    }
    delete[] inputArray;

    return 0;
}