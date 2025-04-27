#include <iostream>
#include <algorithm>
#include <random>
#include <typeinfo>
#include <ctime>
#include <windows.h>
using namespace std;

#include "Card.h"
#include "StandardCard.h"
#include "BonusCard.h"
#include "PenaltyCard.h"
#include "Deck.h"
#include "Player.h"
#include "Game.h"

//------------- Tazabeet --------------------

void clearScreen() {    //clear screen abl kol display lgrid
    #ifdef _WIN32
         std::system("cls");
    #else
        std::system("clear");
    #endif
}

//--------------------------------------------

Card::Card(){
    faceup = false;
    number = 0;
    ph = ' ';
}

Card::Card(bool fu,int n){
    faceup = fu;
    number = n;
    ph = ' ';
}

Card::Card(char c){
    faceup = 1;
    ph = c;
}

int Card::get_number(){
    return number;
}
bool Card::get_face(){
    return faceup;
}
void Card::set_number(int n){
    number = n;
}
void Card::set_face(bool x){
    faceup = x;
}
char Card::get_Ph(){
    return ph;
}
void Card::display(){
    if(ph == ' '){
        if(faceup)
            cout<<"        "<<number<<"        ";
        else
            cout<<"        "<<"*"<<"        ";
    }
    else{
    cout<<"        "<<ph<<"        ";
    }
}

void Card::displayState(){
    string currentState = ( faceup == 1 )? "Card Revealed" : "Card Hidden" ;
    cout<<currentState<<endl;
}

void Card::hide(){
    set_face(0);
}

void Card::reveal(){
    set_face(1);
}

Card::~Card(){

}

bool Card::operator==(const Card& other) const {
        return typeid(*this) == typeid(other) &&
               this->faceup == other.faceup &&
               this->number == other.number;
    }

//--------------- STNDARD CARD CLASS

StandardCard::StandardCard():Card(){}
StandardCard::StandardCard(bool fu,int n) : Card(fu,n){}
StandardCard::~StandardCard(){}


//--------------- BONUS CARD CLASS

BonusCard::BonusCard():Card()
{
    bonus =1;
    number = 7;
}

BonusCard::BonusCard(bool fu,int b):Card(fu,0){
    bonus = b;
    number = 7;
}

BonusCard::~BonusCard(){

}

int BonusCard::getBonus(){
    return bonus;
}

void BonusCard::setBonus(int n){
    bonus = n;
}

void BonusCard::display(){
    if(get_face())
        cout<<"      "<<number<<"(B)"<<"      ";
    else
        cout<<"        "<<"*"<<"        ";
}

bool BonusCard::operator==(const Card& other) const{
    if(typeid(*this)!=typeid(other))
        return false;

    const BonusCard* otherB = static_cast<const BonusCard*>(&other);
    return Card::operator==(other) && this->bonus == otherB->bonus;
}
//---------------- PENALTY CARD CLASS

PenaltyCard::PenaltyCard()
{
    penalty = -1;
    number = 8;
}

PenaltyCard::PenaltyCard(bool fu,int p):Card(fu,0){
    penalty = p;
    number = 8;
}

PenaltyCard::~PenaltyCard(){

}

int PenaltyCard::get_Penalty(){
    return penalty;
}

void PenaltyCard::set_Penalty(int n){
    penalty = n;
}

void PenaltyCard::display(){
    if(get_face())
        cout<<"      "<<number<<"(P)"<<"      ";
    else
        cout<<"        "<<"*"<<"        ";
}

bool PenaltyCard::operator==(const Card& other) const{
    if(typeid(*this)!=typeid(other))
        return false;

    const PenaltyCard* otherPC = static_cast<const PenaltyCard*>(&other);
    return Card::operator==(other) && this->penalty == otherPC->penalty;
}

//---------------- DECK CLASS

Deck::Deck() //constructing starting deck
{
    cout<<"test";
    cards = new Card*[16]; //rows

    for(int i=0;i<12;i++){
        cards[i] = new StandardCard(false,(i%6)+1);
    }

    cards[12] = new BonusCard(false,1);
    cards[13] = new BonusCard(false,1);
    cards[14] = new PenaltyCard(false,-1);
    cards[15] = new PenaltyCard(false,-1);

}

Deck::~Deck()
{
    delete cards;
}



void Deck::shuffle(){
    Card* tmp = nullptr;
    for(int i=0; i<16 ;i++){
        int x = rand() % 16;
        tmp = cards[i];
        cards[i] = cards[x];
        cards[x] = tmp;
    }
}

Card** Deck::getCards() {
    return cards;
}

