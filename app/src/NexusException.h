#ifndef NEXUS_EXCEPTION_H
#define NEXUS_EXCEPTION_H

#include <exception>
#include <string>
#include <sstream>
class NexusException : public std::exception
{
 public:
	NexusException(int line, const char* file) noexcept;

	const char* what() const noexcept override;

	virtual const char* GetType() const noexcept;

	int GetLine() const noexcept;

	const std::string& GetFile() const noexcept;

	std::string GetOriginString() const noexcept;

 private:
	int line;

	std::string file;

 protected:
	mutable std::string whatBuffer;
};

#endif//NEXUS_EXCEPTION_H
