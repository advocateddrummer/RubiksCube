#include <iostream>
#include <random>
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

void Cube::operator=(const Cube & rhs)
{
  for ( int i = 0; i < 6; i++ )
    for ( int j = 0; j < 9; j++ )
      state[i][j] = rhs.state[i][j];

  return;
}

bool Cube::operator==(const Cube & rhs) const
{
  /* Make copy of rhs and manipulate it so that it matches the orientation of
   * the lhs/self cube to facilitate easier comparison.
   */
  Cube tmp = rhs;

  int map{-1};

  /* Find side on temporary copy of rhs that matches the color on the first
   * (bottom/down) side of the lhs/self cube.
   */
  for ( int i = 0; i < 6; i++ ) {
    if ( tmp.state[i][8] == state[0][8] ) {
      map = i;
      //std::cout << "map: " << map << " -> 0" << std::endl;
      break;
    }
  }

  /* Rotate temporary cube so that its bottom/down center matches the lhs/self
   * cube.
   */
  switch ( map ) {
    /* Both faces already align. */
    case 0 :
      break;
    case 1 :
      {
        /* Rotate tmp counterclockwise about the x-axis. */
        tmp.RotateCube(1, -1);
        break;
      }
    case 2 :
      {
        /* Rotate tmp clockwise about the z-axis. */
        tmp.RotateCube(3, 1);
        break;
      }
    case 3 :
      {
        /* Rotate tmp clockwise about the x-axis. */
        tmp.RotateCube(1, 1);
        break;
      }
    case 4 :
      {
        /* Rotate tmp counterclockwise about the z-axis. */
        tmp.RotateCube(3, -1);
        break;
      }
    case 5 :
      {
        /* Rotate tmp twice about the x-axis, but the z-axis would work too. */
        tmp.RotateCube(1, 1);
        tmp.RotateCube(1, 1);
        break;
      }
    default :
      {
        std::cout << "Error: incorrect index in equality overload..." << std::endl;
        break;
      }
  }


  /* Find side on temporary copy of rhs that matches the color on the front
   * side of the lhs/self cube.
   */
  map = -1;
  for ( int i = 0; i < 6; i++ ) {
    if ( tmp.state[i][8] == state[1][8] ) {
      map = i;
      //std::cout << "map: " << map << " -> 1" << std::endl;
      break;
    }
  }

  /* Rotate temporary cube so that its front center matches the front center of
   * the lhs/self cube.
   */
  switch ( map ) {
    /* These should not happen; fall through to default. */
    case 0 :
    case 5 :
    /* Both faces already align. */
    case 1 :
        break;
    case 2 :
      {
        /* Rotate tmp clockwise about the y-axis. */
        tmp.RotateCube(2, 1);
        break;
      }
    case 3 :
      {
        /* Rotate tmp twice about the y-axis. */
        tmp.RotateCube(2, 1);
        tmp.RotateCube(2, 1);
        break;
      }
    case 4 :
      {
        /* Rotate tmp counterclockwise about the y-axis. */
        tmp.RotateCube(2, -1);
        break;
      }
    default :
      {
        std::cout << "Error: incorrect index in equality overload..." << std::endl;
        break;
      }
  }


  /* Perform comparison now that tmp is properly oriented. */
  for ( int i = 0; i < 6; i++ )
    for ( int j = 0; j < 9; j++ )
      if ( state[i][j] != tmp.state[i][j] )
        return false;

  return true;
}

