#include <fstream>
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <tuple>
#include "memory_struct.h"
#include "march_tests.h"
#include "fault.h"
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

void run_increasing(march_element_t element,Memory::Memory_Array& Test_Mem) {
   for(uint32_t i=0;i<MEM_SIZE;i++) {
        for(auto t_op : element) {
            auto op = std::get<0>(t_op); 
            auto val = std::get<1>(t_op);
            if(op == W) 
                Test_Mem.write_mem(i,val);
            if(op == R)
                auto read_val = Test_Mem.read_mem(i);

        }
    }
}

void run_decreasing(march_element_t element,Memory::Memory_Array& Test_Mem) {
   for(uint32_t i=MEM_SIZE-1;i>0;i--) {
        for(auto t_op : element) {
            auto op = std::get<0>(t_op); 
            auto val = std::get<1>(t_op);
            if(op == W) 
                Test_Mem.write_mem(i,val);
            if(op == R)
                auto read_val = Test_Mem.read_mem(i);

        }
    }
}

void run_test(std::string _test_name, Memory::Memory_Array& Test_Mem) {
    march::Test* test;
    test = march::Test::getTest(_test_name); 
    assert(test != nullptr);
    std::cout<<"Running Test "<<test->name()<<std::endl;
    auto test_order = test->march_order();
    auto test_element  = test->march_element();
    for(auto march_element : test_order) {
        switch(march_element.second) {
            case INC : run_increasing(test_element[march_element.first],Test_Mem);
            case DEC : run_decreasing(test_element[march_element.first],Test_Mem);
            case ANY : run_increasing(test_element[march_element.first],Test_Mem);
        }
    }
}    

void check_instance(uint32_t cell_under_test, Memory::Memory_Array& Test_Mem, Memory::fault mem_fault);
    {
        fau
        
    

          
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
        
