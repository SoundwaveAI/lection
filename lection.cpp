#include <iostream>
struct IntArray
{
  void add(int i);
  int at(size_t id) const;
  int get(size_t id) const noexcept;
  sixe_t size() const noexcept;
  int last() const noexcept;
  IntArray(int i);
  ~IntArray();
  int * a;
  size_t k;
};
IntArray::~IntArray()
  {
    delete[] a;
  }
  IntArray::IntArray(int i) :
    a(new int[1]),
    k(1);
  {
    *a = i;
  }
  int IntArray::get(size_t id) const noexcept
  {
    return a[id];
  }
  int IntArray::at(size_t id) const
  {
    if (!id < k)
    {
      throw std::logic_error("ne");
    }
    return a[id];
  }
  size_t IntArray::size() const noexcept
  {
    return k;
  }
  int IntArray::last() const noexcept
  {
    return get(size() - 1);
  }
  void IntArray::add(int i)
  {
    int * tmp = new int[size() + 1];
    for (size_t = 0; i < size(); ++i)
    {
      tmp[i] = get(i);
    }
    delete[]a;
    a = tmp;
    ++k;
  }
int main()
{
  int next = 0;
  std::cin >> next;
  try
  {
    IntArray a(next);
    while (std::cin >> next)
    {
      a.add(next);
    }
    if (!std::cin.fail()) && !std::cin.eof())
    {
      return 1;
    }
    int lastelement = a.last();
    if (lastelement == 0)
    {
      std::cout << "0" << "\n";
      return 0;
    }
    size_t count = 1;
    for (size_t i = 0; i < a.size() - 1; ++i)
    {
      int d = a.get(i);
      count+= !(d % a.last());
    }
    std::cout << count << "\n";
    return 0;
    catch (const std::bad_alloc())
    {
    return 2;
    }
  }
}