void Deck::setCards(Card* c,int i){
    if(i>=0 && i<16){
        cards[i] = c;
    }
    else{
        cout<<"Cards are 16 enter valid index from 0-15"<<endl;
    }
}

void Deck::displayGrid(){
    clearScreen();

    for(int i=0;i<16;i++){
        if(i%4 == 0){
                cout<<endl;
        }
        cards[i]->display();
    }
    cout<<endl;
}

void Deck::faceUpAll(){
    for(int i=0; i<16 ;i++){
        cards[i]->reveal();
    }
}

void Deck::removeCard(int cor){
    cards[cor] = new Card('_'); //Removed Card
}

//---------------- PLAYER CLASS

Player::Player() {
    name = "Unknown";
    score = 0; // Initialize score to 0
    playerTurnI[0] = true; //Awel turn dymn true baaden if we need hnkhli elnext true to play again internally
    for (int i = 1; i < 20; i++) {
        playerTurnI[i] = false;
    }
    for (int i = 0; i < 200; i++) {
        playerTurnEx[i] = true;
    }
}

Player::Player(string name){
    this->name = name;
    score = 0;
    playerTurnI[0] = true;
    for (int i = 1; i < 20; i++) {
        playerTurnI[i] = false;
    }
    for (int i = 0; i < 500; i++) {
        playerTurnEx[i] = true;
    }
}

Player::~Player(){}

string Player::get_Name(){
    return name;
}
void Player::set_Name(string n){
    this->name = n;
}
int Player::get_Score(){
    return score;
}
void Player::set_Score(int n){
    score = n;
}
void Player::displayScore(){
    cout<<"Score: "<<score<<endl;
}
void Player::set_Game(Game* game){
    myGame = game;
}

void Player::reveal(int i,int j){
    int cor = j * 4 + i;
    myGame->get_GameDeck()->getCards()[cor]->reveal();
}
void Player::hide(int i,int j){
    int cor = j * 4 + i;
    myGame->get_GameDeck()->getCards()[cor]->hide();
}

bool Player::inTurnI(int i){
    return playerTurnI[i];
}
void Player::setTurnI(int i, bool b){
    playerTurnI[i] = b;
}
bool Player::inTurnEx(int i){
    return playerTurnEx[i];
}
void Player::setTurnEx(int i, bool b){
    playerTurnEx[i] = b;
}
bool Player::get_playerTurnEx(int i){
    return playerTurnEx[i];
}
bool Player::get_playerTurnI(int i){
    return playerTurnI[i];
}
void Player::addTurnAfterLastTurnI() {
    for (int i = 0; i < 19; i++) {
        if (playerTurnI[i] && !playerTurnI[i + 1]) {
            playerTurnI[i + 1] = true; // Add `true` after the last `true`
            break; // Stop once the update is made
        }
    }
}

void Player::resetPlayerTurnI(){
    playerTurnI[0] = true;
    for (int i = 1; i < 20; i++) {
        playerTurnI[i] = false;
    }
}

//---------------- GAME CLASS ------------


class NullPointerException : public std::exception {
    public:
        const char* what() const noexcept override {
            return "Null pointer exception: Game not initialized yet; No Game Deck!";
        }
};

Game::Game(){
    gameOver = 0;
}
Game::~Game(){

}

void Game::initializeGame(){
    string n1,n2;
    cout << "Please enter player 1 name: ";
    getline(cin, n1);
    cout << "Please enter player 2 name: ";
    getline(cin, n2);

    p1 = new Player(n1);
    p2 = new Player(n2);

    p1->set_Game(this);
    p2->set_Game(this);

    gameDeck = new Deck();
    gameDeck->displayGrid();
    cout<<"Game Intialized; Deck ready!"<<endl;

    gameDeck->shuffle();
}

Deck* Game::get_GameDeck(){
    if(gameDeck != nullptr)
        return gameDeck;
    else
        throw NullPointerException();
}

void Game::set_GameDeck(Card* c,int i) {
     if (gameDeck == nullptr) {
        throw NullPointerException();
    }
    gameDeck->setCards(c,i);
}

Player* Game::getPlayer1(){
    return p1;
}
Player* Game::getPlayer2(){
    return p2;
}
bool Game::get_GameOver(){
    return gameOver;
}

int Game::finale(){
    int count=0;
    int x=0;
    for(int i=0;i<16;i++){
        if (gameDeck->getCards()[i]->get_Ph() == ' ') {
            count++;
            x=i;
        }
    }

     if(count==1){
        Card* c = gameDeck->getCards()[x];
        if(BonusCard* bc = dynamic_cast<BonusCard*>(c)) {
            return bc->getBonus();
        }else if(PenaltyCard* pc = dynamic_cast<PenaltyCard*>(c)){
                return pc->get_Penalty();
        }

    }
    return 0;

}

