#if !defined(STATE_H)
#define STATE_H

#include "main.h"

class State {
public:
	State() { }
	virtual ~State() { }
	virtual void execute(Uint32 ticks, Uint8* keystate) = 0;
	virtual void activate() = 0;
	virtual void deactivate() = 0;
	void set();
public:
	static void update();
	static void set(State* state);
	static State* get() { return current; }
private:
	static State *current, *next, *prev;
	static bool updated;
};

#endif