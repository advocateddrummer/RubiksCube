#include <iostream>
#include <map>
#include "Cube.hpp"

extern "C" char* solution(char* facelets, int maxDepth, long timeOut, int useSeparator, const char* cache_dir);

std::string Cube::StateToKociemba()
{
  /* Build orientation map based on current state. */
  const std::string map = "DFRBLU";
  std::map<char, char> stateToKociembaMap = {};
  for ( auto s: {0, 1, 2, 3, 4, 5} )
    stateToKociembaMap[state[s][8]] = map[s];

  std::string facelets{""};

  /* Initialize map from our Cube state to input required by kociemba. */
  for ( auto s : {5, 2, 1, 0, 4, 3} )
    for ( auto f : {0, 1, 2, 7, 8, 3, 6, 5, 4} )
      facelets += stateToKociembaMap.at(state[s][f]);

  return facelets;
}

const std::string Cube::Solve()
{
  const std::string facelets = this->StateToKociemba();

  /* Call kociemba solution function. */
  char * sol = solution(const_cast<char*>(facelets.c_str()), 24, 1000, 0, "cache");
  if ( sol != NULL )
    std::cout << "Found solution: " << sol << "\n";
  else
    std::cout << "Did not Find solution; return value: " << sol << "\n";

  return std::string(sol);
};
