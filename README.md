# How to Build

1. Clone this repo: git@github.com:advocateddrummer/RubiksCube.git
2. Check out the _dev_ branch: `git checkout dev`
3. Check out my fork of the kociemba code: git@github.com:advocateddrummer/kociemba.git
  * This may go anywhere, but I usually clone it into the root directory of the
    RubiksCube repo
4. Go to `kociemba/kociemba/ckociemba/` and run `make -j libs`
5. Go back to the RubiksCube root directory and create a `build` directory
6. Change directory the build directory and run `cmake ..`
7. If this step succeeds, run `make -j`

This code requires `cmake`, `boost`, `gtest` (googletest) in addition to the
kociemba dependency. I have had luck (one MacOS) installing both `cmake` and
`boost` using `brew`: `brew install cmake boost`.
