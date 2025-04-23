#include <string>

class CCommands
{
public:
	enum class ECommand
	{
		n,
		Error,
		Capitalize,
		Put,
		Get,
		Quit,
	};

	static ECommand CheckForCommand(std::string* _psMessage);

private:
	CCommands() = delete;
	~CCommands() = delete;

	static ECommand DetermineCommand(std::string* _psMessage);

	static void TrimMessage(std::string* _psMessage);

	static ECommand CapitalizeMessage(std::string* _psMessage);

	static ECommand GetMessage(std::string* _psMessage);

	static ECommand PutMessage(std::string* _psMessage);

	static ECommand Quit(std::string* _psMessage);
};