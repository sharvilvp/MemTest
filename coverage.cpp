#include <string>
#include <iostream>
#include "coverage.h"
void Memory::coverage::add_data(std::string instance_name, bool result) {

    if(instance_name.find("SA") != std::string::npos) {
        total_stuck_at_faults++;
        if(!result) 
        count_stuck_at_faults++;
    }
 
    else if(instance_name.find("CFIN") != std::string::npos) {
        total_inversion_faults++;
        if(!result)
        count_inversion_faults++;
    }

    else if(instance_name.find("CFID") != std::string::npos) {
        total_idempotent_faults++;
        if(!result)
        count_idempotent_faults++;
    }

    else if(instance_name.find("TF") != std::string::npos) {
        total_transition_faults++;
        if(!result)
        count_transition_faults++;
    }

    else if(instance_name.find("CFST") != std::string::npos) {
        total_state_faults++;
        if(!result)
        count_state_faults++;
    }
       
    else if(instance_name.find("CFDS") != std::string::npos) {
        total_disturb_faults++;
        if(!result)
        count_disturb_faults++;
    }
}

void Memory::coverage::calculate_coverage() {
    if(total_stuck_at_faults != 0) 
        coverage_stuck_at_faults = static_cast<float>(count_stuck_at_faults)/total_stuck_at_faults;
    
    if(total_transition_faults != 0) 
        coverage_transition_faults = static_cast<float>(count_transition_faults)/total_transition_faults;
    
    if(total_inversion_faults != 0) 
        coverage_inversion_faults = static_cast<float>(count_inversion_faults)/total_inversion_faults;
    
    if(total_idempotent_faults != 0) 
        coverage_idempotent_faults = static_cast<float>(count_idempotent_faults)/total_idempotent_faults;
    
    if(total_state_faults != 0) 
        coverage_state_faults = static_cast<float>(count_state_faults)/total_state_faults;
    

    if(total_disturb_faults != 0) 
        coverage_disturb_faults = static_cast<float>(count_disturb_faults)/total_disturb_faults;
        
}

void Memory::coverage::print_coverage() {
    float a = static_cast<float>(4/8);
    std::cout<<a<<std::endl;
    std::cout<<"Stuck At Fault Coverage "<<coverage_stuck_at_faults*100<<std::endl;
    std::cout<<"Transition Fault Coverage "<<coverage_transition_faults*100<<std::endl;
    std::cout<<"Inversion Fault Coverage "<<coverage_inversion_faults*100<<std::endl;
    std::cout<<"Idempotent Fault Coverage "<<coverage_idempotent_faults*100<<std::endl;
    std::cout<<"State Fault Coverage "<<coverage_state_faults*100<<std::endl;
    std::cout<<"Disturb Fault Coverage "<<coverage_disturb_faults*100<<std::endl;
}
