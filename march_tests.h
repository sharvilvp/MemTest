#ifndef _MARCH_TESTS_H_
#define _MARCH_TESTS_H_
#include "memory_struct.h"
#include "memory_defines.h"
#include <cassert>
#include <map>
namespace march {
    class Test {
            
        private:
        std::string test_name;
        std::map<std::string,order_t> march_order_map;
        std::map<std::string,march_element_t> march_element_map;
        static std::map<std::string,march::Test*> tests;
        Test() { }
        public:
        march::Test& name(std::string _name) {
            test_name = _name;
            return *this;
        }
   
        const std::string& name() const {
            return test_name;
        }
        
        march::Test& march_order(std::string _name, order_t _march_order) {
            march_order_map[_name] = _march_order;
            return *this;
        }

        const std::map<std::string,order_t>& march_order() const {
            return march_order_map;
        }
           
        march::Test& march_element(std::string _name, march_element_t _march_element) {
            march_element_map[_name] = _march_element;
        }

        const std::map<std::string,march_element_t>& march_element() const {
            return march_element_map;
        }

        static march::Test* getTest(std::string _test_name) {
            if(tests.find(_test_name) != tests.end())
                return tests[_test_name];

            return nullptr;
        }
        
        void print_march_map();
        void print_multiton_map();
           
        static march::Test* getTestInstance(std::string _test_name) {
            if(tests.find(_test_name) != tests.end()) 
                return tests[_test_name];
            
            march::Test* p_test = new march::Test;
            tests[_test_name] = p_test;
            return p_test; 
        }


    };
}   
#endif
