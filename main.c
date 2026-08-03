#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define FALSE 0
#define TRUE 1
#define DECK_SIZE 52
#define SUIT_SIZE 4
#define CARD_SIZE 13
#define BLACKJACK 21

typedef struct {
    char* label;
    size_t value;
} BASE_CARD;

typedef struct {
    size_t value;
    char* card_label;
} CARD;

typedef struct {
    char* name;
    CARD cards[DECK_SIZE];
    size_t score;
    size_t npc;
} PLAYER;

char* concat(const char* s1, const char* s2)
{
    const size_t len1 = strlen(s1);
    const size_t len2 = strlen(s2);
    char* result = malloc(len1 + len2 + 1);
    // check for errors in malloc here
    memcpy(result, s1, len1);
    memcpy(result + len1, s2, len2 + 1);
    return result;
}

void free_cards(CARD used_cards[DECK_SIZE])
{
    for (short i = 0; i < DECK_SIZE; ++i) free(used_cards[i].card_label);
}

size_t already_used(const char* card, CARD used_cards[DECK_SIZE])
{
    for (short i = 0; i < DECK_SIZE; ++i) {
        if (!used_cards[i].card_label && !used_cards[i].value) break;
        if (used_cards[i].card_label == card) return TRUE;
    }
    return FALSE;
}

CARD get_card(const char* suits[], const BASE_CARD cards[], CARD used_cards[DECK_SIZE])
{
    char* card_label;
    size_t card_index = 0;

    do card_label = concat(suits[rand() % SUIT_SIZE], cards[card_index = rand() % CARD_SIZE].label); 
    while (already_used(card_label, used_cards));

    CARD card = {
        .value = cards[card_index].value,
        .card_label = card_label
    };

    return card;
}

void handle_player_cards(
    short* used_cards_index,
    PLAYER* current_player,
    const char* suits[],
    const BASE_CARD cards[],
    CARD used_cards[])
{
    while (*used_cards_index++ < DECK_SIZE && current_player->score < BLACKJACK) {
        CARD card = get_card(suits, cards, used_cards);
        current_player->score += card.value;
        printf("%s - Score %d\n", card.card_label, current_player->score);

        if (current_player->score > BLACKJACK) break;
        if (current_player->npc) {
            if (current_player->score >= 17) break;
            continue;
        }

        printf("Hit (ENTER) or Stand (s)? ");
        char action = getchar();
        if (action == 's') break;
    }
}

int main()
{
    srand(time(NULL));

    const BASE_CARD cards[] = {
        { "2", 2 }, { "3", 3 }, { "4", 4 }, { "5", 5 }, { "6", 6 }, { "7", 7 },
        { "8", 8 }, { "9", 9 }, { "10", 10 }, { "J", 10 }, { "Q", 10 }, { "K", 10 }, { "A", 1 }
    };
    const char* suits[] = { "C", "D", "H", "S" };
    CARD used_cards[DECK_SIZE] = {};
    short used_cards_index = 0;
    PLAYER players[] = { { "Player", {}, 0, FALSE }, { "House", {}, 0, TRUE } };
    PLAYER* winner = NULL;

    for (size_t i = 0; i < 2; ++i) {
        PLAYER* current_player = &players[i];
        printf("Player: %s\n", current_player->name);

        handle_player_cards(&used_cards_index, current_player, suits, cards, used_cards);

        printf("Final score: %d\n\n", current_player->score);
        if (current_player->score <= BLACKJACK) winner = current_player;
    }

    if (winner) printf("%s is the winner!\n", winner->name);
    else printf("Bust!");

    free_cards(used_cards);
    return 0;
}
