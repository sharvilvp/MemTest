#include "memory_struct.h" 
#include "memory_defines.h"
#include<iostream>
#include<ctime>
#include<cstdlib>
#include<vector>
#include<algorithm>



void MATS(std::vector<unsigned int> traverse_order,Memory_Array &Test_Array)
{
      int cell_value;
      std::vector<unsigned int>::iterator it;
      
      for(it = traverse_order.begin(); it != traverse_order.end();++it)
        {
            Test_Array.write_value(*it,0);
            
            if(Test_Array.read_and_verify(*it,0) == false)
                std::cout<<"Fault Found At "<<*it<<std::endl;

            Test_Array.write_value(*it,1);

            if(Test_Array.read_and_verify(*it,1) == false)
                std::cout<<"Fault Found At "<<*it<<std::endl;
        }
}

void MATS_PLUS(std::vector<unsigned int> traverse_order, Memory_Array &Test_Array)
{

    int cell_value;
   
    //March Element 1
    for(auto it = traverse_order.begin();it != traverse_order.end();++it)
            Test_Array.write_value(*it,0);

    //March Element 2
    for(auto it = traverse_order.begin();it != traverse_order.end();++it)
        {
            if(Test_Array.read_and_verify(*it,0) == false)
                std::cout<<"Fault Found At "<<*it<<std::endl;
               
            Test_Array.write_value(*it,1);
        }

    //March Element 3
    for(auto it=traverse_order.rbegin();it != traverse_order.rend();++it)
        { 
            if(Test_Array.read_and_verify(*it,1) == false)
               std::cout<<"Fault Found At "<<*it<<std::endl;

            Test_Array.write_value(*it,0);
        }
}


void MATS_PLUS_PLUS(std::vector<unsigned int> traverse_order, Memory_Array &Test_Array)
{

    int cell_value;
   
    //March Element 1
    for(auto it = traverse_order.begin();it != traverse_order.end();++it)
            Test_Array.write_value(*it,0);

    //March Element 2
    for(auto it = traverse_order.begin();it != traverse_order.end();++it)
        {
            if(Test_Array.read_and_verify(*it,0) == false)
                std::cout<<"Fault Found At "<<*it<<std::endl;
               
            Test_Array.write_value(*it,1);
        }

    //March Element 3
    for(auto it=traverse_order.rbegin();it != traverse_order.rend();++it)
        { 
            if(Test_Array.read_and_verify(*it,1) == false)
               std::cout<<"Fault Found At "<<*it<<std::endl;

            Test_Array.write_value(*it,0);

            if(Test_Array.read_and_verify(*it,0) == false)
               std::cout<<"Fault Found At "<<*it<<std::endl;
        }
}

int main(int argc, char* argv[])
{
    srand((unsigned int)time(0));
 
    Memory_Array Test_Array;
    
    std::vector<unsigned int> traverse_order;
    
    //Randomly Generating Addresses For Fault Injection    
    int sa_location =  rand()%MEM_SIZE;
    int trf_location = rand()%MEM_SIZE;
   
    std::cout<<"Inserting Transition Fault at "<<trf_location<<std::endl;
    std::cout<<"Inserting Stuck-At Fault at "<<sa_location<<std::endl;

    //Creating A Traversal Order
    for(int i=0;i<MEM_SIZE;i++)
        traverse_order.push_back(i);
    
    //Shuffling the order to create randomness in traversal 
    std::random_shuffle(traverse_order.begin(),traverse_order.end());

    //Fault Injection
    Test_Array.inject_stuck_at_fault(sa_location);
    Test_Array.inject_transition_fault(trf_location,1);
    
    //NOTE : Uncomment the test 
    MATS_PLUS_PLUS(traverse_order,Test_Array);   
//  MATS_PLUS(traverse_order,Test_Array);    
//  MATS(traverse_order,Test_Array);    
    
    
    return 0;
}
     