void Cube::RandomScramble(const int nMoves)
{
  /* Vector of all _planned_ possible face/cube rotations; once all planned
   * methods are implemented, this vector should be used.
   */
  //const std::vector<string> moveMap{"x", "xp", "xx", "y", "yp", "yy", "z", "zp", "zz", "u", "up", "uu", "U", "Up", "UU", "f", "fp", "ff", "F", "Fp", "FF", "r", "rp", "rr", "R", "Rp", "RR", "b", "bp", "bb", "B", "Bp", "BB", "l", "lp", "ll", "L", "Lp", "LL", "d", "dp", "dd", "D", "Dp", "DD", "m", "mp", "mm"};

  /* Vector of currently possible face/cube rotations. */
  const std::vector<std::string> moveMap{"x", "xp", "xx", "y", "yp", "yy", "z", "zp", "zz", "u", "up", "uu", "f", "fp", "ff", "r", "rp", "rr", "b", "bp", "bb", "l", "lp", "ll", "d", "dp", "dd"};
  const std::vector<void(Cube::*)()> moves{&Cube::x, &Cube::xp, &Cube::xx, &Cube::y, &Cube::yp, &Cube::yy, &Cube::z, &Cube::zp, &Cube::zz, &Cube::u, &Cube::up, &Cube::uu, &Cube::f, &Cube::fp, &Cube::ff, &Cube::r, &Cube::rp, &Cube::rr, &Cube::b, &Cube::bp, &Cube::bb, &Cube::l, &Cube::lp, &Cube::ll, &Cube::d, &Cube::dp, &Cube::dd};

  /* Got this clever, consise logic from here:
   * https://cpppatterns.com/patterns/choose-random-element.html
   */
  std::random_device random_device;
  std::mt19937 engine{random_device()};
  std::uniform_int_distribution<int> dist(0, moves.size() - 1);

  int index{-1};

  for ( int i = 0; i < nMoves; i++ ) {
    index = dist(engine);
    //std::cout << "In Cube::RandomScramble[" << index << "]..., calling " << moveMap[index] << "...\n";
    (this->*moves[index])();
    //std::cout << "In Cube::RandomScramble..., Done\n";
  }

  return;
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

void Cube::ResetCube()
{
  for ( int i = 0; i < 6; i++ )
    for ( int j = 0; j < 9; j++ )
      state[i][j] = solvedState[i][j];

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
  } else
    std::cout << "Error: incorrect direction passed to PermuteFace..." << std::endl;
}

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

void Cube::U()
{
  std::cout << "Performing a \'U\' rotation..." << std::endl;
  std::cout << "Cube state before \'U\': " << std::endl;
  Print();
  RotateFace(7, 1);
  std::cout << "\'U\' rotation complete" << std::endl;
  std::cout << "Cube state after \'U\': " << std::endl;
  Print();
}

void Cube::Up()
{
  std::cout << "Performing a \'Up\' rotation..." << std::endl;
  std::cout << "Cube state before \'Up\': " << std::endl;
  Print();
  RotateFace(7, -1);
  std::cout << "\'Up\' rotation complete" << std::endl;
  std::cout << "Cube state after \'Up\': " << std::endl;
  Print();
}

void Cube::UU()
{
  std::cout << "Performing a \'UU\' rotation..." << std::endl;
  std::cout << "Cube state before \'UU\': " << std::endl;
  Print();
  RotateFace(7, 2);
  std::cout << "\'UU\' rotation complete" << std::endl;
  std::cout << "Cube state after \'UU\': " << std::endl;
  Print();
}

void Cube::f()
{
  std::cout << "Performing a \'f\' rotation..." << std::endl;
  std::cout << "Cube state before \'f\': " << std::endl;
  Print();
  RotateFace(2, 1);
  std::cout << "\'f\' rotation complete" << std::endl;
  std::cout << "Cube state after \'f\': " << std::endl;
  Print();
}

void Cube::fp()
{
  std::cout << "Performing a \'fp\' rotation..." << std::endl;
  std::cout << "Cube state before \'fp\': " << std::endl;
  Print();
  RotateFace(2, -1);
  std::cout << "\'fp\' rotation complete" << std::endl;
  std::cout << "Cube state after \'fp\': " << std::endl;
  Print();
}

