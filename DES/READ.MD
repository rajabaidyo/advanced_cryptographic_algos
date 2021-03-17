DATA ENCRYPTION STANDARD code in c++
-> consists of 3 files
  1) keygen.cpp -> contains the code for generating the 16 round keys
  2) des.cpp -> contains the driver code i.e the main algo code
  3) links.h -> consists of links between the above two files

To run the code... move all the files in a single folder and run the command

command => g++ -std=c++11 *.cpp -o t && ./t
