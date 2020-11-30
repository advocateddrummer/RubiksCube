#include "Cube.hpp"

int main(int argc, char * argv[])
{
  Cube c;

  if (c.IsSolved())
    std::cout << "The cube is solved!!!" << std::endl;
  else
    std::cout << "The cube is NOT solved!!!" << std::endl;

  c.u();
  if (c.IsSolved())
    std::cout << "The cube is solved!!!" << std::endl;
  else
    std::cout << "The cube is NOT solved!!!" << std::endl;

  c.up();
  if (c.IsSolved())
    std::cout << "The cube is solved!!!" << std::endl;
  else
    std::cout << "The cube is NOT solved!!!" << std::endl;

  return 0;
}

