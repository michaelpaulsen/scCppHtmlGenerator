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
    return Tag(element,id).AddClass(classes).SetContent(content);
  
  } 
   void ParseFile(char* fn, Tag* outTag){ 
    Tag* currentElement = nullptr;
    int layer = 0; 
    std::ifstream fp; 
    fp.open(fn);
    char line[1000]; 
    while(fp.getline(line, 1000, '\n')){ 
      auto t = ParseLine(line);
      if(line[0] == '/' ){// if the line starts with a dash then close the tag. 
        if(currentElement->GetParentTag() != nullptr){ 
        // not having this if statment caused a huge bug in the code  
          currentElement = currentElement->GetParentTag();
        }else{ 
        printf("reached top level element %s\n",(currentElement->GetTagName()).c_str());  
        }
        layer--; 
        continue;  
      }
      if(layer++ == 0 ){ //if the element is the top level element
        //incrments layer every time the loop gets this far;  
        currentElement = &t;
        continue; 
      } 
      currentElement->AddTag_v(t); 
      currentElement = &t; 
    }
    fp.close();
     //memcpy(outTag,currentElement,sizeof(Tag)); 
    outTag = currentElement;
     if(outTag == nullptr ) printf("something whent wrong");
  }
}

#endif
