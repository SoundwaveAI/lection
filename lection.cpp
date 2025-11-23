#include <iostream>
#include <fstream>
#include <algorithm>
#include <new>

struct IntArray
{
  int* data;
  size_t size_v;
  IntArray(int size, int v = 0);
  IntArray(const IntArray& rhs);
  IntArray(IntArray&& rhs) noexcept;
  ~IntArray();
  IntArray& operator=(const IntArray& rhs);
  IntArray& operator=(IntArray&& rhs) noexcept;
  size_t size() const noexcept;
  int get(size_t id) const;
  void set(size_t id, int vi);
  void add(int vi);
};

IntArray::~IntArray()
{
  delete[] data;
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
  data(rhs.data),
  size_v(rhs.size_v)
{
  rhs.data = nullptr;
  rhs.size_v = 0;
}
IntArray& IntArray::operator=(IntArray&& rhs) noexcept
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

void IntArray::set(size_t id, int vi)
{
  if (id >= size_v)
  {
    throw std::out_of_range("Index out of range");
  }
  data[id] = vi;
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

class IntMatrix
{
  size_t rows;
  size_t cols;
  IntArray arr;
public:
  IntMatrix(size_t r, size_t c) : rows(r), cols(c), arr(r * c)
  {}
  void set(size_t r, size_t c, int vi)
  {
    arr.set(r * cols + c, vi);
  }
  int get(size_t r, size_t c) const
  {
    return arr.get(r * cols + c);
  }
  void print() const
  {
    for (size_t i = 0; i < rows; ++i)
    {
      for (size_t j = 0; j < cols; ++j)
      {
        std::cout << get(i, j) << (j == cols - 1 ? "" : " ");
      }
      std::cout << "\n";
    }
  }
  void addColumn(size_t after_col, int vi)
  {
    size_t index = (after_col == 0) ? 0 : after_col;
    if (index > cols)
    {
      throw std::logic_error("Wrong Column index");
    }
    size_t new_cols = cols + 1;
    IntArray new_arr(rows * new_cols);
    for (size_t i = 0; i < rows; ++i)
    {
      for (size_t j = 0; j < new_cols; ++j)
      {
        size_t new_index = i * new_cols + j;
        if (j < index)
        {
          new_arr.set(new_index, get(i, j));
        }
        else if (j == index)
        {
          new_arr.set(new_index, vi);
        }
        else
        {
          new_arr.set(new_index, get(i, j - 1));
        }
      }
    }
    arr = std::move(new_arr);
    cols = new_cols;
  }

  void addRowAndCol(size_t a_row, size_t a_col)
  {
    size_t t_r = (a_row == 0) ? 0 : a_row;
    size_t t_c = (a_col == 0) ? 0 : a_col;
    if (t_r > rows || t_c > cols)
    {
      throw std::logic_error("Wrong index");
    }
    size_t new_rows = rows + 1;
    size_t new_cols = cols + 1;
    IntArray new_arr(new_rows * new_cols, 0);
    for (size_t i = 0; i < new_rows; ++i)
    {
      if (i == t_r)
      {
        continue;
      }
      size_t old_i = (i < t_r) ? i : i - 1;
      for (size_t j = 0; j < new_cols; ++j)
      {
        if (j == t_c)
        {
          continue;
        }
        size_t old_j = (j < t_c) ? j : j - 1;
        new_arr.set(i * new_cols + j, get(old_i, old_j));
      }
    }
    arr = std::move(new_arr);
    rows = new_rows;
    cols = new_cols;
  }
};
int main(int argc, char* argv[])
{
  if (argc < 2)
  {
    return 1;
  }
  std::ifstream file(argv[1]);
  if (!file.is_open())
  {
    return 1;
  }
  size_t rows = 0;
  size_t cols = 0;
  if (!(file >> rows >> cols))
  {
    return 1;
  }
  try
  {
    IntMatrix matrix(rows, cols);
    for (size_t i = 0; i < rows; ++i)
    {
      for (size_t j = 0; j < cols; ++j)
      {
        int v;
        if (!(file >> v))
        {
          return 1;
          matrix.set(i, j, v);
        }
      }
    }
    int next = 0;
    while (std::cin >> next)
    {
      if (next == 2)
      {
        size_t col_index;
        int v;
        if (!(std::cin >> col_index >> v))
        {
          return 1;
        }
        matrix.addColumn(col_index, v);
        matrix.print();
      }
      else if (next == 3)
      {
        size_t row_index, col_index;
        if (!(std::cin >> row_index >> col_index))
        {
          return 1;
        }
        matrix.addRowAndCol(row_index, col_index);
        matrix.print();
      }
      else
      {
        return 3;
      }
    }
    if (std::cin.fail() && !std::cin.eof())
    {
      return 1;
    }
  }
  catch (const std::bad_alloc&)
  {
    return 2;
  }
  catch (const std::logic_error&)
  {
    return 3;
  }
  catch (...)
  {
    return 1;
  }
  return 0;
}
