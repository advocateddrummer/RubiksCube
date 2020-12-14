#include <iostream>
#include "Cube.hpp"

void Cube::RotateCube(const int axis, const int direction)
{

  switch (axis) {
    /* Rotate cube around x-axis. */
    case 1 :
      {
        /* Rotate cube clockwise around x-axis. */
        if (direction == 1)
        {
          /* Make temporary copy of top face. */
          std::vector<char> tmp = std::vector<char>(state[5].begin(), state[5].end());

          /* Rotate front face to top face. */
          std::copy(state[1].begin(), state[1].end(), state[5].begin());

          /* Rotate bottom face to front face. */
          std::copy(state[0].begin(), state[0].end(), state[1].begin());

          /* Rotate back face to bottom face. */
          std::copy(state[3].begin()    , state[3].begin() + 4, state[0].begin() + 4);
          std::copy(state[3].begin() + 4, state[3].end() - 1  , state[0].begin());
          std::copy(state[3].end() - 1  , state[3].end()      , state[0].end() - 1);

          /* Rotate top face to back face. */
          std::copy(tmp.begin()    , tmp.begin() + 4, state[3].begin() + 4);
          std::copy(tmp.begin() + 4, tmp.end() - 1  , state[3].begin());
          std::copy(tmp.end() - 1  , tmp.end()      , state[3].end() - 1);

          /* Permute right face. */
          PermuteFace(2, 1);

          /* Permute left face. */
          PermuteFace(4, -1);
        }
        /* Rotate cube counterclockwise around x-axis. */
        else if (direction == -1)
        {
          /* Make temporary copy of top face. */
          std::vector<char> tmp = std::vector<char>(state[5].begin(), state[5].end());

          /* Rotate back face to top face. */
          std::copy(state[3].begin()    , state[3].begin() + 4, state[5].begin() + 4);
          std::copy(state[3].begin() + 4, state[3].end() - 1  , state[5].begin());
          std::copy(state[3].end() - 1  , state[3].end()      , state[5].end() - 1);

          /* Rotate bottom face to back face. */
          std::copy(state[0].begin()    , state[0].begin() + 4, state[3].begin() + 4);
          std::copy(state[0].begin() + 4, state[0].end() - 1  , state[3].begin());
          std::copy(state[0].end() - 1  , state[0].end()      , state[3].end() - 1);

          /* Rotate front face to bottom face. */
          std::copy(state[1].begin(), state[1].end(), state[0].begin());

          /* Rotate top face to front face. */
          std::copy(tmp.begin(), tmp.end(), state[1].begin());

          /* Permute right face. */
          PermuteFace(2, -1);

          /* Permute left face. */
          PermuteFace(4, 1);
        }
        /* Rotate cube twice around x-axis. */
        else if (direction == 2)
        {
          /* TODO: actually implement this logic instead of doing two single
           * rotations.
           */
          /* Rotate top face to bottom face. */
          /* Rotate front face to back face. */
          /* Rotate bottom face to top face. */
          /* Rotate back face to front face. */
          /* Permute right face. */
          /* Permute left face. */
        }
        else
          std::cout << "Error: incorrect direction specified in RotateCube!" << std::endl;
        break;
      }

    /* Rotate cube around y-axis. */
    case 2 :
      {
        /* Rotate cube clockwise around y-axis. */
        if (direction == 1)
        {
          /* Make temporary copy of front face. */
          std::vector<char> tmp = std::vector<char>(state[1].begin(), state[1].end());

          /* Rotate right face to front face, back to right, and left to back. */
          for ( auto i : {2, 3, 4} )
            std::copy(state[i].begin(), state[i].end(), state[i - 1].begin());

          /* Rotate front face to left face. */
          std::copy(tmp.begin(), tmp.end(), state[4].begin());

          /* Permute bottom/down face. */
          PermuteFace(0, -1);

          /* Permute top/up face. */
          PermuteFace(5, 1);
        }
        /* Rotate cube counterclockwise around y-axis. */
        else if (direction == -1)
        {
          /* Make temporary copy of left face. */
          std::vector<char> tmp = std::vector<char>(state[4].begin(), state[4].end());

          /* Rotate back face to left face, right to back, and front to right. */
          for ( auto i : {3, 2, 1} )
            std::copy(state[i].begin(), state[i].end(), state[i + 1].begin());

          /* Rotate left face to front face. */
          std::copy(tmp.begin(), tmp.end(), state[1].begin());

          /* Permute bottom/down face. */
          PermuteFace(0, 1);

          /* Permute top/up face. */
          PermuteFace(5, -1);
        }
        else if (direction == 2)
        {
          /* TODO: actually implement this logic instead of doing two single
           * rotations.
           */
        }
        else
          std::cout << "Error: incorrect direction specified in RotateCube!" << std::endl;
        break;
      }

    /* Rotate cube around z-axis. */
    case 3 :
      {
        /* Rotate cube clockwise around z-axis. */
        if (direction == 1)
        {
          /* Make temporary copy of right face. */
          std::vector<char> tmp = std::vector<char>(state[2].begin(), state[2].end());

          /* Rotate top/up face to right face. */
          std::copy(state[5].begin()    , state[5].begin() + 6, state[2].begin() + 2);
          std::copy(state[5].begin() + 6, state[5].end() - 1  , state[2].begin());
          std::copy(state[5].end() - 1  , state[5].end()      , state[2].end() - 1);

          /* Rotate left face to top/up face. */
          std::copy(state[4].begin()    , state[4].begin() + 6, state[5].begin() + 2);
          std::copy(state[4].begin() + 6, state[4].end() - 1  , state[5].begin());
          std::copy(state[4].end() - 1  , state[4].end()      , state[5].end() - 1);

          /* Rotate bottom/down face to left face. */
          std::copy(state[0].begin()    , state[0].begin() + 6, state[4].begin() + 2);
          std::copy(state[0].begin() + 6, state[0].end() - 1  , state[4].begin());
          std::copy(state[0].end() - 1  , state[0].end()      , state[4].end() - 1);

          /* Rotate right face to bottom/down face. */
          std::copy(tmp.begin()    , tmp.begin() + 6, state[0].begin() + 2);
          std::copy(tmp.begin() + 6, tmp.end() - 1  , state[0].begin());
          std::copy(tmp.end() - 1  , tmp.end()      , state[0].end() - 1);

          /* Permute front face. */
          PermuteFace(1, 1);

          /* Permute back face. */
          PermuteFace(3, -1);
        }
        /* Rotate cube counterclockwise around z-axis. */
        else if (direction == -1)
        {
          /* Make temporary copy of left face. */
          std::vector<char> tmp = std::vector<char>(state[4].begin(), state[4].end());

          /* Rotate top/up face to left face. */
          std::copy(state[5].begin()    , state[5].begin() + 2, state[4].begin() + 6);
          std::copy(state[5].begin() + 2, state[5].end() - 1  , state[4].begin());
          std::copy(state[5].end() - 1  , state[5].end()      , state[4].end() - 1);

          /* Rotate right face to top/up face. */
          std::copy(state[2].begin()    , state[2].begin() + 2, state[5].begin() + 6);
          std::copy(state[2].begin() + 2, state[2].end() - 1  , state[5].begin());
          std::copy(state[2].end() - 1  , state[2].end()      , state[5].end() - 1);

          /* Rotate bottom/down face to right face. */
          std::copy(state[0].begin()    , state[0].begin() + 2, state[2].begin() + 6);
          std::copy(state[0].begin() + 2, state[0].end() - 1  , state[2].begin());
          std::copy(state[0].end() - 1  , state[0].end()      , state[2].end() - 1);

          /* Rotate left face to bottom/down face. */
          std::copy(tmp.begin()    , tmp.begin() + 2, state[0].begin() + 6);
          std::copy(tmp.begin() + 2, tmp.end() - 1  , state[0].begin());
          std::copy(tmp.end() - 1  , tmp.end()      , state[0].end() - 1);

          /* Permute front face. */
          PermuteFace(1, -1);

          /* Permute back face. */
          PermuteFace(3, 1);

        }
        else if (direction == 2)
        {
          /* TODO: actually implement this logic instead of doing two single
           * rotations.
           */
        }
        else
          std::cout << "Error: incorrect direction specified in RotateCube!" << std::endl;
        break;
      }
    default:
      std::cout << "Error: incorrect axis passed to RotateCube..." << std::endl;
  }
}

