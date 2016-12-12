#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main(int argc, char *argv[]){
   if(argc != 3) {
     std::cerr << "argment is not satisfied." << std::endl;
     return 1;
   }
   std::vector<uint8_t> degs;

   std::ifstream ifs1(argv[2]);
   std::string str;

   if (ifs1.fail()){
       return false;
   }
   int i=0;
   while (getline(ifs1, str))
   {
     std::string::size_type index = str.find("#");
     if (index != std::string::npos)
       str = str.substr(0, index);
     degs.push_back(atoi(str.c_str()));
     i++;
   }

   std::ifstream ifs2(argv[1]);

   if (ifs2.fail()){
       return false;
   }
   int j=0;
   while (getline(ifs2, str))
   {
     std::string::size_type index = str.find("#");
     if (index != std::string::npos)
       str = str.substr(0, index);
     std::cout << degs[j] - atoi(str.c_str()) << std::endl;
     j++;
   }
   if(i != j)
    std::cout << "Line number mismatch!" << std::endl;
 }
