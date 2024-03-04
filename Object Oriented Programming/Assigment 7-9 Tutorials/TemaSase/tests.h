#pragma once
#include <string>
using namespace std;

class Tests {
public:

	///DOMAIN///
	void TestLikes();
	void TestTitle();
	void TestPresenter();
	void TestDuration();
	void TestLink();
	void TestSetLikes();
	////VALIDATOR////
	void TestValidatorTitle();
	void TestValidatorPresenter();
	void TestValidatorDuration();
	void TestValidatorLikes();
	void TestValidatorLink();
	////ARRAY?///
	///REPO//
	void TestInitRepo();
	void TestGetSizeRepo();
	void TestGetDA();
	void TestAddRepo();
	void TestRemoveRepo();
	void TestUpdateRepo();
	void TestCheckExists();

	//SERVICE//
	void TestAddService();
	void TestRemoveService();

	void TestUpdateService();
	void TestGetSizeService();
	void TestAddUserService();
	void TestRemoveUserService();
	void TestGetUserRepo();

	void TestChangeRepo();

	void TestChangeBack();


	void TestALL() {
		TestLikes();
		TestTitle();
		TestPresenter();
		TestDuration();
		TestLink();
		TestSetLikes();
		TestValidatorTitle();
		TestValidatorPresenter();
		TestValidatorDuration();
		TestValidatorLikes();
		TestValidatorLink();
		TestInitRepo();
		TestGetSizeRepo();
		TestGetDA();
		TestAddRepo();
		TestRemoveRepo();
		TestUpdateRepo();
		TestCheckExists();

		//SERVICE//
		TestAddService();
		TestRemoveService();

		TestUpdateService();
		TestGetSizeService();
		TestAddUserService();
		TestRemoveUserService();
		TestGetUserRepo();
		TestChangeRepo();

 TestChangeBack();
	}
};
//void();