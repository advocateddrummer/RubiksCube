#include <iostream>
#include <algorithm>
#include "Cube.hpp"

Cube::Cube()
{
  std::cout << "Constructing Cube..." << std::endl;
  state = { { 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o'},
            { 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b'},
            { 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w'},
            { 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g'},
            { 'y', 'y', 'y', 'y', 'y', 'y', 'y', 'y', 'y'},
            { 'r', 'r', 'r', 'r', 'r', 'r', 'r', 'r', 'r'}};
}

/** \brief Perform a clockwise rotation of the up (u) face.
 *
 * This method rotates the upper face clockwise.
 */
void Cube::u()
{
  std::cout << "Performing a \'u\' rotation..." << std::endl;
  std::cout << "Cube state before \'u\': " << std::endl;
  Print();
  /* Make temporary copy of upper front edge. */
  std::vector<char> tmp = std::vector<char>(state[1].begin(), state[1].begin() + 3);
  /* Move upper right edge to upper front. */
  std::copy(state[2].begin(), state[2].begin() + 3, state[1].begin());
  /* Move upper back edge to upper right. */
  std::copy(state[3].begin(), state[3].begin() + 3, state[2].begin());
  /* Move upper left edge to upper back. */
  std::copy(state[4].begin(), state[4].begin() + 3, state[3].begin());
  /* Move upper front edge to upper left. */
  std::copy(tmp.begin(), tmp.begin() + 3, state[4].begin());
  std::cout << "\'u\' rotation complete" << std::endl;
  std::cout << "Cube state after \'u\': " << std::endl;
  Print();
}

void Cube::Print()
{
  std::cout << "in Cube::Print()..." << std::endl;

  for ( const auto &v : state ) {
    for ( const auto &c : v ) {
      std::cout << " " << c << " ";
    }
    std::cout << std::endl;
  }
  std::cout << "Cube::Print() Done..." << std::endl;
}

Cube::~Cube()
{
  std::cout << "Destructing Cube..." << std::endl;
}
