#include "state.h"

State* State::current = NULL;
State* State::next = NULL;
State* State::prev = NULL;
bool State::updated = true;

void State::update() {
	if (!updated) {
		prev = current;
		current = next;
		next = NULL;

		if (prev) prev->deactivate();
		if (current) current->activate();

		updated = true;
	}
}

void State::set() {
	set( this );
}

void State::set(State* state) {
	if (updated) {
		next = state;
		updated = false;
	}
}