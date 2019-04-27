#include <fstream>
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <tuple>
#include "memory_struct.h"
#include "march_tests.h"
//#include "fault.h"
using namespace Memory;     
void build_tests(std::string file_name, std::map<std::string,march::Test*>& test_map) {
    std::ifstream testfile (file_name);
    std::string test_name;
    std::string word;
    int i=0;
    while(testfile>>word) {
            std::transform(word.begin(),word.end(),word.begin(),::tolower);
            std::string temp;
            march::Test* t;
            if(word == "test") {
                testfile>>test_name;
                t = march::Test::getTestInstance(test_name);
                test_map[test_name] = t;
                t->name(test_name);
            }
            if(word == "{") {
                std::string element_name;
                testfile>>element_name;
                testfile>>temp;
                if(temp == "INC")
                    t->march_order(element_name,INC);
                else if(temp == "DEC")
                    t->march_order(element_name,DEC);
                else if(temp == "ANY")
                    t->march_order(element_name,ANY);
                else
                    assert(0);
                testfile>>temp;
                if(temp == "{") {
                    march_element_t element;
                    std::tuple<op_t,int> op;
                    testfile>>temp;
                    while(temp != "}") {
                        if(temp == "R0") {
                            op = std::make_tuple(R,0);
                            element.push_back(op);
                        }
                        else if(temp == "R1") {
                            op = std::make_tuple(R,1);
                            element.push_back(op);
                        }
                        else if(temp == "W0") {
                            op = std::make_tuple(W,0);
                            element.push_back(op);
                        }
                        else if(temp == "W1") {
                            op = std::make_tuple(W,1);
                            element.push_back(op);
                        }
                        else if(temp == "NOP") {
                            op = std::make_tuple(NOP,2);
                            element.push_back(op);
                        }
                        else {
                            assert(0);
                        }
                        testfile >> temp;
                   }
                   t->march_element(element_name,element);
               }
           }
       }
                
       
 }

bool run_increasing(march_element_t element,Memory::Memory_Array& Test_Mem,std::vector<int>& result_vec) {
    for(uint32_t i=0;i<Test_Mem.mem_size;i++) {
        for(auto t_op : element) {
            auto op = std::get<0>(t_op); 
            auto val = std::get<1>(t_op);
            if(op == W) 
                Test_Mem.write_mem(i,val);
            if(op == R) {
                auto read_val = Test_Mem.read_mem(i);
                if(read_val != val) { 
                    return false;
                }
            }

        }
    }
    return true;
}

bool run_decreasing(march_element_t element,Memory::Memory_Array& Test_Mem,std::vector<int>& result_vec) {
   for(int i=Test_Mem.mem_size-1;i>=0;i--) {
        for(auto t_op : element) {
            auto op = std::get<0>(t_op); 
            auto val = std::get<1>(t_op);
            if(op == W) 
                Test_Mem.write_mem(i,val);
            if(op == R) {
                auto read_val = Test_Mem.read_mem(i);
                if(read_val != val) {
                    return false;
                }
            }   

        }
    }
    return true;
}

bool run_test(std::string _test_name, Memory::Memory_Array& Test_Mem) {
    march::Test* test;
    test = march::Test::getTest(_test_name); 
    assert(test != nullptr);
    auto test_order = test->march_order();
    auto test_element  = test->march_element(); 
    std::vector<int> result_vec;
    bool result;
    for(auto march_element : test_order) {
        switch(march_element.second) {
            case INC : result = run_increasing(test_element[march_element.first],Test_Mem,result_vec); 
                       break;
            case DEC : result = run_decreasing(test_element[march_element.first],Test_Mem,result_vec); 
                       break;
            case ANY : result = run_increasing(test_element[march_element.first],Test_Mem,result_vec); 
                       break;
        }
        if(result == false) {
            return false;
        }
    }
    return true;
    //test->print_march_map();
}    

void generate_single_cell_faults(std::vector<fault_t> fault_list,std::map<std::string,Memory::Memory_Array>& instance_map,uint32_t mem_size) {
    std::string instance_name;
    for(auto fault : fault_list) {
        for(int i=0;i<mem_size;i++) {
            Memory::Memory_Array Test_Mem(mem_size);
            switch(fault) {
                case SA0 : Test_Mem.inject_stuck_at_fault(i,0);
                           instance_name = "SA0" + std::to_string(i);
                           instance_map[instance_name] = Test_Mem;
                           break;
                case SA1 : Test_Mem.inject_stuck_at_fault(i,1);
                           instance_name = "SA1" + std::to_string(i);
                           instance_map[instance_name] = Test_Mem;
                           break;
                case TFLH : Test_Mem.inject_stuck_at_fault(i,low2high);
                            instance_name = "TFLH" + std::to_string(i);
                           instance_map[instance_name] = Test_Mem;
                           break;
                case TFHL : Test_Mem.inject_transition_fault(i,high2low);
                            instance_name = "TFHL" + std::to_string(i);
                           instance_map[instance_name] = Test_Mem;
                           break;
            }
        }
    }
}

