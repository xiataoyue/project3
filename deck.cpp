#include "deck.h"

Deck::Deck() {
    for(int i = 0; i < DIAMONDS + 1; i++){
        for(int j = 0; j < ACE + 1; j++){
            deck[13*i + j].spot = static_cast<Spot>(j);
            deck[13*i + j].suit = static_cast<Suit>(i);
        }
    }
    next = 0;
}

void Deck::reset() {
    for(int i = 0; i < DIAMONDS + 1; i++){
        for(int j = 0; j < ACE + 1; j++){
            deck[13*i + j].spot = static_cast<Spot>(j);
            deck[13*i + j].suit = static_cast<Suit>(i);
        }
    }
    next = 0;
}

void Deck::shuffle(int n) {
    Card left[n];
    Card right[DeckSize - n];
    for(int i = 0; i < n; i++){
        left[i] = deck[i];
    }

    for(int i = 0; i < DeckSize - n; i++){
        right[i] = deck[i + n];
    }

    if(n < 26){
        for(int i = 0; i < n; i++){
            this->deck[2*i] = right[i];
            this->deck[2*i + 1] = left[i];
        }
        for(int i = 2*n; i < DeckSize; i++){
            this->deck[i] = right[i - n];
        }
    }
    else{
        for(int i = 0; i < DeckSize - n; i++){
            this->deck[2*i] = right[i];
            this->deck[2*i + 1] = left[i];
        }
        for(int i = 2*(DeckSize - n); i < DeckSize; i++){
            this->deck[i] = left[i - (DeckSize - n)];
        }
    }
    this->next = 0;
}

Card Deck::deal() {
    if(next == DeckSize){
        throw DeckEmpty{};
    }
    this->next ++;
    return deck[next - 1];

}

int Deck::cardsLeft() {
    return DeckSize - next;
}
