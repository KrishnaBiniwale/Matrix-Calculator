#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>

using namespace std;

void printMatrix(vector<vector<double>> &matrix)
{
    if (matrix.size() == 0)
    {
        return;
    }
    for (size_t j = 0; j < matrix[0].size(); j++)
    {
        cout << "| ";
        for (size_t i = 0; i < matrix.size(); i++)
        {
            cout << matrix[i][j] << " ";
        }
        cout << "|" << endl;
    }
}

vector<vector<double>> initializeMatrix()
{
    vector<vector<double>> matrix;
    size_t dimension = 0;
    bool quit = false;

    while (true)
    {
        if (dimension != 0)
        {
            cout << endl;
            printMatrix(matrix);
        }
        else
        {
            cin.ignore();
        }
        cout << "\nEnter the vectors that form your matrix or enter \'Q\' to quit:" << endl;
        cout << "For example, enter the vector v = (1, 2, 3) as \"1 2 3\"." << endl;
        cout << "v = ";
        string str;

        getline(cin, str);
        stringstream ss(str);
        vector<double> vec;
        string num;
        bool cont = false;
        while (ss >> num)
        {
            if (num == "Q" || num == "q")
            {
                cout << endl;
                printMatrix(matrix);
                cout << endl;
                quit = true;
                break;
            }
            else
            {
                double x = 0;
                try
                {
                    x = stod(num);
                }
                catch (...)
                {
                    cout << "\nInvalid Input." << endl;
                    cont = true;
                    break;
                }
                vec.push_back(x);
            }
        }
        if (quit)
        {
            break;
        }
        else if (cont)
        {
            continue;
        }

        if (dimension == 0)
        {
            dimension = vec.size();
            matrix.push_back(vec);
        }
        else if (dimension != vec.size())
        {
            cout << "\nThis vector's dimensions are not compatible with this matrix." << endl;
        }
        else
        {
            matrix.push_back(vec);
        }
    }
    return matrix;
}

double determinant(vector<vector<double>> &matrix)
{
    if (matrix.size() == 1)
    {
        return matrix[0][0];
    }
    else if (matrix.size() == 2)
    {
        return (matrix[0][0] * matrix[1][1]) - (matrix[0][1] * matrix[1][0]);
    }
    else
    {
        double totalDeterminant = 0;
        for (size_t i = 0; i < matrix.size(); i++)
        {
            vector<vector<double>> smaller;
            for (size_t j = 0; j < matrix.size(); j++)
            {
                if (j == i)
                {
                    continue;
                }
                vector<double> vec;
                for (size_t k = 1; k < matrix[0].size(); k++)
                {
                    vec.push_back(matrix[j][k]);
                }
                smaller.push_back(vec);
            }

            double cofactor = matrix[i][0] * determinant(smaller);

            if (i % 2 == 0)
            {
                totalDeterminant += cofactor;
            }
            else
            {
                totalDeterminant -= cofactor;
            }
        }
        return totalDeterminant;
    }
    return 0;
}

vector<vector<double>> multiply(vector<vector<double>> &m1, double scalar)
{
    vector<vector<double>> result;
    for (size_t i = 0; i < m1.size(); i++)
    {
        vector<double> vec;
        for (size_t j = 0; j < m1[0].size(); j++)
        {
            vec.push_back(m1[i][j] * scalar);
        }
        result.push_back(vec);
    }
    return result;
}

vector<vector<double>> multiply(vector<vector<double>> &m1, vector<vector<double>> &m2)
{
    vector<vector<double>> matrix;
    for (size_t width = 0; width < m2.size(); width++)
    {
        vector<double> vec;
        matrix.push_back(vec);
    }

    for (size_t h = 0; h < m1[0].size(); h++)
    {
        for (size_t i = 0; i < m2.size(); i++)
        {
            double sum = 0;
            for (size_t j = 0; j < m1.size(); j++)
            {
                sum += m1[j][h] * m2[i][j];
            }
            matrix[i].push_back(sum);
        }
    }
    return matrix;
}

void display()
{
    cout << endl;
    cout << "Key"
         << " | "
         << "Operations" << endl;
    cout << "-------------------------------" << endl;
    cout << "1: "
         << " | "
         << "Create Matrix" << endl;
    cout << "-------------------------------" << endl;
    cout << "2: "
         << " | "
         << "Delete Matrix" << endl;
    cout << "-------------------------------" << endl;
    cout << "3: "
         << " | "
         << "Change Current Matrix" << endl;
    cout << "-------------------------------" << endl;
    cout << "4: "
         << " | "
         << "Print Current Matrix" << endl;
    cout << "-------------------------------" << endl;
    cout << "5: "
         << " | "
         << "Print All Matrices" << endl;
    cout << "-------------------------------" << endl;
    cout << "6: "
         << " | "
         << "Find Determinant" << endl;
    cout << "-------------------------------" << endl;
    cout << "7: "
         << " | "
         << "Multiply Matrix by Scalar" << endl;
    cout << "-------------------------------" << endl;
    cout << "8: "
         << " | "
         << "Multiply Two Matrices" << endl;
    cout << "-------------------------------" << endl;
    cout << "0: "
         << " | "
         << "Quit" << endl;
    cout << "-------------------------------" << endl;
    cout << endl;
}

