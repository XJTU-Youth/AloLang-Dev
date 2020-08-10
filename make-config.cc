#include <iostream>
using namespace std;

int main()
{
    string tmp1, tmp2;
    cerr << "Specifi compiler path: ";
    getline(cin, tmp1);
    tmp2 = "CC = ";
    tmp2 += tmp1;
    cout << tmp2 << endl;

    cerr << "Specifi ar path: ";
    getline(cin, tmp1);
    tmp2 = "AR = ";
    tmp2 += tmp1;
    cout << tmp2 << endl;

    cerr << "Specifi compile flag(include include path): ";
    getline(cin, tmp1);
    tmp2 = "CFLAG = ";
    tmp2 += tmp1;
    cout << tmp2 << endl;

}