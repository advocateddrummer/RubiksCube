#include <iostream>
#include <random>
#include <map>
#include <algorithm>
#include "Cube.hpp"
#include "Utils.hpp"

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
  std::cout << "In Cube::RandomScramble, performing " << nMoves << " twists...\n";

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
    std::cout << moveMap[index] << " ";
  }

  /* Add some sort of logging/verbosity logic around this a la: */
  //if (log)
  std::cout << "\nCube::RandomScramble Done\n";
  return;
}

void Cube::ApplyTwists(const std::string twists) {

  /* This is probably very inefficient, but this map facilitates the switch
   * statement below.
   */
  const std::map<std::string, int> map { {"x",  0},  {"xp",  1},  {"xx",  3},
                                         {"y",  3},  {"yp",  4},  {"yy",  5},
                                         {"z",  6},  {"zp",  7},  {"zz",  8},
                                         {"d",  9},  {"dp",  10}, {"dd",  11},
                                         {"D",  12}, {"Dp",  13}, {"DD",  14},
                                         {"f",  15}, {"fp",  16}, {"ff",  17},
                                         {"F",  18}, {"Fp",  19}, {"FF",  20},
                                         {"r",  21}, {"rp",  22}, {"rr",  23},
                                         {"R",  24}, {"Rp",  25}, {"RR",  26},
                                         {"b",  27}, {"bp",  28}, {"bb",  29},
                                         {"B",  30}, {"Bp",  31}, {"BB",  32},
                                         {"l",  33}, {"lp",  34}, {"ll",  35},
                                         {"L",  36}, {"Lp",  37}, {"LL",  38},
                                         {"u",  39}, {"up",  40}, {"uu",  41},
                                         {"U",  42}, {"Up",  43}, {"UU",  44},
                                         {"mx", 45}, {"mxp", 46}, {"mxx", 47},
                                         {"my", 48}, {"myp", 49}, {"myy", 50},
                                         {"mz", 51}, {"mzp", 52}, {"mzz", 53} };

  /* Split input solution string into individual twists. */
  std::vector<std::string> words = StringSplit(twists, ' ');

  /* Apply twists. */
  for (const auto &w : words) {
    //std::cout << w << std::endl;
    switch ( map.at(w) ) {
      case 0 :
        {
          //puts("found x");
          this->x();
          break;
        }
      case 1 :
        {
          //puts("found xp");
          this->xp();
          break;
        }
      case 2 :
        {
          //puts("found xx");
          this->xx();
          break;
        }
      case 3 :
        {
          //puts("found y");
          this->y();
          break;
        }
      case 4 :
        {
          //puts("found yp");
          this->yp();
          break;
        }
      case 5 :
        {
          //puts("found yy");
          this->yy();
          break;
        }
      case 6 :
        {
          //puts("found z");
          this->z();
          break;
        }
      case 7 :
        {
          //puts("found zp");
          this->zp();
          break;
        }
      case 8 :
        {
          //puts("found zz");
          this->zz();
          break;
        }
      case 9 :
        {
          //puts("found d");
          this->d();
          break;
        }
      case 10 :
        {
          //puts("found dp");
          this->dp();
          break;
        }
      case 11 :
        {
          //puts("found dd");
          this->dd();
          break;
        }
      case 12 :
        {
          //puts("found D");
          this->D();
          break;
        }
      case 13 :
        {
          //puts("found Dp");
          this->Dp();
          break;
        }
      case 14 :
        {
          //puts("found DD");
          this->DD();
          break;
        }
      case 15 :
        {
          //puts("found f");
          this->f();
          break;
        }
      case 16 :
        {
          //puts("found fp");
          this->fp();
          break;
        }
      case 17 :
        {
          //puts("found ff");
          this->ff();
          break;
        }
      case 18 :
        {
          //puts("found F");
          this->F();
          break;
        }
      case 19 :
        {
          //puts("found Fp");
          this->Fp();
          break;
        }
      case 20 :
        {
          //puts("found FF");
          this->FF();
          break;
        }
      case 21 :
        {
          //puts("found r");
          this->r();
          break;
        }
      case 22 :
        {
          //puts("found rp");
          this->rp();
          break;
        }
      case 23 :
        {
          //puts("found rr");
          this->rr();
          break;
        }
      case 24 :
        {
          //puts("found R");
          this->R();
          break;
        }
      case 25 :
        {
          //puts("found Rp");
          this->Rp();
          break;
        }
      case 26 :
        {
          //puts("found RR");
          this->RR();
          break;
        }
      case 27 :
        {
          //puts("found b");
          this->b();
          break;
        }
      case 28 :
        {
          //puts("found bp");
          this->bp();
          break;
        }
      case 29 :
        {
          //puts("found bb");
          this->bb();
          break;
        }
      case 30 :
        {
          //puts("found B");
          this->B();
          break;
        }
      case 31 :
        {
          //puts("found Bp");
          this->Bp();
          break;
        }
      case 32 :
        {
          //puts("found BB");
          this->BB();
          break;
        }
      case 33 :
        {
          //puts("found l");
          this->l();
          break;
        }
      case 34 :
        {
          //puts("found lp");
          this->lp();
          break;
        }
      case 35 :
        {
          //puts("found ll");
          this->ll();
          break;
        }
      case 36 :
        {
          //puts("found L");
          this->L();
          break;
        }
      case 37 :
        {
          //puts("found Lp");
          this->Lp();
          break;
        }
      case 38 :
        {
          //puts("found LL");
          this->LL();
          break;
        }
      case 39 :
        {
          //puts("found u");
          this->u();
          break;
        }
      case 40 :
        {
          //puts("found up");
          this->up();
          break;
        }
      case 41 :
        {
          //puts("found uu");
          this->uu();
          break;
        }
      case 42 :
        {
          //puts("found U");
          this->U();
          break;
        }
      case 43 :
        {
          //puts("found Up");
          this->Up();
          break;
        }
      case 44 :
        {
          //puts("found UU");
          this->UU();
          break;
        }
      case 45 :
        {
          //puts("found mx");
          this->mx();
          break;
        }
      case 46 :
        {
          //puts("found mxp");
          this->mxp();
          break;
        }
      case 47 :
        {
          //puts("found mxx");
          this->mxx();
          break;
        }
      case 48 :
        {
          //puts("found my");
          this->my();
          break;
        }
      case 49 :
        {
          //puts("found myp");
          this->myp();
          break;
        }
      case 50 :
        {
          //puts("found myy");
          this->myy();
          break;
        }
      case 51 :
        {
          //puts("found mz");
          this->mz();
          break;
        }
      case 52 :
        {
          //puts("found mzp");
          this->mzp();
          break;
        }
      case 53 :
        {
          //puts("found mzz");
          this->mzz();
          break;
        }
      default :
        {
          std::cout << "ERROR unhandled twist: " << w << " in Cube::ApplyTwists\n";
          break;
        }
    }
  }
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

void Cube::SetCubeState(const std::vector<char> newState)
{
  /* TODO: figure out a better way to handle this. */
  /* Make sure that at least the correct number of elements are input. */
  if( newState.size() != 54 )
    throw "Cube::SetCubeState must have an input state with 54 elements!";

  for ( int s = 0; s < 6; s++ )
    for ( int c = 0; c < 9; c++ )
      state[s][c] = newState[s*9 + c];

  return;
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
