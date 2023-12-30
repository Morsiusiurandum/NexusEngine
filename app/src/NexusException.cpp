#include "NexusException.h"

NexusException::NexusException(int line, const char* file) noexcept
	: line(line), file(file)
{
}
const char* NexusException::what() const noexcept
{
	std::ostringstream oss;
	oss << GetType() << std::endl
		<< GetOriginString() << line;
	whatBuffer = oss.str();

	return whatBuffer.c_str();
}

std::string NexusException::GetOriginString() const noexcept
{
	std::ostringstream oss;
	oss << "[File]" << file << std::endl
		<< "[Line]" << line;
	return oss.str();
}
const char* NexusException::GetType() const noexcept
{
	return "Nexus Exception";
}
int NexusException::GetLine() const noexcept
{
	return line;
}
const std::string& NexusException::GetFile() const noexcept
{
	return file;
}
