/*
 * Expected result using ♤ ♡ ♧ ♢
 * -------
 * |10   |
 * |  ♤  |
 * |   10|
 * -------
*/
#include <stdio.h>

typedef struct {
    char suit;
    char* label;
} CARD;

CARD cards[] = {
    { 'C', "2" }, { 'C', "3" }, { 'C', "4" }, { 'C', "5" }, { 'C', "6" }, { 'C', "7" }, { 'C', "8" }, { 'C', "9" }, { 'C', "10" }, { 'C', "J" }, { 'C', "Q" }, { 'C', "K" }, { 'C', "A" },
    { 'D', "2" }, { 'D', "3" }, { 'D', "4" }, { 'D', "5" }, { 'D', "6" }, { 'D', "7" }, { 'D', "8" }, { 'D', "9" }, { 'D', "10" }, { 'D', "J" }, { 'D', "Q" }, { 'D', "K" }, { 'D', "A" },
    { 'H', "2" }, { 'H', "3" }, { 'H', "4" }, { 'H', "5" }, { 'H', "6" }, { 'H', "7" }, { 'H', "8" }, { 'H', "9" }, { 'H', "10" }, { 'H', "J" }, { 'H', "Q" }, { 'H', "K" }, { 'H', "A" },
    { 'S', "2" }, { 'S', "3" }, { 'S', "4" }, { 'S', "5" }, { 'S', "6" }, { 'S', "7" }, { 'S', "8" }, { 'S', "9" }, { 'S', "10" }, { 'S', "J" }, { 'S', "Q" }, { 'S', "K" }, { 'S', "A" },
};

char* suit_icon(char suit)
{
    switch (suit) {
        case 'C': return "♧";
        case 'D': return "♢";
        case 'H': return "♡";
        case 'S': return "♤";
    }
}

void print_card(CARD* card)
{
    printf("-------\n");
    printf("|%-2s   |\n", card->label);
    printf("|  %s  |\n", suit_icon(card->suit));
    printf("|   %2s|\n", card->label);
    printf("-------\n");
}

void print_card_side_by_side(CARD* card, size_t index)
{
    size_t col = index * 10;
    char col_sequence[32] = "";
    if (index != 0) {
        printf("\e[%dA", 5);
        snprintf(col_sequence, sizeof(col_sequence), "\e[%dC", col);
    }

    printf("%s-------\n", col_sequence);
    printf("%s|%-2s   |\n", col_sequence, card->label);
    printf("%s|  %s  |\n", col_sequence, suit_icon(card->suit));
    printf("%s|   %2s|\n", col_sequence, card->label);
    printf("%s-------\n", col_sequence);
}

int main()
{
    for (size_t i = 0; i < 52; ++i)
        print_card(&cards[i]);

    printf("====== testing side by side ======\n");
    for (size_t i = 0; i < 8; ++i)
        print_card_side_by_side(&cards[i], i);
    return 0;
}
