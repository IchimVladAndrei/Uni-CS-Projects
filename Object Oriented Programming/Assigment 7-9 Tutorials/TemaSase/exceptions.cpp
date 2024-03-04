#include "exceptions.h"
#include <utility>

Exceptions::Exceptions(std::string msg)
{
	this->message = move(msg);
}

const char* Exceptions::what() const noexcept {
	return this->message.c_str();
}

ValidatorExceptions::ValidatorExceptions(std::string msg) :Exceptions(move(msg)) {
}

RepoExceptions::RepoExceptions(std::string msg) :Exceptions(move(msg)) {
}
