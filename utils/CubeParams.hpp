#ifndef CUBEPARAMS_HPP
#define CUBEPARAMS_HPP

#include <iostream>

#include "Version.hpp"

/*! \class CubeParams CubeParams.hpp
 *  \brief This class handles all program command line options.
 */
class CubeParams
{
  private:
  public:

    /** \brief Default constructor.
     * Default constructor is default.
     */
    CubeParams();

    /** \brief Custom constructor.
     *
     * This constructor uses boost::program_options to parse input parameters
     * from the command line and/or a configuration file.
     *
     * \param[in] argc command line argument count, passed in from main.
     * \param[in] argv command line arguments, passed in from main.
     *
     */
    CubeParams(const int argc, char * argv[]);

    /** \brief Default destructor.
     * Default destructor is default.
     */
    ~CubeParams();

    int verbose; /**< Level of program verbosity. */
};

#endif /* end of include guard: CUBEPARAMS_HPP */
