//Name: Brennan McCabe
//Date: 6/14/2020
//Project Name: Colosseum
//Project Description: A short game about gladiator combat made for my Midterm Project for CIS 1202
//Note:Some funky stuff can happen if this is run on a linux or mac machine as the system commands i use may not work, for the best experiance run this program on windows

#include<iostream>
#include<string>
#include<iomanip>
#include<fstream>
#include<ctime>

using namespace std;

//This structure defines a gladiator character
struct Gladiator
{
	string name;
	int health = 0;
	int strength = 0;
	int speed = 0;
	int stamina = 0;
	int reputation = 0;
	int fightsFought = 0;
};

//fstream objects that will be used as save files later
ifstream playerSaveFileInput;
ofstream playerSaveFileOutput;

int mainMenu();
void instructions();
void createSaveFiles();
void loadSave(Gladiator&);
void createCharacter(Gladiator&);
void startGame();
void restPhase(Gladiator&, bool&);
void exitSequence(Gladiator);
void combatPhase(Gladiator&);
void combat(Gladiator&, Gladiator*);
int combatMenu();
void lossPhase(Gladiator&);

int main()
{
	int menuChoice;

	//Displaying the main menu and using a switch for the user's choice
	menuChoice = mainMenu();
	while (menuChoice != 3)
	{
		switch (menuChoice)
		{
		case(1):
			startGame();
			break;
		case(2):
			instructions();
			break;
		}
		menuChoice = mainMenu();
	}


	system("Pause");
	return 0;
}

int mainMenu()
{
	//Displaying the main menu
	int choice;
	cout << "**********\n";
	cout << "COLOSSEUM\n";
	cout << "**********\n\n";
	cout << "1.Start Game\n";
	cout << "2.Instructions\n";
	cout << "3.Exit\n\n";
	cin >> choice;
	//Validating the main menu choice
	while (choice > 3 || choice < 1)
	{
		cout << "\n\nERROR - PLEASE ENTER A CHOICE BETWEEN 1 and 3\n\n";
		cin >> choice;
	}
	return choice;
}

void startGame()
{
	bool quitGame = false;
	string yesOrNo;
	Gladiator player;
	//Seeing if the player has a saved game and loading it if they do, otherwise they are taken to the character creation menu
	cout << "\nDo you have a save file?  Y/N\n";
	cin >> yesOrNo;
	if (yesOrNo == "y" || yesOrNo == "Y" || yesOrNo == "yes" || yesOrNo == "Yes")
	{
		loadSave(player);
	}
	else if (yesOrNo == "n" || yesOrNo == "N" || yesOrNo == "no" || yesOrNo == "No")
	{
		createCharacter(player);
	}
	//*********************************************
	//Here is where the main logic of the game is *
	//*********************************************
	cout << "Welcome to the Colosseum gladiator. Your goal here is to survive for as long as you can and try to get a highscore!\n\n";
	while (!quitGame)
	{
		restPhase(player, quitGame);
		//Making sure the player didn't choose to exit
		if (quitGame)
		{
			return;
		}
		combatPhase(player);
		if (player.health <= 0)
		{
			system("cls");
			cout << "You have been defeated, your journey ends here\n";
			quitGame = true;
		}
	}

}

void createCharacter(Gladiator& player)
{
	//Creating a new save file for the player
	createSaveFiles();
	//Clearing the screen
	system("cls");
	//Walking the player through the character creation process
	cout << "Welcome to the character creator! What do you want to name your gladiator?\n";
	cin >> player.name;
	cout << "\n\nGreat! Now lets role for your stats\n\n";
	system("Pause");
	//Randomly generating the player's stats
	unsigned seed = time(0);
	srand(seed);
	player.health = 100;
	player.strength = ((rand() % (10 - 1 + 1)) + 1);
	player.speed = ((rand() % (10 - 1 + 1)) + 1);
	player.stamina = ((rand() % (10 - 1 + 1)) + 1);
	player.reputation = ((rand() % (10 - 1 + 1)) + 1);
	//Putting the new player's stats into a save file
	playerSaveFileOutput.open("playerSave.txt");
	playerSaveFileOutput << player.name << " ";
	playerSaveFileOutput << player.health << " ";
	playerSaveFileOutput << player.strength << " ";
	playerSaveFileOutput << player.speed << " ";
	playerSaveFileOutput << player.stamina << " ";
	playerSaveFileOutput << player.reputation << " ";
	playerSaveFileOutput << player.fightsFought << " ";
	playerSaveFileOutput.close();
	//Displaying the player's stats
	cout << "Here's what you rolled for your stats\n\n";
	cout << "Name: " << player.name << endl;
	cout << "Health: " << player.health << endl;
	cout << "Strength: " << player.strength << endl;
	cout << "Speed: " << player.speed << endl;
	cout << "Stamina: " << player.stamina << endl;
	cout << "Reputation: " << player.reputation << endl;
	cout << "Fights fought: " << player.fightsFought << endl << endl;
	system("Pause");
	system("cls");
}

