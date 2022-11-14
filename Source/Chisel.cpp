#include<string>
#include<array>

using namespace std;
class Chisel
{
public:
	Chisel(string ParsedHTML):
		ParsedHTML(ParsedHTML)
	{
		for (int i = 0; i < BLOCK_COUNT; i++)
		{
			Blocks[i] = "";
		}
	}

private:
	string ParsedHTML;
	const uint8_t BLOCK_COUNT = 4;
	string* Blocks;
	enum BlockTypes {
		Input,
		Output,
		Algorithm,
		Examples
	};
};