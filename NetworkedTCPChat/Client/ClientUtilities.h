#include <string>

class CUtilities
{
public:
	enum class EColour
	{
		White,
		Red,
		Green,
		Yellow,
		Cyan,
	};

	static void Print(std::string _sString, int _iPreNewLines, int _iPostNewLines, EColour _eColour = EColour::White);

private:
	CUtilities() = delete;
	~CUtilities() = delete;

	static void SetTextColour(EColour _eColour);
};