void Game::playTurn(Player* p, int turnI,int turnEx){
    int i1,j1,i2,j2;

    if(finale()!= 0){
        p->set_Score(p->get_Score()+finale());
        for(int i=0;i<16;i++){
            if (gameDeck->getCards()[i]->get_Ph() == ' ') {
                gameDeck->removeCard(i);
            }
        }
        return;
    }

    while (true) {
        cout <<"<<"<< p->get_Name() << "'s turn" << ">>"<< endl;
        cout << "Enter coordinates for 2 cards to reveal x1_y1_x2_y2. Coordinates must start from 0." << endl;

        cin >> i1 >> j1 >> i2 >> j2;
        int c1 = j1 * 4 + i1; //card 1 index in cards[]
        int c2 = j2 * 4 + i2;
        Card* card1 = gameDeck->getCards()[c1];
        Card* card2 = gameDeck->getCards()[c2];

        // Validate input
        if (i1 < 0 || j1 < 0 || i2 < 0 || j2 < 0) {
            cout << "Coordinates cannot be negative. Please try again." << endl;
        } else if (i1 == i2 && j1 == j2) {
            cout << "You cannot select the same card twice. Please try again." << endl;
        } else if (i1 > 3 || j1 > 3 || i2 > 3 || j2 > 3) {
            cout << "Coordinates are out of bounds. Please try again." << endl;
        } else if(card1->get_Ph() !=' ' || card2->get_Ph() != ' '){
            cout<< "You entered coordiantes for an empty slot/s. Please try again." << endl;
        } else {
            break;
        }
    }
    p1->reveal(i1,j1);
    p1->reveal(i2,j2);
    gameDisplay();
    Sleep(1500);
    action( i1, j1, i2, j2, p, turnI, turnEx);
}

void Game::action(int i, int j, int x, int y, Player* p ,int turnI, int turnEx){
    int c1 = j * 4 + i; //card 1 index in cards[]
    int c2 = y * 4 + x;////card 2////
    Card* card1 = gameDeck->getCards()[c1];
    Card* card2 = gameDeck->getCards()[c2];

    if(*card1 == *card2){ //if the 2 cards match
        if(!(dynamic_cast<PenaltyCard*>(card1)) && !(dynamic_cast<BonusCard*>(card1))){
            cout<<"Cards match :) Play Again!";
            Sleep(1500);
            p->addTurnAfterLastTurnI();
        }
        if (BonusCard* bonusCard = dynamic_cast<BonusCard*>(card1)) {
                if(!twoRemaining()){
                    int a1;
                    cout<<"You matched 2 Bonus Cards. Choose 1 or 2 from"<<endl;
                    cout<<"1: Gain 2 points"<<endl;
                    cout<<"2: Gain 1 point & Take an extra turn"<<endl;
                    cin>> a1;
                    if(a1 == 1){
                        p->set_Score(p->get_Score()+2*bonusCard->getBonus());
                        p->setTurnI(turnI+1,true);
                    }
                    else if(a1 == 2){
                        p->set_Score(p->get_Score()+bonusCard->getBonus());
                        cout<<"You took an extra turn";
                        p->addTurnAfterLastTurnI(); //mhtaga tafkeeeeer
                        p->addTurnAfterLastTurnI();
                    }
                    else{
                        cout<<"Invalid input."<<endl;
                        Sleep(1500);
                        action( i, j, x, y, p , turnI, turnEx);
                    }
                }
                else{
                    p->set_Score(p->get_Score()+2*bonusCard->getBonus());
                    cout<<"You gained 2 points!"<<endl;
                }
        }
        // Check if it's a PenaltyCard
        else if (PenaltyCard* penaltyCard = dynamic_cast<PenaltyCard*>(card1)) {
                if(!twoRemaining()){
                    int answer;
                    cout<<"You matched 2 Penalty Cards. Choose 1 or 2 from"<<endl;
                    cout<<"1: Lose 2 points"<<endl;
                    cout<<"2: Skip next turn"<<endl;
                    cin>> answer;
                    if(answer == 1){
                        p->set_Score(p->get_Score()+ 2*penaltyCard->get_Penalty());
                    }
                    else if(answer == 2){
                        cout<<"skipping next time"<<endl;
                        p->setTurnEx(turnEx+1,false);//skip next turn
//                        for(int i=turnEx;i<8;i++){
//                            cout<<p->playerTurnEx[i]<<endl;
//
//                        }
                    }
                    else{
                        cout<<"Invalid input. Enter 1 or 2"<<endl;
                        Sleep(1500);
                        action( i, j, x, y, p ,turnI, turnEx);
                    }
                }
                else{
                    p->set_Score(p->get_Score()+ 2*penaltyCard->get_Penalty());
                    cout<<"You lost 2 points!"<<endl;
                }
        }
        // Check if it's a StandardCard
        else if (dynamic_cast<StandardCard*>(card1)) {
            p->set_Score(p->get_Score()+ 1);
        }
        else {
            cout << "Unknown card type at index " << c1 << endl;
        }

        gameDeck->removeCard(c1); //remove matching cards from deck aka putting a standard card
        gameDeck->removeCard(c2); //with place holder _

    }
    else if ((dynamic_cast<PenaltyCard*>(card1) && dynamic_cast<BonusCard*>(card2)) ||
        (dynamic_cast<BonusCard*>(card1) && dynamic_cast<PenaltyCard*>(card2))) {
        //if one is a PenaltyCard and the other is a BonusCard remove eletneen
        gameDeck->removeCard(c1);
        gameDeck->removeCard(c2);
    }
    else if(BonusCard* bc1 = dynamic_cast<BonusCard*>(card1)){
            p->set_Score(p->get_Score()+ bc1->getBonus());
            gameDeck->removeCard(c1);
            p->hide(x,y);
    }
    else if(BonusCard* bc2 = dynamic_cast<BonusCard*>(card2)){
            p->set_Score(p->get_Score()+ bc2->getBonus());
            gameDeck->removeCard(c2);
            p->hide(i,j);
    }
    else if(PenaltyCard* pc1 = dynamic_cast<PenaltyCard*>(card1)){
            p->set_Score(p->get_Score()+ pc1->get_Penalty());
            gameDeck->removeCard(c1);
            p->hide(x,y);
    }
    else if(PenaltyCard* pc2 = dynamic_cast<PenaltyCard*>(card2)){
            p->set_Score(p->get_Score()+ pc2->get_Penalty());
            gameDeck->removeCard(c2);
            p->hide(i,j);
    }
    else{
        Sleep(1500);
        p->hide(i,j);
        p->hide(x,y);

    }
}

