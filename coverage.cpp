#include <string>
#include <iostream>
#include "coverage.h"
void Memory::coverage::add_data(std::string instance_name) {

    if(instance_name.find("SA") != std::string::npos) 
        count_stuck_at_faults++;
 
    else if(instance_name.find("CFIN") != std::string::npos) 
        count_inversion_faults++;
      
    else if(instance_name.find("CFID") != std::string::npos) 
        count_idempotent_faults++;

    else if(instance_name.find("TF") != std::string::npos)
        count_transition_faults++;

    else if(instance_name.find("CFST") != std::string::npos)
        count_state_faults++;
       
    else if(instance_name.find("CFDS") != std::string::npos)
        count_disturb_faults++;
}

void Memory::coverage::print_coverage() {
    std::cout<<"Stuck At Fault Coverage "<<count_stuck_at_faults<<std::endl;
    std::cout<<"Transition Fault Coverage "<<count_transition_faults<<std::endl;
    std::cout<<"Inversion Fault Coverage "<<count_inversion_faults<<std::endl;
    std::cout<<"Idempotent Fault Coverage "<<count_idempotent_faults<<std::endl;
    std::cout<<"State Fault Coverage "<<count_state_faults<<std::endl;
    std::cout<<"Disturb Fault Coverage "<<count_disturb_faults<<std::endl;
}