void createSaveFiles()
{
	//Creating the playerSave file
	playerSaveFileInput.open("playerSave.txt");
	playerSaveFileInput.close();
	playerSaveFileOutput.open("playerSave.txt");
	playerSaveFileOutput.close();
}

void loadSave(Gladiator& player)
{
	//Grabbing player data from the save and getting the level the
	playerSaveFileInput.open("playerSave.txt");
	playerSaveFileInput >> player.name;
	playerSaveFileInput >> player.health;
	playerSaveFileInput >> player.strength;
	playerSaveFileInput >> player.speed;
	playerSaveFileInput >> player.stamina;
	playerSaveFileInput >> player.reputation;
	playerSaveFileInput >> player.fightsFought;
	playerSaveFileInput.close();
	//Displaying what was pulled from the save
	cout << "Here's your save!\n\n";
	cout << "Name: " << player.name << endl;
	cout << "Health: " << player.health << endl;
	cout << "Strength: " << player.strength << endl;
	cout << "Speed: " << player.speed << endl;
	cout << "Stamina: " << player.stamina << endl;
	cout << "Reputation: " << player.reputation << endl;
	cout << "Fights fought: " << player.fightsFought << endl << endl;
	system("Pause");
	system("cls");

}

void restPhase(Gladiator& player, bool& quitGame)
{
	int choice;
	//Displaying the player's stats
	cout << "\n\nYour gladiator's stats\n";
	cout << "Name: " << player.name << endl;
	cout << "Health: " << player.health << endl;
	cout << "Strength: " << player.strength << endl;
	cout << "Speed: " << player.speed << endl;
	cout << "Stamina: " << player.stamina << endl;
	cout << "Reputation: " << player.reputation << endl;
	cout << "Fights fought: " << player.fightsFought << endl << endl;
	//The rest menu which will allow a player to heal our improve their stats
	cout << "\n\nYou are in the gladiators quartes below the colosseum. There are multiple things you can do here but be careful, you only have time to do one of them before having to fight\n\n";
	cout << "1.Rest and bathe (+10 Health)\n";
	cout << "2.Train with weights (+1 Strength)\n";
	cout << "3.Run around the underground track (+1 Speed)\n";
	cout << "4.Spar with another gladiator (+1 Stamina)\n";
	cout << "5.Talk with some diplomats in the public baths (+5 Reputation)\n";
	cout << "6.Leave the arena (Quit Game)\n\n";
	cin >> choice;
	//This while loop validates rest menu input
	while (choice > 6 || choice < 1)
	{
		cout << "\nPlease enter a choice between 1 and 5\n";
		cin >> choice;
	}
	//A switch that applies changes based on what the user wanted to do in the rest menu
	switch (choice)
	{
	case(1):
		player.health += 10;
		//Resets the player's health to 100 if they go over by healing
		if (player.health >= 100)
		{
			player.health = 100;
		}
		break;
	case(2):
		player.strength += 1;
		break;
	case(3):
		player.speed += 1;
		break;
	case(4):
		player.stamina += 1;
		break;
	case(5):
		player.reputation += 5;
		break;
	case(6):
		exitSequence(player);
		quitGame = true;
		break;
	}
}

void exitSequence(Gladiator player)
{
	//The exit sequence basically just saves the player's data in a save file
	playerSaveFileOutput.open("playerSave.txt");
	playerSaveFileOutput << player.name << " ";
	playerSaveFileOutput << player.health << " ";
	playerSaveFileOutput << player.strength << " ";
	playerSaveFileOutput << player.speed << " ";
	playerSaveFileOutput << player.stamina << " ";
	playerSaveFileOutput << player.reputation << " ";
	playerSaveFileOutput.close();
	cout << "\nGame saved!\n";
}

