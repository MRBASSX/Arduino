#include <Arduino.h>

class Bird
{
private:
int eye;
int neck ;
int left_wing;
int right_wing;
int left_leg;
int right_leg;
int tail ;
int ear;
int beak;


public:


Bird(int eye, int neck, int left_wing, int right_wing, int left_leg, int right_leg, int tail, int ear,
    int beak) {
this->eye = eye;
this->neck = neck;
this->left_wing = left_wing;
this->right_wing = right_wing;
this->left_leg = left_leg;
this->right_leg = right_leg;
this->tail = tail;
this->ear = ear;
this->beak = beak;
}


 void fly(int State,int State1){


      
        digitalWrite(getLeft_leg(),State);
        digitalWrite(getRight_leg(),State);
        delay(1000);
        digitalWrite(getLeft_wing(),State);
        digitalWrite(getRight_wing(),State);
        delay(1000);
        digitalWrite(getLeft_leg(),State1);
        digitalWrite(getRight_leg(),State1);


    }
   void walk(int State,int State1){


      
        digitalWrite(getLeft_leg(),State);
        digitalWrite(getRight_leg(),State);
        delay(1000);
        digitalWrite(getLeft_leg(),State1);
        digitalWrite(getRight_leg(),State1);


    }


int getEye() {
    return eye;
}


void setEye(int eye) {
    this->eye = eye;
}


int getNeck() {
    return neck;
}


void setNeck(int neck) {
    this->neck = neck;
}


int getLeft_wing() {
    return left_wing;
}


void setLeft_wing(int left_wing) {
    this->left_wing = left_wing;
}


int getRight_wing() {
    return right_wing;
}


void setRight_wing(int right_wing) {
    this->right_wing = right_wing;
}


int getLeft_leg() {
    return left_leg;
}


void setLeft_leg(int left_leg) {
    this->left_leg = left_leg;
}


int getRight_leg() {
    return right_leg;
}


void setRight_leg(int right_leg) {
    this->right_leg = right_leg;
}


int getTail() {
    return tail;
}


void setTail(int tail) {
    this->tail = tail;
}


int getEar() {
    return ear;
}


void setEar(int ear) {
    this->ear = ear;
}


int getBeak() {
    return beak;
}


void setBeak(int beak) {
    this->beak = beak;
}

  
};


