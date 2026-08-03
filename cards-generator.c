#include <stdio.h>

typedef struct {
    char* label;
    size_t value;
} BASE_CARD;

typedef struct {
    char suit;
    char* label;
    size_t value;
    size_t is_ace;
} CARD;

int main()
{
    const char suits[] = { 'C', 'D', 'H', 'S' };
    const BASE_CARD cards[] = {
        { "2", 2 }, { "3", 3 }, { "4", 4 }, { "5", 5 }, { "6", 6 }, { "7", 7 },
        { "8", 8 }, { "9", 9 }, { "10", 10 }, { "J", 10 }, { "Q", 10 }, { "K", 10 }, { "A", 1 }
    };

    for (size_t i = 0; i < 4; ++i) {
        for (size_t j = 0; j < 13; ++j) {
            BASE_CARD card = cards[j];
            char* is_ace_str = card.label == "A" ? "TRUE" : "FALSE";
            printf("{ '%c', \"%s\", %d, %s }, ", suits[i], card.label, card.value, is_ace_str);
        }
        printf("\n");
    }

    return 0;
}
