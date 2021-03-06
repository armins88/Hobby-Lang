// Executables must have the following defined if the library contains
// doctest definitions. For builds with this disabled, e.g. code shipped to
// users, this can be left out.
#ifdef ENABLE_DOCTEST_IN_LIBRARY
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
#endif

#include <iostream>
#include <stdlib.h>
#include <string>

#include "exampleConfig.h"
#include "example.h"
#include "interperter.h"

using namespace std;

/*
 * Simple main program that demontrates how access
 * CMake definitions (here the version number) from source code.
 */
int main()
{
  std::cout << "HobbyLang v"
            << PROJECT_VERSION_MAJOR
            << "."
            << PROJECT_VERSION_MINOR
            << "."
            << PROJECT_VERSION_PATCH
            << "."
            << PROJECT_VERSION_TWEAK
            << endl;

  // while(1){
  string text = "BEGIN;"
                "number := 5 * 10 ;"
                "x := number;"
                "a := number;"
                "b := 10 * a + 10 * number / 4;"
                "c := a - - b;"
                "END;"
                "x := 11;"
                "END.";

  text = "PROGRAM;"
         "VAR;"
        //  "a, b : INTEGER;"
        //  "y    : REAL;"

         "BEGIN;"
        //  "a := 23 + 2;"
        //  "b := 4 * 4;"
         "c := 3.14;"
         //"b := 10 * a + 10 * a / 4;"
         //"y := 20 / 7 + 3.14;"
         "END.";
      // getline (cin, text);

  Lexer lexer(text);
  Parser parser(lexer);
  Interperter interperter(lexer);
  interperter.interpert();
  interperter.printGlobalScope();

  //cout << interperter.interpert() << endl;
  // if(lexer.getError())break;
  // }
  return 1;
}
