#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

std::string dataDir; // Define a global variable

// https://github.com/catchorg/Catch2/blob/devel/docs/own-main.md#adding-your-own-command-line-options
int main( int argc, char* argv[] ) {
  Catch::Session session; // There must be exactly one instance

  // Build a new parser on top of Catch2's
  using namespace Catch::clara;
  auto cli
    = session.cli()              // Get Catch2's command line parser
    | Opt( dataDir, "dataDir" ) // bind variable to a new option, with a hint string
        ["-dd"]["--dataDir"]    // the option names it will respond to
        ("directory for data files");        // description string for the help output

  // Now pass the new composite back to Catch2 so it uses that
  session.cli( cli );

  // Let Catch2 (using Clara) parse the command line
  int returnCode = session.applyCommandLine( argc, argv );
  if( returnCode != 0 ) // Indicates a command line error
      return returnCode;
 
  return session.run();
}