#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>


typedef struct {
    const char *name;
} NamedState;

typedef struct {
    NamedState *states;
    size_t statesCapacity;

    size_t position;
} StateRegistry;



static size_t addState(StateRegistry *stateRegistry, const char *name) {
    NamedState namedState;
    namedState.name = name;

    if (stateRegistry->position >= stateRegistry->statesCapacity) {
        fprintf(stderr,
                "Error: cannot add new state to StateRegistry, because position %llu >= capacity %llu\n",
                stateRegistry->position,
                stateRegistry->statesCapacity
        );
        fflush(stderr);

        return 0;
    }

    size_t newStatePosition = stateRegistry->position++;

    stateRegistry->states[newStatePosition] = namedState;
    return newStatePosition;
}

static StateRegistry createStateRegistry(size_t capacity) {
    StateRegistry stateRegistry;
    stateRegistry.states = calloc(capacity, sizeof(NamedState));
    stateRegistry.statesCapacity = capacity;
    stateRegistry.position = 0;

    addState(&stateRegistry, "0");

    return stateRegistry;
}

static size_t getOrAddState(StateRegistry *stateRegistry, const char *name) {
    for (int i = 0; i < stateRegistry->position; ++i) {
        if (strcmp(stateRegistry->states[i].name, name) == 0) {
            return i;
        }
    }

    return addState(stateRegistry, name);
}
