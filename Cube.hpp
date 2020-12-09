#include <vector>

class Cube
{
  private:
    /*
     * This variable is a vector of six character vectors and maintains the
     * state of the cube object, the cube state orientation is as follows:
     *   * first vector:  bottom face, orange
     *   * second vector: front face,  blue
     *   * third vector:  right face,  white
     *   * fourth vector: back face,   green
     *   * fifth vector:  left face,   yellow
     *   * sixth vector:  top face,    red
     *
     *   Currently, the map is as follows: the first three elements represent
     *   the top three cubies, the next two elements are the remaining two
     *   cubies on the right side, the next two elements, the remaining two
     *   bottom cubies, the next element, the single remaining cubies on the
     *   left side, and the last element represents the center cubie. To
     *   determine which are the top, right, bottom, and left cubies, imagine
     *   that the cube has been rotated such that the face in question is in
     *   the 'front' position, (where the blue side is by default). The back
     *   face most be rotated horizontally to the front location whereas the
     *   top and bottom faces must be rotated vertically to the front position
     *   to identify the cubie orientation for these faces. Below is a graphic
     *   to help illustrate.
     *
     *      ----  ----  ----
     *     | 0 | | 1 | | 2 |
     *      ----  ----  ----
     *     | 7 | | 8 | | 3 |
     *      ----  ----  ----
     *     | 6 | | 5 | | 4 |
     *      ----  ----  ----
     */
    std::vector<std::vector<char>> state;

