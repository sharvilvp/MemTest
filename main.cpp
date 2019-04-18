#include "memory_struct.h"
#include "march_tests.h"
#include "tester.h"
#include "coverage.h"
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <cassert>
#include <type_traits>
/* Description : Initialiazing the memory array(1 bit, 10 location). 
 * '0' : bit zero 
 * '1' : bit one 
 * '2' : Dont'Care 
 */    
int main(int argc,char* argv[]) {
    std::string file_name = "march_tests.txt";
    std::string output_file = "report.txt";
    std::map<std::string,march::Test*> test_map;
    std::vector<fault_t> fault_list_1 = {SA0,SA1,TFLH,TFHL};
    std::vector<fault_t> fault_list_2 = {CFINHL,CFINLH,CFIDLH0,CFIDLH1};
    std::map<std::string,Memory::Memory_Array> instance_map;
    std::map<std::string,bool> result_map;
    Memory::coverage cover_fault;
    generate_single_cell_faults(fault_list_1,instance_map);
    generate_coupled_faults(fault_list_2,instance_map);
    build_tests(file_name,test_map);
    Memory::Memory_Array Test_Mem;
    run_test("MATS_PLUS",Test_Mem);
    for(auto instance : instance_map) {
        std::cout<<instance.first<<std::endl;
        result_map[instance.first] = run_test("MATS_PLUS",instance.second);
    }
    std::cout<<std::boolalpha;
    for(auto result : result_map) {
       if(!result.second)
       cover_fault.add_data(result.first); 
       std::cout<<result.first<<" : "<<result.second<<std::endl;
    }
    std::ofstream march_result;
    march_result.open(output_file);
    cover_fault.print_coverage(); 
    march_result<<"=========================================================================="<<std::endl;
    march_result<<"                             MARCH TESTS REPORT                           "<<std::endl;
    march_result<<"=========================================================================="<<std::endl;
    march_result<<"MEMORY SIZE : "<<MEM_SIZE<< " bits "<<std::endl;
    march_result<<"TEST     SA     TF    CFIN    CFID    CFST   CFDS" <<std::endl;
    march_result<<"=========================================================================="<<std::endl;
    march_result.close();  
    //Test_Mem.inject_stuck_at_fault(0,0);
    //run_test("MATS",Test_Mem); 
    //Test_Mem.print_mem_array();
    return 0;
}

