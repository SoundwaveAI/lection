#include <iostream>
struct IntArray
{
  int* data;
  size_t size_v;
  IntArray(int size, int v = 0);
  IntArray(const IntArray& rhs);
  IntArray(IntArray&& rhs) noexcept;
  ~IntArray();
  IntArray& operator = (const IntArray& rhs);
  IntArray& operator = (IntArray&& rhs) noexcept;
  size_t size() const noexcept;
  int get(size id) const;
  void set(size_t id, int vi);
  void add(int vi);
};

IntArray::~IntArray()
{
  delete[] a;
}
IntArray::IntArray(int size, int v) :
  data(new int[size]),
  size_v(size)
{
  for (size_t i = 0; i < size_v; ++i)
  {
    data[i] = v;
  }
}
IntArray::IntArray(const IntArray& rhs) :
  data(new int[rhs.size_v]),
  size_v(rhs.size_v)
{
  for (size_t i = 0; i < size_v; ++i)
  {
    data[i] = rhs.data[i];
  }
}
IntArray& IntArray::operator=(const IntArray& rhs)
{
  if (this != &rhs)
  {
    int* tmp = new int[rhs.size_v];
    for (size_t i = 0; i < rhs.size_v; ++i)
    {
      tmp[i] = rhs.data[i];
    }
    delete[] data;
    data = tmp;
    size_v = rhs.size_v;
  }
  return *this;
}
IntArray::IntArray(IntArray&& rhs) noexcept:
  data(rhs.data);
  size_v(rhs.size_v)
{
  rhs.data = nullptr;
  rhs.size_v = 0;
}
IntArray& IntArray::operator=(const IntArray&& rhs) noexcept
{
  if (this != &rhs)
  {
    delete[] data;
    data = rhs.data;
    size_v = rhs.size_v;
    rhs.data = nullptr;
    rhs.size_v = 0;
  }
  return *this;
}

int IntArray::get(size_t id) const
{
  if (id >= size_v)
  {
    throw std::out_of_range("Index out of range");
  }
  return data[id];
}

int IntArray::set(size_t id, int v) const
{
  if (id >= size_v)
  {
    throw std::out_of_range("Index out of range");
  }
  data[id] = v;
}

size_t IntArray::size() const noexcept
{
  return size_v;
}

void IntArray::add(int v)
{
  int * tmp = new int[size_v + 1];
  for (size_t i = 0; i < size_v; ++i)
  {
    tmp[i] = data[i];
  }
  tmp[size_v] = v;
  delete[] data;
  data = tmp;
  ++size_v;
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
    if (std::cin.fail() && !std::cin.eof())
    {
      return 1;
    }
    int lastelement = a.last();
    if (lastelement == 0)
    {
      std::cout << "0" << "\n";
      return 0;
    }
    size_t count = 0;
    for (size_t i = 0; i < a.size() - 1; ++i)
    {
      int d = a.get(i);
      if (d % lastelement == 0)
      {
        count++;
      }
    }
    std::cout << count << "\n";
    return 0;
  } catch (const std::bad_alloc()) {
    return 2;
  } catch (...) {
    return 1;
  }
}
