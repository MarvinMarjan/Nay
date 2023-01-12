#pragma once

#include <string>

namespace sys
{
	enum ExceptionList {
		FileNotFound
	};

	class Exception
	{
	public:
		friend Exception exception(ExceptionList, std::string);
		friend class System;

	private:

		std::string name;
		std::string msg;
		std::string complement = "";
	};

	Exception exception(ExceptionList exception_type, std::string complement = "")
	{
		Exception _exception;

		switch (exception_type)
		{
		case FileNotFound:
			_exception.name = "FileNotFound";
			_exception.msg = "couldn't found the following file";
			_exception.complement = complement;
		}

		return _exception;
	}
}