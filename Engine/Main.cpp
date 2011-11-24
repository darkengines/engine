#include <stdio.h>
#include <stdlib.h>
#include "Vector3.h"
#include "System.h"

int main(int argc, char** argv) {
	bool done = 0;
	System* system = new System();
	system->Initialize();
	system->Run();
	system->Shutdown();
	getchar();
	return 0;
}