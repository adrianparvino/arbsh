//Main.cpp
#include <iostream>
#include "TST.h"
 
int main(int argc, char** argv) {
  
 TSTNode *root = NULL;
 root = Insert(root, "boats");
 root = Insert(root, "boat");
 root = Insert(root, "bat");
 root = Insert(root, "bats");
 root = Insert(root, "stages");
 
 PrintAllStringsInTST(root);
 std::cout << "Maximum length string in this TST is of size "<< MaxLenStringLen(root) << std::endl;
 
 char *str = "hello";
 char *str1 = "bat";
 
 if (SearchTST(root, str) == false)
  std::cout << "\""<<str<<"\" not found in TST" << std::endl;
 else
  std::cout << "\"" << str << "\" is present in TST" << std::endl;
 
 if (SearchTST(root, str1) == false)
  std::cout << "\"" << str << "\" not found in TST" << std::endl;
 else
  std::cout << "\"" << str1 << "\" is present in TST" << std::endl;
 
 DeleteTST(root);
 
#ifdef DEBUG_PROGRAM_MEMORY
 CheckTSTMem();
#endif
  
 return 0;
}
