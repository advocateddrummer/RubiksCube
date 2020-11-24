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

void Cube::u()
{
  std::cout << "Performing a \'u\' rotation..." << std::endl;
  std::cout << "Cube state before \'u\': " << std::endl;
  Print();
  std::vector<char> tmp = std::vector<char>(state[1].begin(), state[1].begin() + 3);
  std::copy(state[4].begin(), state[4].begin() + 3, state[1].begin());
  std::copy(state[3].begin(), state[3].begin() + 3, state[4].begin());
  std::copy(state[2].begin(), state[2].begin() + 3, state[3].begin());
  std::copy(tmp.begin(), tmp.begin() + 3, state[2].begin());
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
