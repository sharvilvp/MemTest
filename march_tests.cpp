#include <fstream>
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <tuple>
#include "memory_struct.h"
#include "march_tests.h"
#include "memory_defines.h"
#include <map>

std::map<std::string,march::Test*> march::Test::tests;

void march::Test::print_march_map () {
    assert(march_order_map.size() == march_element_map.size());
    std::cout<<"============================================"<<std::endl;
    for(auto element : march_order_map) {
        auto order = element.second;
        std::cout<<element.first<<std::endl;
        switch(order) {
            case 0 : std::cout<<"INC ";
            case 1 : std::cout<<"DEC ";
            case 2 : std::cout<<"ANY ";
        }
        auto op_vec = march_element_map[element.first];
        for(auto op : op_vec) {
            auto op1 = std::get<0>(op);
            auto op2 = std::get<1>(op);
            switch(op1) {
                case 0 : std::cout<<"R";break;
                case 1 : std::cout<<"W";break;
                case 2 : std::cout<<"NOP";break;
            }
            std::cout<<op2<<" ";
        }       
        std::cout<<std::endl;
    }
}

void march::Test::print_multiton_map() {
    assert(tests.size() != 0);
    std::cout<<"============================================"<<std::endl;
    for(auto test : tests) {
        std::cout<<test.first<<"        ";
        std::cout<<test.second<<std::endl;
    }
}