bool Game::isOver() {
    for (int i = 0; i < 16; i++) {
        if (gameDeck->getCards()[i]->get_Ph() == ' ') {
            return false;
        }
    }
    return true;
}
void Game::gameDisplay(){
        gameDeck->displayGrid();
        cout<<p1->get_Name()<<"'s Score: "<<p1->get_Score()<<endl;
        cout<<p2->get_Name()<<"'s Score: "<<p2->get_Score()<<endl;
    }

bool Game::twoRemaining(){
    int count = 0;
    for (int i = 0; i < 16; i++) {
        if (gameDeck->getCards()[i]->get_Ph() == ' ') {
            count++;
        }
    }
    return (count <= 2 && count > 0);
}

void Game::flow(){

    int ex1 = 0; int ex2 = 0;
    while(!isOver()){
            if(p1->inTurnEx(ex1)&& !isOver()){ //If externally in turn
                p1->resetPlayerTurnI();
                int i1 = 0;
                    while(p1->inTurnI(i1)&& !isOver()){
                        playTurn(p1,i1++,ex1);
                        gameDisplay();
                    }

            }
            if(!isOver() && p2->inTurnEx(ex2)){
                    p2->resetPlayerTurnI();
                    int i2 = 0;
                    while(p2->inTurnI(i2)&& !isOver()){
                        playTurn(p2,i2++,ex2);
                        gameDisplay();
                    }

            }
            ///////IMPORTANT PLACEMENT
            ex1++;
            ex2++;
    }
    cout<<"Game Over!"<<endl;
    if(p1->get_Score()>p2->get_Score()){
        cout<<"Winner is "<<p1->get_Name()<<"!"<<endl;
    }
    else if(p2->get_Score()>p1->get_Score()){
        cout<<"Winner is "<<p2->get_Name()<<"!"<<endl;
    }
    else{
        cout<<"Tie!"<<endl;
    }

}
//----------------- Main method ----------------

// felakher mynfaash ykhtar skip next turn fe penalty
// wfee moshkla flturn
//capacity

int main()
{
    srand(time(0));  // Randomize using the current time

    Game* g = new Game();
    g->initializeGame();  // Initialize the game (creates players and deck)
//    g->get_GameDeck()->faceUpAll();
    g->flow();
     // Reveal all cards
//
//    g->gameDisplay();
//    g->playTurn(g->getPlayer1());  // Start the turn for player 1
//    g->gameDisplay();
    // Display the score (just to check)

  // for std::this_thread::sleep_for
    // Stall for 2 seconds

    return 0;
}


