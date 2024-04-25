#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <stdlib.h>
#include <conio.h>
#include <cstring>
using namespace std;

//Declaring Function Prototypes
int fileRead();
int tossWinner();
char inputValidation();
int* simulation(string*, string*, int, int, int, int);
int display(string, int, int, string, int, int, int, int, string, int, int, string*, int[], float, int[], int, int, string*, int);
void choiceOperation();

int main()
{
	//Initializing Needed Variable
	int size = 11;
	string* team1 = new string[size]{"Hanif Muhammad", "Javed Miandad", "Imran Khan", "Younis Khan", "Babar Azam", "Muhammad Rizwan", "Shoaib Akhter", "Shaheen Afridi", "Yasir Khan", "Wasim Akram", "Waqar Younis"};
	string* team2 = new string[size]{"Viv Richards", "Sachin Tendulkar", "Zaheer Abbas", "Greg Chappell", "David Gower", "AB de Villiars", "Shaun Pollock", "Richard Hadlee", "Joel Garner", "Glen McGarth", "Bret Lee"};
	int wickets = 0;
	int overs = 0;
	char randomCoin;
	int toss;
	int coin = 0;
	int innings = 0;
	
	//Configuration file for reading the number of overs
	overs = fileRead();
	cout << "The match has " << overs  << " overs " << endl;
	
	//Getting the output of the coin if its heads or tails
	randomCoin = inputValidation();
	toss = tossWinner();
	if(randomCoin == 't')
	{
		coin = 1;
	}
	
	//Expressions to check which output of the satisfies the condition
	//If the coin and the call is same the first team will bat.
	if (coin == toss)
	{
		cout << "Team 1, You won the toss! You will bat first!" << endl;
		//Expression to check if r key is pressed to jump to our desired overs;
		if(getch() == 'r')
		{
			int newOver;
			cout << "Enter Overs: ";
			cin >> newOver;
			overs = newOver;
		}
		system("cls");
		
		//First Innings function
		int* InningsRecord1 = simulation(team1, team2, size,overs,wickets, innings);
		cout << "\n2nd innings starting!"<<endl;
		
		//2nd innings function
		int* InningsRecord2 = simulation(team2, team1, size,overs,wickets, innings);
		
		//Variables to store the total score of both teams
		int totalScore1 = InningsRecord1[0];
		int totalScore2 = InningsRecord2[0];
		
		//Writing the output in the file to store it for furthur use 
		ofstream fout;
		fout.open("CurrentMatchSummary.txt", ios::trunc);
		
		//cout << "Total Score of Team1: " << totalScore1 << endl;
		//cout << "Total Score of Team2: " << totalScore2 << endl;
		
		//Expressions to check which team won
		//Simultaneously writing in the file
		if(InningsRecord1[0] > InningsRecord2[0])
		{
			cout << "Match Winner: Team 1!!" << endl;
			fout << "Match Winner: Team 1!!" << endl;
		}
		else if(InningsRecord1[0] < InningsRecord2[0])
		{
			cout << "Match Winner: Team 2!!" << endl;
			fout << "Match Winner: Team 2!!" << endl;
		}
		else if(InningsRecord1[0] == InningsRecord2[0])
		{
			cout << "Match Drawn!!" << endl;
			fout << "Match Drawn!!" << endl;
		}
		
		//Expressions to check which team player would be awarded as the batsman of the match
		//Simultaneously writing in the file
		if(InningsRecord1[1] > InningsRecord2[1])
		{
			cout << "Batsman of the match: " <<  team1[InningsRecord1[4]] << endl;
			fout << "Batsman of the match: " <<  team1[InningsRecord1[4]] << endl;
		}
		else if(InningsRecord1[1] < InningsRecord2[1])
		{
			cout << "Batsman of the match: " << team2[InningsRecord2[4]] << endl;
			fout << "Batsman of the match: " << team2[InningsRecord2[4]] << endl;
		}
		else if(InningsRecord1[1] == InningsRecord2[1])
		{
			cout << "No top Batsman" << endl;
			fout << "No top Batsman" << endl;
		}
		
		//Expression to award who is the bowler of the match
		//Simultaneously writing in the file
		if(InningsRecord1[2] > InningsRecord2[2])
		{
			cout << InningsRecord1[4]+5;
			cout << "Bowler of the match: " << team1[InningsRecord1[3]+5] << endl;
			fout << "Bowler of the match: " << team1[InningsRecord1[3]+5] << endl;
		}
		else if(InningsRecord1[2] < InningsRecord2[2])
		{
			cout << "Bowler of the match: " << team2[InningsRecord2[3]+5] << endl;
			fout << "Bowler of the match: " << team2[InningsRecord2[3]+5] << endl;
		}
		else if(InningsRecord1[2] == InningsRecord2[2])
		{
			cout << "No top Bowler" << endl;
			fout << "No top Bowler" << endl;
		}
	}
	
	//The expression if the coin and call is not same
	//Team 2 will bat first in this case and Team 1 will bowl first.
	else
	{
		cout << "Team 1, You lost! You will bowl first!" << endl;
		//To set the number of overs
		if(getch()=='r')
		{
			int newOver;
			cout << "Enter Overs: ";
			cin >> newOver;
			overs = newOver;
		}
		//System call for clearing screen 
		system("cls");
		
		//First and Second innings
		int* InningsRecord1 = simulation(team2, team1, size,overs,wickets, innings);
		cout << "\n2nd innings starting!"<<endl;
		int* InningsRecord2 = simulation(team1, team2, size,overs,wickets, innings);
		
		/*
		The next couple of expression as shown in the previous condition
		checks which team is the winner, who is the  batsman of the match, and
		who is the bowler of the match. These expressions goes to line 214.
		Simultaneously, writing them in a file
		*/
		cout << "Total Score of Team1: " << InningsRecord1[0] << endl;
		cout << "Total Score of Team2: " << InningsRecord2[0] << endl;		
		ofstream fout;
		fout.open("CurrentMatchSummary.txt", ios::trunc);
		
		cout << InningsRecord1[2] << " " << InningsRecord2[2] << endl;
		cout << InningsRecord1[3] << " " << InningsRecord2[3] << endl;
		if(InningsRecord1[0] > InningsRecord2[0])
		{
			cout << "Match Winner: Team 1!!" << endl;
			fout << "Match Winner: Team 1!!" << endl;
		}
		else if(InningsRecord1[0] < InningsRecord2[0])
		{
			cout << "Match Winner: Team 2!!" << endl;
			fout << "Match Winner: Team 2!!" << endl;
		}
		else if(InningsRecord1[0] == InningsRecord2[0])
		{
			cout << "Match Drawn!!" << endl;
			fout << "Match Drawn!!" << endl;
		}

		if(InningsRecord1[1] > InningsRecord2[1])
		{
			cout << "Batsman of the match: " <<  team1[InningsRecord1[4]] << endl;
			fout << "Batsman of the match: " <<  team1[InningsRecord1[4]] << endl;
		}
		else if(InningsRecord1[1] < InningsRecord2[1])
		{
			cout << "Batsman of the match: " << team2[InningsRecord2[4]] << endl;
			fout << "Batsman of the match: " << team2[InningsRecord2[4]] << endl;
		}
		else if(InningsRecord1[1] == InningsRecord2[1])
		{
			cout << "No top Batsman" << endl;
			cout << "No top Batsman" << endl;
		}
		
		if(InningsRecord1[2] > InningsRecord2[2])
		{
			cout << "Bowler of the match: " << team1[InningsRecord1[3]+ 6] << endl;
			fout << "Bowler of the match: " << team1[InningsRecord1[3]+ 6] << endl;
		}
		else if(InningsRecord1[2] < InningsRecord2[2])
		{
			cout << "Bowler of the match: " << team2[InningsRecord2[3]+ 6] << endl;
			fout << "Bowler of the match: " << team2[InningsRecord2[3]+ 6] << endl;
		}
		else if(InningsRecord1[2] == InningsRecord2[2])
		{
			cout << "No top Bowler" << endl;
			fout << "No top Bowler" << endl;
		}
		//Closing the file
		fout.close();
	}
	
	//Function to show the menu for furthur information
	choiceOperation();
	delete[] team1;
	delete[] team2;
}

