#include "Main.h"

FILE _iob[] = { *stdin, *stdout, *stderr };
extern "C" FILE * __cdecl __iob_func(void) { return _iob; }

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