#include <iostream>
#include <iomanip>
#include <omp.h>
#include <windows.h>
#include <sstream>
#include "function.hpp"
using namespace std;

string func = "(x^3)-2";
double f(double x) {
    return function(func, x);
}

void Bisection(double, double, double, double &);
void SIMDPool(double, double, double, int, double&);
int Menu(double, double, double, int, double, double, bool);
void print_table(double, double, double, int, double, double);
bool validate_interval(double, double);
string to_string_with_precision(double, int);
void loading();

int main() {

    double a = -100, b = 100, c = 0.001, root1, root2, temp;
    int N = 10;
    bool flag = false;

    while (1) {
        switch (Menu(a, b, c, N, root1, root2, flag)) {
            case 1:
                loading();
                if (validate_interval(a,b)) {
                    Bisection(a, b, c, root1);
                    SIMDPool(a, b, c, N, root2);
                    flag = true;
                } else {
                    root1 = NULL;
                    root2 = NULL;
                    loading();
                }
                break;

            case 2:
                loading();
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
                cout << "\n\n\n\n\t\t\t\tPlease enter the function : ";
                cin >> func;
                root1 = NULL;
                root2 = NULL;
                loading();
                break;

            case 3:
                do {
                    loading();
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
                    cout << "\n\n\n\n\t\t\t\tPlease enter the number of points : ";
                    cin >> N;
                    if (N <= 0) {
                        loading();
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
                        cout << "\n\n\n\n\t\t\t\tPlease enter a valid value!";
                        Sleep(3000);
                    }
                } while (N <= 0);
                root1 = NULL;
                root2 = NULL;
                loading();
                break;

            case 4:
                loading();
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
                cout << "\n\n\n\n\t\t\t\tPlease enter start of the interval : ";
                cin >> a;
                root1 = NULL;
                root2 = NULL;
                loading();
                break;

            case 5:
                loading();
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
                cout << "\n\n\n\n\t\t\t\tPlease enter end of the interval : ";
                cin >> b;
                root1 = NULL;
                root2 = NULL;
                loading();
                break;

            case 6:
                loading();
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
                cout << "\n\n\n\n\t\t\t\tPlease enter the calculation error value : ";
                cin >> c;
                root1 = NULL;
                root2 = NULL;
                loading();
                break;

            case 7:
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
                system("cls");
                cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t\t\t\t*** Good Bye ***";
                Sleep(3000);
                exit(1);

            default:
                system("cls");
                cout << "\n\n\n\n\t\t\t\tPlease enter correct option!";
                Sleep(3000);
        }
    }

    return 0;
}

void Bisection(double a, double b, double c, double &root) {
    double m;
    while (abs(b-a) >= c) {
        m = (a+b)/2;
        if (f(m) == 0)
            break;
        else if (f(a) * f(m) < 0)
            b = m;
        else
            a = m;
    }
    root =  m;
}

void SIMDPool(double a, double b, double c, int N, double &root) {
    bool flag = true;
    double y[N+2];
    while (abs(b-a) >= c && flag) {
        double s = (b-a)/(N+1);

        #pragma omp parallel
        {
            #pragma omp for
            for (int k = 0; k <= N+1; k++)
                y[k] = f(a + k*s);

            #pragma omp for
            for (int k = 1; k <= N+1; k++) {
                if (y[k] == 0) {
                    a = a + k*s;
                    flag = false;
                }
                else if (y[k-1] * y[k] < 0) {
                    b = a + k*s;
                    a = a + (k-1)*s;
                }
            }
        }
    }

    root =  a;
}

