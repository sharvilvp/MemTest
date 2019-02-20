#include<cstdlib>
#include<ctime>
#include "memory_defines.h"

class Memory_Cell 
    {
	    private :
	        int value;
	        int stuck_at_0;
	        int stuck_at_1;
            int transition_value;
	        bool visited;

        public :
	        Memory_Cell()
	            {
		            this->stuck_at_0 = 0;
		            this->stuck_at_1 = 0;
                    this->transition_value = 3;
                    this->value = 2;
	            }

	       int read_value()
	            {
		            if(this->stuck_at_0)
			            return 0;
		            if(this->stuck_at_1)
			            return 1; 
                    return value;
	            }
            

	
            void write_value(int write_value)
	            {
		            if(this->stuck_at_0)
                        {
                            this->value = 0;
                            return;
                        }
            	    if(this->stuck_at_1)
                        {
			                this->value = 1;
                            return;
                        }
                    if(this->transition_value == this->value)
                        {
                            this->value = this->transition_value;
                            return;
                        
                        }
                    this->value = write_value;
                    return;
	            }

           	void stuck_at_fault_injection()
	            {	
		            srand((unsigned)time(0));
	            int i = rand()%MEM_SIZE;
		            if(i%2 == 0)
			            this->stuck_at_0 = 1;
    	            else 
			            this->stuck_at_1 = 1;
	            }	    
       
            void transition_fault_injection(int fault_value)
                {
                    this->transition_value = fault_value;
                }
        };

class Memory_Array
    {
public:
    //Memory Array For Test With Configurable Memory Size 
	Memory_Cell Test_Mem[MEM_SIZE];

    //Inject Stuck At Faults 
    void inject_stuck_at_fault(int address)
	{	
		Test_Mem[address].stuck_at_fault_injection();
	}
    
    //Inject Transition Faults
    void inject_transition_fault(int address,int transition_value)
    {
        Test_Mem[address].transition_fault_injection(transition_value);
    }



	void write_value(int address,int data)
    {
	    Test_Mem[address].write_value(data);
    }


    bool read_and_verify(int address,int value_to_be_verified)
    {
            int read_cell_value;
            read_cell_value = Test_Mem[address].read_value();

            if(read_cell_value == value_to_be_verified)
                return true;
            else 
                return false;
    }
				
};	
