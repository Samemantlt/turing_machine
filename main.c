#include <stdio.h>
#include <stdlib.h>

#include "parser.c"


const int MAX_INSTRUCTIONS_COUNT = 2048;
const int MAX_STATE_REGISTRY_CAPACITY = 2048;


bool readInstructionsFromFile(const char *filename,
                              Instruction *instructions,
                              size_t *instructionsCount,
                              size_t maxInstructionsCount,
                              StateRegistry *stateRegistry) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error: file cannot be opened '%s'\n", filename);
        fflush(stderr);
        return false;
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = calloc(fileSize + 1, sizeof(char));
    fread(buffer, sizeof(char), fileSize, file);
    fclose(file);

    bool success = readInstructions(buffer, fileSize, instructions, instructionsCount, MAX_INSTRUCTIONS_COUNT,
                                    stateRegistry);

    free(buffer);

    return success;
}


void initializeRibbon(TuringMachine *machine, char *input, size_t length) {
    memcpy(&machine->ribbon[1], input, length);
    machine->carriagePosition = length + 1;
}

void initializeRibbonFromConsole(TuringMachine *machine) {
    printf("Enter start ribbon: ");
    fflush(stdout);
    char startRibbon[256];
    fgets(startRibbon, sizeof(startRibbon), stdin);

    size_t len = strlen(startRibbon);

    initializeRibbon(machine, startRibbon, len - 1);
}

void printCarriage(size_t index) {
    for (int i = 0; i < index; ++i) {
        printf(" ");
    }
    printf("^\n");
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "You must specify instructions file");
        fflush(stderr);
        return 1;
    }

    bool silent = false;

    if (argc >= 3) {
        if (strcmp(argv[2], "-s") == 0) {
            silent = true;
        }
    }

    char *ribbonInput = NULL;

    if (argc == 4) {
        ribbonInput = argv[3];
    }

    StateRegistry stateRegistry = createStateRegistry(MAX_STATE_REGISTRY_CAPACITY);
    Instruction instructions[MAX_INSTRUCTIONS_COUNT];
    size_t instructionsCount = 0;

    bool successReading = readInstructionsFromFile(argv[1],
                                                   instructions,
                                                   &instructionsCount,
                                                   MAX_INSTRUCTIONS_COUNT,
                                                   &stateRegistry);
    if (!successReading) {
        fprintf(stderr, "Error reading instructions from file 'instructions.tu'\n");
        fflush(stderr);
        return 1;
    }

    TuringMachine machine = createTuringMachine(instructions, instructionsCount, 32, 0, 0);

    if (ribbonInput) {
        if (silent) {
            initializeRibbon(&machine, ribbonInput, strlen(ribbonInput));
        }
    } else {
        initializeRibbonFromConsole(&machine);
    }

    while (!machine.ended) {
        if (!silent) {
            printf("\n");
            printf("%s\n", machine.ribbon);
            printCarriage(machine.carriagePosition);

            fflush(stdout);
        }

        bool success = runOnce(&machine, silent);
        if (!success) {
            fprintf(stderr, "Error when running iteration of turing machine\n");
            fflush(stderr);
            return 1;
        }
    }

    if (!silent) {
        fflush(stdout);
        printf("Ended!\n");
    }

    if (silent) {
        printf("%s", machine.ribbon);
    }
}