    /* This variable holds the solved state of the cube for use in methods like
     * ResetCube.
     */
    const std::vector<std::vector<char>> solvedState = { { 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o'},
                                                         { 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b'},
                                                         { 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w'},
                                                         { 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g', 'g'},
                                                         { 'y', 'y', 'y', 'y', 'y', 'y', 'y', 'y', 'y'},
                                                         { 'r', 'r', 'r', 'r', 'r', 'r', 'r', 'r', 'r'}};

    /** \brief Generalized face permutation methods
     *
     * This method is used to permute the face cubies on the flat/front of
     * whatever face is being rotated. I.e., this will permute all the 'up'
     * colors during any of the u/up/uu rotations.
     *
     * \param[in] faceID the face identifier as follows:
     *            * 0 = d (lower/bottom/down face)
     *            * 1 = f (front face)
     *            * 2 = r (right face)
     *            * 3 = b (back face)
     *            * 4 = l (left face)
     *            * 5 = u (upper/top/up face)
     *
     * \param[in] direction [defaults to 1] direction to rotate the face as
     *            follows:
     *            * 1  = one rotation clockwise
     *            * -1 = one rotation counterclockwise
     *            * 2  = rotate face twice
     */
    void PermuteFace(const int faceID, const int direction);

    /** \brief Generalized face rotation method.
     *
     * This method generalizes the rotation of cube faces.
     *
     * \param[in] faceID the face identifier as follows:
     *            * 1  = u (upper/top face)
     *            * 2  = f (front face)
     *            * 3  = r (right face)
     *            * 4  = b (back face)
     *            * 5  = l (left face)
     *            * 6  = d (lower/bottom/down face)
     *            * 7  = U (upper/top and middle faces)
     *            * 8  = F (front and middle faces)
     *            * 9  = R (right and middle faces)
     *            * 10 = B (back and middle faces)
     *            * 11 = L (left and middle faces)
     *            * 12 = D (lower/bottom/down and middle faces)
     *            * 13 = mv (middle vertical slice)
     *            * 14 = mh (middle horizontal slice)
     * \param[in] direction [defaults to 1] direction to rotate the face as
     *            follows:
     *            * 1  = one rotation clockwise
     *            * -1 = one rotation counterclockwise
     *            * 2  = rotate face twice
     *
     */
    void RotateFace(const int faceID, const int direction = 1);

    /** \brief Generalized cube rotation method.
     *
     * This method generalizes the rotation of an entire cube. In this code,
     * the x-axis passes through the r/l faces, the y-axis through the u/d
     * faces, and the z-axis through the f/b faces.
     *
     * \param[in] axis the axis identifier as follows:
     *            * 1  = cube rotation about x axis
     *            * 2  = cube rotation about y axis
     *            * 3  = cube rotation about z axis
     * \param[in] direction [defaults to 1] direction to rotate the face as
     *            follows:
     *            * 1  = cube rotation clockwise
     *            * -1 = cube rotation counterclockwise
     *            * 2  = rotate cube twice
     *
     */
    void RotateCube(const int axis, const int direction = 1);

  public:

    /** \brief Default constructor.
     * Default constructor is default.
     */
    Cube();

    /** \brief Default destructor.
     * Default destructor is default.
     */
    virtual ~Cube();

    /** \brief Overload assignment operator
     * Overload = in order to set one cube equal to another cube state.
     */
    void operator=(const Cube& rhs);

    /** \brief Overload equality operator
     * Overload == in order to compare two cube states.
     */
    bool operator==(const Cube& rhs) const;

    /** \brief Scramble the cube state
     * This method performs a random of the cube state.
     *
     * \param[in] nMoves [defaults to 25] number of moves to use to scramble
     * the cube state.
     *
     */
    void RandomScramble(const int nMoves = 25);

    /** \brief Print cube state.
     * This method simply prints out the current cube state, as represented by
     * the internal 'state' vector variable.
     */
    void Print() const;

    /** \brief Reset cube state
     * This method resets the cube state to the solved state.
     */
    void ResetCube();

    /** \brief Determine if the cube is solved.
     * This method compares the cube state against a solved cube state to
     * determine if the cube has been solved.
     *
     * \retval 1 if the cube is solved.
     * \retval 0 if the cube is not solved.
     */
    int IsSolved();

    /*
     * TODO: implement cube rotations a la:
     * x/xp
     * y/yp
     * z/zp
     */
    /** \brief Perform a clockwise rotation of the cube about the x-axis.
     *
     * This method rotates the cube clockwise about the x-axis.
     */
    void x();

    /** \brief Perform a counterclockwise rotation of the cube about the x-axis.
     *
     * This method rotates the cube counterclockwise about the x-axis.
     */
    void xp();

    /** \brief Perform a double rotation of the cube about the x-axis.
     *
     * This method rotates the cube twice about the x-axis.
     */
    void xx();

    /** \brief Perform a clockwise rotation of the cube about the y-axis.
     *
     * This method rotates the cube clockwise about the y-axis.
     */
    void y();

    /** \brief Perform a counterclockwise rotation of the cube about the y-axis.
     *
     * This method rotates the cube counterclockwise about the y-axis.
     */
    void yp();

    /** \brief Perform a double rotation of the cube about the y-axis.
     *
     * This method rotates the cube twice about the y-axis.
     */
    void yy();

    /** \brief Perform a clockwise rotation of the cube about the z-axis.
     *
     * This method rotates the cube clockwise about the z-axis.
     */
    void z();

    /** \brief Perform a counterclockwise rotation of the cube about the z-axis.
     *
     * This method rotates the cube counterclockwise about the z-axis.
     */
    void zp();

    /** \brief Perform a double rotation of the cube about the z-axis.
     *
     * This method rotates the cube twice about the z-axis.
     */
    void zz();

    /*
     * In all the member functions below:
     * u/U stands for the 'up' face
     * f/F stands for the 'front' face
     * r/R stands for the 'right' face
     * b/B stands for the 'back' face
     * l/L stands for the 'left' face
     * d/D stands for the 'down' face
     *
     * Face values by themselves (u, f, L, etc.) represent a rotation of that
     * face clockwise whereas a face suffixed with a 'p' (up, fp, Lp, etc.)
     * represents a counterclockwise rotation of the associated face.
     *
     * A capital face value (U, R, D, etc.) represents both the face
     * represented by the lower case variant along with the adjacent slice of
     * the cube. In other words, R means rotate both the right face and the
     * vertical slice of cubies adjacent to the right face clockwise. (This is
     * equivalent to the 'l' rotation followed by a 'x' rotation of the entire
     * cube.)
     */

    /********************************************************************/
    /************************* Up face methods. *************************/
    /********************************************************************/

    /** \brief Perform a clockwise rotation of the up (u) face.
     *
     * This method rotates the upper face clockwise.
     */
    void u();

    /** \brief Perform a counterclockwise rotation of the up (u) face.
     *
     * This method rotates the upper face counterclockwise.
     */
    void up();

    /** \brief Perform a double rotation of the up (u) face.
     *
     * This method rotates the upper face twice; the direction in this case
     * does not matter as both a double clockwise or counterclockwise rotation
     * results in the same state.
     */
    void uu();

    void U();
    void Up();
    void UU();

    /********************************************************************/
    /*********************** Front face methods. ************************/
    /********************************************************************/

    /** \brief Perform a clockwise rotation of the front (f) face.
     *
     * This method rotates the front face clockwise.
     */
    void f();

    /** \brief Perform a counterclockwise rotation of the front (f) face.
     *
     * This method rotates the front face counterclockwise.
     */
    void fp();

    /** \brief Perform a double rotation of the front (f) face.
     *
     * This method rotates the front face twice; the direction in this case
     * does not matter as both a double clockwise or counterclockwise rotation
     * results in the same state.
     */
    void ff();

    void F();
    void Fp();
    void FF();

    /********************************************************************/
    /*********************** Right face methods. ************************/
    /********************************************************************/

    /** \brief Perform a clockwise rotation of the right (r) face.
     *
     * This method rotates the right face clockwise.
     */
    void r();

    /** \brief Perform a counterclockwise rotation of the right (r) face.
     *
     * This method rotates the right face counterclockwise.
     */
    void rp();

    /** \brief Perform a double rotation of the right (r) face.
     *
     * This method rotates the right face twice; the direction in this case
     * does not matter as both a double clockwise or counterclockwise rotation
     * results in the same state.
     */
    void rr();

    void R();
    void Rp();
    void RR();

    /********************************************************************/
    /************************ Back face methods. ************************/
    /********************************************************************/

    /** \brief Perform a clockwise rotation of the back (b) face.
     *
     * This method rotates the back face clockwise.
     */
    void b();

    /** \brief Perform a counterclockwise rotation of the back (b) face.
     *
     * This method rotates the back face counterclockwise.
     */
    void bp();

    /** \brief Perform a double rotation of the back (b) face.
     *
     * This method rotates the back face twice; the direction in this case
     * does not matter as both a double clockwise or counterclockwise rotation
     * results in the same state.
     */
    void bb();

    void B();
    void Bp();
    void BB();

    /********************************************************************/
    /************************ Left face methods. ************************/
    /********************************************************************/

    /** \brief Perform a clockwise rotation of the left (l) face.
     *
     * This method rotates the left face clockwise.
     */
    void l();

    /** \brief Perform a counterclockwise rotation of the left (l) face.
     *
     * This method rotates the left face counterclockwise.
     */
    void lp();

    /** \brief Perform a double rotation of the left (l) face.
     *
     * This method rotates the left face twice; the direction in this case does
     * not matter as both a double clockwise or counterclockwise rotation
     * results in the same state.
     */
    void ll();

    void L();
    void Lp();
    void LL();

    /********************************************************************/
    /************************ Down face methods. ************************/
    /********************************************************************/

    /** \brief Perform a clockwise rotation of the down (d) face.
     *
     * This method rotates the bottom/down face clockwise.
     */
    void d();

    /** \brief Perform a counterclockwise rotation of the down (d) face.
     *
     * This method rotates the bottom/down face counterclockwise.
     */
    void dp();

    /** \brief Perform a double rotation of the down (d) face.
     *
     * This method rotates the bottom/down face twice; the direction in this
     * case does not matter as both a double clockwise or counterclockwise
     * rotation results in the same state.
     */
    void dd();

    void D();
    void Dp();
    void DD();

    /********************************************************************/
    /*********************** Middle slice methods ***********************/
    /********************************************************************/

    /** \brief Perform a clockwise rotation of the horizontal middle (mh)
     *         slice.
     *
     * This method rotates the horizontal middle slice clockwise.
     */
    void mh();

    /** \brief Perform a counterclockwise rotation of the horizontal middle
     *         (mh) slice.
     *
     * This method rotates the horizontal middle slice counterclockwise.
     */
    void mph();

    /** \brief Perform a double rotation of the horizontal middle (mh) slice.
     *
     * This method rotates the horizontal middle slice twice; the direction in
     * this case does not matter as both a double clockwise or counterclockwise
     * rotation results in the same state.
     */
    void mmh();

    /** \brief Perform a clockwise rotation of the vertical middle (m) slice.
     *
     * This method rotates the vertical middle slice clockwise.
     */
    void mv();

    /** \brief Perform a counterclockwise rotation of the vertical middle (m)
     *         slice.
     *
     * This method rotates the vertical middle slice counterclockwise.
     */
    void mpv();

    /** \brief Perform a double rotation of the vertical middle (m) slice.
     *
     * This method rotates the vertical middle slice twice; the direction in
     * this case does not matter as both a double clockwise or counterclockwise
     * rotation results in the same state.
     */
    void mmv();
};
