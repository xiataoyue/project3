#include "deck.h"
#include "hand.h"
#include "player.h"
#include "rand.h"
#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

int main(int argc, char *argv[]){
    if(argc != 4){
        cout << "Wrong number of arguments!" << endl;
        return 0;
    }

    unsigned int bankroll = atoi(argv[1]);
    int hand = atoi(argv[2]);
    string username = argv[3];

    Player *player;
    if(username == "simple") player = get_Simple();
    else if(username == "counting") player = get_Counting();
    else{
        cout << "Wrong user name!" << endl;
        return 0;
    }


    Deck deck;
    Card card[DeckSize];
    int temp = 0;
    int thishand = 0;
    int wager;
    unsigned int minimum = 5;

    cout << "Shuffling the deck" << endl;
    for(int i = 0; i <7; i++){
        int cut = get_cut();
        deck.shuffle(cut);
        cout << "cut at " << cut << endl;
        player->shuffled();
    }

    for(; thishand < hand; thishand++){
        if(bankroll < minimum){
            cout << "Player has " << bankroll << " after " << thishand << " hands" << endl;
            return 0;
        }

        try{
            if(deck.cardsLeft() == 0) throw DeckEmpty{};
        }
        catch(DeckEmpty a){
            cout << "No cards left" << endl;
            cout << "Shuffling the deck" << endl;
            for(int i = 0; i <7; i++){
                int cut = get_cut();
                deck.shuffle(cut);
                cout << "cut at " << cut << endl;
            }
            player->shuffled();
        }

        cout << "Hand " << thishand  + 1 << " bankroll " << bankroll << endl;
        if(deck.cardsLeft() < 20){
            cout << "Shuffling the deck" << endl;
            for(int i = 0; i <7; i++){
                int cut = get_cut();
                deck.shuffle(cut);
                cout << "cut at " << cut << endl;
            }
            player->shuffled();
        }

        wager = player->bet(bankroll, minimum);
        cout << "Player bets " << wager << endl;

        Hand player1, dealer;
        card[temp] = deck.deal();
        cout << "Player dealt " << SpotNames[card[temp].spot] << " of " << SuitNames[card[temp].suit] << endl;
        player1.addCard(card[temp]);
        if(username == "counting") player->expose(card[temp]);
        temp++;

        card[temp] = deck.deal();
        cout << "Dealer dealt " << SpotNames[card[temp].spot] << " of " << SuitNames[card[temp].suit] << endl;
        dealer.addCard(card[temp]);
        if(username == "counting") player->expose(card[temp]);
        temp++;

        card[temp] = deck.deal();
        cout << "Player dealt " << SpotNames[card[temp].spot] << " of " << SuitNames[card[temp].suit] << endl;
        player1.addCard(card[temp]);
        if(username == "counting") player->expose(card[temp]);
        temp++;

        card[temp] = deck.deal();
        int hole = temp;
        dealer.addCard(card[temp]);
        temp++;

        if(player1.handValue().count == 21){
            if(wager % 2) bankroll += (3*wager - 1)/2;
            else bankroll += 3*wager / 2;
            cout << "Player dealt natural 21" << endl;
            temp = 0;
            continue;
        }

        while(player->draw(card[1], player1) && player1.handValue().count <= 21){
            card[temp] = deck.deal();
            cout << "Player dealt " << SpotNames[card[temp].spot] << " of " << SuitNames[card[temp].suit] << endl;
            player1.addCard(card[temp]);
            player->expose(card[temp]);
            temp++;
        }

        cout << "Player's total is " << player1.handValue().count << endl;

        if(player1.handValue().count > 21){
            cout << "Player busts" << endl;
            bankroll -= wager;
            temp = 0;
            continue;
        }

        cout << "Dealer's hole card is " << SpotNames[card[hole].spot] << " of " << SuitNames[card[hole].suit] << endl;
        player->expose(card[hole]);

        while(dealer.handValue().count < 17){
            card[temp] = deck.deal();
            cout << "Dealer dealt " << SpotNames[card[temp].spot] << " of " << SuitNames[card[temp].suit] << endl;
            dealer.addCard(card[temp]);
            player->expose(card[temp]);
        }

        cout << "Dealer's total is " << dealer.handValue().count << endl;

        if(dealer.handValue().count > 21){
            cout << "Dealer busts" << endl;
            bankroll += wager;
            temp = 0;
            continue;
        }

        if(player1.handValue().count > dealer.handValue().count){
            cout << "Player wins" << endl;
            bankroll += wager;
        }
        else if(dealer.handValue().count > player1.handValue().count){
            cout << "Dealer wins" << endl;
            bankroll -= wager;
        }
        else{
            cout << "Push" << endl;
        }
        temp = 0;
    }

    cout << "Player has " << bankroll << " after " << thishand << " hands" << endl;

    return 0;
}

