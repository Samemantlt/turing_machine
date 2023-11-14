#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "instruction.c"
#include "machine.c"
#include "stateRegistry.c"


static Instruction readInstruction(char* line, StateRegistry* stateRegistry){
    char* currentStateStr = malloc(32);
    Symbol currentSymbol;
    Symbol newSymbol;
    char* newStateStr = malloc(32);


    int result = sscanf(line, "%s %c %c %s", currentStateStr, &currentSymbol, &newSymbol, newStateStr);
    if (result == EOF)
        return EMPTY_INSTRUCTION;

    if (result != 4)
        return EMPTY_INSTRUCTION;


    size_t currentState = getOrAddState(stateRegistry, currentStateStr);
    size_t newState = getOrAddState(stateRegistry, newStateStr);


    return createInstruction(currentState, currentSymbol, newSymbol, newState, line);
}

static bool readInstructions(char* textInstructions,
                      size_t textInstructionsLength,
                      Instruction* instructions,
                      size_t* instructionsCount,
                      size_t maxInstructionsCount,
                      StateRegistry* stateRegistry){
    size_t start_line = 0;

    for (int i = 0; i < textInstructionsLength; ++i) {
        if (textInstructions[i] == '\n' || i == textInstructionsLength - 1){
            if (textInstructions[start_line] == '#'){
                start_line = i + 1;
                continue;
            }

            if (i - start_line <= 2) {  // eg. "1\r\n"
                start_line = i + 1;
                continue;
            }

            char* line = malloc(i - start_line + 1);
            memcpy(line, &textInstructions[start_line], i - start_line);
            line[i - start_line] = '\0';

            Instruction newInstruction = readInstruction(line, stateRegistry);

            // free(line); --- Used in Instruction

            if (!isEmptyInstruction(&newInstruction)){
                size_t newInstructionIndex = (*instructionsCount)++;
                if (newInstructionIndex >= maxInstructionsCount)
                    return false;

                instructions[newInstructionIndex] = newInstruction;
            }

            start_line = i + 1;
        }
    }

    return true;
}