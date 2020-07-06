#include "player.h"

class SimplePlayer: public Player{
 public:
     int bet(unsigned int bankroll, unsigned int minimum){
         if(bankroll < minimum) return 0;
         return minimum;
     }

     bool draw(Card dealer, const Hand& player){
         if(!player.handValue().soft) {
             if (player.handValue().count <= 11) return true;
             else if (player.handValue().count == 12 && !(dealer.spot >= FOUR && dealer.spot <= SIX))
                 return true;
             else
                 return player.handValue().count >= 13 && player.handValue().count <= 16 &&
                        !(dealer.spot >= TWO && dealer.spot <= SIX);
         }
         else{
             if(player.handValue().count <= 17) return true;
             else if(player.handValue().count == 18 && (dealer.spot == TWO || dealer.spot == SEVEN || dealer.spot == EIGHT))
                 return false;
             else return player.handValue().count < 19;
         }
     }

     void expose(Card c){}
     void shuffled(){}


};

class CountingPlayer: public SimplePlayer{
 int count;

 public:
    CountingPlayer(): count(0) {}

    int bet(unsigned int bankroll, unsigned int minimum){
        if(count >= 2 && bankroll >= 2*minimum) return 2*minimum;
        else return minimum;
    }

    void expose(Card c){
        if(c.spot >= TEN && c.spot <= ACE) count --;
        if(c.spot >= TWO && c.spot <= SIX) count ++;
    }

    void shuffled(){
        count = 0;
    }


};

static SimplePlayer simple;
Player *get_Simple(){
    return &simple;
}

static CountingPlayer counting;
Player *get_Counting(){
    return &counting;
}