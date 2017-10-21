/*
 *     Дано N кубиков. Требуется определить каким количеством способов можно 
 * выстроить из N кубиков пирамиду. Каждый вышележащий слой пирамиды должен 
 * быть не больше нижележащего.
 */
#include <iostream>
#include <cassert>

long long partitions(int n)
{
    long long **p = new long long*[n+1];
    assert(p);

    for (int i = 0; i <= n; i++)
    {
        p[i] = new long long[n+1];
        assert(p[i]);
        p[i][0] = 0;
    }
    p[0][0] = 1;
    for (int i = 0; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (j <= i)
                p[i][j] = p[i][j-1] + p[i-j][j];
            else
                p[i][j] = p[i][i];
        }
    }

    long long result = p[n][n];

    for (int i = 0; i <= n; i++)
        delete[] p[i];
    delete[] p;
    return result;
}

int main()
{
    int n = 0;
    std::cin >> n;
    assert(n > 0);
    std::cout << partitions(n);
    return 0;
}
