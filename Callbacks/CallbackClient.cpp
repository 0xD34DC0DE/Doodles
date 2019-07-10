#include "CallbackClient.h"



CallbackClient::CallbackClient()
{
}

void CallbackClient::eventFunction(uint32_t value)
{
	std::printf("object: %p\t,value is :%u\n", this, value);
}

void CallbackClient::registerToHandler(CallbackHandler& handler)
{
	handler.registerCallback(std::bind(&CallbackClient::eventFunction, this, std::placeholders::_1));
}