int main()
{
    cout << "\nThis is a matrix calculator.\n"
         << endl;
    bool quit = false;
    vector<vector<vector<double>>> matrices;
    vector<vector<double>> currentMatrix;
    size_t currentIndex;
    while (true)
    {
        display();
        cout << "Operation #: ";
        int key;
        cin >> key;
        cout << endl;

        switch (key)
        {
        case 0:
        {
            quit = true;
        }
        break;
        case 1:
        {
            vector<vector<double>> matrix = initializeMatrix();
            if (matrix.size() != 0)
            {
                matrices.push_back(matrix);
                currentMatrix = matrices[matrices.size() - 1];
                currentIndex = matrices.size() - 1;
            }
        }
        break;
        case 2:
        {
            cout << "Matrix Deletion #: ";
            size_t index = 0;
            cin >> index;
            if (cin.fail() || (index - 1 < 0 || index - 1 >= matrices.size()))
            {
                cout << "Invalid Matrix #" << endl;
            }
            else
            {
                swap(matrices[index - 1], matrices[matrices.size() - 1]);
                matrices.pop_back();
                if (currentIndex == index - 1)
                {
                    currentIndex = matrices.size() - 1;
                    currentMatrix = matrices[matrices.size() - 1];
                }
                cout << "\nDeletion Successful" << endl;
            }
        }
        break;
        case 3:
        {
            cout << "Matrix Selection #: ";
            size_t index = 0;
            cin >> index;
            if (cin.fail() || (index - 1 < 0 || index - 1 >= matrices.size()))
            {
                cout << "Invalid Matrix #" << endl;
            }
            else
            {
                currentMatrix = matrices[index - 1];
                currentIndex = index - 1;
                cout << endl;
                cout << "Change Successful\n"
                     << endl;
                cout << "New Matrix #" << index << "\n"
                     << endl;
                printMatrix(currentMatrix);
            }
        }
        break;
        case 4:
        {
            if (matrices.size() != 0)
            {
                cout << "Matrix #" << currentIndex + 1 << "\n"
                     << endl;
                printMatrix(currentMatrix);
            }
        }
        break;
        case 5:
        {
            for (size_t i = 0; i < matrices.size(); i++)
            {
                cout << "Matrix #" << i + 1 << ":\n"
                     << endl;
                printMatrix(matrices[i]);
                cout << endl;
            }
        }
        break;
        case 6:
        {
            if (currentMatrix.size() == 0 || currentMatrix.size() != currentMatrix[0].size())
            {
                cout << "This operation is not possible with this matrix." << endl;
            }
            else
            {
                double num = determinant(currentMatrix);
                cout << "The determinant of the current matrix is: " << num << endl;
            }
        }
        break;
        case 7:
        {
            if (matrices.size() < 1)
            {
                cout << "There are not enough matrices. Initialize a matrix before you multiply it." << endl;
                break;
            }
            size_t num1 = 0;
            while (true)
            {
                cout << "Select first matrix: ";
                cin >> num1;
                cout << endl;
                if (cin.fail() || (num1 - 1 < 0 || num1 - 1 >= matrices.size()))
                {
                    cout << "Invalid Number.\n"
                         << endl;
                }
                else
                {
                    break;
                }
            }
            vector<vector<double>> m1 = matrices[num1 - 1];
            double scalar = 0;
            while (true)
            {
                cout << "Select scalar to multiply by: ";
                cin >> scalar;
                cout << endl;
                if (cin.fail())
                {
                    cout << "Invalid Number.\n"
                         << endl;
                }
                else
                {
                    break;
                }
            }

            vector<vector<double>> matrix = multiply(m1, scalar);
            cout << "The original matrix was: \n"
                 << endl;
            printMatrix(currentMatrix);
            cout << endl;
            cout << "The resulting matrix is: \n"
                 << endl;
            printMatrix(matrix);
            matrices.push_back(matrix);
            currentMatrix = matrices[matrices.size() - 1];
            currentIndex = matrices.size() - 1;
        }
        break;
        case 8:
        {
            if (matrices.size() < 1)
            {
                cout << "There are not enough matrices. Initialize some matrices before you multiply them." << endl;
                break;
            }
            size_t num1 = 0;
            while (true)
            {
                cout << "Select first matrix: ";
                cin >> num1;
                cout << endl;
                if (cin.fail() || (num1 - 1 < 0 || num1 - 1 >= matrices.size()))
                {
                    cout << "Invalid Number.\n"
                         << endl;
                }
                else
                {
                    break;
                }
            }
            vector<vector<double>> m1 = matrices[num1 - 1];
            size_t num2 = 0;
            while (true)
            {
                cout << "Select second matrix: ";
                cin >> num2;
                cout << endl;
                if (cin.fail() || (num2 - 1 < 0 || num2 - 1 >= matrices.size()))
                {
                    cout << "Invalid Number.\n"
                         << endl;
                }
                else
                {
                    break;
                }
            }
            vector<vector<double>> m2 = matrices[num2 - 1];

            if (m1.size() != m2[0].size())
            {
                cout << "This operation is not possible with these matrices." << endl;
            }
            else
            {
                vector<vector<double>> matrix = multiply(m1, m2);
                cout << "The resulting matrix is: \n"
                     << endl;
                printMatrix(matrix);
                matrices.push_back(matrix);
                currentMatrix = matrices[matrices.size() - 1];
                currentIndex = matrices.size() - 1;
            }
        }
        break;
        }

        if (quit)
        {
            break;
        }
    }
    cout << endl;
}
