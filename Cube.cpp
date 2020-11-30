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

int Cube::IsSolved()
{
  /* Loop over all faces, grab the first element on each face and compare the
   * remaining elements against it, if they all match, for all faces, the cube
   * is solved.
   */
  for ( const auto & v : state ) {
    const char first = v.front();

    for ( auto c = v.begin() + 1; c != v.end(); c++ ) {
      /* A subsequent element on the current face does not match the first
       * element, the cube is _not_ solved.
       */
      if (first != *c)
        return 0;
    }
  }
  /* All faces have matching colors, the cube is solved. */
  return 1;
}

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

void Cube::up()
{
  std::cout << "Performing a \'up\' rotation..." << std::endl;
  std::cout << "Cube state before \'up\': " << std::endl;
  Print();
  /* Make temporary copy of upper front edge. */
  std::vector<char> tmp = std::vector<char>(state[1].begin(), state[1].begin() + 3);
  /* Move upper left edge to upper front. */
  std::copy(state[4].begin(), state[4].begin() + 3, state[1].begin());
  /* Move upper back edge to upper left. */
  std::copy(state[3].begin(), state[3].begin() + 3, state[4].begin());
  /* Move upper right edge to upper back. */
  std::copy(state[2].begin(), state[2].begin() + 3, state[3].begin());
  /* Move upper front edge to upper right. */
  std::copy(tmp.begin(), tmp.begin() + 3, state[2].begin());
  std::cout << "\'up\' rotation complete" << std::endl;
  std::cout << "Cube state after \'up\': " << std::endl;
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