/*
This function reads the configuration file and gives us the nubmber of
overs, this match is played for.
*/
int fileRead()
{
	int number;
	ifstream inputData;
	inputData.open("configuration.txt");
	if(inputData.is_open())  //If file is found in the directory
	{
		while(!inputData.eof())
		{
			inputData >> number;
			//cout << "The match has " << overs  << " overs " << endl;;
			return number;
		}
	}
	else //If is file is not in the directory
	{
		cout << "Unable to find file!" << endl;
	}
}

//Function to return the random number between 0 or 1 to furhtur tell us who won the toss
int tossWinner()
{
	srand(time(NULL));
	int randNum = rand()%2;
	return randNum;
}

//Input validation for toss. Verifys that the input is h or t.
char inputValidation()
{
	char tossChoice;
	bool guess;
	cout << "Toss is going to begin!\n0- Heads\n1- Tails\nTeam 1, Call: h for heads and t for tails!" << endl;
	bool test = false;
	do
	{
		cin >> tossChoice;
		if(tossChoice == 'h' || tossChoice == 't' || tossChoice == 'H' || tossChoice == 'T')
		{
			test = true;
		}
		else
		{
			cout << "Invalid Input!! Press h for heads, t for tails!" << endl;
		}
	}while(!test);
	return tossChoice;
}

