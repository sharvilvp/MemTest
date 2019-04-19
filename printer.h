#include<iostream>
#include<fstream>
#include "coverage.h"
void print_header(std::ofstream& march_result) {
    march_result<<"=========================================================================="<<std::endl;
    march_result<<"                             MARCH TESTS REPORT                           "<<std::endl;
    march_result<<"=========================================================================="<<std::endl;
    march_result<<"MEMORY SIZE : "<<MEM_SIZE<< " bits "<<std::endl;
    march_result<<"=========================================================================="<<std::endl;
    march_result<<std::setw(10)<<std::left<<"TEST";
    march_result<<std::setw(10)<<std::left<<"SA";
    march_result<<std::setw(10)<<std::left<<"TF";
    march_result<<std::setw(10)<<std::left<<"CFIN";
    march_result<<std::setw(10)<<std::left<<"CFID";
    march_result<<std::setw(10)<<std::left<<"CFST";
    march_result<<std::setw(10)<<std::left<<"CFDS"<<std::endl;
}

void print_body(std::ofstream& march_result,  Memory::coverage& cover_fault, std::string test_name) {
    march_result<<std::setw(10)<<std::left<<test_name;
    march_result<<std::setw(10)<<std::left<<std::to_string(cover_fault.coverage_stuck_at_faults)+"%";
    march_result<<std::setw(10)<<std::left<<std::to_string(cover_fault.coverage_transition_faults)+"%";
    march_result<<std::setw(10)<<std::left<<std::to_string(cover_fault.coverage_inversion_faults)+"%";
    march_result<<std::setw(10)<<std::left<<std::to_string(cover_fault.coverage_idempotent_faults)+"%";
    march_result<<std::setw(10)<<std::left<<std::to_string(cover_fault.coverage_state_faults)+"%";
    march_result<<std::setw(10)<<std::left<<std::to_string(cover_fault.coverage_disturb_faults)+"%"<<std::endl;
}
