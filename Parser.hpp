#ifndef parser
  #define parser
  #ifndef MAX_STRING_LENGTH
    #define MAX_STRING_LENGTH 100
  #endif
  #ifndef LIBS
    #define LIBS
  #endif
  #include "HTMLTag.hpp";
  #include <iostream>
  #include <string>
  #include <cstring>
  #include <assert.h>

void parseFile(std::string inFile){ 
  char line[MAX_STRING_LENGTH]; 
  std::ifstream file;
  const char* delimiters = " ";
  file.open(inFile); 
  assert(file.is_open() && "unable to open file" ); 
  while(!file.eof()){
    file.getline(line,MAX_STRING_LENGTH,'\n');
    std::cout <<"procesing line " << line; 
    char *token = std::strtok(line, delimiters);
    //std::cout<< "element : "<< token; 
    int x = 1; 
    while (token) {
      if(x == 1){ 
        }
      std::cout <<'\n'<<token;  
      token = std::strtok(nullptr, delimiters);
      x++;    
    }
    std::cout<<'\n'; 
  }
} 
#endif
