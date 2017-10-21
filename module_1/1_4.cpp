/* 
 * Дано натуральное число N. Представить N в виде A + B, так, что НОД(A, B) 
 * максимален, A ≤ B. Вывести A и B. Если возможно несколько ответов - вывести 
 * ответ с минимальным A.
 */
#include <iostream>
#include <assert.h>
#include <math.h>

/*
 * Поиск разложения на числа с максимальным НОД
 */
void find_a_b(int n, int &a, int &b)
{
    // Два тривиальных случая: n = 0 и n = 1
    if (n == 0)
    {
        a = b = 0;
        return;
    }
    if (n == 1)
    {
        a = 0;
        b = 1;
        return;
    }

    a = 1;
    b = n - a;

    int multiplier = 2;
    int sqrt_n = sqrt(n);
    // Ищем первый из простых множителей n
    while(n % multiplier != 0 && multiplier <= sqrt_n)
            multiplier++;

    if (n % multiplier == 0)
    {
        a = n / multiplier;
        b = n - a;
    }
}

int main(int argc, char *argv[])
{
    int n = 0;
    int a = 0, b = 0;

    std::cin >> n;

    assert(n >= 0 && n < 10000000);
    find_a_b(n, a, b);

    std::cout << a << " " << b;

    return 0;
}

