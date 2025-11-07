#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std; 

class Matrix {
    private: 
        vector<vector<int>> _matrix;
    public:
        Matrix() {} //initializes an empty matrix

        Matrix (int size) { //creates an n x n square matrix that is filled with 0's
            _matrix.resize(size, vector<int>(size,0));
        }

        Matrix(const vector<vector<int>> &mat) { //takes in a 2D vector and stores it inside _matrix
            _matrix = mat;
        }    //may not end up needing this constructor 

        int get_value (int row, int col) const { //define get_value instead of interacting directly with std::vector
           return _matrix[row][col]; 
        }

        void set_value (int row, int col, int val) { //define set_value instead of interacting directly with std::vector
           _matrix[row][col] = val;
        }

        int size() const { //function that gives the size of the matrix
            return _matrix.size();
        }

        vector<int> &get_row (int row) { //return a reference to the OG row
            return _matrix[row];
        }

        Matrix operator+(const Matrix &other) const { //overloaded operator for +
            int n = size();
            Matrix result(n);

            for (int i=0; i<n; i++){
                for (int j=0; j<n; j++){
                    int sum = get_value(i,j) + other.get_value(i,j); //add each element together
                    result.set_value(i,j,sum);
                }
            }
            return result;
        }

        Matrix operator*(const Matrix &other) const { //overloaded operator for *
            int n = size();
            Matrix result(n);

            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    int sum = 0;
                    for (int k = 0; k < n; k++) {
                        sum += get_value(i, k) * other.get_value(k, j);
                    }
                    result.set_value(i, j, sum);
                }
            }
            return result;
        }
        
        void read_matrix(ifstream &File, int size) {
            _matrix.resize(size, vector<int>(size)); //changes the matrices size to n before reading

            for (int i = 0; i<size; i++){ //store matrix
                for (int j = 0; j<size; j++){
                    int val;
                    File >> val;
                    set_value(i,j,val);
                }
            }
        }
        
        void print_matrix() {
            for (const auto &row : _matrix) {
                for (int val : row)
                    cout << val << "\t";
                cout << endl;
            }
        }

        int diagonal_sum() {
            int n = size();
            
            int main_sum = 0;
            int secondary_sum = 0;

            for (int i = 0; i < n; i++) {
                main_sum += get_value(i,i); // main diagonal
                secondary_sum += get_value(i, n-1-i); // secondary diagonal
            }

            int total_sum = main_sum + secondary_sum;

            return total_sum;
        }

        Matrix swap_rows(int row1, int row2) {
            Matrix result = *this; //make a new result copy of the OG matrix

            vector<int> temp = result.get_row(row1); //store first row in temp
            result.get_row(row1) = result.get_row(row2); //swap values
            result.get_row(row2) = temp; //swap values

            return result;
        }

        Matrix swap_cols(int col1, int col2) {
            int n = size();
            Matrix result = *this;

            for (int i=0; i<n; i++) {
                int temp = result.get_value(i,col1); //store col1 val in temp
                result.set_value(i, col1, result.get_value(i,col2)); //swap col1 and col2 values
                result.set_value(i,col2, temp); //swap the col2 and col values
            }
            return result;
        }

        Matrix insert_value(int row, int col, int val) {
            int n = size();
            Matrix result = *this;

            for (int i=0; i<n; i++){
                for (int j=0; j<n; j++){
                    if (result.get_value(i,j) == result.get_value(row,col)) {
                        result.set_value(i,j,val); //once the loop arrives on the target position, switch in the value
                    }
                }
            }
            return result;
        }
};


int main() {

    string filename;
    cout << "Enter a file name: " <<endl;
    cin >> filename; 

    ifstream File(filename);

    if (!File) { // always check that the file opened successfully
        cerr << "Error: could not open file.\n";
        return 1;
    }

    int size;
    File >> size;  // read the first number (the size)

    Matrix A, B;

    //Task 1
    A.read_matrix(File, size);
    B.read_matrix(File, size);

    cout << "Matrix A:\n";
    A.print_matrix();
    cout << "\n";

    cout << "Matrix B:\n";
    B.print_matrix();
    cout << "\n";

    //Task 2
    Matrix C = A + B;
    cout << "A + B:\n";
    C.print_matrix();
    cout << "\n";

    //Task 3
    Matrix D = A * B;
    cout << "A * B:\n";
    D.print_matrix();
    cout << "\n";

    //Task 4
    int sum = A.diagonal_sum();
    cout << "Sum of the diagonal elements of A: " << sum << endl;
    cout << "\n";

    //Task 5
    int row1;
    int row2;
    string userinput1;
    string userinput2;
    
    cout << "Enter the first row number to swap with: ";
    cin >> userinput1;
    if (userinput1.empty()) {
        row1 = 0; //set default value as 0
    } else {
        row1 = stoi(userinput1);
    }

    cout << "Enter the second row number to swap with: ";
    cin >> userinput2;
    if (userinput2.empty()) {
        row2 = 1; //set default value as 1
    } else {
        row2 = stoi(userinput2);
    }

    cout << "A with rows " << row1 << " and " << row2 << " swapped:" << endl;
    Matrix E = A.swap_rows(row1,row2);
    E.print_matrix();
    cout << "\n";

    //Task 6
    int col1;
    int col2;

    cout << "Enter the first col number to swap with: ";
    cin >> userinput1;
    if (userinput1.empty()) {
        col1 = 0; //set default value as 0
    } else {
        col1 = stoi(userinput1);
    }

    cout << "Enter the second col number to swap with: ";
    cin >> userinput2;
    if (userinput2.empty()) {
        col2 = 1; //set default value as 1
    } else {
        col2 = stoi(userinput2);
    }

    cout << "A with cols " << col1 << " and " << col2 << " swapped:" << endl;
    Matrix F = A.swap_cols(col1,col2);
    F.print_matrix();
    cout << "\n";

    //Task 7
    int value;
    string userinput3;

    cout << "Enter the row index to insert to: ";
    cin >> userinput1;
    if (userinput1.empty()) {
        row1 = 0; //set default value as 0
    } else {
        row1 = stoi(userinput1);
    }

    cout << "Enter the col index to insert to: ";
    cin >> userinput2;
    if (userinput2.empty()) {
        col1 = 0; //set default value as 0
    } else {
        col1 = stoi(userinput2);
    }

    cout << "Enter the value to insert: ";
    cin >> userinput3;
    if (userinput3.empty()) {
        value = 100; //set default value as 1
    } else {
        value = stoi(userinput3);
    }

    cout << "A with " << value << " inserted at " << row1 << ", " << col1<< ":"<< endl;
    Matrix G = A.insert_value(row1,col1,value);
    G.print_matrix();
    cout << "\n";

    File.close();
    return 0;
}