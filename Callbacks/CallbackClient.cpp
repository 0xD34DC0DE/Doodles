#include "Callbacks.h"


unsigned int CallbackClient::m_s_instanceCount = 0;

CallbackClient::CallbackClient()
{
	m_instanceID = CallbackClient::m_s_instanceCount++;
}

void CallbackClient::eventFunction(uint32_t value)
{
	std::printf("object at 0x%x instance #%u, value is :%u\n", (unsigned int)(this), m_instanceID, value);
}

void CallbackClient::registerToHandler(CallbackHandler& handler)
{
	handler.registerCallback(std::bind(&CallbackClient::eventFunction, this, std::placeholders::_1));
}
