#include "Wood.h"
#include "FullState.h"
#include "EmptyState.h"
#include "NormalState.h"
#include <iostream>

Wood::Wood(StateOfResources* initialState, int initialQuantity) : state(initialState), quantity(initialQuantity) {
    fullState = new FullState();
    emptyState = new EmptyState(this);
    normalState = new NormalState();
}

void Wood::useResource(int quantity) {
    state->useResource(quantity);
    this->quantity -= quantity;
    if (this->quantity <= 0) {
        this->quantity = 0;
        setState(emptyState);
    } else if (this->quantity < getMaxCapacity()) {
        setState(normalState);
    } else {
        setState(fullState);
    }
}

void Wood::generateResource(int quantity) {
    this->quantity += quantity;
    if (this->quantity >= getMaxCapacity()) {
        this->quantity = getMaxCapacity();
        setState(fullState);
    } else if (this->quantity > 0) {
        setState(normalState);
    } else {
        setState(emptyState);
    }
}

void Wood::setState(StateOfResources* newState) {
    state = newState;
}

int Wood::getQuantity() const {
    return quantity;
}

int Wood::getMaxCapacity() const {
    return 100; // Example max capacity
}