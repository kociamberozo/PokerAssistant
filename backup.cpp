#include <iostream>
#include <cstdlib>
using namespace std;
int main(){
  bool mainRun = true;
  bool endGame;//endGame question for restart or quit
  bool chooseRand;//security for whoStars answer
  bool chooseRandManualy;//security for whoStarts out of range (manual input)
  bool actualGame;//heart of the game
  bool roundPlay;//loop for current hand
  bool startingBidControl;//simple security loop use
  bool bidRiseControl;//simple security loop use
  bool bidRoundControl;//simple security loop use
  bool reduceChipsControl;//simply you cannot put on the table more than you own
  bool handWinnerControl;
  bool numberOfPlayersControl;
  bool chipsPerPlayerControl;
  bool brokenPlayer;//if player has 0 chips than he can not host the game
  char newGame;//endGame answer value (y/n)
  char randAnswer;//whoStarts answer value (y/n) ~ (rand/manual)
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
  int riseMarker;//saveing id of player that made a rise
  int riseStop;//hold ammount of players and count down
  while(mainRun){
    hand = 1;
    bidHandCounter = 0;
    endGame = true;
    chooseRand = true;
    chooseRandManualy = true;
    actualGame = true;
    startingBidControl = true;
    numberOfPlayersControl = true;
    chipsPerPlayerControl = true;
    while(numberOfPlayersControl){
      cout << "\nPodaj liczbę graczy: ";
      cin >> numberOfPlayers;
      if(numberOfPlayers < 2){
        cout << "\nLiczba graczy nie może być mniejsza od 2. ";
        numberOfPlayersControl = true;
      }
      else{ numberOfPlayersControl = false; }
    }
    int TabOfPLayers[numberOfPlayers];//array of actual chips
    while(chipsPerPlayerControl){
      cout << "\nPodaj liczbę rzetonów przypadających na gracza: ";
      cin >> chipsPerPlayer;
      if(chipsPerPlayer < 100){
        cout << "\nLiczba rzetonów nie może być mniejsza od 100. ";
        chipsPerPlayerControl = true;
      }
      else{ chipsPerPlayerControl = false; }
    }
    for(int i = 0; i < numberOfPlayers; i++){
      TabOfPLayers[i] = chipsPerPlayer;
    }
    while(startingBidControl){
      cout << "\nPodaj stawkę, którą zapłaci rozgrywający gracz: ";
      cin >> startingBid;
      if((startingBid < 0) || (startingBid > chipsPerPlayer)){
        startingBidControl = true;
        cout << "\nStawka nie może być mniejsza od 0, ani większa od połowy rzetonów przypadających na gracza. ";
      }
      else{ startingBidControl = false; }
    }
    while(bidRiseControl){
      cout << "\nPodaj o ile stawka będzie się zwiększać: ";
      cin >> bidRise;
      if((bidRise < 0) || (bidRise > chipsPerPlayer)){
        bidRiseControl = true;
        cout << "\nWartość nie może być mniejsza od 0, ani większa od połowy rzetonów przypadających na gracza. ";
      }
      else{ bidRiseControl = false; }
    }
    if(bidRise != 0){
      while(bidRoundControl){
        cout << "\nPodaj co ile rund stawka będzie zwiększana: ";
        cin >> bidRound;
        if(bidRound <= 0){
          bidRoundControl = true;
          cout << "\nLiczba rund nie może być mniejsza lub równa 0. ";
        }
        else{ bidRoundControl = false; }
      }
    }
    while(chooseRand){
      cout << "\nCzy chcesz żeby komputer wylosował gracza, który zaczynie rozgrywkę? (y/n) ";
      cin >> randAnswer;
      if(randAnswer == 121){ chooseRand = false; whoStarts = rand() % numberOfPlayers + 1;  }
      if(randAnswer == 110){
        chooseRand = false;
        while(chooseRandManualy){
          cout << "\nKtóry gracz ma zaczynać? (dostępny zakres: <" << "1 - " << numberOfPlayers << ">) ";
          cin >> whoStarts;
          if((whoStarts >= 1) && (whoStarts <= numberOfPlayers)){ chooseRandManualy = false; }
          else{ cout << "\nWybrany gracz musi zostać wybrany z podanego zakresu. "; }
        }
      }
    }
    //********************************** MAIN GAME ********************************************
    while(actualGame = true){
      handWin = 0;
      brokenPlayer = true;
      while(brokenPlayer){
        if(TabOfPLayers[whoStarts - 1] <= 0){ whoStarts++; }
        else{ brokenPlayer = false; }
      }
      cout << "\n***********************************************************";
      cout << "\n                       ROZDANIE: " << hand;
      cout << "\n***********************************************************";
      for(int i = 0; i < numberOfPlayers; i++){
        cout << "\nGracz " << i + 1 << " posiada: " << TabOfPLayers[i];
      }
      cout << "\n***********************************************************";
      cout << "\n                ROZDANIE FUNDUJE GRACZ: " << whoStarts;
      cout << "\n                AKTUALNY KOSZT WEJŚCIA: " << startingBid;
      cout << "\n***********************************************************\n\n";
      TabOfPLayers[whoStarts - 1] = TabOfPLayers[whoStarts - 1] - startingBid;
      handWin = handWin + startingBid;
      bidHandCounter++;
      if(bidHandCounter >= bidRound){
        bidHandCounter = 0;
        startingBid = startingBid + bidRise;
      }
      for(int i = 0; i < 4; i++){
        roundPlay = true;
        if(i == 0){ cout << "\nRunda 1 - kart na stole: 0"; }
        if(i == 1){ cout << "\nRunda 2 - kart na stole: 3"; }
        if(i == 2){ cout << "\nRunda 3 - kart na stole: 4"; }
        if(i == 3){ cout << "\nRunda 4 - kart na stole: 5"; }
        cout << "\nRozpoczyna gracz: " << whoStarts;
        guardian = 0;
        lastHand = 0;
        reduceChips = 0;
        while(roundPlay){
          guardian++;
          reduceChipsControl = true;
          while(reduceChipsControl){
            cout << "\nCzy odejmujesz graczowi " << whoStarts << " rzetony? (jeżeli nie wpisz 0) ";
            cin >> reduceChips;
            if(reduceChips > TabOfPLayers[whoStarts - 1]){
              cout << "\nPodana wartość przekracza liczbę rzetonów gracza: " << TabOfPLayers[whoStarts - 1];
              reduceChipsControl = true;
            }
            else{
              if((reduceChips < lastHand) && (reduceChips != 0)){
                cout << "\nPoprzedni gracz podbił stawkę. Sprawdź go/ podbij stawke/ spasuj(wpis 0) ";
                reduceChipsControl = true;
              }
              else{ reduceChipsControl = false; }
            }
          }
          if(reduceChips > lastHand){
            cout << "\nStawka została podbita";
            riseMarker = whoStarts;
            riseStop = numberOfPlayers;
          }
          if(reduceChips != 0){ lastHand = reduceChips; }
          handWin = handWin + reduceChips;
          TabOfPLayers[whoStarts - 1] = TabOfPLayers[whoStarts - 1] - reduceChips;
          whoStarts++;
          if(whoStarts > numberOfPlayers){ whoStarts = 1; }
          if(guardian >= numberOfPlayers){ roundPlay = false; }
        }
      }
      handWinnerControl = true;
      while(handWinnerControl){
        cout << "\nKtóry gracz wygrywa rozdanie? ";
        cin >> handWinner;
        if((handWinner < 1) || (handWinner > numberOfPlayers)){
          handWinnerControl = true;
          cout << "Podano wartość spoza zakresu liczby graczy. ";
        }
        else{
          TabOfPLayers[handWinner - 1] = TabOfPLayers[handWinner - 1] + handWin;
          handWinnerControl = false;
        }
      }
      whoStarts++;
      hand++;
      if(whoStarts > numberOfPlayers){ whoStarts = 1; }
      for(int i = 0; i < numberOfPlayers; i++){
        if(TabOfPLayers[i] <= 0){ countLoose++; }
        if(countLoose >= (numberOfPlayers - 1)){ actualGame = false; }
      }
    }
    //********************************** MAIN GAME ********************************************
    while(endGame){
      cout << "\nGra zakończona. Rozpocząć nową? (y/n) ";
      cin >> newGame;
      if(newGame == 121){ endGame = false; mainRun = true;  }
      if(newGame == 110){ mainRun = false; endGame = false; }
    }
  }
}
