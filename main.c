#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define FALSE 0
#define TRUE 1
#define DECK_SIZE 52
#define BLACKJACK 21

typedef struct {
    char suit;
    char* label;
    size_t value;
    size_t is_ace;
} CARD;

typedef struct {
    char* name;
    CARD cards[DECK_SIZE];
    size_t score;
    size_t npc;
} PLAYER;

size_t already_used(CARD card, CARD used_cards[DECK_SIZE])
{
    for (short i = 0; i < DECK_SIZE; ++i) {
        if (!used_cards[i].label && !used_cards[i].value) break;
        if (used_cards[i].label == card.label && used_cards[i].suit == card.suit) return TRUE;
    }
    return FALSE;
}

// TODO transform cards in global
CARD get_card(const CARD cards[], CARD used_cards[DECK_SIZE])
{
    CARD card;

    do card = cards[rand() % DECK_SIZE]; 
    while (already_used(card, used_cards));

    return card;
}

void handle_player_cards(
    short* used_cards_index,
    PLAYER* current_player,
    const CARD cards[],
    CARD used_cards[])
{
    while (*used_cards_index++ < DECK_SIZE && current_player->score < BLACKJACK) {
        CARD card = get_card(cards, used_cards);
        current_player->score += card.value;
        printf("%c%s - Score %d\n", card.suit, card.label, current_player->score);

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

    const CARD cards_2[] = {
        { 'C', "2", 2, FALSE }, { 'C', "3", 3, FALSE }, { 'C', "4", 4, FALSE }, { 'C', "5", 5, FALSE }, { 'C', "6", 6, FALSE }, { 'C', "7", 7, FALSE }, { 'C', "8", 8, FALSE }, { 'C', "9", 9, FALSE }, { 'C', "10", 10, FALSE }, { 'C', "J", 10, FALSE }, { 'C', "Q", 10, FALSE }, { 'C', "K", 10, FALSE }, { 'C', "A", 1, TRUE }, 
        { 'D', "2", 2, FALSE }, { 'D', "3", 3, FALSE }, { 'D', "4", 4, FALSE }, { 'D', "5", 5, FALSE }, { 'D', "6", 6, FALSE }, { 'D', "7", 7, FALSE }, { 'D', "8", 8, FALSE }, { 'D', "9", 9, FALSE }, { 'D', "10", 10, FALSE }, { 'D', "J", 10, FALSE }, { 'D', "Q", 10, FALSE }, { 'D', "K", 10, FALSE }, { 'D', "A", 1, TRUE }, 
        { 'H', "2", 2, FALSE }, { 'H', "3", 3, FALSE }, { 'H', "4", 4, FALSE }, { 'H', "5", 5, FALSE }, { 'H', "6", 6, FALSE }, { 'H', "7", 7, FALSE }, { 'H', "8", 8, FALSE }, { 'H', "9", 9, FALSE }, { 'H', "10", 10, FALSE }, { 'H', "J", 10, FALSE }, { 'H', "Q", 10, FALSE }, { 'H', "K", 10, FALSE }, { 'H', "A", 1, TRUE }, 
        { 'S', "2", 2, FALSE }, { 'S', "3", 3, FALSE }, { 'S', "4", 4, FALSE }, { 'S', "5", 5, FALSE }, { 'S', "6", 6, FALSE }, { 'S', "7", 7, FALSE }, { 'S', "8", 8, FALSE }, { 'S', "9", 9, FALSE }, { 'S', "10", 10, FALSE }, { 'S', "J", 10, FALSE }, { 'S', "Q", 10, FALSE }, { 'S', "K", 10, FALSE }, { 'S', "A", 1, TRUE }, 
    };
    CARD used_cards[DECK_SIZE] = {};
    short used_cards_index = 0;
    PLAYER players[] = { { "Player", {}, 0, FALSE }, { "House", {}, 0, TRUE } };
    PLAYER* winner = NULL;

    for (size_t i = 0; i < 2; ++i) {
        PLAYER* current_player = &players[i];
        printf("Player: %s\n", current_player->name);

        handle_player_cards(&used_cards_index, current_player, cards_2, used_cards);

        printf("Final score: %d\n\n", current_player->score);
        if (current_player->score <= BLACKJACK) winner = current_player;
    }

    if (winner) printf("%s is the winner!\n", winner->name);
    else printf("Bust!");

    return 0;
}
