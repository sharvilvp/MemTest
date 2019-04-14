#include "memory_struct.h" 
#include <cassert>
#include <map>
//====================== Memory Cell Function implementation ================================
//Description :  memory cells has following parameters:
//value                     : bit value for the memory cell
//stuck_at_0/1              : models stuck at faults
//transition_fault_value    : value for which cell cannot transit
//prev_trans                : remembers transition (high2low or low2high) for inv/idm faults 
//mem_op                    : remembers last operation on the cell for disturb faults 
//==========================================================================================
using namespace Memory;
void Memory_Cell::set_transition_value(uint32_t fault_value) {
    transition_fault_value = fault_value;
}

void Memory_Cell::write_cell(uint32_t _value) {
    //If memory cell has transition value and the value being
    //written differs then hold the fault value to model the 
    //faulty behaviour. Also the value should not be X(2).
    if(transition_fault_value == value && transition_fault_value != 2) {
        value = transition_fault_value; 
        return; }
    
    //if cell is stuck at zero, hold zero. 
    if(stuck_at_0) {
        value = 0; return; }
    
    //if cell is stuck at one, hold one. 
    if(stuck_at_1) {
        value = 1; return; }

    //else remember the transition
    mem_op = W;
    if((value == 0 || value == 2) && _value == 1) 
        prev_trans = low2high;
    else if((value == 1 || value == 2) && _value == 0) 
        prev_trans = high2low;
    
    value = _value;
    return;
}
//FIXME:find a way to get rid of this | redundant.
uint32_t Memory_Cell::cell_value() {
    return value; }

uint32_t Memory_Cell::read_cell() {
    return value; }   

//====================== Memory Array Function implementation ================================
//Description : memory array has following parameters:
//value                     : bit value for the memory cell
//stuck_at_0/1              : models stuck at faults
//transition_fault_value    : value for which cell cannot transit
//prev_trans                : remembers transition (high2low or low2high) for inv/idm faults 
//mem_op                    : remembers last operation on the cell for disturb faults 
//==========================================================================================

void Memory_Array::write_mem(uint32_t address,uint32_t write_value) {
    Mem_Arr[address].write_cell(write_value); 
    if(address == inv_aggressor) {
        if(Mem_Arr[inv_aggressor].prev_trans == inv_tran_value) {
            auto value = Mem_Arr[inv_victim].cell_value();
            Mem_Arr[inv_victim].write_cell(1-value);
        }
    }
    if(address == idm_aggressor) {
        if(Mem_Arr[idm_aggressor].prev_trans == idm_tran_value) {
            Mem_Arr[idm_victim].write_cell(idm_victim_value);
        }
    }
    if(address == stc_aggressor) {
       if(Mem_Arr[stc_aggressor].read_cell() == stc_agg_state) {
          Mem_Arr[stc_victim].write_cell(stc_vic_value);
       }
   }
   if(address == dist_aggressor) {
       if(Mem_Arr[dist_aggressor].mem_op == dist_agg_op) {
          Mem_Arr[dist_victim].write_cell(dist_vic_value);
       }
   } 
        
}

uint32_t Memory_Array::read_mem(uint32_t address) {
    return Mem_Arr[address].read_cell();
}
void Memory_Array::inject_stuck_at_fault(uint32_t fault_address, uint32_t stuck_at_value) {
        
    if(stuck_at_value == 0) {
        fault_map[fault_address] = "SA0";
        Mem_Arr[fault_address].set_stuck_at_0();
    }
    if(stuck_at_value == 1) {
        fault_map[fault_address] = "SA1";
        Mem_Arr[fault_address].set_stuck_at_1();
    }
}
         
void Memory_Array::inject_transition_fault(uint32_t fault_address, uint32_t fault_value) {
    fault_map[fault_address] = "TF";
    Mem_Arr[fault_address].set_transition_value(fault_value);
} 

void Memory_Array::inject_inversion_fault(uint32_t victim, uint32_t aggressor, transition_t tran_value) {
//    assert(aggressor == victim); 
    inv_aggressor = aggressor;
    inv_victim = victim;
    inv_tran_value = tran_value;
} 

void Memory_Array::inject_idempotent_fault(uint32_t victim, uint32_t aggressor, transition_t tran_value, uint32_t vict_value) {
//    assert(aggressor == victim);
    idm_aggressor = aggressor;
    idm_victim = victim;
    idm_tran_value = tran_value;
    idm_victim_value = vict_value;
} 

void Memory_Array::inject_state_fault(uint32_t victim, uint32_t aggressor, uint32_t agg_state, uint32_t vict_value) {
//    assert(aggressor == victim); 
    stc_aggressor = aggressor;
    stc_victim = victim;
    stc_agg_state = agg_state;
    stc_vic_value = vict_value;
} 

void Memory_Array::inject_disturb_fault(uint32_t victim, uint32_t aggressor, op_t agg_op, uint32_t vict_value) {
//    assert(aggressor == victim); 
    dist_aggressor = aggressor;
    dist_victim = victim;
    dist_agg_op = agg_op;
    dist_vic_value = vict_value;
} 

void Memory_Array::print_mem_array() {
    for(uint32_t i=0;i<MEM_SIZE;i++) {
        std::cout<<Mem_Arr[i].cell_value()<<std::endl;
    }
}
