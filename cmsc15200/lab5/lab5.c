#include <stdio.h>
#include <stdlib.h>

enum face {
    JACK, QUEEN, KING
};

enum suit {
    HEARTS, DIAMONDS, SPADES, CLUBS
};

enum card_tag {
    FACE, NUMBERED
};

struct face_card {
    enum face rank;
    enum suit suit;
};

struct numbered_card {
    unsigned int rank;
    enum suit suit;
};

union card_type {
    struct face_card f;
    struct numbered_card n;
};

struct card {
    union card_type type;
    enum card_tag tag;
};

struct card make_numbered_card(unsigned int rank, enum suit suit)
{
    struct card card;
    card.tag = NUMBERED;
    card.type.n.rank = rank;
    card.type.n.suit = suit;

    return card;
}

enum suit flush(struct card *hand, unsigned int num_cards) {
    enum suit flush_suit;
    switch (hand[0].tag) {
        case FACE:
            flush_suit = hand[0].type.f.suit;
            break;
        case NUMBERED:
            flush_suit = hand[0].type.n.suit;
            break;
    }
    for (int i = 0; i < num_cards-1; i++) {
        switch(hand[i].tag) {
            case FACE:
                switch(hand[i+1].tag) {
                    case FACE:
                        if (hand[i].type.f.suit != hand[i+1].type.f.suit) {
                            return -1;
                        }
                        else {
                            flush_suit = hand[i].type.f.suit;
                            break;
                        }
                    case NUMBERED:
                        if (hand[i].type.f.suit != hand[i+1].type.n.suit) {
                            return -1;
                        }
                        else {
                            flush_suit = hand[i].type.f.suit;
                            break;
                        }
                }
            case NUMBERED:
                switch(hand[i+1].tag) {
                    case FACE:
                        if (hand[i].type.n.suit != hand[i+1].type.f.suit) {
                            return -1;
                        }
                        else {
                            flush_suit = hand[i].type.n.suit;
                            break;
                        }
                    case NUMBERED:
                        if (hand[i].type.n.suit != hand[i+1].type.n.suit) {
                            return -1;
                        }
                        else {
                            flush_suit = hand[i].type.n.suit;
                            break;
                        }
                }
        }
    }
    return flush_suit;
}

int N_of_a_kind(struct card *hand, unsigned int num_cards, unsigned int N) {
    unsigned int counts[13] = {0};
    for (int i = 0; i < num_cards; i++) {
        switch(hand[i].tag){
            case FACE:
                switch(hand[i].type.f.rank) {
                    case JACK:
                        if (counts[10] + 1 == N) {
                            return 1;
                        }
                        else {
                            counts[10] ++;
                            break;
                        }
                    case QUEEN:
                        if (counts[11] + 1 == N) {
                            return 1;
                        }
                        else {
                            counts[11] ++;
                            break;
                        }
                    case KING:
                        if (counts[12] + 1 == N) {
                            return 1;
                        }   
                        else {
                            counts[12] ++;
                            break;
                        }
                }
                break;
            case NUMBERED:
                if (counts[hand[i].type.n.rank-1] + 1 == N) {
                    return 1;
                }
                else {
                    counts[hand[i].type.n.rank-1] ++;
                    break;
                }
        }
    }
    return 0;
}

unsigned int twenty_one(struct card *hand, unsigned int num_cards) {
    int score = 0;
    int num_aces = 0;
    for (int i = 0; i < num_cards; i++) {
        switch(hand[i].tag) {
            case FACE:
                switch(hand[i].type.f.rank){
                    case JACK:
                        score += 10;
                        break;
                    case QUEEN:
                        score += 10;
                        break;
                    case KING:
                        score += 10;
                        break;
                }
                break;
            case NUMBERED:
                score += hand[i].type.n.rank;
                if (hand[i].type.n.rank == 1){
                    num_aces ++;
                }
                break; 
        }   
    }
    for (int i = 0; i < num_aces; i++) {
        if (score + 10 > 21){
            break;
        }
        score += 10;
    }
    return score;
}

int main() {
    struct card ace;
    ace.tag = NUMBERED;
    ace.type.n.rank = 1;
    ace.type.n.suit = SPADES;

    struct card king;
    king.tag = FACE;
    king.type.f.rank = KING;
    king.type.f.suit = SPADES;

    struct card c1 = make_numbered_card(1, SPADES);
    struct card c2 = make_numbered_card(9, HEARTS);
    struct card c3 = make_numbered_card(3, SPADES);
    struct card c4 = make_numbered_card(9, DIAMONDS);
    struct card hand[] = {ace, c1, c2, c3};
    struct card hand2[] = {ace}; 
    printf("%d\n",  flush(hand, 4));
    printf("%d\n", flush(hand2, 1));
    printf("%d\n", N_of_a_kind(hand, 4, 2));
    printf("%d\n", N_of_a_kind(hand, 4, 3));
    printf("%d\n", twenty_one(hand, 4));
    printf("%d\n", twenty_one(hand2, 1));
    struct card hand3[] = {king, c4};
    printf("%d\n", twenty_one(hand3, 2));
    return 0;
}
