using namespace std;
#include "domain.h"
#include "../TemaSase/testdomain.h"
#include <assert.h>
void Test_Domain::TestLikes() {
	Tutorial a("abc", "acx", "12:12", 143, "www.a");
	assert(a.get_likes() == 143);
}