#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef size_t MachineState;
typedef char Symbol;


static const Symbol MOVE_CARRIAGE_LEFT = '<';
static const Symbol MOVE_CARRIAGE_RIGHT = '>';
static const Symbol END_PROGRAM = '#';
static const Symbol NO_OPERATION = '_';


typedef struct {
    MachineState currentState;
    Symbol currentSymbol;
    Symbol newSymbol;
    MachineState newState;
    char* line;
} Instruction;


static const Instruction EMPTY_INSTRUCTION = {0, 0, 0, 0, 0};


static Instruction createInstruction(MachineState currentState, Symbol currentSymbol, Symbol newSymbol, MachineState newState, char* line) {
    Instruction instruction = {currentState, currentSymbol, newSymbol, newState, line};
    return instruction;
}

static bool isEmptyInstruction(const Instruction* instruction){
    return memcmp(instruction, &EMPTY_INSTRUCTION, sizeof(Instruction)) == 0;
}


