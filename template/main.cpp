/*
Phoenix Brehm
EECS 348
Th 11AM
Lab07
Goal: to take an input file about square matrices and then perform operations using a matrix class, to print the matrix, overload adding and multiplication operators, swapping two rows and getting the sum of the diagonal of a matrix.
*/
#include <fstream>
#include <iostream>

using namespace std;

class Matrix {
public:
    int matrix_size;
    double** matrix_data;

    Matrix(int size = 0) : matrix_size(size) {
        matrix_data = new double*[matrix_size];
        for (int i = 0; i < matrix_size; ++i) {
            matrix_data[i] = new double[matrix_size];
        }
    }

    Matrix& operator=(const Matrix& other) {
        if (this == &other) {
            return *this;
        }

        for (int i = 0; i < matrix_size; ++i) {
            delete[] matrix_data[i];
        }
        delete[] matrix_data;

        matrix_size = other.matrix_size;

        matrix_data = new double*[matrix_size];
        for (int i = 0; i < matrix_size; ++i) {
            matrix_data[i] = new double[matrix_size];
            for (int j = 0; j < matrix_size; ++j) {
                matrix_data[i][j] = other.matrix_data[i][j];
            }
        }

        return *this;
    }

    ~Matrix() {
        for (int i = 0; i < matrix_size; ++i) {
            delete[] matrix_data[i];
        }
        delete[] matrix_data;
    }
};

void read_matrix_from_file(const string& file_name, Matrix& matrix_1, Matrix& matrix_2) {
    //Read matrix data from the file
    ifstream myfile(file_name,ifstream::in);
    int n;
    int d;
    try{
        myfile >> n; //reads line 1 in file
        if(n <= 0){ //if we read anything other than an int, we default to 0, and since that is an invalid matrix size anyhow
            throw 0;
        }
    }
    catch(...){
        cout << "Incorrect Size for Matrices\nAll operations will be performed with empty matrices\n";
        return;
    }
    Matrix matrix_A(n);
    Matrix matrix_B(n);

    cout << "Reading from file, will only take in the first " << (n*n*2)+1 << " entries in the file (including the size parameter). All others will be ignored.\n";

    for(int i = 0; i<n;i++){
        for(int j = 0; j<n;j++){
            myfile >> d;
            matrix_A.matrix_data[i][j] = d;
        }

    }
    if(myfile.fail() && !myfile.eof()){ //if bad data was detected
        cout << "INVALID DATA IS DETECTED\nAll operations will be performed with empty matrices\n";
        return;
    }

    for(int i = 0; i<n;i++){
        for(int j = 0; j<n;j++){
            myfile >> d;
            matrix_B.matrix_data[i][j] = d;
        }

    }
    if(myfile.fail() && !myfile.eof()){ //if bad data was detected
        cout << "INVALID DATA IS DETECTED\nAll operations will be performed with empty matrices\n";
        return;
    }

    matrix_1 = matrix_A;
    matrix_2 = matrix_B; //these two statements happen down here so that the values stay as zero
    myfile.close();
    
}

void print_matrix(const Matrix& matrix) {
    //Print the matrix to the console
    for(int i = 0; i<matrix.matrix_size;i++){
        for(int j = 0; j<matrix.matrix_size;j++){
            cout << matrix.matrix_data[i][j] << " "; //iterate through each data point of the matrix and when we fully print a row: new line
        }
        cout << "\n";
    }
}

