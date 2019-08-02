#pragma once
#include "CallbackHandler.h"

class VirtualClient
{
public:
	VirtualClient();
	void registerToHandler(CallbackHandler& handler);
	virtual void update(uint32_t evnt) = 0;
};

