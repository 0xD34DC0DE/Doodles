#include "CallbackHandler.h"



CallbackHandler::CallbackHandler()
{
}

void CallbackHandler::registerCallback(cb_void_uint32 function)
{
	m_callbacks.emplace_back(function);
}

void CallbackHandler::triggerEvent(uint32_t value)
{
	for (auto &callback : m_callbacks)
	{
		callback(value);
	}
}
