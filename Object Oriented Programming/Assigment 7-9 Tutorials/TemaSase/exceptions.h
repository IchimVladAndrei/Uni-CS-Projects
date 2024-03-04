#include <string>
#include <exception>
#include <utility>

class Exceptions :public std::exception
{
protected:
	std::string message;
public:
	explicit Exceptions(std::string msg);
	const char* what() const noexcept override;

};
class ValidatorExceptions :public Exceptions
{
public:
	explicit ValidatorExceptions(std::string msg);
};

class RepoExceptions :public Exceptions
{
public:
	explicit RepoExceptions(std::string msg);
};