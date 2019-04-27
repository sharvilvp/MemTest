#include "memory_struct.h"
#include "march_tests.h"
#include "tester.h"
#include "coverage.h"
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <cassert>
#include <string>
#include <type_traits>
#include <iomanip>
#include "printer.h"
/* Description : Initialiazing the memory array(1 bit, 10 location). 
 * '0' : bit zero 
 * '1' : bit one 
 * '2' : Dont'Care 
 */    
int main(int argc,char* argv[]) {
    //Accept memory_size from the user.
    uint32_t mem_size;
    mem_size = std::stoul(argv[1],nullptr,10);
   
    //Accept Test name and test file from the user 
    //std::string test_name = argv[2];
    std::string file_name = "march_tests.txt";
    std::string output_file = "report.txt";
    std::string output_csv = "march_test.csv";
        
    //Create maps for Test_Name Verus Generated March Elements
    std::map<std::string,march::Test*> test_map;

    //FIXME : Create a single function for getting single and coupled fault lists 
    std::vector<fault_t> fault_list_1 = {SA0,SA1,TFLH,TFHL};
    std::vector<std::string> tests = {"MATS_PLUS","MARCHX","MARCH_1","MARCH_2","MATS++"};
    std::vector<fault_t> fault_list_2 = {CFINHL,CFINLH,CFIDLH0,CFIDLH1,CFIDHL0,CFIDHL1,CFST00,CFST01,CFST10,CFST11};

    //Generate Test Memory Instances.
    std::map<std::string,Memory::Memory_Array> instance_map;
    generate_single_cell_faults(fault_list_1,instance_map,mem_size);
    generate_coupled_faults(fault_list_2,instance_map,mem_size);
    
    std::map<std::string,std::map<std::string,bool>> output_map;
    
    //Build the test map
    build_tests(file_name,test_map);

    //Coverage object

    for(auto test_name : tests) {
        std::map<std::string,bool> result_map;
        for(auto instance : instance_map) {
            result_map[instance.first] = run_test(test_name,instance.second);
        }
        output_map[test_name] = result_map;
    }

    std::ofstream march_result;
    std::ofstream march_result_csv;
    march_result.open(output_file,std::ios_base::app);
    march_result_csv.open(output_csv,std::ios_base::app);
    print_header(march_result,mem_size);
    for(auto march_test : output_map) {
        Memory::coverage cover_fault;
        std::cout<<march_test.first<<std::endl;
        auto result_map = march_test.second; 
        for(auto result : result_map) {
                cover_fault.add_data(result.first,result.second); 
                std::cout<<result.first<<" : "<<result.second<<std::endl;
        }
        cover_fault.calculate_coverage();
        cover_fault.print_coverage(); 
        print_body(march_result,cover_fault,march_test.first);
        print_csv(march_result_csv,cover_fault,march_test.first);
            
    }
    march_result.close();  
    //Test_Mem.inject_stuck_at_fault(0,0);
    //run_test("MATS",Test_Mem); 
    //Test_Mem.print_mem_array();
    return 0;
}