void rotate_left(std::vector<int>& address_list) {
       int temp = address_list[0];
       int i;
       for(i=0;i<address_list.size()-1;i++) 
           address_list[i] = address_list[i+1];
       address_list[i] = temp;
}
void generate_coupled_faults(std::vector<fault_t> fault_list, std::map<std::string,Memory::Memory_Array>& instance_map,uint32_t mem_size) {
    std::string instance_name;
    std::vector<int> agg_vic_list;

    for(int i=0;i<mem_size;i++) {
        agg_vic_list.push_back(i);
    }

     
    for(auto fault : fault_list) {
        switch(fault) {
            case CFINLH : for(int i=0;i<mem_size;i++) {
                            Memory::Memory_Array Test_Mem(mem_size);
                            Test_Mem.inject_inversion_fault(agg_vic_list[0],agg_vic_list[mem_size-1],low2high);
                            instance_name = "CFINLHV" + std::to_string(agg_vic_list[0]) + "A" + std::to_string(agg_vic_list[mem_size-1]);
                            instance_map[instance_name] = Test_Mem;
                            rotate_left(agg_vic_list);
                          } 
                          break;
            case CFINHL : for(int i=0;i<mem_size;i++) {
                            Memory::Memory_Array Test_Mem(mem_size);
                            Test_Mem.inject_inversion_fault(agg_vic_list[0],agg_vic_list[mem_size-1],high2low);
                            instance_name = "CFINHLV" + std::to_string(agg_vic_list[0]) + "A" + std::to_string(agg_vic_list[mem_size-1]);
                            instance_map[instance_name] = Test_Mem;
                            rotate_left(agg_vic_list);
                          }
                          break; 
            case CFIDLH0 : for(int i=0;i<mem_size;i++) {
                            Memory::Memory_Array Test_Mem(mem_size);
                            Test_Mem.inject_idempotent_fault(agg_vic_list[0],agg_vic_list[mem_size-1],low2high,0);
                            instance_name = "CFIDLH0V" + std::to_string(agg_vic_list[0]) + "A" + std::to_string(agg_vic_list[mem_size-1]);
                            instance_map[instance_name] = Test_Mem;
                            rotate_left(agg_vic_list);
                          }
                          break; 
            case CFIDLH1 : for(int i=0;i<mem_size;i++) {
                            Memory::Memory_Array Test_Mem(mem_size);
                            Test_Mem.inject_idempotent_fault(agg_vic_list[0],agg_vic_list[mem_size-1],low2high,1);
                            instance_name = "CFIDLH1V" + std::to_string(agg_vic_list[0]) + "A" + std::to_string(agg_vic_list[mem_size-1]);
                            instance_map[instance_name] = Test_Mem;
                            rotate_left(agg_vic_list);
                          }
                          break; 
            case CFIDHL0 : for(int i=0;i<mem_size;i++) {
                            Memory::Memory_Array Test_Mem(mem_size);
                            Test_Mem.inject_idempotent_fault(agg_vic_list[0],agg_vic_list[mem_size-1],high2low,0);
                            instance_name = "CFIDHL0V" + std::to_string(agg_vic_list[0]) + "A" + std::to_string(agg_vic_list[mem_size-1]);
                            instance_map[instance_name] = Test_Mem;
                            rotate_left(agg_vic_list);
                          }
                          break; 
            case CFIDHL1 : for(int i=0;i<mem_size;i++) {
                            Memory::Memory_Array Test_Mem(mem_size);
                            Test_Mem.inject_idempotent_fault(agg_vic_list[0],agg_vic_list[mem_size-1],high2low,1);
                            instance_name = "CFIDHL1V" + std::to_string(agg_vic_list[0]) + "A" + std::to_string(agg_vic_list[mem_size-1]);
                            instance_map[instance_name] = Test_Mem;
                            rotate_left(agg_vic_list);
                          }
                          break; 
            case CFST00 : for(int i=0;i<mem_size;i++) {
                            Memory::Memory_Array Test_Mem(mem_size);
                            Test_Mem.inject_state_fault(agg_vic_list[0],agg_vic_list[mem_size-1],0,0);
                            instance_name = "CFST00V" + std::to_string(agg_vic_list[0]) + "A" + std::to_string(agg_vic_list[mem_size-1]);
                            instance_map[instance_name] = Test_Mem;
                            rotate_left(agg_vic_list);
                          }
                          break; 
            case CFST01 : for(int i=0;i<mem_size;i++) {
                            Memory::Memory_Array Test_Mem(mem_size);
                            Test_Mem.inject_state_fault(agg_vic_list[0],agg_vic_list[mem_size-1],0,1);
                            instance_name = "CFST01V" + std::to_string(agg_vic_list[0]) + "A" + std::to_string(agg_vic_list[mem_size-1]);
                            instance_map[instance_name] = Test_Mem;
                            rotate_left(agg_vic_list);
                          }
                          break; 
            case CFST10 : for(int i=0;i<mem_size;i++) {
                            Memory::Memory_Array Test_Mem(mem_size);
                            Test_Mem.inject_state_fault(agg_vic_list[0],agg_vic_list[mem_size-1],1,0);
                            instance_name = "CFST10V" + std::to_string(agg_vic_list[0]) + "A" + std::to_string(agg_vic_list[mem_size-1]);
                            instance_map[instance_name] = Test_Mem;
                            rotate_left(agg_vic_list);
                          }
                          break; 
            case CFST11 : for(int i=0;i<mem_size;i++) {
                            Memory::Memory_Array Test_Mem(mem_size);
                            Test_Mem.inject_state_fault(agg_vic_list[0],agg_vic_list[mem_size-1],1,1);
                            instance_name = "CFST11V" + std::to_string(agg_vic_list[0]) + "A" + std::to_string(agg_vic_list[mem_size-1]);
                            instance_map[instance_name] = Test_Mem;
                            rotate_left(agg_vic_list);
                          }
            
        }
    }
}    
          
//int main() {
//    std::string file_name = "march_tests.txt";
//    std::map<std::string,march::Test*> test_map;
//    read_file(file_name,test_map);
//    test_map["MATS"]->print_march_map();
//    test_map["MARCHC"]->print_march_map();
//    test_map["MARCHC"]->print_multiton_map();
//    Memory_Array Test_Mem;
//    test_map["MATS"]->run_tests("MATS",Test_Mem); 
//    return 0;
//}
        
