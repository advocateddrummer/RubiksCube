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
     *            * 13 = m (middle face)
     * \param[in] direction [defaults to 1] direction to rotate the face as
     *            follows:
     *            * 1  = one rotation clockwise
     *            * -1 = one rotation counterclockwise
     *            * 2  = rotate face twice
     *
     */
    void RotateFace(const int faceID, const int direction = 1);

  public:

    /** \brief Default constructor.
     * Default constructor is default.
     */
    Cube();

    /** \brief Default destructor.
     * Default destructor is default.
     */
    virtual ~Cube();

    /** \brief Print cube state.
     * This method simply prints out the current cube state, as represented by
     * the internal 'state' vector variable.
     */
    void Print();

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
    void f();
    void fp();
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

    /** \brief Perform a double rotation of the right (u) face.
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
    void b();
    void bp();
    void bb();

    void B();
    void Bp();
    void BB();

    /********************************************************************/
    /************************ Left face methods. ************************/
    /********************************************************************/
    void l();
    void lp();
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
};
