#ifndef CARD_H
#define CARD_H


class Card
{
     //if !faceup *
    char ph;
    protected:
    int number;
    bool faceup;
    void set_face(bool x);
    public:
        Card();
        Card(bool fu,int n);
        Card(char c);
        int get_number();
        char get_Ph();
        bool get_face();
        void set_number(int n);
        void reveal();
        void hide();
        void displayState();
        virtual void display();
        virtual bool operator==(const Card& other) const;
        virtual ~Card();
};

#endif // CARD_H