/*
This function is the one which is calculating every information. This function is
basically the backbone  of this code. Calculating score, displaying scorecard, etc. 
everything is being done on this function.
This function stimulates the game. 
*/
int* simulation(string* batTeam, string* bowlTeam, int size, int overs, int wickets, int innings)
{
	//Displaying the batting and the bowling team!
	cout << " =====================================================" << endl;
	cout << "|       Batting Team       |        Bowling Team      |" << endl;
	cout << " =====================================================" << endl;
	for(int i=0; i<size; i++)
	{
		cout << "|" <<setw(3)<< i+1 <<setw(20)<<batTeam[i]<<setw(4)<< "|"
		<<setw(3) << i+1 <<setw(20)<<bowlTeam[i]<<setw(4)<<"|" <<endl; 
	}
	cout << " =====================================================" << endl;
	
	//Expression to set over mid-game
	if(getch() == 'r')
	{
		int newOver;
		cout << "Enter Overs: ";
		cin>>newOver;
		overs = newOver;
	}
	system("cls");
	
	//Initializing variables and dynamic arrays
	int *batsman = new int[11];
	for(int i=0; i<11; i++)
	{
		batsman[i] = 0;
	}
	string p1 = batTeam[0];
	string p2 = batTeam[1];
	int player1 = batsman[0]; //Always playing the ball 
	int player2 = batsman[1]; //On the other other side
	int nextBatsman = 2;
	int maxBalls = overs*6;
	int total_balls = 0;
	int balls_played1 = 0;
	int balls_played2 = 0;
	int score = 0;
	int total_score = 0;
	int count = 0;
	float runRate = 0.0;
	int Overs = 0;
	int* overall = new int[5];
	for(int i=0; i<5; i++)
	{
		overall[i] = 0;
	}
	int *bowlers_wickets = new int[5];
	for(int i=0; i<5;i++)
	{
		bowlers_wickets[i] = 0;
	}
	
	//Loop for calculating score and displayiing scorecard repeatedly
	for(int i=0; i<overs; i++)
	{
		for(int j=0; j<6; j++)
		{
			//Current Bowler
			string bowler = bowlTeam[count+6];
			cout << "Press enter to bowl..." << endl;
			getch();  //Functionality to press enter for bowl
			
			//This expression generates a random number for batsman with probability
			if(nextBatsman < 6)
			{
				double prob = (double)rand()/RAND_MAX;
				if(prob >= 0.9)
				{
					score = -1;
				}
				else
				{
					score = rand()%7;
				}
				cout <<"Runs: "<< score << endl;  //Displays the run scored by batsman facing the bowler
				
				
				//if the score is 1,3,5 the two batsman swap thier positions and the next batsman will the bowler now 
				if(score == 1 || score == 3 || score == 5)
				{
					total_score += score;
					player1 += score;
					balls_played1++;
					batsman[nextBatsman-2] = player1;
					batsman[nextBatsman-1] = player2;
					
					//Displays scorecard
					Overs = display(p1, player1, total_score, p2, player2, balls_played1, balls_played2, total_balls, bowler,i,j, bowlTeam,bowlers_wickets, runRate,batsman, wickets, nextBatsman, batTeam, overs);
					if(Overs > overs)
					{
						//cout << "Over exceeding limit!\n";
					}
					else
					{
						i=Overs;
						total_balls+=i*6;
					}
					
					//Swapping the batsman 
					string temp2 = p1;
					p1 = p2;
					p2 = temp2;
					
					int temp = player1;
					player1 = player2;
					player2 = temp;
					
					int temp3 = balls_played1;
					balls_played1 = balls_played2;
					balls_played2 = temp3;					
				}
				//If the score is even. Batsman doesnot swap
				else if(score%2==0)
				{
					total_score += score;
					player1 += score;
					balls_played1++;
					batsman[nextBatsman-2] = player1;
					batsman[nextBatsman-1] = player2;
					
					int Overs = display(p1, player1, total_score, p2, player2, balls_played1, balls_played2, total_balls, bowler,i,j, bowlTeam,bowlers_wickets,runRate, batsman, wickets, nextBatsman, batTeam, overs);	
					if(Overs > overs)
					{
					//	cout << "Over exceeding limit!\n";
					}
					else
					{
						i=Overs;
						total_balls+=i*6;
					}
				}
				
				//If score is -1 then the bowler will be out. 
				else if(score == -1)
				{
					//Bowler index will be stored for saving the number of wickets taken by him
					balls_played1++;
					bowlers_wickets[count] +=1;
					batsman[nextBatsman-2] = player1;
					batsman[nextBatsman-1] = player2;
					Overs = display(p1, player1, total_score, p2, player2, balls_played1, balls_played2, total_balls, bowler,i,j, bowlTeam, bowlers_wickets, runRate, batsman, wickets, nextBatsman, batTeam, overs);
					if(Overs > overs)
					{
					//	cout << "Over exceeding limit!\n";
					}
					else
					{
						i=Overs;
						total_balls+=i*6;
					}
					balls_played1=0;
					p1 = batTeam[nextBatsman];
					player1 = batsman[nextBatsman];
					nextBatsman++;
					wickets++;
				}
			}
			
			//Expression to check if the bowlers are batting for them the
			//probability will 50% to get out.
			//The code functionality is the same as given in above if
			else
			{
				double prob = (double)rand()/RAND_MAX;
				if(prob < 0.5)
				{
					score = -1;
				}
				else
				{
					score = rand()%7;
				}
				cout <<"Runs: "<< score << endl;
				if(score == 1 || score == 3 || score == 5)
				{
					total_score += score;
					player1 += score;
					balls_played1++;
					batsman[nextBatsman-2] = player1;
					batsman[nextBatsman-1] = player2;
					Overs = display(p1, player1, total_score, p2, player2, balls_played1, balls_played2, total_balls, bowler,i,j, bowlTeam,bowlers_wickets, runRate, batsman, wickets, nextBatsman, batTeam, overs);
					if(Overs > overs)
					{
					//	cout << "Over exceeding limit!\n";
					}
					else
					{
						i=Overs;
						total_balls+=i*6;
					}	
					string temp2 = p1;
					p1 = p2;
					p2 = temp2;
					
					int temp = player1;
					player1 = player2;
					player2 = temp;
					
					int temp3 = balls_played1;
					balls_played1 = balls_played2;
					balls_played2 = temp3;
					
				}
				else if(score%2==0)
				{
					total_score += score;
					player1 += score;
					balls_played1++;
					batsman[nextBatsman-2] = player1;
					batsman[nextBatsman-1] = player2;
					Overs = display(p1, player1, total_score, p2, player2, balls_played1, balls_played2, total_balls, bowler,i,j,bowlTeam,bowlers_wickets, runRate, batsman, wickets, nextBatsman, batTeam, overs); 	
					if(Overs > overs)
					{
					//	cout << "Over exceeding limit!\n";
					}
					else
					{
						i=Overs;
						total_balls+=i*6;
					}
				}
				
				else if(score == -1)
				{
					if(wickets == 9)
					{
						wickets++;
						balls_played1++;
						bowlers_wickets[count] += 1;
						Overs = display(p1, player1, total_score, p2, player2, balls_played1, balls_played2, total_balls, bowler,i,j,bowlTeam,bowlers_wickets, runRate, batsman, wickets, nextBatsman, batTeam, overs);
						if(Overs > overs)
						{
						//	cout << "Over exceeding limit!\n";
						}
						else
						{
							i=Overs;
							total_balls+=i*6;
						}
						balls_played1=0;
						innings++;
						cout << "Innings over! All out!" << endl;
						//In case of all players are out, the valuable information will be returned to main() function
						int topBatsman = batsman[0];
						int topBowler = bowlers_wickets[0];
						int topBatsmanIndex = 0;
						int topBowlerIndex = 0;
						for(int i=0; i<11; i++)
						{
							if(topBatsman < batsman[i])
							{
								topBatsman = batsman[i];
								topBatsmanIndex = i;
							}
						}
						for(int i=0; i<5; i++)
						{
							if(topBowler<bowlers_wickets[i])
							{
								topBowler = bowlers_wickets[i];
								topBowlerIndex = i;	
							}
						}
						overall[0] = total_score;
						overall[1] = topBatsman;
						overall[2] = topBowler;
						overall[3] = topBowlerIndex;
						overall[4] = topBatsmanIndex;
						return overall;
					}
					balls_played1++;
					bowlers_wickets[count] += 1;
					batsman[nextBatsman-2] = player1;
					batsman[nextBatsman-1] = player2;
					Overs = display(p1, player1, total_score, p2, player2, balls_played1, balls_played2, total_balls, bowler,i,j,bowlTeam,bowlers_wickets, runRate, batsman, wickets, nextBatsman, batTeam, overs);
					if(Overs > overs)
					{
					//	cout << "Over exceeding limit!\n";
					}
					else
					{
						i=Overs;
						total_balls+=i*6;
					}
					balls_played1=0;
					
					p1 = batTeam[nextBatsman];
					player1 = batsman[nextBatsman];
					nextBatsman++;
					wickets++;	
				}
			}
			total_balls++;
			cout << "Total: " << i*6 << endl;
		}
		string temp2 = p1;
		p1 = p2;
		p2 = temp2;
		
		int temp = player1;
		player1 = player2;
		player2 = temp;
		
		int temp3 = balls_played1;
		balls_played1 = balls_played2;
		balls_played2 = temp3;
		
		//Incase if all balls are played, then the valuable information is again
		//returned to main() function
		if(total_balls == maxBalls)
		{
			innings++;
			cout << "Innings Over. All overs played!" << endl;
			int topBatsman = batsman[0];
			int topBowler = bowlers_wickets[0];
			int topBowlerIndex = 0;
			int topBatsmanIndex = 0;
			for(int i=0; i<11; i++)
			{
				if(topBatsman < batsman[i])
				{
					topBatsman = batsman[i];
					topBatsmanIndex = i;
				}
			}
			
			for(int i=0; i<5; i++)
			{
				if(topBowler<bowlers_wickets[i])
				{
					topBowler = bowlers_wickets[i];
					topBowlerIndex = i;
				}
			}
			overall[0] = total_score;
			overall[1] = topBatsman;
			overall[2] = topBowler;
			overall[3] = topBowlerIndex;
			overall[4] = topBatsmanIndex;
			
			return overall;
		}
		
		//To make that the player coming bowl is always the bowlers of the team
		count++;
		if(count == 5)
		{
			count = 0;
		}
	}
}