int Menu(double a, double b, double c, int N, double root1, double root2, bool flag) {
    system("cls");

    if (flag) {
        cout << "\n\n\n\n";
        print_table(a, b, c, N, root1, root2);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
        cout << "\t\t\t\t--------------------------------------------------------------------------------------------------------------------------------------------------------" << endl << endl;
    }

    int option;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    if (!flag)
        cout << "\n\n\n\n";
    cout << "\t\t\t\t[+] Menu [+]" << endl << endl;
    cout << "\t\t\t\t--------------------------------------------------------------------------------------------------------------------------------------------------------" << endl << endl;
    cout << "\t\t\t\t[1] Calculate Root In The Interval => ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << "[" << to_string_with_precision(a, 2) << " , " << to_string_with_precision(b, 2) << "]" << endl << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "\t\t\t\t[2] Change Function => ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << func << endl << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "\t\t\t\t[3] Change The Number of Points => ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << N << endl << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "\t\t\t\t[4] Change Start of The Interval => ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << to_string_with_precision(a, 2) << endl << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "\t\t\t\t[5] Change End of The Interval => ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << to_string_with_precision(b, 2) << endl << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "\t\t\t\t[6] Change Calculation Error => ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << to_string(c) << endl << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "\t\t\t\t[7] Exit" << endl << endl;
    cout << "\t\t\t\t--------------------------------------------------------------------------------------------------------------------------------------------------------" << endl << endl;
    cout << "\t\t\t\tPlease enter option : ";
    cin >> option;
    return option;
}

void print_table(double a, double b, double c, int N, double root1, double root2) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    cout << "\t\t\t\t--------------------------------------------------------------------------------------------------------------------------------------------------------" << endl << endl;
    cout << "\t\t\t\t[#] Root Table [#]\n\n";

    int rows = 2;
    int cols = 5;
    int width = 28;
    string data[rows][cols];
    data[0][0] = "Function";
    data[0][1] = "Interval";
    data[0][2] = "Calculation Error";
    data[0][3] = "Bisection Root";
    data[0][4] = "SIMD Root";
    data[1][0] = func;
    data[1][1] = "[" + to_string_with_precision(a, 2) + " , " + to_string_with_precision(b, 2) + "]";
    data[1][2] = to_string(c);
    if (root1 == NULL)
        data[1][3] = "NaN";
    else
        data[1][3] = to_string(root1);
    if (root2 == NULL)
        data[1][4] = "NaN";
    else
        data[1][4] = to_string(root2);

    cout << "\t\t\t\t " << setfill((char)205) << setw(width*cols+cols-1) << (char)205 << endl;
    for (int i = 0; i < rows; i++) {
        cout << "\t\t\t\t";
        cout << (char)186;
        for (int j = 0; j < cols; j++) {
            int padding = (width - data[i][j].length()) / 2;
            cout << right << setfill(' ') << setw(padding) << ' ';
            cout << left << setfill(' ') << setw(width - padding) << data[i][j];
            cout << (char)186;
        }
        cout << endl;
        if (i != rows - 1)
            cout << "\t\t\t\t " << setfill((char)205) << setw(width*cols+cols-1) << (char)205 << endl;
    }
    cout << "\t\t\t\t " << setfill((char)205) << setw(width*cols+cols-1) << (char)205 << endl;
    cout << "\n\t\t\t\t--------------------------------------------------------------------------------------------------------------------------------------------------------" << endl << endl;
}

bool validate_interval(double a, double b) {
    if (f(a) * f(b) >= 0) {
        system("cls");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
        cout << "\n\n\n\n\t\t\t\tYou have not assumed right interval!";
        Sleep(3000);
        return false;
    }
    return true;
}

string to_string_with_precision(double x, int precision) {
    ostringstream out;
    out << fixed << setprecision(precision) << x;
    return out.str();
}

void loading() {
    system("cls");
    system("COLOR 0e");
    printf("\e[?25l");

    SetConsoleCP(437);
    SetConsoleOutputCP(437);
    int bar1 = 177, bar2 = 219;

    cout << "\n\n\n\n\t\t\t\tLoading...";
    cout << "\n\n\t\t\t\t";

    for(int i = 0; i < 25; i++)
        cout << (char)bar1;

    cout <<"\r";
    cout <<"\t\t\t\t";
    for(int i = 0; i < 25; i++) {
        cout << (char)bar2;
        Sleep(15);
    }
    Sleep(40);
    system("cls");
}