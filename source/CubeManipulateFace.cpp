#include <iostream>
#include "Cube.hpp"

void Cube::SexyMove(const int count)
{
  for ( int c = 0; c < count; c++ ) {
    this->r();
    this->u();
    this->rp();
    this->up();
  }

  return;
}

void Cube::Sune(const int count)
{
  for ( int c = 0; c < count; c++ ) {
    this->r();
    this->u();
    this->rp();
    this->u();
    this->r();
    this->uu();
    this->rp();
  }

  return;
}

void Cube::AntiSune(const int count)
{
  for ( int c = 0; c < count; c++ ) {
    this->r();
    this->uu();
    this->rp();
    this->up();
    this->r();
    this->up();
    this->rp();
  }

  return;
}

void Cube::PermuteFace(const int faceID, const int direction)
{

  if ( faceID < 0 || faceID > 5 ) {
    std::cout << "Error: incorrect faceID passed to RotateFace..." << std::endl;
    return;
  }

  if ( direction == 1 )
  {
    /* Permute face clockwise. */
    /* Make temporary copy of first edge. */
    std::vector<char> tmp = std::vector<char>(state[faceID].begin() + 1, state[faceID].begin() + 3);
    std::copy(state[faceID].begin()    , state[faceID].begin() + 1, state[faceID].begin() + 2);
    std::copy(state[faceID].begin() + 6, state[faceID].end() - 1  , state[faceID].begin());
    std::copy(state[faceID].begin() + 4, state[faceID].begin() + 6, state[faceID].begin() + 6);
    std::copy(state[faceID].begin() + 3, state[faceID].begin() + 4, state[faceID].begin() + 5);
    std::copy(tmp.begin()              , tmp.end()                , state[faceID].begin() + 3);
  } else if ( direction == -1 )
  {
    /* Permute face counterclockwise. */
    /* Make temporary copy of first edge.*/
    std::vector<char> tmp = std::vector<char>(state[faceID].begin(), state[faceID].begin() + 2);
    std::copy(state[faceID].begin() + 2, state[faceID].begin() + 5, state[faceID].begin());
    std::copy(state[faceID].begin() + 5, state[faceID].begin() + 7, state[faceID].begin() + 3);
    std::copy(state[faceID].begin() + 7, state[faceID].end() - 1  , state[faceID].begin() + 5);
    std::copy(tmp.begin()              , tmp.end()                , state[faceID].begin() + 6);
  } else if ( direction == 2 )
  {
    /* Permute face twice. */
    std::swap_ranges(state[faceID].begin(), state[faceID].begin() + 4, state[faceID].begin() + 4);
  } else
    std::cout << "Error: incorrect direction passed to PermuteFace..." << std::endl;
}

