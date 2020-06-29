#include "hand.h"

Hand::Hand() {
    curValue.count = 0;
    curValue.soft = false;
}

void Hand::discardAll() {
    this->curValue.soft = false;
    this->curValue.count = 0;
}

void Hand::addCard(Card c) {
    if(c.spot == ACE){
        if(curValue.count > 10) this->curValue.count += 1;
        else{
            this->curValue.count += 11;
            this->curValue.soft = true;
        }
    }
    else if(c.spot >= TWO && c.spot <= TEN){
        if(this->curValue.count + c.spot + 2 > 21 && this->curValue.soft){
            this->curValue.count -= 10;
            this->curValue.count += c.spot;
            this->curValue.soft = false;
        }
        else this->curValue.count += (c.spot + 2);

    }
    else{
        if(this->curValue.count + 10 > 21 && this->curValue.soft){
            this->curValue.soft = false;
        }
        else this->curValue.count += 10;
    }

}

HandValue Hand::handValue() const {
    return this->curValue;
}