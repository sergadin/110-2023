#include "vector.h"
using namespace std;

int main (void)
{
    try
    {
        Vector v1(5, 1), v2(5, 2), v3(5, 0);
        Vector v4(6, 3);
        v2.writeLoc();
        v3.writeLoc(); v3.writeLoc(); v3.writeLoc();
        printf ("Vector 2:");
        v2.printVect();
        printf("Vector 3:");
        v3.printVect();
        v1 = v2;
        v2.writeInc(v3);
        printf("%d\n", (v2 < v3));
        printf("%d\n", (v3 < v2));
        v4 < v3;
    }

    catch(Error &err)
    {
        cout << "Исключение: " << err.get_mes() << "\n";
    }

    catch (...)
    {
        cout << "Что-то пошло не так и мы не знаем, что это" << "\n";
    }

    return 0;
}

