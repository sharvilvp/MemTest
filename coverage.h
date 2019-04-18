#ifndef _COVERAGE_H_
#define _COVERAGE_H_ 
#include "memory_defines.h"
namespace Memory {
    class coverage {
        private:
            int count_stuck_at_faults=0;
            int count_transition_faults=0;
            int count_inversion_faults=0;
            int count_idempotent_faults=0;
            int count_state_faults=0;
            int count_disturb_faults=0;
        public:
           void add_data(std::string instance_name);
           void calculate_coverage();
           void print_coverage();
    };
} 
#endif