//This function prints the scorecard and simultaneously saves them in a file
int display(string player1, int score1, int total_score, string player2, int score2, int balls_played1, int balls_played2, int totalBalls, string bowler, int over, int ball, string* bowlerCard, int wicketTaken[], float runRate, int batsman[], int id, int order, string* batters, int OrigOver)
{
	int wick = 0;
	for(int i=0; i<5; i++)
	{
		wick+= wicketTaken[i];
	}
	
	int corrOver = over+1;
	runRate = ((float)total_score)/((float)corrOver);
		
	cout << setw(1) << " ----------------------------------------------------------------" << endl;
	cout << setw(2) << "|" << setw(35) << "SCORECARD"  << setw(28) << "|" << endl;
	cout << setw(1) << " ----------------------------------------------------------------" << endl;
	cout << setw(2) << "|" << setw(20) << "Batsman Name" << setw(7) << "|" << setw(25) << "| " << " R " << " | " << " B " << " |"<<endl; 
	cout << setw(1) << " ----------------------------------------------------------------" << endl;
	cout << setw(2) << "|" << setw(20) << player1 << setw(7) << "|" << setw(24) << "|" << setw(3)<< score1 <<setw(3)<< "|" << setw(3)<< balls_played1 <<setw(3)<< "|"<<endl; 
	cout << setw(1) << " ----------------------------------------------------------------" << endl; 
	cout << setw(2) << "|" << setw(20) << player2 << setw(7) << "|" << setw(24) << "|" << setw(3)<< score2 <<setw(3)<< "|" << setw(3)<< balls_played2 <<setw(3)<< "|"<<endl; 
	cout << setw(1) << " ----------------------------------------------------------------" << endl;
	cout << setw(2) << "|" << setw(63) << "|" <<endl; 
	cout << setw(2) << "|" << setw(19) <<"Overs: " <<over<<"."<<ball+1 <<setw(14)<<"RunRate: "<<setprecision(2)<< runRate << setw(12) << "Total:" <<setw(7)<< total_score <<"/"<<wick<<setw(3)<< "|" <<endl;
	cout << setw(1) << " ----------------------------------------------------------------" << endl; 
	cout << endl<<endl;
	
	cout << setw(1) << " ----------------------------------------------------------------" << endl;
	cout << setw(2) << "|" << setw(20) << "Bowler Name" << setw(32) << "|" << setw(8) << "Wickets" << setw(3) << "|" <<endl;
	cout << setw(1) << " ----------------------------------------------------------------" << endl;
	cout << setw(2) << "|" << setw(20) << bowlerCard[6] <<setw(38) << wicketTaken[0] << setw(5) <<"|"<<endl;
	cout << setw(2) << "|" << setw(20) << bowlerCard[7] <<setw(38) << wicketTaken[1] << setw(5) <<"|"<<endl;
	cout << setw(2) << "|" << setw(20) << bowlerCard[8] <<setw(38) << wicketTaken[2] << setw(5) <<"|"<<endl;
	cout << setw(2) << "|" << setw(20) << bowlerCard[9] <<setw(38) << wicketTaken[3] << setw(5) <<"|"<<endl;
	cout << setw(2) << "|" << setw(20) << bowlerCard[10] <<setw(38) << wicketTaken[4] << setw(5) <<"|"<<endl;
	cout << setw(1) << " ----------------------------------------------------------------" << endl;
	
	ofstream fout;
	fout.open("results.txt", ios::app);
	fout << setw(1) << " ----------------------------------------------------------------" << endl;
	fout << setw(2) << "|" << setw(35) << "SCORECARD"  << setw(28) << "|" << endl;
	fout << setw(1) << " ----------------------------------------------------------------" << endl;
	fout << setw(2) << "|" << setw(20) << "Batsman Name" << setw(7) << "|" << setw(25) << "| " << " R " << " | " << " B " << " |"<<endl; 
	fout << setw(1) << " ----------------------------------------------------------------" << endl;
	fout << setw(2) << "|" << setw(20) << player1 << setw(7) << "|" << setw(24) << "|" << setw(3)<< score1 <<setw(3)<< "|" << setw(3)<< balls_played1 <<setw(3)<< "|"<<endl; 
	fout << setw(1) << " ----------------------------------------------------------------" << endl; 
	fout << setw(2) << "|" << setw(20) << player2 << setw(7) << "|" << setw(24) << "|" << setw(3)<< score2 <<setw(3)<< "|" << setw(3)<< balls_played2 <<setw(3)<< "|"<<endl; 
	fout << setw(1) << " ----------------------------------------------------------------" << endl;
	fout << setw(2) << "|" << setw(63) << "|" <<endl; 
	fout << setw(2) << "|" << setw(19) <<"Overs: " <<over<<"."<<ball+1 <<setw(14)<<"RunRate: "<<setprecision(2)<< runRate << setw(12) << "Total:" <<setw(7)<< total_score <<"/"<<wick<<setw(3)<< "|" <<endl;
	fout << setw(1) << " ----------------------------------------------------------------" << endl; 
	fout << endl<<endl;
	
	fout << setw(1) << " ----------------------------------------------------------------" << endl;
	fout << setw(2) << "|" << setw(20) << "Bowler Name" << setw(32) << "|" << setw(8) << "Wickets" << setw(3) << "|" <<endl;
	fout << setw(1) << " ----------------------------------------------------------------" << endl;
	fout << setw(2) << "|" << setw(20) << bowlerCard[6] <<setw(38) << wicketTaken[0] << setw(5) <<"|"<<endl;
	fout << setw(2) << "|" << setw(20) << bowlerCard[7] <<setw(38) << wicketTaken[1] << setw(5) <<"|"<<endl;
	fout << setw(2) << "|" << setw(20) << bowlerCard[8] <<setw(38) << wicketTaken[2] << setw(5) <<"|"<<endl;
	fout << setw(2) << "|" << setw(20) << bowlerCard[9] <<setw(38) << wicketTaken[3] << setw(5) <<"|"<<endl;
	fout << setw(2) << "|" << setw(20) << bowlerCard[10] <<setw(38) << wicketTaken[4] << setw(5) <<"|"<<endl;
	fout << setw(1) << " ----------------------------------------------------------------" << endl;
	
	fout.close();
	
	ofstream fout1;
	fout1.open("CurrentMatchDetails.txt", ios::app);
	
	fout1 << setw(1) << " ----------------------------------------------------------------" << endl;
	fout1 << setw(2) << "|" << setw(35) << "SCORECARD"  << setw(28) << "|" << endl;
	fout1 << setw(1) << " ----------------------------------------------------------------" << endl;
	fout1 << setw(2) << "|" << setw(20) << "Batsman Name" << setw(7) << "|" << setw(25) << "| " << " R " << " | " << " B " << " |"<<endl; 
	fout1 << setw(1) << " ----------------------------------------------------------------" << endl;
	fout1 << setw(2) << "|" << setw(20) << player1 << setw(7) << "|" << setw(24) << "|" << setw(3)<< score1 <<setw(3)<< "|" << setw(3)<< balls_played1 <<setw(3)<< "|"<<endl; 
	fout1 << setw(1) << " ----------------------------------------------------------------" << endl; 
	fout1 << setw(2) << "|" << setw(20) << player2 << setw(7) << "|" << setw(24) << "|" << setw(3)<< score2 <<setw(3)<< "|" << setw(3)<< balls_played2 <<setw(3)<< "|"<<endl; 
	fout1 << setw(1) << " ----------------------------------------------------------------" << endl;
	fout1 << setw(2) << "|" << setw(63) << "|" <<endl; 
	fout1 << setw(2) << "|" << setw(19) <<"Overs: " <<over<<"."<<ball+1 <<setw(14)<<"RunRate: "<<setprecision(2)<< runRate << setw(12) << "Total:" <<setw(7)<< total_score <<"/"<<wick<<setw(3)<< "|" <<endl;
	fout1 << setw(1) << " ----------------------------------------------------------------" << endl; 
	fout1 << endl<<endl;
	
	fout1 << setw(1) << " ----------------------------------------------------------------" << endl;
	fout1 << setw(2) << "|" << setw(20) << "Bowler Name" << setw(32) << "|" << setw(8) << "Wickets" << setw(3) << "|" <<endl;
	fout1 << setw(1) << " ----------------------------------------------------------------" << endl;
	fout1 << setw(2) << "|" << setw(20) << bowlerCard[6] <<setw(38) << wicketTaken[0] << setw(5) <<"|"<<endl;
	fout1 << setw(2) << "|" << setw(20) << bowlerCard[7] <<setw(38) << wicketTaken[1] << setw(5) <<"|"<<endl;
	fout1 << setw(2) << "|" << setw(20) << bowlerCard[8] <<setw(38) << wicketTaken[2] << setw(5) <<"|"<<endl;
	fout1 << setw(2) << "|" << setw(20) << bowlerCard[9] <<setw(38) << wicketTaken[3] << setw(5) <<"|"<<endl;
	fout1 << setw(2) << "|" << setw(20) << bowlerCard[10] <<setw(38) << wicketTaken[4] << setw(5) <<"|"<<endl;
	fout1 << setw(1) << " ----------------------------------------------------------------" << endl;
	
	fout1.close();	
	if(getch()=='r')
	{
		int newOver;
		cout << "Enter Over: ";
		cin >> newOver;
		OrigOver = newOver;
		return OrigOver;
	}
	system("cls");
}


//Function to let us display something from reading a file of our choice
void choiceOperation()
{
	ifstream fin;
	getch();
	system("cls");
	cout << "1- Current Match Summary\n" 
	<< "2- Previous Match Details\n"
	<< "3- Current Innings Details\n";
	
	int choice = 0;
	cout  << "Enter Choice: ";
	cin >> choice;
	string line;
	switch(choice)
	{
		case 1:
			fin.open("CurrentMatchSummary.txt");
			while(getline(fin,line))
			{
				cout << line << endl;
			}
		break;
		case 2:
			fin.open("results.txt");
			while(getline(fin,line))
			{
				cout << line << endl;
			}
		break;
		case 3:
			fin.open("CurrentMatchDetails.txt");
			while(getline(fin,line))
			{
				cout << line << endl;
			}
		break;
		default:
		cout <<"Invalid Option" << endl;	
	}
}


