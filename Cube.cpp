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

/* TODO: default direction to clockwise? */
void Cube::RotateFace(const int faceID, const int direction)
{
  /* This array contains the indices into the state array that correspond to
   * the faces required for u/d rotations (indices[0]), f/b rotations
   * (indices[1]), and r/l rotations (indices[2]).
   */
  const std::vector<std::vector<int>> indices = { { 1, 2, 3, 4}, {0, 2, 5, 4}, {0, 3, 5, 1} };

  switch (faceID) {
    /* This case handles all upper/top face rotations. */
    case 1 :
      {
        const std::vector<int> index = indices[0];
        if (direction == 1) {
          /* Make temporary copy of first edge. */
          std::vector<char> tmp = std::vector<char>(state[index.at(0)].begin(), state[index.at(0)].begin() + 3);
          /* Rotate upper face clockwise. */
          for ( auto i = index.begin() + 1; i != index.end(); i++ )
            std::copy(state[*i].begin(), state[*i].begin() + 3, state[*i - 1].begin());

          std::copy(tmp.begin(), tmp.begin() + 3, state[index.at(3)].begin());
        } else if (direction == -1) {
          /* Make temporary copy of first edge. */
          std::vector<char> tmp = std::vector<char>(state[index[3]].begin(), state[index[3]].begin() + 3);
          /* Rotate upper face counterclockwise. */
          for ( auto i = index.rbegin() + 1; i != index.rend(); i++ )
            std::copy(state[*i].begin(), state[*i].begin() + 3, state[*i + 1].begin());

          std::copy(tmp.begin(), tmp.begin() + 3, state[index.at(0)].begin());
        } else if (direction == 2) {
          /* Rotate upper face twice; swap front, back edges, left, right
           * edges.
           */
          std::swap_ranges(state[index.at(0)].begin(), state[index.at(0)].begin() + 3, state[index.at(2)].begin());
          std::swap_ranges(state[index.at(1)].begin(), state[index.at(1)].begin() + 3, state[index.at(3)].begin());
        } else {
          std::cout << "Error: incorrect direction specified in RotateFace!" << std::endl;
        }
        break;
      }
    /* This case handles all front face rotations. */
    case 2 :
      break;
    /* This case handles all right face rotations. */
    case 3 :
      break;
    /* This case handles all back face rotations. */
    case 4 :
      break;
    /* This case handles all left face rotations. */
    case 5 :
      break;
    /* This case handles all lower/down/bottom face rotations. */
    case 6 :
      break;
    /* This case handles all upper/top face rotations that also include the
     * middle/adjacent layer.
     */
    case 7 :
      break;
    /* This case handles all front face rotations that also include the
     * middle/adjacent layer.
     */
    case 8 :
      break;
    /* This case handles all right face rotations that also include the
     * middle/adjacent layer.
     */
    case 9 :
      break;
    /* This case handles all back face rotations that also include the
     * middle/adjacent layer.
     */
    case 10 :
      break;
    /* This case handles all left face rotations that also include the
     * middle/adjacent layer.
     */
    case 11 :
      break;
    /* This case handles all lower/down/bottom face rotations that also include
     * the middle/adjacent layer.
     */
    case 12 :
      break;
    /* This case handles all middle layer rotations. Currently, this is only
     * the _vertical_ middle layer as I am not sure that the horizontal layer
     * will ever need to be rotated.
     */
    case 13 :
      break;
  }
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

void Cube::uu()
{
  std::cout << "Performing a \'uu\' rotation..." << std::endl;
  std::cout << "Cube state before \'uu\': " << std::endl;
  Print();
  /* Make temporary copy of upper front edge. */
  std::vector<char> tmp = std::vector<char>(state[1].begin(), state[1].begin() + 3);
  /* Move upper back edge to upper front. */
  std::copy(state[3].begin(), state[3].begin() + 3, state[1].begin());
  /* Move upper front edge to upper back. */
  std::copy(tmp.begin(), tmp.begin() + 3, state[3].begin());
  /* Make temporary copy of upper right edge. */
  tmp = std::vector<char>(state[2].begin(), state[2].begin() + 3);
  /* Move upper left edge to upper right. */
  std::copy(state[4].begin(), state[4].begin() + 3, state[2].begin());
  /* Move upper right edge to upper left. */
  std::copy(tmp.begin(), tmp.begin() + 3, state[4].begin());
  std::cout << "\'uu\' rotation complete" << std::endl;
  std::cout << "Cube state after \'uu\': " << std::endl;
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
