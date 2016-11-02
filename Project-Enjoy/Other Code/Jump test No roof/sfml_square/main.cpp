#include "app.h"

int main()
{
	App app;

	// Game loop, run while the window is open
	while (app.Tick());

	return 0;
}
