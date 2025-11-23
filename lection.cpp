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
IntArray::IntArray(int i) :
  a(new int[1]),
  k(1)
  {
    *a = i;
}
IntArray::IntArray(const IntArray& rhs) :
  data(new int[rhs.get_size()),
  size(rhs.get_size())
  {
    for (size_t i = 0; i < get_size(); ++i)
    {
      data[i] = rhs.get_size(i);
    }
}
IntArray& IntArray::operator=(const IntArray& rhs)
{
  int* tmp = new int[rhs.get_size()];
  for (size_t i = 0; i < rhs.get_size(); ++i)
  {
    tmp[i] = rhs.get(i);
  }
  delete[] data;
  data = tmp;
  size = rhs.get_size();
  return *this;
}
IntArray::IntArray(IntArray && rhs) :
  data(rhs.data);
  size(rhs.get_size())
  {
    rhs.data = nullptr;
}
IntArray& IntArray::operator=(const IntArray && rhs)
{
  delete[] data;
  data = rhs.data;
  size = rhs.size;
  rhs.data = nullptr;
  return *this;
}
int IntArray::get_size(size_t id) const noexcept
{
  if (id >= k)
  {
    return 0;
  }
  return a[id];
}
int IntArray::at(size_t id) const
{
  if (id >= k)
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
  return get(k - 1);
}
void IntArray::add(int i)
{
  int * tmp = new int[k + 1];
  for (size_t j = 0; j < k; ++j)
  {
    tmp[j] = a[j];
  }
  tmp[k] = i;
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