void combatPhase(Gladiator& player)
{
	//Dynamically creating an enemy for the player to fight
	Gladiator* enemyPtr = nullptr;
	enemyPtr = new Gladiator;
	//Randomly generating the enemy's stats using the number of fights the player has won to scale the combat difficulty
	unsigned seed = time(0);
	srand(seed);
	enemyPtr->name = "Enemy";
	enemyPtr->health = 100;
	enemyPtr->strength = ((rand() % ((player.fightsFought + 5) - (player.fightsFought) + 1)) + (player.fightsFought));
	enemyPtr->speed = ((rand() % ((player.fightsFought + 5) - (player.fightsFought) + 1)) + (player.fightsFought));
	enemyPtr->stamina = ((rand() % ((player.fightsFought + 5) - (player.fightsFought) + 1)) + (player.fightsFought));
	enemyPtr->reputation = ((rand() % ((player.fightsFought + 5) - (player.fightsFought) + 1)) + (player.fightsFought));

	//Clearing the screen for combat text
	system("cls");
	//Comparing the enemy to the player
	cout << "\nThis is fight number " << player.fightsFought + 1 << endl << endl;
	cout << "Here's how you and your enemy match up\n";
	cout << "            Player" << "          " << "Enemy\n";
	cout << "Strength:   " << player.strength << "          " << enemyPtr->strength << endl;
	cout << "Speed:      " << player.speed << "          " << enemyPtr->speed << endl;
	cout << "Stamina:    " << player.stamina << "          " << enemyPtr->stamina << endl;
	cout << "Reputation: " << player.reputation << "          " << enemyPtr->reputation << endl << endl;
	system("Pause");
	system("cls");
	combat(player, enemyPtr);
	delete(enemyPtr);
}

void combat(Gladiator& player, Gladiator* enemy)
{
	int choice;
	unsigned seed = time(0);
	srand(seed);
	//Combat will continue to run until either the player's or the enemy's health reaches 0
	while (player.health > 0 && enemy->health > 0)
	{
		//These variables are used for combat calculations and are reset to 0 for each bout
		int playerAttack = 0, enemyAttack = 0;
		//Displaying the health of both characters
		cout << "Player Health: " << player.health << "   Enemy Health: " << enemy->health << endl << endl;
		choice = combatMenu();
		switch (choice)
		{
		case(1):
			//Calculating Attacks
			playerAttack = ((rand() % ((player.strength + player.speed) - 1+ 1)) + (1));
			enemyAttack = ((rand() % ((enemy->strength + enemy->speed) - 1 + 1)) + (1));
			//Seeing who won
			if (playerAttack > enemyAttack)
			{
				cout << "\n\nYou struck the enemy for " << playerAttack << " damage!\n";
				enemy->health -= playerAttack;
			}
			else if (enemyAttack > playerAttack)
			{
				cout << "\n\nThe enemy struck you for " << enemyAttack << " damage!\n";
				player.health -= enemyAttack;
			}
			else
			{
				cout << "\n\nYou and the enemy traded blows but neither of you landed a hit\n";
			}
			break;
		case(2):
			//Calculating Attacks
			playerAttack = ((rand() % ((player.speed) - 1 + 1)) + 1);
			enemyAttack = ((rand() % ((enemy->speed) - 1 + 1)) + 1);
			//Seeing who won
			if (playerAttack > enemyAttack)
			{
				cout << "\n\nYou struck the enemy for " << playerAttack << " damage!\n";
				enemy->health -= playerAttack;
			}
			else if (enemyAttack > playerAttack)
			{
				cout << "\n\nThe enemy struck you for " << enemyAttack << " damage!\n";
				player.health -= enemyAttack;
			}
			else
			{
				cout << "\n\nYou and the enemy traded blows but neither of you landed a hit\n";
			}
			break;
		case(3):
			//Calculating Attacks
			playerAttack = ((rand() % ((player.strength + player.stamina) - 1 + 1)) + 1);
			enemyAttack = ((rand() % ((enemy->strength + enemy->stamina) - 1 + 1)) + 1);
			//Seeing who won
			if (playerAttack > enemyAttack)
			{
				cout << "\n\nYou struck the enemy for " << playerAttack << " damage!\n";
				enemy->health -= playerAttack;
			}
			else if (enemyAttack > playerAttack)
			{
				cout << "\n\nThe enemy struck you for " << enemyAttack << " damage!\n";
				player.health -= enemyAttack;
			}
			else
			{
				cout << "\n\nYou and the enemy traded blows but neither of you landed a hit\n";
			}
			break;
		case(4):
			//Calculating Attacks
			playerAttack = ((rand() % ((player.stamina) - 1 + 1)) + 1);
			enemyAttack = ((rand() % ((enemy->stamina) - 1 + 1)) + 1);
			//Seeing who won
			if (playerAttack >= enemyAttack)
			{
				cout << "\n\nYou blocked the enemy's attacks and regained some of your health\n";
				player.health += 5;
				//Player's health cannot go over 100
				if (player.health > 100)
				{
					player.health = 100;
				}
			}
			else if (enemyAttack > playerAttack)
			{
				cout << "\n\nThe enemy broke through your defenses and dealt " << enemyAttack << " damage!\n";
				player.health -= enemyAttack;
			}
			break;
		case(5):
			cout << "The emperors guards beat you and take you before the emperor\n";
			player.health = 0;
			//This just exits the switch which will take the player to the loss phase
			break;
		}
		system("Pause");
		system("cls");
	}
	//Adding to the fights fought
	player.fightsFought += 1;
	//If the player dies their health will be set to 10 in case they win favour later and are allowed to continue
	if (player.health <= 0)
	{
		player.health = 50;
		lossPhase(player);
	}
}

