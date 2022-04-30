#ifndef parser
  #define parser
  #define LIBS
  #include "HTMLTag.hpp";
  #include <iostream>
  #include <string>
  #include <cstring>

Tag parseLine(char* line){ 
  std::cout <<"procesing line " << line; 
  char *token = std::strtok(line, delimiters);
  int x = 1; 
  while (token) {
    std::cout <<'\n'<<token;  
    token = std::strtok(nullptr, delimiters);
    x++;    
  }
  std::cout<<'\n';
  return Tag("tempRetVal","TEMPRETVAL");
} 
#endif
