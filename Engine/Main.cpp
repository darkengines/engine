#include <stdio.h>
#include <stdlib.h>
#include "Vector3.h"
#include "Matrix4.h"
#include "System.h"
#include <Windows.h>

int main(int argc, char** argv) {

	/*SetPriorityClass(GetCurrentProcess(),
					 REALTIME_PRIORITY_CLASS
	);*/

	System* system = new System();
	system->Initialize();
	system->Run();
	system->Shutdown();
	getchar();
	return 0;
}