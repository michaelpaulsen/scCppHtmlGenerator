#ifndef HTML_TAG
#define HTML_TAG
#include <string>
#include <iostream> 
#include <vector>  
#include <fstream>
std::string ToId(std::string s){
  std::string id;
  for(int x = 0; x< s.size(); x++){ 
    char cc = s[x]; 
    if(cc == ' ' && x != s.size()-1){ 
      id += '_'; 
    }else{ 
      id += toupper(cc);
    }
  }
  return id; 
}
class Tag{
  const std::string EmptyElements[10] = {
  "area",
  "base",
  "br",
  "hr",
  "img",
  "input",
  "link",
  "meta",
  "param",
  "col"
 }; 
  bool isEmptyTag(){ 
    /*area, base, br, col, hr, img, input, link, meta, and param.*/
   for(int x = 0; x<10; x++){ 
      if(this->tagName == Tag::EmptyElements[x]){
        return true; 
      }
     }
    return false; // this is faster by at least 1.5 times 
    //something about the compiler being smarter than me 
    //see: https://quick-bench.com/q/uPsblpoRZd1P86LtVqq_UMooMKA
  }
  void PrintClasses(std::ostream& out){ 
    if(!(this->classes.empty())){
      bool f = true; 
      out << " class =\"";
        for(auto& x : this->classes){ 
          if(!f ){ 
          out << ' '; 
          }
          out << x;
          f =false; 
        }
        out<<'"';
    }
  }
  void PrintAtrributes(std::ostream& out){
    for(auto& x : this->attributes){ 
      out <<' '<< x.first;
      if(x.second != "\0"){ 
        out<< " = \"" << x.second << "\" "; 
      }
    }
  }
  void PrintOpenTag(std::ostream& out,int count){
      
      for(int t = 0; t< count; t++) { out << '\t';}; 

      if(this->tagName != "\0"){
        out<< '<' << this->tagName; 
        
        if(Id != "\0"){ 
          out<<" id = \"" << Id << "\" "; 
        } 
        this->PrintClasses(out); 
        this->PrintAtrributes(out);
        if(this->isEmptyTag()){
          out << '/';
        }
        out<<'>';  
    }
  }
  void PrintCloseTag(std::ostream& out,int count){ 
    if(this->tagName != "\0" && !this->isEmptyTag()){  
      if(content.empty()){ 
        for(int t = 0; t< count; t++) {
          out << '\t';
        }
      }
      out<< "</" << this->tagName << '>';   
    }
    out << '\n'; 
  }
  //private members 
  std::vector<std::pair<std::string, std::string>> attributes;
  std::string Id;
  Tag* parentTag = nullptr; 
  //the HTML spesifcation says that an element can only have one id so this dosn't need to be a vector. 
std::vector<std::string> classes;
//this is a vector of classes these are printed as a space sperated list as per the spesifcation. 
  std::string tagName;
// this is a string that repersents the tag name. 
  std::string content; 
//the actuall content of the element [only printed if the element has no children]
  std::vector<Tag> childTags;
//the children of the tag 
public: 
  auto GetName(){ 
    return this->tagName; 
  }
  Tag(std::string tn, std::string id = "\0" ){
    tagName = tn;
    Id      = id;
    content = std::string(); 
  }
  void PrintTagChildren(std::ostream& out,int count = 0){ 
    out << '\n';
    for(auto& x : this->childTags){
      x.Print(out, count);   
    }
  }
  void PrintTagContent(std::ostream& out){ 
    out<< this->content; 
  }
  void Print(std::ostream& out = std::cout,int count = 0){ 
    if(this->GetParentTag() != nullptr){ //prevent dereferanceing nullptr seg faults 
    std::cout << "parent tag tagname " << (*GetParentTag()).GetName(); 
      }
    this->PrintOpenTag(out, count);
    
    if(!this->childTags.empty()){ 
      this->PrintTagChildren(out, ++count);
      }else{ 
      out << this->content; 
      }
    this->PrintCloseTag(out, --count); 
  }
  void SetParent(Tag* t ){
    this->parentTag = t;
  }
  Tag*  GetParentTag(){ 
      return this->parentTag; 
  }
  Tag  AddClass(std::string className){ 
    this->classes.push_back(className);
    return *this; 
  }
  Tag  AddAtribute(std::string attr, std::string attrVal = "\0"){ 
    this->attributes.push_back(std::make_pair(attr,attrVal));
    return *this;
  }
  Tag  AddTag(Tag ChildTag){
    auto t = ChildTag; 
    t.SetParent(this);
    this->childTags.push_back(t);
    return *this; 
  }
  Tag  SetContent(std::string c){
    this->content = c;
    return *this;
  }
  void AddTag_v(Tag ChildTag){ 
    auto t = ChildTag; 
    t.SetParent(this);
    this->childTags.push_back(t);
    printf("start of loop\n");
    for(auto &y :childTags){ 
      if(y != 0){ 
        printf("%p", &y);
      }else{ 
        printf("somthing whent wrong"); 
      }
    }
    printf("\nend of loop \n\n");
  }
  auto GetTagName(){
    return this->tagName; 
  }
};
//end of class Tag 

#ifdef LIBS
Tag MakeCssLink(std::string href){ 
  return Tag("link").AddAtribute("href", href).AddAtribute("rel","stylesheet"); 
  }
Tag MakePageTitle(std::string title){
  auto id = ToId(title);
  return Tag("Title", "PAGE_"+id).SetContent(title); 
}
Tag MakeHero(std::string imgSrc, std::string textEl, std::string textContent, std::string text_class ="\0", std::string image_class ="\0", std::string div_class="\0"){ 
  auto div = Tag("div").AddClass("HERO").AddClass(div_class);
  div.AddTag(Tag("img").AddClass("hero__img").AddClass(image_class).AddAtribute("src",imgSrc));
div.AddTag(Tag(textEl).AddClass("hero_Text").SetContent(textContent).AddClass(text_class)); 
  return div; 
}
Tag MakeFooter(std::string yearStart, std::string yearEnd, std::string name){ 
  std::string copystr = "&copy; " + yearStart +  " - " + yearEnd + " " + name + "all rights reserved"; 
  return Tag("footer","PAGE_FOOTER").AddTag(Tag("div").AddTag(Tag("p").SetContent(copystr).AddClass("small"))); 
}

const auto UTF8 =  Tag("meta").AddAtribute("charset", "UTF-8" );
const auto UTF16 = Tag("meta").AddAtribute("charset", "UTF-16" );
/*
It is very important to always label Web documents explicitly. HTTP 1.1 says that the default charset is ISO-8859-1. But there are too many unlabeled documents in other encodings, so browsers use the reader's preferred encoding when there is no explicit charset parameter. 
[https://www.w3.org/International/articles/http-charset/index#:~:text=It%20is%20very%20important%20to,is%20no%20explicit%20charset%20parameter.]
*/
const auto JQUERY = Tag("script").AddAtribute("src", "https://code.jquery.com/jquery-3.6.0.min.js").AddAtribute("integrity", "sha256-/xUj+3OJU5yExlq6GSYGSHk7tPXikynS7ogEvDej/m4=").AddAtribute("crossorigin", "anonymous");

#endif
#endif
