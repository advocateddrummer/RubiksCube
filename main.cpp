#include <iostream>
#include "CubeParams.hpp"
#include "Cube.hpp"
#include "Version.hpp"

int main(int argc, char * argv[])
{
  /* Parse command line arguments. */
  CubeParams * cp = new CubeParams(argc, argv);

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
