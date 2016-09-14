#include <iostream>
#include <cstdlib>
using namespace std;
void cleaner(){
  for(int i = 0; i < 100; i++){
    cout << "\n";
  }
}
void displayBoard(int TabOfPlayers[], int hand, int numberOfPlayers, int whoStarts, int startingBid){
  cout << "\n***********************************************************";
  cout << "\n                       ROZDANIE: " << hand;
  cout << "\n***********************************************************";
  for(int i = 0; i < numberOfPlayers; i++){
    cout << "\nGracz " << i + 1 << " posiada: " << TabOfPlayers[i];
  }
  cout << "\n***********************************************************";
  cout << "\n                ROZDANIE FUNDUJE GRACZ: " << whoStarts;
  cout << "\n                AKTUALNY KOSZT WEJŚCIA: " << startingBid;
  cout << "\n***********************************************************\n\n";
}
void displayRound(int iteration, int handWin){
  if(iteration == 0){ cout << "\nRunda 1 - kart na stole: 0 - suma żetonów na stole: " << handWin << "\n"; }
  if(iteration == 1){ cout << "\nRunda 2 - kart na stole: 3 - suma żetonów na stole: " << handWin << "\n"; }
  if(iteration == 2){ cout << "\nRunda 3 - kart na stole: 4 - suma żetonów na stole: " << handWin << "\n"; }
  if(iteration == 3){ cout << "\nRunda 4 - kart na stole: 5 - suma żetonów na stole: " << handWin << "\n"; }
}
int main(){
  bool mainRun = true;
  bool chooseRandManualy;//security for whoStarts out of range (manual input)
  bool actualGame;//heart of the game
  bool roundPlay;//loop for current hand
  bool inputControl;
  bool brokenPlayer;//if player has 0 chips than he can not host the game
  char charAnswer;//used for (y/n) answers
  int numberOfPlayers;
  int chipsPerPlayer;
  int whoStarts; //id of player that starts the game
  int guardian;//counts moves on current hand
  int reduceChips;//individual for each player
  int countLoose;//counting loosers;
  int startingBid;//first bid for manual setup
  int bidRise;//rise of the bid for every hand; also for manual setup
  int bidRound;//how often will bid rise; manual setup
  int hand;//cosmetic change; info for the players about how long they play
  int bidHandCounter;//counter needed for rising bid
  int handWin;//ammount of chips on the table
  int handWinner;//player that gets the handWin
  int lastHand;//for checking if next player made a rise
  int riseStop;//hold ammount of players and count down
  int displayFounderID;
  int displayFoundingCost;
  int guardian2;
  while(mainRun){
    bidHandCounter = 0;
    cleaner();
    inputControl = true;
    while(inputControl){
      cout << "\nPodaj liczbę graczy: ";
      cin >> numberOfPlayers;
      if(numberOfPlayers < 2){
        cleaner();
        cout << "\nLiczba graczy nie może być mniejsza od 2.\n";
      }
      else{ inputControl = false; }
    }
    guardian2 = numberOfPlayers;
    int TabOfPlayers[numberOfPlayers];
    int TabOfLoosers[numberOfPlayers];
    for(int i = 0; i < numberOfPlayers; i++){
      TabOfLoosers[i] = 0;
    }
    cleaner();
    inputControl = true;
    while(inputControl){
      cout << "\nPodaj liczbę żetonów przypadających na gracza: ";
      cin >> chipsPerPlayer;
      if(chipsPerPlayer < 100){
        cleaner();
        cout << "\nLiczba żetonów nie może być mniejsza od 100.\n";
      }
      else{ inputControl = false; }
    }
    for(int i = 0; i < numberOfPlayers; i++){
      TabOfPlayers[i] = chipsPerPlayer;
    }
    cleaner();
    inputControl = true;
    while(inputControl){
      cout << "\nPodaj stawkę, którą zapłaci rozgrywający gracz: ";
      cin >> startingBid;
      if((startingBid < 0) || (startingBid > chipsPerPlayer)){
        cleaner();
        cout << "\nStawka nie może być mniejsza od 0, ani większa od połowy żetonów przypadających na gracza.\n";
      }
      else{ inputControl = false; }
    }
    cleaner();
    inputControl = true;
    while(inputControl){
      cout << "\nPodaj o ile stawka będzie się zwiększać: ";
      cin >> bidRise;
      if((bidRise < 0) || (bidRise > chipsPerPlayer)){
        cleaner();
        cout << "\nWartość nie może być mniejsza od 0, ani większa od połowy żetonów przypadających na gracza.\n";
      }
      else{ inputControl = false; }
    }
    cleaner();
    inputControl = true;
    if(bidRise != 0){
      while(inputControl){
        cout << "\nPodaj co ile rund stawka będzie zwiększana: ";
        cin >> bidRound;
        if(bidRound <= 0){
          cleaner();
          cout << "\nLiczba rund nie może być mniejsza lub równa 0.\n";
        }
        else{ inputControl = false; }
      }
    }
    cleaner();
    inputControl = true;
    chooseRandManualy = true;
    while(inputControl){
      cout << "\nCzy chcesz żeby komputer wylosował gracza, który zaczynie rozgrywkę? (y/n) ";
      cin >> charAnswer;
      if(charAnswer == 121){
        inputControl = false;
        whoStarts = rand() % numberOfPlayers + 1;
      }
      if(charAnswer == 110){
        inputControl = false;
        cleaner();
        while(chooseRandManualy){
          cout << "\nKtóry gracz ma zaczynać? (dostępny zakres: <" << "1 - " << numberOfPlayers << ">) ";
          cin >> whoStarts;
          if((whoStarts >= 1) && (whoStarts <= numberOfPlayers)){ chooseRandManualy = false; }
          else{
            cleaner();
            cout << "\nWybrany gracz musi zostać wybrany z podanego zakresu.\n";
          }
        }
      }
    }
    //********************************** MAIN GAME ********************************************
    hand = 1;
    actualGame = true;
    while(actualGame = true){
      handWin = 0;
      brokenPlayer = true;
      while(brokenPlayer){
        if(TabOfPlayers[whoStarts - 1] <= 0){ whoStarts++; }
        else{ brokenPlayer = false; }
      }

      TabOfPlayers[whoStarts - 1] = TabOfPlayers[whoStarts - 1] - startingBid;
      handWin += startingBid;
      displayFoundingCost = startingBid;
      displayFounderID = whoStarts;
      bidHandCounter++;
      if(bidHandCounter >= bidRound){
        bidHandCounter = 0;
        startingBid += bidRise;
      }

      for(int i = 0; i < 4; i++){
        roundPlay = true;
        cleaner();
        displayBoard(TabOfPlayers,hand,numberOfPlayers,displayFounderID,displayFoundingCost);
        displayRound(i,handWin);
        cout << "\nRozpoczyna gracz: " << whoStarts << "\n";
        guardian = 0;
        lastHand = 0;
        reduceChips = 0;
        riseStop = 0;
        while(roundPlay){
          riseStop--;
          guardian++;
          inputControl = true;
          while(inputControl){
            if(TabOfLoosers[whoStarts - 1] != 1){
              cout << "\nCzy odejmujesz graczowi " << whoStarts << " żetony? (jeżeli nie wpisz 0) ";
              cin >> reduceChips;
              if(reduceChips > TabOfPlayers[whoStarts - 1]){
                cout << "\nPodana wartość przekracza liczbę żetonów gracza: " << TabOfPlayers[whoStarts - 1] << "\n";
              }
              else{
                if(reduceChips < 0){ cout << "\nChciałbyś\n"; }
                else{
                  if((reduceChips < lastHand) && (reduceChips != 0)){
                    cout << "\nPoprzedni gracz podbił stawkę. Sprawdź go/ podbij stawke/ spasuj(wpis 0)\n";
                  }
                  else{ inputControl = false; }
                }
              }
            }
            else{
              whoStarts++;
             }

          }
          if(reduceChips > lastHand){
            cout << "\nStawka została podbita.\n";
            riseStop = numberOfPlayers - 1;
          }
          if(reduceChips != 0){ lastHand = reduceChips; }
          handWin += reduceChips;
          TabOfPlayers[whoStarts - 1] -= reduceChips;
          whoStarts++;
          if(whoStarts > numberOfPlayers){ whoStarts = 1; }
          if((guardian >= guardian2) && (riseStop <= 0)){ roundPlay = false; }
        }
      }
      inputControl = true;
      while(inputControl){
        cout << "\nKtóry gracz wygrywa rozdanie? ";
        cin >> handWinner;
        if((handWinner < 1) || (handWinner > numberOfPlayers)){
          cout << "\nPodano wartość spoza zakresu liczby graczy.\n";
        }
        else{
          TabOfPlayers[handWinner - 1] += handWin;
          inputControl = false;
        }
      }
      whoStarts++;
      hand++;
      if(whoStarts > numberOfPlayers){ whoStarts = 1; }
      for(int i = 0; i < numberOfPlayers; i++){
        if(TabOfPlayers[i] == 0){
          TabOfLoosers[i] = 1;
          guardian2--;
        }
      }
      for(int i = 0; i < numberOfPlayers; i++){
        if(TabOfPlayers[i] <= 0){ countLoose++; }
        if(countLoose >= (numberOfPlayers - 1)){ actualGame = false; }
      }
    }
    //********************************** MAIN GAME ********************************************
    inputControl = true;
    while(inputControl){
      cout << "\nGra zakończona. Rozpocząć nową? (y/n) ";
      cin >> charAnswer;
      if(charAnswer == 121){ inputControl = false; mainRun = true; }
      if(charAnswer == 110){ inputControl = false; mainRun = false; }
    }
  }
}
