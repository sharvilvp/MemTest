#ifndef _COVERAGE_H_
#define _COVERAGE_H_ 
#include "memory_defines.h"
namespace Memory {
    class coverage {
        private:
            int count_stuck_at_faults=0;
            int total_stuck_at_faults=0;
            int count_transition_faults=0;
            int total_transition_faults=0;
            int count_inversion_faults=0;
            int total_inversion_faults=0;
            int count_idempotent_faults=0;
            int total_idempotent_faults=0;
            int count_state_faults=0;
            int total_state_faults=0;
            int count_disturb_faults=0;
            int total_disturb_faults=0;
        public:
            float coverage_stuck_at_faults; 
            float coverage_transition_faults; 
            float coverage_inversion_faults; 
            float coverage_idempotent_faults; 
            float coverage_state_faults; 
            float coverage_disturb_faults; 
            void add_data(std::string instance_name,bool result);
            void calculate_coverage();
            void print_coverage();
    };
} 
#endif
