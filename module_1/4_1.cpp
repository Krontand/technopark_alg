/* 
 * Реализовать очередь с динамическим зацикленным буфером.
 */
#include <iostream>
#include <assert.h>

template <class T>
class Queue {
public:
    Queue(size_t size);
    ~Queue() { free(); }

    Queue(const Queue<T>& other) = delete;
    Queue(Queue<T>&& other) { *this = std::forward<Queue>(other); }

    Queue<T>& operator=(const Queue<T>& other) = delete;
    Queue<T>& operator=(Queue<T>&& other);

    bool is_empty() const {return !(count);}

    void push_back(const T& value);
    T pop_front();

private:

    size_t head;
    size_t tail;

    // Текущее количество элементов в очереди
    size_t count;
    // Размер буфера
    size_t buf_size;
    T* buf;

    const float realloc_coefficient = 1.5;

    void reallocate();
    void free();
};

template <class T>
Queue<T>::Queue(size_t size)
{
    assert(size > 0);
    head = 0;
    tail = 0;
    buf_size = size;
    count = 0;
    buf = new T[size];
    assert(buf);
}

template <class T>
Queue<T>& Queue<T>::operator=( Queue<T>&& other )
{
    free();
    this->buf = other.buf;
    this->head = other.head;
    this->tail = other.tail;
    other.buf = nullptr;
    other.buf_size = 0;

    return *this;
}

template <class T>
void Queue<T>::free()
{
    delete[] buf;
    head = 0;
    tail = 0;
    buf_size = 0;
}

template <class T>
void Queue<T>::reallocate()
{
    int old_buf_size = buf_size;
    T* old_buf = buf;

    buf_size *= realloc_coefficient;
    buf = new T[buf_size];

    for (int i = 0; i < count; i++)
    {
        buf[i] = old_buf[head++];
        if (head == old_buf_size)
            head = 0;
    }
    head = 0;
    tail = count;

    delete[] old_buf;
}

template <class T>
void Queue<T>::push_back( const T& data )
{
    if (count == buf_size)
        reallocate();
    buf[tail++] = data;
    if (tail == buf_size)
        tail = 0;
    count++;
}

template <class T>
T Queue<T>::pop_front()
{
    if (is_empty())
        return -1;
    int return_index = head;
    if(head == buf_size - 1)
        head = 0;
    else
        head++;
    count--;
    return buf[return_index];
}

int main(int argc, char *argv[])
{
    int n = 0;
    std::cin >> n;

    Queue<int> queue(4);
    int command = 0;
    int value = 0;
    int err = 0;
    for (int i = 0; i < n; i++)
    {
        std::cin >> command >> value;
        switch(command)
        {
        case 2:
            if (queue.pop_front() != value)
                err = 1;
            break;
        case 3:
            queue.push_back(value);
            break;
        default:
            assert(0);
        }
    }

    if (err)
        std::cout << "NO";
    else
        std::cout << "YES";

    return 0;
}

