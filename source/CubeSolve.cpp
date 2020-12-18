#include <iostream>
#include <map>
#include "Utils.hpp"
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

  //std::cout << "facelets.size(): \"" << facelets.size() << "\"\n";
  //std::cout << "facelets: \"" << facelets << "\"\n";

  return facelets;
}

const std::string Cube::TranslateKociembaTwists(const std::string kociembaSolution)
{
  /* Map from kociemba solution to internal twists. */
  const std::map<std::string, std::string> solutionTraslationMap { {"D", "d"}, {"D'", "dp"}, {"D2", "dd"},
                                                                   {"F", "f"}, {"F'", "fp"}, {"F2", "ff"},
                                                                   {"R", "r"}, {"R'", "rp"}, {"R2", "rr"},
                                                                   {"B", "b"}, {"B'", "bp"}, {"B2", "bb"},
                                                                   {"L", "l"}, {"L'", "lp"}, {"L2", "ll"},
                                                                   {"U", "u"}, {"U'", "up"}, {"U2", "uu"} };
  std::string ourSolution{""};

  std::vector<std::string> words = StringSplit(kociembaSolution, ' ');

  /* Initialize our solution from the kociemba solution. */
  for (const auto &w : words) {
    ourSolution += solutionTraslationMap.at(w);
    ourSolution += " ";
  }

  //std::cout << "ourSolution.size(): \"" << ourSolution.size() << "\" kociembaSolution.size(): \"" << kociembaSolution.size() << "\"\n";
  //std::cout << "ourSolution: \"" << ourSolution << "\" kociembaSolution: \"" <<  kociembaSolution << "\"\n";

  return ourSolution;
}

const std::string Cube::Solve()
{
  const std::string facelets = this->StateToKociemba();

  //std::cout << "in Cube::Solve(); facelets = " << facelets.c_str() << "\n";

  /* Call kociemba solution function. */
  char * sol = solution(const_cast<char*>(facelets.c_str()), 24, 1000, 0, "cache");
  if ( sol != NULL )
    std::cout << "Found solution: " << sol << "\n";
  else
    std::cout << "Did not Find solution; return value: " << sol << "\n";

  const std::string ourSolution = TranslateKociembaTwists(std::string(sol));

  return ourSolution;
};
