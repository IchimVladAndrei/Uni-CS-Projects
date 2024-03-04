#define _CRTDBG_MAP_ALLOC
#include <stdio.h>
#include <stdlib.h>
#include "console.h"
#include "repo.h"
#include "dynamic.h"
#include "service.h"
#include "reundo.h"
#include <crtdbg.h>
#include "tests.h"


int main()
{
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	DynamicArray* arr = createDA(100);
	Repos* repo = createRepos(*arr);
	Repos n_repo;
	init_repo(repo);
	n_repo = duplicate(repo);
	UndoRedo* undoredo = createUndoRepo(100, &n_repo);
	Service* service = create_service(*repo,*undoredo);
	Console* console = create_console(*service);
	solve(console);
	destroy_ui(console);
	destroy_s(service);
	destroy_reundo(undoredo);
	destroy(arr);
	free(n_repo.array.data);
	//test_ALL();
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
	_CrtDumpMemoryLeaks();

	return 0;
}