void print_matrix(const Matrix& matrix_1, const Matrix& matrix_2) {
    //Print both matrices to the console
    for(int i = 0; i<matrix_1.matrix_size;i++){
        for(int j = 0; j<matrix_1.matrix_size;j++){
            cout << matrix_1.matrix_data[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
    for(int i = 0; i<matrix_2.matrix_size;i++){
        for(int j = 0; j<matrix_2.matrix_size;j++){
            cout << matrix_2.matrix_data[i][j] << " ";
        }
        cout << "\n";
    }
    //does the same thing as print matrix but does it twice with two different matrices
}

Matrix add_matrices(const Matrix& matrix_1, const Matrix& matrix_2) {
    //Implemented matrix addition
    Matrix retMat(matrix_1.matrix_size);
    for(int i=0;i<matrix_1.matrix_size; i++){
        for(int j=0; j<matrix_1.matrix_size;j++){
            retMat.matrix_data[i][j] = (matrix_1.matrix_data[i][j] + matrix_2.matrix_data[i][j]);
        }
    }
    return retMat;
}

Matrix multiply_matrices(const Matrix& matrix_1, const Matrix& matrix_2) {
    //Implemented matrix multiplication
    Matrix retMat(matrix_1.matrix_size); //since both inputted matrices are square, our multiplicative output will be of the same size
    int sum = 0;
    for(int i=0; i<matrix_1.matrix_size; i++){
        for(int j=0; j<matrix_1.matrix_size; j++){
            for(int k=0; k<matrix_1.matrix_size; k++){
                sum += matrix_1.matrix_data[i][k] * matrix_2.matrix_data[k][j];
            }
            retMat.matrix_data[i][j] = sum;
            sum = 0;
        }
    }
    return retMat;
}

// Overloaded + operator for matrix addition
Matrix operator+(const Matrix& matrix_1, const Matrix& matrix_2){
   return add_matrices(matrix_1, matrix_2);
}

// Overloaded * operator for matrix multiplication
Matrix operator*(const Matrix& matrix_1, const Matrix& matrix_2){
    return multiply_matrices(matrix_1, matrix_2);
}

void get_diagonal_sum(const Matrix& matrix) {
    //Calculate and print the sum of the diagonal elements
    int sum = 0;
    for(int i=0; i<matrix.matrix_size; i++){
        sum += matrix.matrix_data[i][i]; //[i][i] is the diagonal
    }
    cout << "Sum of Diagonal Elements is: " << sum << "\n";
}

void swap_matrix_row(Matrix& matrix, int row1, int row2) {
    //Swap the rows 'row1' and 'row2' in the matrix
    Matrix swapMat(matrix.matrix_size);
    if(row1 < 0 || row1 >= matrix.matrix_size || row2 < 0 || row2 >= matrix.matrix_size){ //if index <0 or outside of bounds
        cout << "Operation cannot be performed with these row indices\n";
        return;
    }
    for(int i=0;i<matrix.matrix_size;i++){
        for(int j=0;j<matrix.matrix_size;j++){
            if(i == row1){
                swapMat.matrix_data[i][j] = matrix.matrix_data[row2][j];
            }else if(i == row2){
                swapMat.matrix_data[i][j] = matrix.matrix_data[row1][j];
            }else{
                swapMat.matrix_data[i][j] = matrix.matrix_data[i][j];
            }
        }
    }
    matrix = swapMat; //reassigns the swapped values to the matrix
}

int main(int argc, char* argv[]) {
    Matrix matrix_1, matrix_2;
    read_matrix_from_file("matrix.txt", matrix_1, matrix_2);

    cout << "print_matrix" << endl;
    print_matrix(matrix_1, matrix_2);

    cout << "add_matrices result:" << endl;
    Matrix add_result_1 = add_matrices(matrix_1, matrix_2);
    Matrix add_result_2 = matrix_1 + matrix_2;
    print_matrix(add_result_1);
    cout << "\n";
    print_matrix(add_result_2);

    
    cout << "multiply_matrices result:" << endl;
    Matrix multiply_result_1 = multiply_matrices(matrix_1, matrix_2);
    Matrix multiply_result_2 = matrix_1 * matrix_2;
    print_matrix(multiply_result_1);
    cout << "\n";
    print_matrix(multiply_result_2);

    cout << "get matrix diagonal sum" << endl;
    get_diagonal_sum(matrix_1);
    
    cout << "\n";
    cout << "swap matrix rows" << endl;
    swap_matrix_row(matrix_1, 0, 1);
    print_matrix(matrix_1);

    cout << "\n";
    cout << "Press Enter Key to Quit.";
    cin.get();
    return 0;
}