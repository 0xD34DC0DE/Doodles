#include "CallbackClient.h"

int main()
{
	CallbackClient cb1;
	CallbackClient cb2;

	CallbackHandler cbh;

	cb1.registerToHandler(cbh);
	cb2.registerToHandler(cbh);

	cbh.triggerEvent(12345);

	getchar();

	return 0;
}