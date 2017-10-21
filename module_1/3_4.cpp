/*    
 *     Дан отсортированный массив различных целых чисел A[0..n-1] и массив 
 * целых чисел B[0..m-1]. Для каждого элемента массива B[i] найдите 
 * минимальный индекс элемента массива A[k], ближайшего по значению к B[i]. 
 * Время работы поиска для каждого элемента B[i]: O(log(k)).
 * n ≤ 110000, m ≤ 1000.
 */
#include <iostream>
#include <assert.h>

int binary_search(int *arr, int count, int key)
{
    if (count == 1)
        return arr[0];

    int l = 0;
    int r = 1;

    // Ищем интервал для бинарного поиска
    while (r < count && arr[r] < key)
    {
        int t = r;
        r = r + 2 * (r - l + 1);
        l = t;
    }
    if (r >= count)
        r = count - 1;
    // Бинарный поиск
    while (r - l > 1)
    {
        int mid = (l + r) / 2;
        if (arr[mid] > key)
            r = mid;
        else
            l = mid;
    }

    // Возвращаем ближайший к ключу элемент
    if (key - arr[l] > arr[r] - key)
        return r;
    return l;

}

void twins(int *result, int *a, int n, int *b, int m)
{
    for(int i = 0; i < m; i++)
    {
        result[i] = binary_search(a, n, b[i]);
    }
}

int main(int argc, char *argv[])
{
    int n = 0;
    std::cin >> n;
    assert(n <= 110000 && n > 0);
    int *a = new int[n];
    for(int i = 0; i < n; i++)
        std::cin >> a[i];

    int m = 0;
    std::cin >> m;
    assert(m <= 1000 && m > 0);
    int *b = new int[m];
    for(int i = 0; i < m; i++)
        std::cin >> b[i];

    int *result = new int[m];
    twins(result, a, n, b, m);

    for (int i = 0; i < m; i++)
        std::cout << result[i] << " ";

    delete[] a;
    delete[] b;
    delete[] result;
}

