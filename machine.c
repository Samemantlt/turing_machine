#pragma once

#include <stdio.h>
#include "stdlib.h"
#include "instruction.c"

typedef struct {
    Instruction *instructions;
    size_t instructionsCount;

    Symbol *ribbon;
    size_t ribbonLength;

    MachineState currentState;
    size_t carriagePosition;

    bool ended;
} TuringMachine;


static TuringMachine createTuringMachine(Instruction *instructions,
                                  size_t instructionsCount,
                                  size_t ribbonLength,
                                  MachineState currentState,
                                  size_t carriagePosition) {
    TuringMachine machine;

    machine.instructions = instructions;
    machine.instructionsCount = instructionsCount;

    machine.ribbonLength = ribbonLength;
    machine.ribbon = malloc(ribbonLength * sizeof(Symbol));
    for (int i = 0; i < ribbonLength; ++i) {
        machine.ribbon[i] = '_';
    }
    machine.ribbon[ribbonLength - 1] = '\0';

    machine.currentState = currentState;
    machine.carriagePosition = carriagePosition;

    machine.ended = false;

    return machine;
}

static TuringMachine createDefaultTuringMachine(Instruction *instructions, size_t instructionsCount) {
    return createTuringMachine(instructions, instructionsCount, 32, 0, 16 - 1);
}

static bool runOnce(TuringMachine *turingMachine, bool silent) {
    if (turingMachine->ended){
        fprintf(stderr, "Trying to run ended turing machine\n");
        fflush(stderr);
        return false;
    }

    Symbol currentSymbol = turingMachine->ribbon[turingMachine->carriagePosition];
    MachineState currentState = turingMachine->currentState;

    Instruction *foundInstruction = NULL;
    bool found = false;

    for (int i = 0; i < turingMachine->instructionsCount; ++i) {
        Instruction instruction = turingMachine->instructions[i];

        if (instruction.currentState == currentState && instruction.currentSymbol == currentSymbol) {
            foundInstruction = &turingMachine->instructions[i];
            found = true;

            break;
        }
    }

    if (!found) {
        fprintf(stderr, "Error: no matching instruction found for symbol '%c' and state '%llu'\n", currentSymbol,
                currentState);
        fflush(stderr);
        return false;
    }

    if (!silent){
        printf("Executing: %s\n", foundInstruction->line);
        fflush(stdout);
    }

    turingMachine->currentState = foundInstruction->newState;

    if (foundInstruction->newSymbol == MOVE_CARRIAGE_RIGHT) {
        turingMachine->carriagePosition++;
        return true;
    }

    if (foundInstruction->newSymbol == MOVE_CARRIAGE_LEFT) {
        turingMachine->carriagePosition--;
        return true;
    }

    if (foundInstruction->newSymbol == END_PROGRAM) {
        turingMachine->ended = true;
        return true;
    }

    turingMachine->ribbon[turingMachine->carriagePosition] = foundInstruction->newSymbol;
    return true;
}