#include <fstream>

#include <boost/program_options.hpp>
namespace po = boost::program_options;

#include "CubeParams.hpp"

CubeParams::CubeParams()
{
  explain = false; /**< By default, do not explain nomenclature. */
  verbose = 0;
}

CubeParams::CubeParams(const int argc, char * argv[])
{
  std::cout << "Parsing parameters..." << std::endl;

  try {
    std::string configFile;

    /* Declare a group of generic options that are allowed only on the command line. */
    po::options_description generic("Generic options");
    generic.add_options()
      ("help,h",                                         "produce help message.")
      ("version,V",                                      "print version string.")
      ("config,c",  po::value<std::string>(&configFile), "name of a configuration file.")
      //("config,c",  po::value<std::string>(&configFile)->default_value("rc.cfg"), "name of a configuration file.")
      ;

    /*
     * Declare a group of generic options that will be allowed both on the
     * command line and in a configuration file.
     */
    po::options_description config("Configuration");
    config.add_options()
      ("verbose,v", po::value<int>(&verbose)->default_value(0),      "verbosity level.")
      ("explain,e", po::bool_switch(&explain)->default_value(false), "explain RubiksCube nomenclature.")
      ;

    /*
     * These are the options that are visible to the user; they are only used
     * to print the help message.
     */
    po::options_description visible;
    visible.add(generic).add(config);

    /* These are the options that are valid on the command line. */
    po::options_description cmdLineOptions;
    cmdLineOptions.add(generic).add(config);

    /* These are the options that are valid in a configuration file. */
    po::options_description configFileOptions;
    configFileOptions.add(config);

    /* Parse the command line. */
    po::variables_map vm;
    store(po::parse_command_line(argc, argv, visible), vm);

    /* Handle generic options. */
    if (vm.count("help")) {
      /* Print help message. */
      std::cout << visible << "\n";
      exit(EXIT_SUCCESS);
    }

    if (vm.count("version")) {
      /* Print version information. */
      std::cout << "RubiksCube: version " << VERSION << std::endl;
      exit(EXIT_SUCCESS);
    }

    /* Get configuration file name. */
    if (vm.count("config")) {
      configFile = vm["config"].as<std::string>();

      /*
       * Parse the configuration file if it has been specified and exists; this
       * must be done before calling notify in order to get any required
       * options specified in the configuration file.
       */
      std::ifstream configFileStream(configFile.c_str());
      if (!configFileStream) {
        std::cout << "Cannot locate configuration file: <" << configFile << ">" << std::endl;
      } else {
        std::cout << "Located configuration file: <" << configFile << ">" << std::endl;
        store(parse_config_file(configFileStream, configFileOptions), vm);
      }
    }

    /*
     * notify is called AFTER dealing with the --help/--version options and
     * parsing the configuration file so that the 'the option xxx is required
     * but missing' error is not reported.  Required options are not required
     * in these cases.
     */
    notify(vm);

    /* Report values. */
    std::cout << "\nRubiksCube Configurations:" << std::endl;
    std::cout << "Version:         " << VERSION << "\n";
    std::cout << "Verbosity level: " << verbose << "\n";
    std::cout << "Explain:         " << explain << "\n";

  }
  catch(std::exception & e) {
    std::cout << e.what() << "\n";
    exit(EXIT_FAILURE);
  }

  std::cout << "Parameter parsing complete." << std::endl;
}
