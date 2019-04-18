#ifndef _MEMORY_STRUCT_H_
#define _MEMORY_STRUCT_H_
#include <iostream>
#include "memory_defines.h"
#include <map>
#include <string>
namespace Memory{ 
class Memory_Cell {

    private :
	    uint32_t value;
        bool stuck_at_0 = false;
        bool stuck_at_1 = false;
        uint32_t transition_fault_value;

    public :
        //Cell Constructor/Destructors.
        Memory_Cell() : value(2),transition_fault_value(2) {} 
        ~Memory_Cell() {}
        transition_t prev_trans;
        op_t mem_op; 
        
        //Functions to simulate working of a memory cell.
        void set_transition_value(uint32_t fault_value);
        void set_stuck_at_0() { stuck_at_0 = true; }
        void set_stuck_at_1() { stuck_at_1 = true; } 
        void write_cell(uint32_t _value);
        uint32_t read_cell();
        uint32_t cell_value();

};

//NOTE:Currently only unlinked faults are being modelled. 
//Class memory array having a has-a relationship with memory cell
class Memory_Array {
    private :
        Memory_Cell Mem_Arr[MEM_SIZE];
        std::map<uint32_t,std::string> fault_map = {};        
        
        //Inversion fault parameters
        uint32_t inv_aggressor;
        uint32_t inv_victim;
        transition_t inv_tran_value;
       
        //Idempotent fault parameter
        uint32_t idm_aggressor;
        uint32_t idm_victim;
        transition_t idm_tran_value;
        uint32_t idm_victim_value;

        //State Coupling fault
        uint32_t stc_aggressor;
        uint32_t stc_victim;
        uint32_t stc_agg_state;
        uint32_t stc_vic_value;

        //Disturb faults
        uint32_t dist_aggressor;
        uint32_t dist_victim;
        op_t dist_agg_op;
        uint32_t dist_vic_value;
        
    public :
        //Constructors/Destructors for memory array
        //Initialiazing all parameters to Max Address as memory has
        //address range 0 - MEM_SIZE
        Memory_Array() :
            inv_aggressor(MEM_SIZE),
            inv_victim(MEM_SIZE),
            inv_tran_value(no_tran),
            idm_aggressor(MEM_SIZE),
            idm_victim(MEM_SIZE),
            idm_tran_value(no_tran),
            idm_victim_value(2),
            stc_aggressor(MEM_SIZE),
            stc_victim(MEM_SIZE),
            stc_agg_state(2),
            stc_vic_value(2),
            dist_aggressor(MEM_SIZE),
            dist_victim(MEM_SIZE),
            dist_agg_op(NOP),
            dist_vic_value(2) {}

        ~Memory_Array() {}

        std::string mem_name;
        
        //Basic reading and writing to memory
        uint32_t read_mem(uint32_t address);
        void write_mem(uint32_t address,uint32_t write_value);

        //function signatures for injecting different faults in memory.
        void inject_stuck_at_fault(uint32_t fault_address, uint32_t stuck_at_value);
        void inject_transition_fault(uint32_t fault_address, uint32_t fault_value); 
        void inject_inversion_fault(uint32_t victim, uint32_t aggressor, transition_t tran_value);
        void inject_idempotent_fault(uint32_t victim, uint32_t aggressor, transition_t tran_value, uint32_t vict_value);
        void inject_state_fault(uint32_t victim, uint32_t aggressor, uint32_t agg_state, uint32_t vict_value);
        void inject_disturb_fault(uint32_t victim, uint32_t aggressor, op_t agg_op, uint32_t vict_value );

        //helper/visualization functions.
        void print_mem_array();
};
}        
        
#endif             
