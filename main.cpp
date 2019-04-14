#include "memory_struct.h"
#include "march_tests.h"
#include "tester.h"
#include <iostream>
#include <map>
#include <vector>
#include <cassert>
/* Description : Initialiazing the memory array(1 bit, 10 location). 
 * '0' : bit zero 
 * '1' : bit one 
 * '2' : Dont'Care 
 */    
int main(int argc,char* argv[]) {
    std::string file_name = "march_tests.txt";
    std::map<std::string,march::Test*> test_map;
    build_tests(file_name,test_map);
    Memory_Array Test_Mem;
    run_test("MATS",Test_Mem); 
    return 0;
}

