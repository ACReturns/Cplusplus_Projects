#include <iostream>
#include <string>
#include <cctype>

using namespace std;

class InitializeGame
{
	public:
		void StartGame()
		{
			cout << "Please input Rock, Paper or Scissors" << endl;
		}
};

class Choices
{
	public:
		bool VerifyHand(string hand)
		{
			if (hand == "Rock" || hand == "Paper" || hand == "Scissors")
			{
				return true;
			}
			else
			{
				// Automatic loss if the entry isn't one of the 3 proper entries
				cout << "invalid entry\n";
				return false;
			}
		}
};

class StringVerification
{
public:
	string Verify(string input)
	{
		input[0] = toupper(input[0]);

		// Ensure all letters after the first one are in line with the expection of lowercase
		for (int i = 1; i < input.length(); i++)
		{
			input[i] = tolower(input[i]);
		}

		return input;
	}
};

class Results
{
	public:
		string MatchUps(string p1, string p2)
		{
			//Player vs CPU results
			if (p1 == "Rock" && p2 == "Scissors" || p1 == "Scissors" && p2 == "Paper" || p1 == "Paper" && p2 == "Rock")
			{
				cout << p1 << " beats " << p2 << " | " << "Player 1 wins" << endl;
				return "Player";
			}
			else if (p2 == "Rock" && p1 == "Scissors" || p2 == "Scissors" && p1 == "Paper" || p2 == "Paper" && p1 == "Rock")
			{
				cout << p2 << " beats " << p1 << " | " << "CPU wins" << endl;
				return "CPU";
			}
			else if (p1 == p2)
			{
				cout << "It's a Draw so nobody wins" << endl;
				return "Draw";
			}
		}
};

class Score
{
	public:
		int UpdateScore(int score)
		{
			return score + 1;
		}
};

class Rematch
{
	public:
		string userResponse;
		bool RematchCPU()
		{
			StringVerification stringVerify;
			cout << "Would you like to play again? (Y / Yes)" << endl;
			cin >> userResponse;
			userResponse = stringVerify.Verify(userResponse);

			if (userResponse == "Y" || userResponse == "Yes")
			{
				cout << "Rematching CPU" << endl << endl;
				return true;
			}
			else
			{
				return false;
			}
		}
};

int main()
{
	srand(time(NULL)); //initialize the random seed
	string handOptions[3] = { "Rock", "Paper", "Scissors" };
	string playerOption;
	string cpuOption;
	string winner;
	
	int randomSelect;
	int playerScore = 0;
	int cpuScore = 0;
	bool retryMatch = true;

	InitializeGame start;
	Choices choice;
	Results result;
	Score score;
	Rematch rematch;
	StringVerification stringVerify;
	
	while (retryMatch)
	{
		start.StartGame();
		cin >> playerOption;

		playerOption = stringVerify.Verify(playerOption);

		randomSelect = rand() % 3;
		cpuOption = handOptions[randomSelect];

		if (!choice.VerifyHand(playerOption))
		{
			cout << "Invalid input, CPU wins by default" << endl;
			cpuScore = score.UpdateScore(cpuScore);
			cout << endl << "Score" << endl << "Player: " << playerScore << endl << "CPU: " << cpuScore << endl;
			retryMatch = rematch.RematchCPU();
		}
		else
		{
			cout << "Player uses: " << playerOption << endl;
			cout << "CPU uses: " << cpuOption << endl;

			// Verify the winner and update the score
			winner = result.MatchUps(playerOption, cpuOption);
			if (winner == "Player")
			{
				playerScore = score.UpdateScore(playerScore);
			}
			else if (winner == "CPU")
			{
				cpuScore = score.UpdateScore(cpuScore);
			}
			cout << endl << "Score" << endl << "Player: " << playerScore << endl << "CPU: " << cpuScore << endl << endl;
			
			retryMatch = rematch.RematchCPU();
		}
	}
	
	system("exit");
}