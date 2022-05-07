#ifndef parser
  #define parser
  #define LIBS
  #include "HTMLTag.hpp";
  #include <iostream>
  #include <string>
  #include <cstring>
namespace Parser{ 
  Tag ParseLine(char line[]){ 
    char* token = std::strtok(line, " ");
    std::string content;
    std::string element;
    std::string classes;
    std::string id;
    int x = 1; 
    
    while (token) {
    
      if(x == 1){ 
          element = token; 
      }else if( token[0] == '.' || token[0] == '#'){
        char* m = (token+sizeof(char));
        if(token[0] == '.'){
            if(classes != "\0"){ 
              classes+= " "; 
            }
            classes+= m;
          }else{ 
            id = m; 
          }
      }
     token = std::strtok(nullptr, " ");
      x++;    
    }
    #ifdef DEBUG 
    printf("el : %s, id : %s, classes: %s, content: %s\n",element.c_str(), id.c_str(), classes.c_str(), content.c_str());
    #endif
    return Tag(element,id).AddClass(classes).SetContent(content);
  
  } 
}
#endif
