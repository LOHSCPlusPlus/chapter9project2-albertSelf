#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

const int MAX_NUM_GAMES = 500;
const int MAX_NAME_CHAR = 100;



struct VideoGame{
  enum {MAX_NAME_CHAR=100};
  char title[MAX_NAME_CHAR];
  int sales;
  char platforms[MAX_NAME_CHAR];
  char releasedate[MAX_NAME_CHAR];
  char developer[MAX_NAME_CHAR];
  char publisher[MAX_NAME_CHAR];
  VideoGame();
};

void getInt(const char info[], int &val);
void getDouble(const char info[], double &val);
void getCstring(const char info[], char val[]);
void printGame(VideoGame game[], int numGames);
void addGame(VideoGame game[], int &numGames);
void removeGame(VideoGame game[], int &numGames);
void findPublisher(VideoGame game[], int numGames);
void savedata(VideoGame game[], int numGames);
int readgameData(VideoGame game[]);

void menu(VideoGame game[], int &numGames)
 {
  int option = 0;
  while(option != 7){
    cout << "Welcome to the Video Game list" << endl;
    cout << "Select a menu option: " << endl; 
    cout << "1. Show entire game list" << endl;
    cout << "2. Add a game to the list" << endl;
    cout << "3. Search a game by publisher" << endl;
    cout << "4. Remove a game from the list" << endl;
    cout << "5. Reload the list from data base" << endl;
    cout << "6. Save data to file" << endl;
    cout << "7. Exit List Program" << endl;
    cin >> option;
    switch (option)
    {
      case 1:
      printGame(game, numGames);
      break;
      case 2:
      addGame(game, numGames);
      break;
      case 3:
      findPublisher(game, numGames);
      break;
      case 4:
      removeGame(game, numGames);
      break;
      case 5:
      numGames = readgameData(game);
      break;
      case 6:
      savedata(game, numGames);
    }
  }
  cout << "Thank you for using our Game list" << endl;
}

VideoGame readgame(ifstream &inFile){
    VideoGame game; 
    inFile.get(game.title, VideoGame::MAX_NAME_CHAR, ';');
    inFile.ignore(100,';');
    inFile >> game.sales;
    inFile.ignore(100,';');
    inFile.get(game.platforms, VideoGame::MAX_NAME_CHAR, ';');
    inFile.ignore(100,';');
    inFile.get(game.releasedate, VideoGame::MAX_NAME_CHAR, ';');
    inFile.ignore(100,';');
    inFile.get(game.developer, VideoGame::MAX_NAME_CHAR, ';');
    inFile.ignore(100,';');
    inFile.get(game.publisher, VideoGame::MAX_NAME_CHAR, '\n');
    inFile.ignore(100, '\n');
    return game;
}

VideoGame::VideoGame() {
for(int index = 0; index < MAX_NAME_CHAR; index++){
  publisher[index] = '0';
}
for(int index = 0; index < MAX_NAME_CHAR; index++){
  publisher[index] = '0';
}
for(int index = 0; index < MAX_NAME_CHAR; index++){
  releasedate[index] = '0';
}
for(int index = 0; index < MAX_NAME_CHAR; index++){
  developer[index] = '0';
}
for(int index = 0; index < MAX_NAME_CHAR; index++){
  platforms[index] = '0';
}
sales = 0;
}

void findPublisher(VideoGame game[], int numGames){
  cout << "What publisher would you like to search? : ";
  char term[MAX_NAME_CHAR];
  cin >> term;
  for(int index = 0; index < numGames; index++){
    if(strcmp(game[index].publisher, term)) {
      cout << index << ". ";
      cout << game[index].title << " ";
      cout << game[index].sales << " ";
      cout << game[index].platforms << " ";
      cout << game[index].developer << " ";
      cout << game[index].publisher << " ";
      cout << endl;
    }
  }
}

int readgameData(VideoGame game[]) {
    ifstream gameFile("videogames.txt");
    int numGames = 0;
    while(gameFile.peek() != EOF && numGames < MAX_NUM_GAMES){
        game[numGames] = readgame(gameFile);
        numGames++;
    }
    return numGames;
}

void addGame(VideoGame game[], int &numGames) {
    if(numGames == MAX_NUM_GAMES){
      cout << "Maximum amount of games reached";
      return;
    }
    getCstring("title", game[numGames].title);
    getInt("copies Sold", game[numGames].sales);
    getCstring("platform", game[numGames].platforms);
    getCstring("developer", game[numGames].developer);
    getCstring("publisher", game[numGames].publisher);
    numGames++;
}


void getInt(const char info[], int &val){
  cout << "Enter the amount of " << info << " of the Game: ";
  cin >> val;
  while (!cin) {
      cin.clear();
      cin.ignore(1000,'\n');
      cout << "Invalid Data!" << endl;
      cout << "Enter the amount of " << info << "of the Game: ";
      cin >> val;
    }
}

void getCstring(const char info[], char val[]){
  cout << "Enter the " << info << " of the Game: ";
  cin.ignore(100, '\n');
  cin.getline(val, 100);
  while (!cin) {
      cin.clear();
      cin.ignore(1000,'\n');
      cout << "Invalid Data!" << endl;
      cout << "Enter the " << info << "of the Game: ";
      cin >> val;
    }
}

void printGame(VideoGame game[], int numGames){
  for(int index = 0; index < numGames; index++){
      cout << index << ". ";
      cout << game[index].title << " ";
      cout << game[index].sales << " ";
      cout << game[index].platforms << " ";
      cout << game[index].developer << " ";
      cout << game[index].publisher << " ";
      cout << endl;
    }
  }


void removeGame(VideoGame game[], int &numGames){
  cout << "Which game number would you like to remove? ";
  int index = 0;
  cin >> index;
  for(int count = index; count < numGames; count++){
    game[count] = game[count + 1];
  }
  numGames--;
}

void savedata(VideoGame game[], int numGames){
  ofstream outfile("videogames.txt");
  for(int index = 0; index < numGames; index++){
    outfile << game[index].title << ";";
    outfile << game[index].sales << ";";
    outfile << game[index].platforms << ";";
    outfile << game[index].developer << ";";
    outfile << game[index].publisher << ";";
    outfile << endl;
  }
}


int main() {
  int numGames = 0;
  VideoGame game[MAX_NUM_GAMES];
  numGames = readgameData(game);
  menu(game, numGames);
  return 0;
}