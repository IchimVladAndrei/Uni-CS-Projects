#include <iostream>
#include <crtdbg.h>
#include "repo.h"
#include "service.h"
#include "console.h"
#include "domain.h"
#include "dynamic.h"
using namespace std;
int main() {
	DynamicArray<Tutorial>* DA = new DynamicArray<Tutorial>(100);
	DynamicArray<Tutorial>* DAuser = new DynamicArray<Tutorial>(100);
	Repo* repo = new Repo(DA);
	Repo* repo_user = new Repo(DAuser);
	repo->init_repo();
	Service* service = new Service(repo, repo_user);
	Validator* validator = new Validator();
	Console* console = new Console(service,validator);
	console->solve();
	delete console;
	delete validator;
//new c
	return 0;

}