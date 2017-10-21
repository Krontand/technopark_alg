/*
 *     Дан фрагмент последовательности скобок, состоящей из символов (){}[].
 * Требуется определить, возможно ли продолжить фрагмент в обе стороны, 
 * получив корректную последовательность.
 */
#include <iostream>
#include <cstring>
#include <assert.h>

template <class T>
class Stack {
public:
    Stack(size_t size);
    ~Stack() { free(); }

    Stack(const Stack<T>& other) = delete;
    Stack(Stack<T>&& other) { *this = std::forward<Stack>(other); }

    Stack<T>& operator=(const Stack<T>& other) = delete;
    Stack<T>& operator=(Stack<T>&& other);

    bool is_empty() const { return !(head); }
    int count() { return head; }

    void push(const T& value);
    T pop();

    T top() { return buf[head]; }

private:

    size_t head;

    // Размер буфера
    size_t buf_size;
    T* buf;

    const float realloc_coefficient = 1.5;

    void reallocate();
    void free();
};

template <class T>
Stack<T>::Stack(size_t size)
{
    assert(size > 0);
    head = 0;
    buf_size = size;
    buf = new T[size];
    assert(buf);
}

template <class T>
Stack<T>& Stack<T>::operator=( Stack<T>&& other )
{
    free();
    this->buf = other.buf;
    this->head = other.head;
    other.buf = nullptr;
    other.buf_size = 0;

    return *this;
}

template <class T>
void Stack<T>::free()
{
    delete[] buf;
    head = 0;
    buf_size = 0;
}

template <class T>
void Stack<T>::reallocate()
{
    T* old_buf = buf;

    buf_size *= realloc_coefficient;
    buf = new T[buf_size];

    for (int i = 0; i <= head; i++)
        buf[i] = old_buf[i];

    delete[] old_buf;
}

template <class T>
void Stack<T>::push( const T& data )
{
    if (head == buf_size - 1)
        reallocate();
    head++;
    buf[head] = data;
}

template <class T>
T Stack<T>::pop()
{
    if (is_empty())
        return -1;
    head--;
    return buf[head+1];
}

// Возвращает true, если передана открывающая скобка
bool is_opening(const char bracket)
{
    switch(bracket)
    {
    case '(':
        return true;
        break;
    case '[':
        return true;
        break;
    case '{':
        return true;
        break;
    }
    return false;
}

// Возвращает открывающую скобку, соответствующую переданной закрывающей
char get_opening(const char bracket)
{
    switch(bracket)
    {
    case ')':
        return '(';
        break;
    case ']':
        return '[';
        break;
    case '}':
        return '{';
        break;
    }
    return 0;
}

// Возвращает открывающую скобку, соответствующую переданной закрывающей
char get_closing(const char bracket)
{
    switch(bracket)
    {
    case '(':
        return ')';
        break;
    case '[':
        return ']';
        break;
    case '{':
        return '}';
        break;
    }
    return 0;
}

bool check_brackets(const char* input, char *output)
{
    Stack<char> stack(10);
    Stack<char> brackets_add_left(10); // Скобки для добавления в начало выражения
    bool correct = true;
    // Проверка корректности
    for(int i = 0; input[i] != '\0' && correct; i++)
    {
        if (is_opening(input[i]))
            stack.push(input[i]);
        else
        {
            if(stack.is_empty())
                brackets_add_left.push(get_opening(input[i]));
            else
                if(stack.top() == get_opening(input[i]))
                    stack.pop();
                else
                    correct = false;
        }
    }
    // Дополнение выражения до корректного
    if (correct)
    {
        int i = brackets_add_left.count();
        for (int j = 0; !brackets_add_left.is_empty(); j++)
            output[j] = brackets_add_left.pop();
        output[i] = '\0';
        strcat(output, input);
        for(i = strlen(output); !stack.is_empty(); i++ )
        {
            output[i] = get_closing(stack.pop());
        }
    }
    return correct;
}

int main(int argc, char *argv[])
{
    const int max_length = 800000;

    char *input = new char[max_length];
    char *output = new char[2 * max_length];

    assert(input);
    assert(output);

    std::cin >> input;
    if (check_brackets(input, output))
        std::cout << output;
    else
        std::cout << "IMPOSSIBLE";

    delete[] input;
    delete[] output;

    return 0;
}

