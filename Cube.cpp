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

void Cube::RotateFace(const int faceID, const int direction)
{
  /* This array contains the indices into the state array that correspond to
   * the faces required for u/d rotations (indices[0]), f/b rotations
   * (indices[1]), and r/l rotations (indices[2]).
   */
  const std::vector<std::vector<int>> indices = { { 1, 2, 3, 4}, {0, 2, 5, 4}, {5, 1, 0, 3} };

  switch (faceID) {
    /* TODO: case 1 and 6 are essentially mirrors; agglomerate them. */
    /* This case handles all upper/top face rotations. */
    case 1 :
      {
        const std::vector<int> index = indices[0];
        if (direction == 1) {
          /* Make temporary copy of first edge. */
          std::vector<char> tmp = std::vector<char>(state[index.at(0)].begin(), state[index.at(0)].begin() + 3);
          /* Rotate upper face clockwise. */
          for ( auto i = index.begin() + 1; i != index.end(); i++ )
            std::copy(state[*i].begin(), state[*i].begin() + 3, state[*(i - 1)].begin());

          std::copy(tmp.begin(), tmp.begin() + 3, state[index.at(3)].begin());
        } else if (direction == -1) {
          /* Make temporary copy of first edge. */
          std::vector<char> tmp = std::vector<char>(state[index[3]].begin(), state[index[3]].begin() + 3);
          /* Rotate upper face counterclockwise. */
          for ( auto i = index.rbegin() + 1; i != index.rend(); i++ )
            std::copy(state[*i].begin(), state[*i].begin() + 3, state[*(i - 1)].begin());

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
      {
        const std::vector<int> index = indices[2];
        if (direction == 1) {
          /* Make temporary copy of first edge. */
          std::vector<char> tmp = std::vector<char>(state[index.at(0)].begin() + 2, state[index.at(0)].begin() + 5);
          /* Rotate right face clockwise. */
          for ( auto i = index.begin() + 1; i != index.end() - 1; i++ )
            std::copy(state[*i].begin() + 2, state[*i].begin() + 5, state[*(i - 1)].begin() + 2);

          std::copy(state[index.at(3)].begin(), state[index.at(3)].begin() + 1, state[index.at(2)].begin() + 4);
          std::copy(state[index.at(3)].begin() + 6, state[index.at(3)].begin() + 8, state[index.at(2)].begin() + 2);

          std::copy(tmp.begin(), tmp.begin() + 2, state[index.at(3)].begin() + 6);
          std::copy(tmp.begin() + 2, tmp.end(), state[index.at(3)].begin());
        } else if (direction == -1) {
          /* Make temporary copy of first edge. */
          std::vector<char> tmp = std::vector<char>(state[index.at(2)].begin() + 2, state[index.at(2)].begin() + 5);
          /* Rotate right face counterclockwise. */
          for ( auto i = index.rbegin() + 2; i != index.rend(); i++ )
            std::copy(state[*i].begin() + 2, state[*i].begin() + 5, state[*(i - 1)].begin() + 2);

          std::copy(state[index.at(3)].begin(), state[index.at(3)].begin() + 1, state[index.at(0)].begin() + 4);
          std::copy(state[index.at(3)].begin() + 6, state[index.at(3)].begin() + 8, state[index.at(0)].begin() + 2);

          std::copy(tmp.begin(), tmp.begin() + 2, state[index.at(3)].begin() + 6);
          std::copy(tmp.begin() + 2, tmp.end(), state[index.at(3)].begin());
        } else if (direction == 2) {
          /* Rotate right face twice; swap front, back edges, left, right
           * edges.
           */
          std::swap_ranges(state[index.at(0)].begin() + 2, state[index.at(0)].begin() + 5, state[index.at(2)].begin() + 2);
          std::swap_ranges(state[index.at(1)].begin() + 2, state[index.at(1)].begin() + 4, state[index.at(3)].begin() + 6);
          std::swap_ranges(state[index.at(1)].begin() + 4, state[index.at(1)].begin() + 5, state[index.at(3)].begin());
        } else {
          std::cout << "Error: incorrect direction specified in RotateFace!" << std::endl;
        }
        break;
      }
    /* This case handles all back face rotations. */
    case 4 :
      break;

    /* This case handles all left face rotations. */
    case 5 :
      {
        const std::vector<int> index = indices[2];
        if (direction == 1) {
          /* Make temporary copy of first edge. */
          std::vector<char> tmp = std::vector<char>(state[index.at(2)].begin(), state[index.at(2)].begin() + 1);
          tmp.push_back(state[index.at(2)].at(6));
          tmp.push_back(state[index.at(2)].at(7));

          /* Rotate left face clockwise. */
          for ( auto i = index.rbegin() + 2; i != index.rend(); i++ ) {
            std::copy(state[*i].begin(), state[*i].begin() + 1, state[*(i - 1)].begin());
            std::copy(state[*i].begin() + 6, state[*i].begin() + 8, state[*(i - 1)].begin() + 6);
          }

          std::copy(state[index.at(3)].begin() + 2, state[index.at(3)].begin() + 4, state[index.at(0)].begin() + 6);
          std::copy(state[index.at(3)].begin() + 4, state[index.at(3)].begin() + 5, state[index.at(0)].begin());

          std::copy(tmp.begin(), tmp.begin() + 3, state[index.at(3)].begin() + 2);
        } else if (direction == -1) {
          /* Make temporary copy of first edge. */
          std::vector<char> tmp = std::vector<char>(state[index.at(0)].begin(), state[index.at(0)].begin() + 1);
          tmp.push_back(state[index.at(0)].at(6));
          tmp.push_back(state[index.at(0)].at(7));

          /* Rotate left face counterclockwise. */
          for ( auto i = index.begin() + 1; i != index.end() - 1; i++ ) {
            std::copy(state[*i].begin(), state[*i].begin() + 1, state[*(i - 1)].begin());
            std::copy(state[*i].begin() + 6, state[*i].begin() + 8, state[*(i - 1)].begin() + 6);
          }

          std::copy(state[index.at(3)].begin() + 2, state[index.at(3)].begin() + 4, state[index.at(2)].begin() + 6);
          std::copy(state[index.at(3)].begin() + 4, state[index.at(3)].begin() + 5, state[index.at(2)].begin());

          std::copy(tmp.begin(), tmp.begin() + 1, state[index.at(3)].begin() + 4);
          std::copy(tmp.begin() + 1, tmp.end(), state[index.at(3)].begin() + 2);
        } else if (direction == 2) {
          /* Rotate left face twice; swap front, back edges, left, right edges. */
          std::swap_ranges(state[index.at(0)].begin(), state[index.at(0)].begin() + 1, state[index.at(2)].begin());
          std::swap_ranges(state[index.at(0)].begin() + 6, state[index.at(0)].begin() + 8, state[index.at(2)].begin() + 6);
          std::swap_ranges(state[index.at(1)].begin(), state[index.at(1)].begin() + 1, state[index.at(3)].begin() + 4);
          std::swap_ranges(state[index.at(1)].begin() + 6, state[index.at(1)].begin() + 8, state[index.at(3)].begin() + 2);
        } else {
          std::cout << "Error: incorrect direction specified in RotateFace!" << std::endl;
        }
        break;
      }
      break;

    /* This case handles all lower/down/bottom face rotations. */
    case 6 :
      {
        const std::vector<int> index = indices[0];
        if (direction == 1) {
          /* Make temporary copy of first edge. */
          std::vector<char> tmp = std::vector<char>(state[index[3]].begin() + 4, state[index[3]].begin() + 7);
          /* Rotate bottom/down face clockwise. */
          for ( auto i = index.rbegin() + 1; i != index.rend(); i++ )
            std::copy(state[*i].begin() + 4, state[*i].begin() + 7, state[*i + 1].begin() + 4);

          std::copy(tmp.begin(), tmp.begin() + 3, state[index.at(0)].begin() + 4);
        } else if (direction == -1) {
          /* Make temporary copy of first edge. */
          std::vector<char> tmp = std::vector<char>(state[index.at(0)].begin() + 4, state[index.at(0)].begin() + 7);
          /* Rotate bottom/down face counterclockwise. */
          for ( auto i = index.begin() + 1; i != index.end(); i++ )
            std::copy(state[*i].begin() + 4, state[*i].begin() + 7, state[*i - 1].begin() + 4);

          std::copy(tmp.begin(), tmp.begin() + 3, state[index.at(3)].begin() + 4);
        } else if (direction == 2) {
          /* Rotate bottom/down face twice; swap front, back edges, left, right
           * edges.
           */
          std::swap_ranges(state[index.at(0)].begin() + 4, state[index.at(0)].begin() + 7, state[index.at(2)].begin() + 4);
          std::swap_ranges(state[index.at(1)].begin() + 4, state[index.at(1)].begin() + 7, state[index.at(3)].begin() + 4);
        } else {
          std::cout << "Error: incorrect direction specified in RotateFace!" << std::endl;
        }
        break;
      }
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
  RotateFace(1, 1);
  std::cout << "\'u\' rotation complete" << std::endl;
  std::cout << "Cube state after \'u\': " << std::endl;
  Print();
}

void Cube::up()
{
  std::cout << "Performing a \'up\' rotation..." << std::endl;
  std::cout << "Cube state before \'up\': " << std::endl;
  Print();
  RotateFace(1, -1);
  std::cout << "\'up\' rotation complete" << std::endl;
  std::cout << "Cube state after \'up\': " << std::endl;
  Print();
}

void Cube::uu()
{
  std::cout << "Performing a \'uu\' rotation..." << std::endl;
  std::cout << "Cube state before \'uu\': " << std::endl;
  Print();
  RotateFace(1, 2);
  std::cout << "\'uu\' rotation complete" << std::endl;
  std::cout << "Cube state after \'uu\': " << std::endl;
  Print();
}

void Cube::d()
{
  std::cout << "Performing a \'d\' rotation..." << std::endl;
  std::cout << "Cube state before \'d\': " << std::endl;
  Print();
  RotateFace(6, 1);
  std::cout << "\'d\' rotation complete" << std::endl;
  std::cout << "Cube state after \'d\': " << std::endl;
  Print();
}

void Cube::dp()
{
  std::cout << "Performing a \'dp\' rotation..." << std::endl;
  std::cout << "Cube state before \'dp\': " << std::endl;
  Print();
  RotateFace(6, -1);
  std::cout << "\'dp\' rotation complete" << std::endl;
  std::cout << "Cube state after \'dp\': " << std::endl;
  Print();
}

void Cube::dd()
{
  std::cout << "Performing a \'dd\' rotation..." << std::endl;
  std::cout << "Cube state before \'dd\': " << std::endl;
  Print();
  RotateFace(6, 2);
  std::cout << "\'dd\' rotation complete" << std::endl;
  std::cout << "Cube state after \'dd\': " << std::endl;
  Print();
}

void Cube::r()
{
  std::cout << "Performing a \'r\' rotation..." << std::endl;
  std::cout << "Cube state before \'r\': " << std::endl;
  Print();
  RotateFace(3, 1);
  std::cout << "\'r\' rotation complete" << std::endl;
  std::cout << "Cube state after \'r\': " << std::endl;
  Print();
}

void Cube::rp()
{
  std::cout << "Performing a \'rp\' rotation..." << std::endl;
  std::cout << "Cube state before \'rp\': " << std::endl;
  Print();
  RotateFace(3, -1);
  std::cout << "\'rp\' rotation complete" << std::endl;
  std::cout << "Cube state after \'rp\': " << std::endl;
  Print();
}

void Cube::rr()
{
  std::cout << "Performing a \'rr\' rotation..." << std::endl;
  std::cout << "Cube state before \'rr\': " << std::endl;
  Print();
  RotateFace(3, 2);
  std::cout << "\'rr\' rotation complete" << std::endl;
  std::cout << "Cube state after \'rr\': " << std::endl;
  Print();
}

void Cube::l()
{
  std::cout << "Performing a \'l\' rotation..." << std::endl;
  std::cout << "Cube state before \'l\': " << std::endl;
  Print();
  RotateFace(5, 1);
  std::cout << "\'l\' rotation complete" << std::endl;
  std::cout << "Cube state after \'l\': " << std::endl;
  Print();
}

void Cube::lp()
{
  std::cout << "Performing a \'lp\' rotation..." << std::endl;
  std::cout << "Cube state before \'lp\': " << std::endl;
  Print();
  RotateFace(5, -1);
  std::cout << "\'lp\' rotation complete" << std::endl;
  std::cout << "Cube state after \'lp\': " << std::endl;
  Print();
}

void Cube::ll()
{
  std::cout << "Performing a \'ll\' rotation..." << std::endl;
  std::cout << "Cube state before \'ll\': " << std::endl;
  Print();
  RotateFace(5, 2);
  std::cout << "\'ll\' rotation complete" << std::endl;
  std::cout << "Cube state after \'ll\': " << std::endl;
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
