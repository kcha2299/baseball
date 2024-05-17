#include <string>
#include <stdexcept>

using namespace std;

struct GuessResult {
	bool solved;
	int strikes;
	int balls;
};

class Baseball {
public:
	explicit Baseball(const string& question)
		: question(question), result{ false, 0, 0 }
	{
	}

	bool isDuplicatedNumber(const std::string& guessNumber)
	{
		return (guessNumber[0] == guessNumber[1] ||
			guessNumber[0] == guessNumber[2] ||
			guessNumber[1] == guessNumber[2]);
	}

	void assertIlegalArgument(const std::string& guessNumber)
	{
		if (guessNumber.length() != 3) {
			throw length_error("Must be three letters.");
		}

		for (char ch : guessNumber) {
			if (ch >= '0' && ch <= '9') continue;
			throw invalid_argument("Must be number");
		}

		if (isDuplicatedNumber(guessNumber)) {
			throw invalid_argument("Must not have the same number");
		}
	}

	void countStrike(char number, int numberIdx) {
		if (number != question[numberIdx]) return;
		
		result.strikes++;
	}

	void countBall(char number, int numberIdx) {
		for (int qIdx = 0; qIdx < 3; qIdx++) {
			if (qIdx == numberIdx) continue;
			if (number != question[qIdx]) continue;

			result.balls++;
		}
	}

	GuessResult guess(const string& guessNumber) {
		assertIlegalArgument(guessNumber);
		if (guessNumber == question) {
			return { true, 3, 0 };
		}

		for (int index = 0; index < 3; index++) {
			countStrike(guessNumber[index], index);
			countBall(guessNumber[index], index);
		}

		return result;
	}

private:
	string question;
	GuessResult result;
};