void Cube::ff()
{
  std::cout << "Performing a \'ff\' rotation..." << std::endl;
  std::cout << "Cube state before \'ff\': " << std::endl;
  Print();
  RotateFace(2, 2);
  std::cout << "\'ff\' rotation complete" << std::endl;
  std::cout << "Cube state after \'ff\': " << std::endl;
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

void Cube::b()
{
  std::cout << "Performing a \'b\' rotation..." << std::endl;
  std::cout << "Cube state before \'b\': " << std::endl;
  Print();
  RotateFace(4, 1);
  std::cout << "\'b\' rotation complete" << std::endl;
  std::cout << "Cube state after \'b\': " << std::endl;
  Print();
}

void Cube::bp()
{
  std::cout << "Performing a \'bp\' rotation..." << std::endl;
  std::cout << "Cube state before \'bp\': " << std::endl;
  Print();
  RotateFace(4, -1);
  std::cout << "\'bp\' rotation complete" << std::endl;
  std::cout << "Cube state after \'bp\': " << std::endl;
  Print();
}

void Cube::bb()
{
  std::cout << "Performing a \'bb\' rotation..." << std::endl;
  std::cout << "Cube state before \'bb\': " << std::endl;
  Print();
  RotateFace(4, 2);
  std::cout << "\'bb\' rotation complete" << std::endl;
  std::cout << "Cube state after \'bb\': " << std::endl;
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

void Cube::mx()
{
  std::cout << "Performing a \'mx\' rotation..." << std::endl;
  std::cout << "Cube state before \'mx\': " << std::endl;
  Print();
  RotateFace(13, 1);
  std::cout << "\'mx\' rotation complete" << std::endl;
  std::cout << "Cube state after \'mx\': " << std::endl;
  Print();
}

void Cube::mxp()
{
  std::cout << "Performing a \'mxp\' rotation..." << std::endl;
  std::cout << "Cube state before \'mxp\': " << std::endl;
  Print();
  RotateFace(13, -1);
  std::cout << "\'mxp\' rotation complete" << std::endl;
  std::cout << "Cube state after \'mxp\': " << std::endl;
  Print();
}

void Cube::mxx()
{
  std::cout << "Performing a \'mxx\' rotation..." << std::endl;
  std::cout << "Cube state before \'mxx\': " << std::endl;
  Print();
  RotateFace(13, 2);
  std::cout << "\'mxx\' rotation complete" << std::endl;
  std::cout << "Cube state after \'mxx\': " << std::endl;
  Print();
}

void Cube::my()
{
  std::cout << "Performing a \'my\' rotation..." << std::endl;
  std::cout << "Cube state before \'my\': " << std::endl;
  Print();
  RotateFace(14, 1);
  std::cout << "\'my\' rotation complete" << std::endl;
  std::cout << "Cube state after \'my\': " << std::endl;
  Print();
}

void Cube::myp()
{
  std::cout << "Performing a \'myp\' rotation..." << std::endl;
  std::cout << "Cube state before \'myp\': " << std::endl;
  Print();
  RotateFace(14, -1);
  std::cout << "\'myp\' rotation complete" << std::endl;
  std::cout << "Cube state after \'myp\': " << std::endl;
  Print();
}

void Cube::myy()
{
  std::cout << "Performing a \'myy\' rotation..." << std::endl;
  std::cout << "Cube state before \'myy\': " << std::endl;
  Print();
  RotateFace(14, 2);
  std::cout << "\'myy\' rotation complete" << std::endl;
  std::cout << "Cube state after \'myy\': " << std::endl;
  Print();
}

void Cube::mz()
{
  std::cout << "Performing a \'mz\' rotation..." << std::endl;
  std::cout << "Cube state before \'mz\': " << std::endl;
  Print();
  RotateFace(15, 1);
  std::cout << "\'mz\' rotation complete" << std::endl;
  std::cout << "Cube state after \'mz\': " << std::endl;
  Print();
}

void Cube::mzp()
{
  std::cout << "Performing a \'mzp\' rotation..." << std::endl;
  std::cout << "Cube state before \'mzp\': " << std::endl;
  Print();
  RotateFace(15, -1);
  std::cout << "\'mzp\' rotation complete" << std::endl;
  std::cout << "Cube state after \'mzp\': " << std::endl;
  Print();
}

void Cube::mzz()
{
  std::cout << "Performing a \'mzz\' rotation..." << std::endl;
  std::cout << "Cube state before \'mzz\': " << std::endl;
  Print();
  RotateFace(15, 2);
  std::cout << "\'mzz\' rotation complete" << std::endl;
  std::cout << "Cube state after \'mzz\': " << std::endl;
  Print();
}

/* Cube rotation methods. */

void Cube::x()
{
  std::cout << "Performing an \'x\' cube rotation..." << std::endl;
  std::cout << "Cube state before \'x\': " << std::endl;
  Print();
  RotateCube(1, 1);
  std::cout << "\'x\' cube rotation complete" << std::endl;
  std::cout << "Cube state after \'x\': " << std::endl;
  Print();
}

void Cube::xp()
{
  std::cout << "Performing an \'xp\' cube rotation..." << std::endl;
  std::cout << "Cube state before \'xp\': " << std::endl;
  Print();
  RotateCube(1, -1);
  std::cout << "\'xp\' cube rotation complete" << std::endl;
  std::cout << "Cube state after \'xp\': " << std::endl;
  Print();
}

void Cube::xx()
{
  std::cout << "Performing an \'xx\' cube rotation..." << std::endl;
  std::cout << "Cube state before \'xx\': " << std::endl;
  Print();
  /* For now, just perform two clockwise rotations. */
  RotateCube(1, 1);
  RotateCube(1, 1);
  std::cout << "\'xx\' cube rotation complete" << std::endl;
  std::cout << "Cube state after \'xx\': " << std::endl;
  Print();
}

void Cube::y()
{
  std::cout << "Performing an \'y\' cube rotation..." << std::endl;
  std::cout << "Cube state before \'y\': " << std::endl;
  Print();
  RotateCube(2, 1);
  std::cout << "\'y\' cube rotation complete" << std::endl;
  std::cout << "Cube state after \'y\': " << std::endl;
  Print();
}

void Cube::yp()
{
  std::cout << "Performing an \'yp\' cube rotation..." << std::endl;
  std::cout << "Cube state before \'yp\': " << std::endl;
  Print();
  RotateCube(2, -1);
  std::cout << "\'yp\' cube rotation complete" << std::endl;
  std::cout << "Cube state after \'yp\': " << std::endl;
  Print();
}

void Cube::yy()
{
  std::cout << "Performing an \'yy\' cube rotation..." << std::endl;
  std::cout << "Cube state before \'yy\': " << std::endl;
  Print();
  /* For now, just perform two clockwise rotations. */
  RotateCube(2, 1);
  RotateCube(2, 1);
  std::cout << "\'yy\' cube rotation complete" << std::endl;
  std::cout << "Cube state after \'yy\': " << std::endl;
  Print();
}

void Cube::z()
{
  std::cout << "Performing an \'z\' cube rotation..." << std::endl;
  std::cout << "Cube state before \'z\': " << std::endl;
  Print();
  RotateCube(3, 1);
  std::cout << "\'z\' cube rotation complete" << std::endl;
  std::cout << "Cube state after \'z\': " << std::endl;
  Print();
}

void Cube::zp()
{
  std::cout << "Performing an \'zp\' cube rotation..." << std::endl;
  std::cout << "Cube state before \'zp\': " << std::endl;
  Print();
  RotateCube(3, -1);
  std::cout << "\'zp\' cube rotation complete" << std::endl;
  std::cout << "Cube state after \'zp\': " << std::endl;
  Print();
}

void Cube::zz()
{
  std::cout << "Performing an \'zz\' cube rotation..." << std::endl;
  std::cout << "Cube state before \'zz\': " << std::endl;
  Print();
  /* For now, just perform two clockwise rotations. */
  RotateCube(3, 1);
  RotateCube(3, 1);
  std::cout << "\'zz\' cube rotation complete" << std::endl;
  std::cout << "Cube state after \'zz\': " << std::endl;
  Print();
}

void Cube::Print() const
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