void Cube::RotateFace(const int faceID, const int direction)
{
  switch (faceID) {
    /* TODO: case 1 and 6 are essentially mirrors; agglomerate them. */
    /* This case handles all upper/top face rotations. */
    case 1 :
      {
        if (direction == 1) {
          /* Make temporary copy of first edge. */
          std::vector<char> tmp = std::vector<char>(state[1].begin(), state[1].begin() + 3);

          /* Rotate upper face clockwise. */
          for ( auto i : {2, 3, 4} )
            std::copy(state[i].begin(), state[i].begin() + 3, state[i - 1].begin());

          std::copy(tmp.begin(), tmp.begin() + 3, state[4].begin());

          PermuteFace(5, 1);
        } else if (direction == -1) {
          /* Make temporary copy of first edge. */
          std::vector<char> tmp = std::vector<char>(state[4].begin(), state[4].begin() + 3);

          /* Rotate upper face counterclockwise. */
          for ( auto i : {3, 2, 1} )
            std::copy(state[i].begin(), state[i].begin() + 3, state[i + 1].begin());

          std::copy(tmp.begin(), tmp.begin() + 3, state[1].begin());

          PermuteFace(5, -1);
        } else if (direction == 2) {
          /* Rotate upper face twice; swap front, back edges, left, right
           * edges.
           */
          std::swap_ranges(state[1].begin(), state[1].begin() + 3, state[3].begin());
          std::swap_ranges(state[2].begin(), state[2].begin() + 3, state[4].begin());

          PermuteFace(5, 2);
        } else {
          std::cout << "Error: incorrect direction specified in RotateFace!" << std::endl;
        }
        break;
      }

    /* This case handles all front face rotations. */
    case 2 :
      {
        if (direction == 1) {
          /* Make temporary copy of first edge. */
          std::vector<char> tmp = std::vector<char>(state[0].begin(), state[0].begin() + 3);

          /* Rotate front face clockwise. */
          std::copy(state[2].begin()    , state[2].begin() + 1, state[0].begin() + 2);
          std::copy(state[2].begin() + 6, state[2].begin() + 8, state[0].begin());

          std::copy(state[5].begin() + 4, state[5].begin() + 6, state[2].begin() + 6);
          std::copy(state[5].begin() + 6, state[5].begin() + 7, state[2].begin());

          std::copy(state[4].begin() + 2, state[4].begin() + 5, state[5].begin() + 4);

          std::copy(tmp.begin(), tmp.begin() + 3, state[4].begin() + 2);

          PermuteFace(1, 1);
        } else if (direction == -1) {
          /* Make temporary copy of first edge. */
          std::vector<char> tmp = std::vector<char>(state[0].begin(), state[0].begin() + 3);

          /* Rotate front face counterclockwise. */
          std::copy(state[4].begin() + 2, state[4].begin() + 5, state[0].begin());

          std::copy(state[5].begin() + 4, state[5].begin() + 7, state[4].begin() + 2);

          std::copy(state[2].begin()    , state[2].begin() + 1, state[5].begin() + 6);
          std::copy(state[2].begin() + 6, state[2].begin() + 8, state[5].begin() + 4);

          std::copy(tmp.begin() + 2, tmp.begin() + 3, state[2].begin());
          std::copy(tmp.begin()    , tmp.begin() + 2, state[2].begin() + 6);

          PermuteFace(1, -1);
        } else if (direction == 2) {
          /* Rotate front face twice; swap front, back edges, left, right
           * edges.
           */
          std::swap_ranges(state[0].begin()    , state[0].begin() + 3, state[5].begin() + 4);
          std::swap_ranges(state[2].begin()    , state[2].begin() + 1, state[4].begin() + 4);
          std::swap_ranges(state[2].begin() + 6, state[2].begin() + 8, state[4].begin() + 2);

          PermuteFace(1, 2);
        } else {
          std::cout << "Error: incorrect direction specified in RotateFace!" << std::endl;
        }
        break;
      }

    /* This case handles all right face rotations. */
    case 3 :
      {
        if (direction == 1) {
          /* Make temporary copy of first edge. */
          std::vector<char> tmp = std::vector<char>(state[5].begin() + 2, state[5].begin() + 5);

          /* Rotate right face clockwise. */
          std::copy(state[1].begin() + 2, state[1].begin() + 5, state[5].begin() + 2);
          std::copy(state[0].begin() + 2, state[0].begin() + 5, state[1].begin() + 2);

          std::copy(state[3].begin()    , state[3].begin() + 1, state[0].begin() + 4);
          std::copy(state[3].begin() + 6, state[3].begin() + 8, state[0].begin() + 2);

          std::copy(tmp.begin()    , tmp.begin() + 2, state[3].begin() + 6);
          std::copy(tmp.begin() + 2, tmp.end()      , state[3].begin());
          PermuteFace(2, 1);
        } else if (direction == -1) {
          /* Make temporary copy of first edge. */
          std::vector<char> tmp = std::vector<char>(state[0].begin() + 2, state[0].begin() + 5);

          /* Rotate right face counterclockwise. */
          std::copy(state[1].begin() + 2, state[1].begin() + 5, state[0].begin() + 2);
          std::copy(state[5].begin() + 2, state[5].begin() + 5, state[1].begin() + 2);

          std::copy(state[3].begin()    , state[3].begin() + 1, state[5].begin() + 4);
          std::copy(state[3].begin() + 6, state[3].begin() + 8, state[5].begin() + 2);

          std::copy(tmp.begin()    , tmp.begin() + 2, state[3].begin() + 6);
          std::copy(tmp.begin() + 2, tmp.end()      , state[3].begin());

          PermuteFace(2, -1);
        } else if (direction == 2) {
          /* Rotate right face twice; swap front, back edges, left, right
           * edges.
           */
          std::swap_ranges(state[5].begin() + 2, state[5].begin() + 5, state[0].begin() + 2);
          std::swap_ranges(state[1].begin() + 2, state[1].begin() + 4, state[3].begin() + 6);
          std::swap_ranges(state[1].begin() + 4, state[1].begin() + 5, state[3].begin());

          PermuteFace(2, 2);
        } else {
          std::cout << "Error: incorrect direction specified in RotateFace!" << std::endl;
        }
        break;
      }

    /* This case handles all back face rotations. */
    case 4 :
      {
        if (direction == 1) {
          /* Make temporary copy of first edge. */
          std::vector<char> tmp = std::vector<char>(state[0].begin() + 4, state[0].begin() + 7);

          /* Rotate back face clockwise. */
          std::copy(state[4].begin()    , state[4].begin() + 1, state[0].begin() + 6);
          std::copy(state[4].begin() + 6, state[4].begin() + 8, state[0].begin() + 4);

          std::copy(state[5].begin()    , state[5].begin() + 2, state[4].begin() + 6);
          std::copy(state[5].begin() + 2, state[5].begin() + 3, state[4].begin());

          std::copy(state[2].begin() + 2, state[2].begin() + 5, state[5].begin());

          std::copy(tmp.begin(), tmp.begin() + 3, state[2].begin() + 2);

          PermuteFace(3, 1);
        } else if (direction == -1) {
          /* Make temporary copy of first edge. */
          std::vector<char> tmp = std::vector<char>(state[0].begin() + 4, state[0].begin() + 7);

          /* Rotate back face counterclockwise. */
          std::copy(state[2].begin() + 2, state[2].begin() + 5, state[0].begin() + 4);

          std::copy(state[5].begin(), state[5].begin() + 3, state[2].begin() + 2);

          std::copy(state[4].begin()    , state[4].begin() + 1, state[5].begin() + 2);
          std::copy(state[4].begin() + 6, state[4].begin() + 8, state[5].begin());

          std::copy(tmp.begin()    , tmp.begin() + 2, state[4].begin() + 6);
          std::copy(tmp.begin() + 2, tmp.begin() + 3, state[4].begin());

          PermuteFace(3, -1);
        } else if (direction == 2) {
          /* Rotate back face twice; swap front, back edges, left, right
           * edges.
           */
          std::swap_ranges(state[0].begin() + 4, state[0].begin() + 7, state[5].begin());
          std::swap_ranges(state[2].begin() + 2, state[2].begin() + 4, state[4].begin() + 6);
          std::swap_ranges(state[2].begin() + 4, state[2].begin() + 5, state[4].begin());

          PermuteFace(3, 2);
        } else {
          std::cout << "Error: incorrect direction specified in RotateFace!" << std::endl;
        }
        break;
      }

    /* This case handles all left face rotations. */
    case 5 :
      {
        if (direction == 1) {
          /* Make temporary copy of first edge. */
          std::vector<char> tmp = std::vector<char>(state[0].begin() + 6, state[0].begin() + 8);
          tmp.push_back(state[0].at(0));

          /* Rotate left face clockwise. */
          std::copy(state[1].begin()    , state[1].begin() + 1, state[0].begin());
          std::copy(state[1].begin() + 6, state[1].begin() + 8, state[0].begin() + 6);

          std::copy(state[5].begin()    , state[5].begin() + 1, state[1].begin());
          std::copy(state[5].begin() + 6, state[5].begin() + 8, state[1].begin() + 6);

          std::copy(state[3].begin() + 2, state[3].begin() + 4, state[5].begin() + 6);
          std::copy(state[3].begin() + 4, state[3].begin() + 5, state[5].begin());

          std::copy(tmp.begin(), tmp.begin() + 3, state[3].begin() + 2);

          PermuteFace(4, 1);
        } else if (direction == -1) {
          /* Make temporary copy of first edge. */
          std::vector<char> tmp = std::vector<char>(state[5].begin(), state[5].begin() + 1);
          tmp.push_back(state[5].at(6));
          tmp.push_back(state[5].at(7));

          /* Rotate left face counterclockwise. */
          std::copy(state[1].begin()    , state[1].begin() + 1, state[5].begin());
          std::copy(state[1].begin() + 6, state[1].begin() + 8, state[5].begin() + 6);

          std::copy(state[0].begin()    , state[0].begin() + 1, state[1].begin());
          std::copy(state[0].begin() + 6, state[0].begin() + 8, state[1].begin() + 6);

          std::copy(state[3].begin() + 2, state[3].begin() + 4, state[0].begin() + 6);
          std::copy(state[3].begin() + 4, state[3].begin() + 5, state[0].begin());

          std::copy(tmp.begin()    , tmp.begin() + 1, state[3].begin() + 4);
          std::copy(tmp.begin() + 1, tmp.end()      , state[3].begin() + 2);

          PermuteFace(4, -1);
        } else if (direction == 2) {
          /* Rotate left face twice; swap front, back edges, left, right edges. */
          std::swap_ranges(state[5].begin()    , state[5].begin() + 1, state[0].begin());
          std::swap_ranges(state[5].begin() + 6, state[5].begin() + 8, state[0].begin() + 6);
          std::swap_ranges(state[1].begin()    , state[1].begin() + 1, state[3].begin() + 4);
          std::swap_ranges(state[1].begin() + 6, state[1].begin() + 8, state[3].begin() + 2);

          PermuteFace(4, 2);
        } else {
          std::cout << "Error: incorrect direction specified in RotateFace!" << std::endl;
        }
        break;
      }

    /* This case handles all lower/down/bottom face rotations. */
    case 6 :
      {
        if (direction == 1) {
          /* Make temporary copy of first edge. */
          std::vector<char> tmp = std::vector<char>(state[4].begin() + 4, state[4].begin() + 7);

          /* Rotate bottom/down face clockwise. */
          for ( auto i : {3, 2, 1} )
            std::copy(state[i].begin() + 4, state[i].begin() + 7, state[i + 1].begin() + 4);

          std::copy(tmp.begin(), tmp.begin() + 3, state[1].begin() + 4);

          PermuteFace(0, 1);
        } else if (direction == -1) {
          /* Make temporary copy of first edge. */
          std::vector<char> tmp = std::vector<char>(state[1].begin() + 4, state[1].begin() + 7);

          /* Rotate bottom/down face counterclockwise. */
          for ( auto i : {2, 3, 4} )
            std::copy(state[i].begin() + 4, state[i].begin() + 7, state[i - 1].begin() + 4);

          std::copy(tmp.begin(), tmp.begin() + 3, state[4].begin() + 4);

          PermuteFace(0, -1);
        } else if (direction == 2) {
          /* Rotate bottom/down face twice; swap front, back edges, left, right
           * edges.
           */
          std::swap_ranges(state[1].begin() + 4, state[1].begin() + 7, state[3].begin() + 4);
          std::swap_ranges(state[2].begin() + 4, state[2].begin() + 7, state[4].begin() + 4);

          PermuteFace(0, 2);
        } else {
          std::cout << "Error: incorrect direction specified in RotateFace!" << std::endl;
        }
        break;
      }

    /* TODO: swap top and bottom (up and down) logic in this method to match
     * the cube state orientation.
     */
    /* This case handles all upper/top face rotations that also include the
     * middle/adjacent layer.
     */
    case 7 :
      {
        /* For now this is implemented by separately rotating both the top/up
         * face and the adjacent horizontal middle slice which achieves the
         * desired effect. If this is found to be less efficient, the
         * appropriate logic may be coded here.
         */
        RotateFace(1, direction);
        RotateFace(14, direction);
        break;
      }

    /* This case handles all front face rotations that also include the
     * middle/adjacent layer.
     */
    case 8 :
      {
        /* For now this is implemented by separately rotating both the front
         * face and the adjacent vertical middle slice which achieves the
         * desired effect. If this is found to be less efficient, the
         * appropriate logic may be coded here.
         */
        RotateFace(2, direction);
        RotateFace(15, direction);
        break;
      }

    /* This case handles all right face rotations that also include the
     * middle/adjacent layer.
     */
    case 9 :
      {
        /* For now this is implemented by separately rotating both the right
         * face and the adjacent vertical middle slice which achieves the
         * desired effect. If this is found to be less efficient, the
         * appropriate logic may be coded here.
         */
        RotateFace(3, direction);
        RotateFace(13, direction);
        break;
      }

    /* This case handles all back face rotations that also include the
     * middle/adjacent layer.
     */
    case 10 :
      {
        /* For now this is implemented by separately rotating both the back
         * face and the adjacent vertical middle slice which achieves the
         * desired effect. If this is found to be less efficient, the
         * appropriate logic may be coded here.
         */
        RotateFace(4, direction);

        /* This is necessary as the back face rotates opposite to the vertical
         * middle slice, i.e., a clockwise rotation of the back face matches a
         * counterclockwise rotation of its adjacent middle slice.
         */
        RotateFace(15, ((direction != 2) ? -1*direction : direction));
        break;
      }

    /* This case handles all left face rotations that also include the
     * middle/adjacent layer.
     */
    case 11 :
      {
        /* For now this is implemented by separately rotating both the left
         * face and the adjacent vertical middle slice which achieves the
         * desired effect. If this is found to be less efficient, the
         * appropriate logic may be coded here.
         */
        RotateFace(5, direction);

        /* This is necessary as the left face rotates opposite to the vertical
         * middle slice, i.e., a clockwise rotation of the left face matches a
         * counterclockwise rotation of its adjacent middle slice.
         */
        RotateFace(13, ((direction != 2) ? -1*direction : direction));
        break;
      }

    /* This case handles all lower/down/bottom face rotations that also include
     * the middle/adjacent layer.
     */
    case 12 :
      {
        /* For now this is implemented by separately rotating both the
         * bottom/down face and the adjacent horizontal middle slice which
         * achieves the desired effect. If this is found to be less efficient,
         * the appropriate logic may be coded here.
         */
        RotateFace(6, direction);

        /* This is necessary as the bottom/down face rotates opposite to the
         * horizontal middle slice, i.e., a clockwise rotation of the
         * bottom/down face matches a counterclockwise rotation of its adjacent
         * middle slice.
         */
        RotateFace(14, ((direction != 2) ? -1*direction : direction));
        break;
      }

    /* This case handles all vertical middle layer rotations about the x-axis
     * (the slice in the y/z plane).
     */
    case 13 :
      {
        if (direction == 1) {
          /* Rotate vertical middle slice clockwise about the x-axis (from the
           * perspective of the right face).
           */

          /* Make temporary copy of first edge (on top/up face). */
          std::vector<char> tmp = std::vector<char>(state[5].begin() + 1, state[5].begin() + 2);
          tmp.push_back(state[5][5]);
          tmp.push_back(state[5][8]);

          /* Rotate front slice to top/up face. */
          state[5][1] = state[1][1];
          state[5][5] = state[1][5];
          state[5][8] = state[1][8];

          /* Rotate bottom/down slice to front face. */
          state[1][1] = state[0][1];
          state[1][5] = state[0][5];
          state[1][8] = state[0][8];

          /* Rotate back slice to bottom/down face. */
          state[0][1] = state[3][5];
          state[0][5] = state[3][1];
          state[0][8] = state[3][8];

          /* Rotate top/up slice to back face. */
          state[3][5] = tmp[0];
          state[3][1] = tmp[1];
          state[3][8] = tmp[2];

        } else if (direction == -1) {
          /* Rotate vertical middle slice counterclockwise about the x-axis
           * (from the perspective of the right face).
           */

          /* Make temporary copy of first edge (on top/up face). */
          std::vector<char> tmp = std::vector<char>(state[5].begin() + 1, state[5].begin() + 2);
          tmp.push_back(state[5][5]);
          tmp.push_back(state[5][8]);

          /* Rotate back slice to top/up face. */
          state[5][1] = state[3][5];
          state[5][5] = state[3][1];
          state[5][8] = state[3][8];

          /* Rotate bottom/down slice to back face. */
          state[3][5] = state[0][1];
          state[3][1] = state[0][5];
          state[3][8] = state[0][8];

          /* Rotate front slice to bottom/down face. */
          state[0][1] = state[1][1];
          state[0][5] = state[1][5];
          state[0][8] = state[1][8];

          /* Rotate top/up slice to front face. */
          state[1][1] = tmp[0];
          state[1][5] = tmp[1];
          state[1][8] = tmp[2];

        } else if (direction == 2) {
          /* Rotate vertical middle slice twice about the x-axis. */

          /* Swap values between top/up and bottom/down faces. */
          std::swap(state[5][1], state[0][1]);
          std::swap(state[5][5], state[0][5]);
          std::swap(state[5][8], state[0][8]);

          /* Swap values between front and back faces. */
          std::swap(state[1][1], state[3][5]);
          std::swap(state[1][5], state[3][1]);
          std::swap(state[1][8], state[3][8]);

        } else {
          std::cout << "Error: incorrect direction specified in RotateFace!" << std::endl;
        }
        break;
      }

    /* This case handles all horizontal middle layer rotations about the y-axis
     * (the slice int the x/z plane).
     */
    case 14 :
      {
        if (direction == 1) {
          /* Rotate horizontal middle slice clockwise about the y-axis (from
           * the perspective of the top face).
           */

          /* Make temporary copy of first edge (on front face). */
          std::vector<char> tmp = std::vector<char>(state[1].begin() + 3, state[1].begin() + 4);
          tmp.push_back(state[1][7]);
          tmp.push_back(state[1][8]);

          /* Rotate right slice to front, back to right, and left to back. */
          for ( auto i : {2, 3, 4} ) {
            state[i - 1][3] = state[i][3];
            state[i - 1][7] = state[i][7];
            state[i - 1][8] = state[i][8];
          }

          /* Rotate front slice to left face. */
          state[4][3] = tmp[0];
          state[4][7] = tmp[1];
          state[4][8] = tmp[2];

        } else if (direction == -1) {
          /* Rotate horizontal middle slice counterclockwise about the y-axis
           * (from the perspective of the top face).
           */

          /* Make temporary copy of first edge (on left face). */
          std::vector<char> tmp = std::vector<char>(state[4].begin() + 3, state[4].begin() + 4);
          tmp.push_back(state[4][7]);
          tmp.push_back(state[4][8]);

          /* Rotate back to left, right to back, and front slice to right. */
          for ( auto i : {3, 2, 1} ) {
            state[i + 1][3] = state[i][3];
            state[i + 1][7] = state[i][7];
            state[i + 1][8] = state[i][8];
          }

          /* Rotate left slice to front face. */
          state[1][3] = tmp[0];
          state[1][7] = tmp[1];
          state[1][8] = tmp[2];
        } else if (direction == 2) {
          /* Rotate horizontal middle slice twice about the y-axis. */

          /* Swap values between right and left faces. */
          std::swap(state[2][3], state[4][3]);
          std::swap(state[2][7], state[4][7]);
          std::swap(state[2][8], state[4][8]);

          /* Swap values between front and back faces. */
          std::swap(state[1][3], state[3][3]);
          std::swap(state[1][7], state[3][7]);
          std::swap(state[1][8], state[3][8]);

        } else {
          std::cout << "Error: incorrect direction specified in RotateFace!" << std::endl;
        }
        break;
      }

    /* This case handles all vertical middle layer rotations about the z-axis
     * (the slice in the x/y plane).
     */
    case 15 :
      {
        if (direction == 1) {
          /* Rotate vertical middle slice clockwise about the z-axis (from the
           * perspective of the front face).
           */

          /* Make temporary copy of first edge (on top/up face). */
          std::vector<char> tmp = std::vector<char>(state[5].begin() + 3, state[5].begin() + 4);
          tmp.push_back(state[5][7]);
          tmp.push_back(state[5][8]);

          /* Rotate left slice to top/up face. */
          state[5][3] = state[4][1];
          state[5][7] = state[4][5];
          state[5][8] = state[4][8];

          /* Rotate bottom/down slice to left face. */
          state[4][5] = state[0][3];
          state[4][1] = state[0][7];
          state[4][8] = state[0][8];

          /* Rotate right slice to bottom/down face. */
          state[0][3] = state[2][1];
          state[0][7] = state[2][5];
          state[0][8] = state[2][8];

          /* Rotate top/up slice to right face. */
          state[2][5] = tmp[0];
          state[2][1] = tmp[1];
          state[2][8] = tmp[2];

        } else if (direction == -1) {
          /* Rotate vertical middle slice counterclockwise about the z-axis
           * (from the perspective of the front face).
           */

          /* Make temporary copy of first edge (on top/up face). */
          std::vector<char> tmp = std::vector<char>(state[5].begin() + 3, state[5].begin() + 4);
          tmp.push_back(state[5][7]);
          tmp.push_back(state[5][8]);

          /* Rotate right slice to top/up face. */
          state[5][7] = state[2][1];
          state[5][3] = state[2][5];
          state[5][8] = state[2][8];

          /* Rotate bottom/down slice to right face. */
          state[2][1] = state[0][3];
          state[2][5] = state[0][7];
          state[2][8] = state[0][8];

          /* Rotate left slice to bottom/down face. */
          state[0][7] = state[4][1];
          state[0][3] = state[4][5];
          state[0][8] = state[4][8];

          /* Rotate top/up slice to left face. */
          state[4][1] = tmp[0];
          state[4][5] = tmp[1];
          state[4][8] = tmp[2];

        } else if (direction == 2) {
          /* Rotate vertical middle slice twice about the z-axis. */

          /* Swap values between top/up and bottom/down faces. */
          std::swap(state[5][3], state[0][7]);
          std::swap(state[5][7], state[0][3]);
          std::swap(state[5][8], state[0][8]);

          /* Swap values between right and left faces. */
          std::swap(state[2][1], state[4][5]);
          std::swap(state[2][5], state[4][1]);
          std::swap(state[2][8], state[4][8]);

        } else {
          std::cout << "Error: incorrect direction specified in RotateFace!" << std::endl;
        }
        break;
      }

    default:
      std::cout << "Error: incorrect faceID passed to RotateFace..." << std::endl;
      break;
  }
}
