#pragma once
#include "CallbackHandler.h"

class CallbackClient
{
public:
	CallbackClient();

	void eventFunction(uint32_t value);
	void registerToHandler(CallbackHandler& handler);

private:
	
};

