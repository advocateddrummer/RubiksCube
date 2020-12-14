#include <iostream>
#include <random>
#include <algorithm>
#include "Cube.hpp"

Cube::Cube()
{
  //std::cout << "Constructing Cube..." << std::endl;
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
  /* Add some sort of logging/verbosity logic around this a la: */
  //if (log)
  //std::cout << "In Cube::RandomScramble, performing " << nMoves << " twists...\n";

  /* Vector of possible face/cube rotation string descriptions. */
  const std::vector<std::string> moveMap{"x", "xp", "xx",
                                         "y", "yp", "yy",
                                         "z", "zp", "zz",
                                         "u", "up", "uu",
                                         "U", "Up", "UU",
                                         "f", "fp", "ff",
                                         "F", "Fp", "FF",
                                         "r", "rp", "rr",
                                         "R", "Rp", "RR",
                                         "b", "bp", "bb",
                                         "B", "Bp", "BB",
                                         "l", "lp", "ll",
                                         "L", "Lp", "LL",
                                         "d", "dp", "dd",
                                         "D", "Dp", "DD",
                                         "mx", "mxp", "mxx",
                                         "my", "myp", "myy",
                                         "mz", "mzp", "mzz"};

  /* Vector of possible face/cube rotation function/method pointers. */
  const std::vector<void(Cube::*)()> moves{&Cube::x, &Cube::xp, &Cube::xx,
                                           &Cube::y, &Cube::yp, &Cube::yy,
                                           &Cube::z, &Cube::zp, &Cube::zz,
                                           &Cube::u, &Cube::up, &Cube::uu,
                                           &Cube::U, &Cube::Up, &Cube::UU,
                                           &Cube::f, &Cube::fp, &Cube::ff,
                                           &Cube::F, &Cube::Fp, &Cube::FF,
                                           &Cube::r, &Cube::rp, &Cube::rr,
                                           &Cube::R, &Cube::Rp, &Cube::RR,
                                           &Cube::b, &Cube::bp, &Cube::bb,
                                           &Cube::B, &Cube::Bp, &Cube::BB,
                                           &Cube::l, &Cube::lp, &Cube::ll,
                                           &Cube::L, &Cube::Lp, &Cube::LL,
                                           &Cube::d, &Cube::dp, &Cube::dd,
                                           &Cube::D, &Cube::Dp, &Cube::DD,
                                           &Cube::mx, &Cube::mxp, &Cube::mxx,
                                           &Cube::my, &Cube::myp, &Cube::myy,
                                           &Cube::mz, &Cube::mzp, &Cube::mzz};

  /* Got this clever, concise logic from here:
   * https://cpppatterns.com/patterns/choose-random-element.html
   */
  std::random_device random_device;
  std::mt19937 engine{random_device()};
  std::uniform_int_distribution<int> dist(0, moves.size() - 1);

  int index{-1};

  for ( int i = 0; i < nMoves; i++ ) {
    index = dist(engine);
    (this->*moves[index])();
    /* Add some sort of logging/verbosity logic around this a la: */
    //if (log)
    //std::cout << moveMap[index] << " ";
  }

  /* Add some sort of logging/verbosity logic around this a la: */
  //if (log)
  //std::cout << "\nCube::RandomScramble Done\n";
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


void Cube::u()
{
  //std::cout << "Performing a \'u\' rotation..." << std::endl;
  RotateFace(1, 1);
}

void Cube::up()
{
  //std::cout << "Performing a \'up\' rotation..." << std::endl;
  RotateFace(1, -1);
}

void Cube::uu()
{
  //std::cout << "Performing a \'uu\' rotation..." << std::endl;
  RotateFace(1, 2);
}

void Cube::U()
{
  //std::cout << "Performing a \'U\' rotation..." << std::endl;
  RotateFace(7, 1);
}

void Cube::Up()
{
  //std::cout << "Performing a \'Up\' rotation..." << std::endl;
  RotateFace(7, -1);
}

void Cube::UU()
{
  //std::cout << "Performing a \'UU\' rotation..." << std::endl;
  RotateFace(7, 2);
}

void Cube::f()
{
  //std::cout << "Performing a \'f\' rotation..." << std::endl;
  RotateFace(2, 1);
}

void Cube::fp()
{
  //std::cout << "Performing a \'fp\' rotation..." << std::endl;
  RotateFace(2, -1);
}

void Cube::ff()
{
  //std::cout << "Performing a \'ff\' rotation..." << std::endl;
  RotateFace(2, 2);
}

void Cube::F()
{
  //std::cout << "Performing a \'F\' rotation..." << std::endl;
  RotateFace(8, 1);
}

void Cube::Fp()
{
  //std::cout << "Performing a \'Fp\' rotation..." << std::endl;
  RotateFace(8, -1);
}

void Cube::FF()
{
  //std::cout << "Performing a \'FF\' rotation..." << std::endl;
  RotateFace(8, 2);
}

void Cube::d()
{
  //std::cout << "Performing a \'d\' rotation..." << std::endl;
  RotateFace(6, 1);
}

void Cube::dp()
{
  //std::cout << "Performing a \'dp\' rotation..." << std::endl;
  RotateFace(6, -1);
}

void Cube::dd()
{
  //std::cout << "Performing a \'dd\' rotation..." << std::endl;
  RotateFace(6, 2);
}

void Cube::D()
{
  //std::cout << "Performing a \'D\' rotation..." << std::endl;
  RotateFace(12, 1);
}

void Cube::Dp()
{
  //std::cout << "Performing a \'Dp\' rotation..." << std::endl;
  RotateFace(12, -1);
}

void Cube::DD()
{
  //std::cout << "Performing a \'DD\' rotation..." << std::endl;
  RotateFace(12, 2);
}

void Cube::r()
{
  //std::cout << "Performing a \'r\' rotation..." << std::endl;
  RotateFace(3, 1);
}

void Cube::rp()
{
  //std::cout << "Performing a \'rp\' rotation..." << std::endl;
  RotateFace(3, -1);
}

void Cube::rr()
{
  //std::cout << "Performing a \'rr\' rotation..." << std::endl;
  RotateFace(3, 2);
}

void Cube::R()
{
  //std::cout << "Performing a \'R\' rotation..." << std::endl;
  RotateFace(9, 1);
}

void Cube::Rp()
{
  //std::cout << "Performing a \'Rp\' rotation..." << std::endl;
  RotateFace(9, -1);
}

void Cube::RR()
{
  //std::cout << "Performing a \'RR\' rotation..." << std::endl;
  RotateFace(9, 2);
}

void Cube::b()
{
  //std::cout << "Performing a \'b\' rotation..." << std::endl;
  RotateFace(4, 1);
}

void Cube::bp()
{
  //std::cout << "Performing a \'bp\' rotation..." << std::endl;
  RotateFace(4, -1);
}

void Cube::bb()
{
  //std::cout << "Performing a \'bb\' rotation..." << std::endl;
  RotateFace(4, 2);
}

void Cube::B()
{
  //std::cout << "Performing a \'B\' rotation..." << std::endl;
  RotateFace(10, 1);
}

void Cube::Bp()
{
  //std::cout << "Performing a \'Bp\' rotation..." << std::endl;
  RotateFace(10, -1);
}

void Cube::BB()
{
  //std::cout << "Performing a \'BB\' rotation..." << std::endl;
  RotateFace(10, 2);
}

void Cube::l()
{
  //std::cout << "Performing a \'l\' rotation..." << std::endl;
  RotateFace(5, 1);
}

void Cube::lp()
{
  //std::cout << "Performing a \'lp\' rotation..." << std::endl;
  RotateFace(5, -1);
}

void Cube::ll()
{
  //std::cout << "Performing a \'ll\' rotation..." << std::endl;
  RotateFace(5, 2);
}

void Cube::L()
{
  //std::cout << "Performing a \'L\' rotation..." << std::endl;
  RotateFace(11, 1);
}

void Cube::Lp()
{
  //std::cout << "Performing a \'Lp\' rotation..." << std::endl;
  RotateFace(11, -1);
}

void Cube::LL()
{
  //std::cout << "Performing a \'LL\' rotation..." << std::endl;
  RotateFace(11, 2);
}

void Cube::mx()
{
  //std::cout << "Performing a \'mx\' rotation..." << std::endl;
  RotateFace(13, 1);
}

void Cube::mxp()
{
  //std::cout << "Performing a \'mxp\' rotation..." << std::endl;
  RotateFace(13, -1);
}

void Cube::mxx()
{
  //std::cout << "Performing a \'mxx\' rotation..." << std::endl;
  RotateFace(13, 2);
}

void Cube::my()
{
  //std::cout << "Performing a \'my\' rotation..." << std::endl;
  RotateFace(14, 1);
}

void Cube::myp()
{
  //std::cout << "Performing a \'myp\' rotation..." << std::endl;
  RotateFace(14, -1);
}

void Cube::myy()
{
  //std::cout << "Performing a \'myy\' rotation..." << std::endl;
  RotateFace(14, 2);
}

void Cube::mz()
{
  //std::cout << "Performing a \'mz\' rotation..." << std::endl;
  RotateFace(15, 1);
}

void Cube::mzp()
{
  //std::cout << "Performing a \'mzp\' rotation..." << std::endl;
  RotateFace(15, -1);
}

void Cube::mzz()
{
  //std::cout << "Performing a \'mzz\' rotation..." << std::endl;
  RotateFace(15, 2);
}

/* Cube rotation methods. */

void Cube::x()
{
  //std::cout << "Performing an \'x\' cube rotation..." << std::endl;
  RotateCube(1, 1);
}

void Cube::xp()
{
  //std::cout << "Performing an \'xp\' cube rotation..." << std::endl;
  RotateCube(1, -1);
}

void Cube::xx()
{
  //std::cout << "Performing an \'xx\' cube rotation..." << std::endl;
  /* For now, just perform two clockwise rotations. */
  RotateCube(1, 1);
  RotateCube(1, 1);
}

void Cube::y()
{
  //std::cout << "Performing an \'y\' cube rotation..." << std::endl;
  RotateCube(2, 1);
}

void Cube::yp()
{
  //std::cout << "Performing an \'yp\' cube rotation..." << std::endl;
  RotateCube(2, -1);
}

void Cube::yy()
{
  //std::cout << "Performing an \'yy\' cube rotation..." << std::endl;
  /* For now, just perform two clockwise rotations. */
  RotateCube(2, 1);
  RotateCube(2, 1);
}

void Cube::z()
{
  //std::cout << "Performing an \'z\' cube rotation..." << std::endl;
  RotateCube(3, 1);
}

void Cube::zp()
{
  //std::cout << "Performing an \'zp\' cube rotation..." << std::endl;
  RotateCube(3, -1);
}

void Cube::zz()
{
  //std::cout << "Performing an \'zz\' cube rotation..." << std::endl;
  /* For now, just perform two clockwise rotations. */
  RotateCube(3, 1);
  RotateCube(3, 1);
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
  //std::cout << "Destructing Cube..." << std::endl;
}
