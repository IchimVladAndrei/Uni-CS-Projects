
#include <iostream>
#include <crtdbg.h>
#include "../TemaSase/repo.h"
#include "../TemaSase/service.h"
#include "../TemaSase/domain.h"
#include "../TemaSase/tests.h"
#include "fileRepo.h"
using namespace std;


int main() {
	{

	
	/*Repo repo;
	Repo repo_user;
	repo.init_repo();*/
		Repo repo_user;
	/*FileRepo repo_user(R"(C:\Users\potat\Documents\TemaSase\tutoriale.txt)");*/
	FileRepo repo(R"(C:\Users\potat\Documents\TemaSase\tutoriale.txt)");
	
	//repo.add_repo("Class", "Charlie", "12:40", 1000, "www.a");
	//try {
	//	repo.init_repo();
	//}
	//catch (RepoExceptions& msg) {
	//	cout << msg.what();
	//	cout << "\n";
	//	cin.clear();
	//	cin.ignore();
	//}
	Service service(repo, repo_user);
	Console console(service);
	console.solve();

}
		
	//search for bugs in 4
		//try except
		// 		//when the info is not correct the link of tutorial appears??

		//html csv file
	//do i need test again?
	//HEADERS and INCLUDES
	//organise code
	//exclude comments
	//make better comments
	
	//BUGS :
	//when deleting a tutorial that exists in the admin repo, and exist in a previous user repo->>>> adaug file repo user din ala de admin ((SOLUTION, make user repo memory based?))


	/*Tests T;///_CrtDumpMemoryLeaks();
	T.TestALL();*/
	return 0;


}