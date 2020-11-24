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
     */
    std::vector<std::vector<char>> state;

  public:

    /** \brief Default constructor.
     * Default constructor is default.
     */
    Cube();

    /** \brief Default destructor.
     * Default destructor is default.
     */
    virtual ~Cube();

    void Print();

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
    /* Up face methods. */
    void u();
    void up();
    void uu();

    void U();
    void Up();
    void UU();

    /* Front face methods. */
    void f();
    void fp();
    void ff();

    void F();
    void Fp();
    void FF();

    /* Right face methods. */
    void r();
    void rp();
    void rr();

    void R();
    void Rp();
    void RR();

    /* Back face methods. */
    void b();
    void bp();
    void bb();

    void B();
    void Bp();
    void BB();

    /* Left face methods. */
    void l();
    void lp();
    void ll();

    void L();
    void Lp();
    void LL();

    /* Down face methods. */
    void d();
    void dp();
    void dd();

    void D();
    void Dp();
    void DD();
};
