#include <iostream>
#include "CubeParams.hpp"
#include "Cube.hpp"
#include "Version.hpp"

int main(int argc, char * argv[])
{
  /* Parse command line arguments. */
  CubeParams * cp = new CubeParams(argc, argv);

  Cube c;

  c.RandomScramble();
  c.Print();
  const std::string solution = c.Solve();
  c.ApplyTwists(solution);
  c.Print();

  if (!c.IsSolved()) {
    puts("NOT SOLVED...");
    return EXIT_FAILURE;
  } else {
    puts("SOLVED!!!");
    return 0;
  }
}
