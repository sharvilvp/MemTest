#ifndef _MEMORY_DEFINES_H_
#define _MEMORY_DEFINES_H_
#define DRF_DELAY 50
#define MEM_SIZE 8
#define STUCK_AT_FAULT_PROBABILITY 1
#define TRANSITION_FAULT_PROBABILITY 5
#define INVERSION_FAULT_PROBABILITY 1
#define FAULT_PROBABILITY 20
#include<vector>
#include<tuple>
typedef enum {
    low2high,
    high2low,
    no_tran
} transition_t;

typedef enum {
    R,
    W,
    NOP
} op_t;

typedef enum {
    INC,
    DEC,
    ANY
} order_t;   

typedef enum {
    NO,
    SA0,
    SA1,
    TFLH,
    TFHL,
    CFINHL,
    CFINLH,
    CFIDLH0,
    CFIDLH1,
    CFIDHL0,
    CFIDHL1,
    CFST00,
    CFST01,
    CFST10,
    CFST11,
    CFDSW00,
    CFDSW01,
    CFDSW10,
    CFDSW11,
    CFDSR00,
    CFDSR01,
    CFDSR10,
    CFDSR11
} fault_t;

typedef std::tuple<op_t,uint32_t> march_operation_t;
typedef std::vector<std::tuple<op_t,uint32_t>> march_element_t;
#endif
