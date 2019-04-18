#ifndef _FAULT_H_
#define _FAULT_H_ 
#include <iostream>
#include "memory_defines.h" 
#include "memory_struct.h"
namespace Memory {
    class fault {
        private :
            std::vector<fault_t> fault_list;
        public :
            void create_fault_list (std::vector<fault_t> _fault_list) {
                fault_list = _fault_list;
            }
            std::vector<fault_t> get_fault_list () {
                return fault_list; 
            }
                
            void generate_fault_instances(std::vector<fault_t> fault_list,std::vector<Test_Mem> mem_list);  
                 
    };   
}
#endif