int combatMenu()
{
	//Displaying the combat menu
	int choice;
	cout << "Choose your next move\n\n";
	cout << "1. Normal Attack (Strength & Speed)\n";
	cout << "2. Quick Attack  (Speed)\n";
	cout << "3. Power Attack (Strength & Stamina)\n";
	cout << "4. Defend (Stamina)\n";
	cout << "5. Give up\n\n";
	cin >> choice;
	//Validating menu choice
	if (choice > 5 || choice < 1)
	{
		cout << "\nPlease enter an option between 1 and 5\n";
		cin >> choice;
	}
	return choice;
}

void lossPhase(Gladiator& player)
{
	int favor;
	cout << "\n\nYou have lost this battle, the emperor will now decide your fate\n";
	system("Pause");
	system("cls");
	//Determining what the emperor's favor of the gladiator is
	favor = ((rand() % ((player.reputation + 10) - 1 + 1)) + 1);
	//Calculating wether the player lives or dies
	if (favor >= 10)
	{
		cout << "The emperor has decided that you may live to see another day\n";
		cout << "Your reputation has been reset\n";
		player.reputation = 0;
		system("Pause");
		system("cls");
	}
	else if (favor < 10)
	{
		cout << "Today is not your day, the emperor has decided that you shall be executed\n";
		player.health = 0;
		system("Pause");
		system("cls");
	}


}

void instructions()
{
	system("cls");
	cout << "This game simulates a gladiator arena\n";
	cout << "Your goal is to survive for as long as you can\n\n";
	cout << "Before each fight you have multiple options to boost your stats or exit the game (Your game will be saved when exiting)\n";
	cout << "Strength: How strong you are\n";
	cout << "Speed: How fast you are\n";
	cout << "Stamina: How long you can hold up\n";
	cout << "Reputation: How much people like you\n";
	cout << "\nDuring combat you have five options\n";
	cout << "Normal Attack: This is your standard attack, it uses you and your oppenents strength and speed\n";
	cout << "Quick Attack: This is a fast attack that uses just you and your oppenents speed\n";
	cout << "Power Attack: This is a heavy attack that uses you and your opponents strength and stamina\n";
	cout << "Defend: This will use your stamina against your opponents, if you win this you get +10 health\n";
	cout << "Give up: This will cause you to lose the battle and go up against the emperor's judgement\n";
	cout << "\nAfter you lose or give up a fight you will have to face the emperor's judgement\n";
	cout << "The emperor will decide wheter you live or die based on your reputation\n";
	system("Pause");
	system("cls");
}