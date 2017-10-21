/*
 *     В город N приехал цирк с командой атлетов. Они хотят удивить горожан
 * города N — выстроить из своих тел башню максимальной высоты. Башня — это 
 * цепочка атлетов, первый стоит на земле, второй стоит у него на плечах, 
 * третий стоит на плечах у второго и т.д.
 *     Каждый атлет характеризуется силой si (kg) и массой mi (kg). Сила — 
 * это максимальная масса, которую атлет способен держать у себя на плечах.
 *     К сожалению ни один из атлетов не умеет программировать, так как всю 
 * жизнь они занимались физической подготовкой, и у них не было времени на 
 * изучение языков программирования. Помогите им, напишите программу, которая 
 * определит максимальную высоту башни, которую они могут составить.
 *     Известно, что если атлет тяжелее, то он и сильнее:
 * если mi>mj, то si > sj.
 *     Атлеты равной массы могут иметь различную силу.
 */


#include <cassert>
#include <iostream>

struct Athlete
{
    int strength;
    int weight;
};

class AthletesArray {
public:
    AthletesArray(size_t size);
    ~AthletesArray() { delete this->buf; }

    void push_back(const Athlete& value);
    void sort(int start = 0, int end = 0);
    const Athlete& operator[](size_t i) const { return buf[i]; }
    int count() { return _count; }

private:
    size_t _count;
    size_t buf_size;
    Athlete* buf;

    const float realloc_coefficient = 1.5;

    void reallocate();
};


AthletesArray::AthletesArray(size_t size)
{
    assert(size > 0);
    buf_size = size;
    _count = 0;
    buf = new Athlete[size];
    assert(buf);
}


void AthletesArray::reallocate()
{
    Athlete* old_buf = buf;

     buf_size *= realloc_coefficient;
     buf = new Athlete[buf_size];

     for (size_t i = 0; i < _count; i++)
         buf[i] = old_buf[i];

     delete[] old_buf;
}


void AthletesArray::push_back(const Athlete& data)
{
    if (_count == buf_size)
        reallocate();
    buf[_count++] = data;
}


void AthletesArray::sort(int start, int end)
{
    if (end == 0)
        end = this->count() - 1;

    int i = start;
    int j = end;
    Athlete &center = buf[(i + j) / 2];

    do
    {
        while (buf[i].weight < center.weight ||
               buf[i].weight == center.weight && buf[i].strength < center.strength)
            i++;
        while (buf[j].weight > center.weight ||
               buf[j].weight == center.weight && buf[j].strength > center.strength)
            j--;

        if (i <= j)
        {
          std::swap(buf[i], buf[j]);
          i++;
          j--;
        }
    } while (i < j);

    if (j > start)
        this->sort(start, j);
    if (end > i)
        this->sort(i, end);
}

int get_height(AthletesArray &athletes)
{
    athletes.sort();
    int total_weight = athletes[0].weight;
    int height = 1;
    for (int i = 1; i < athletes.count(); i++)
    {
        if (athletes[i].strength >= total_weight)
        {
            total_weight += athletes[i].weight;
            height++;
        }
    }
    return height;
}

int main()
{
    AthletesArray athletes(10);
    Athlete athlete;
    while(scanf("%d %d", &athlete.weight, &athlete.strength) == 2)
        athletes.push_back(athlete);
    std::cout << get_height(athletes);

}
