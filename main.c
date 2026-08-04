#include <signal.h>
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
    CARD* cards[DECK_SIZE];
    size_t score;
    size_t npc;
} PLAYER;

CARD cards[] = {
    { 'C', "2", 2, FALSE }, { 'C', "3", 3, FALSE }, { 'C', "4", 4, FALSE }, { 'C', "5", 5, FALSE }, { 'C', "6", 6, FALSE }, { 'C', "7", 7, FALSE }, { 'C', "8", 8, FALSE }, { 'C', "9", 9, FALSE }, { 'C', "10", 10, FALSE }, { 'C', "J", 10, FALSE }, { 'C', "Q", 10, FALSE }, { 'C', "K", 10, FALSE }, { 'C', "A", 1, TRUE },
    { 'D', "2", 2, FALSE }, { 'D', "3", 3, FALSE }, { 'D', "4", 4, FALSE }, { 'D', "5", 5, FALSE }, { 'D', "6", 6, FALSE }, { 'D', "7", 7, FALSE }, { 'D', "8", 8, FALSE }, { 'D', "9", 9, FALSE }, { 'D', "10", 10, FALSE }, { 'D', "J", 10, FALSE }, { 'D', "Q", 10, FALSE }, { 'D', "K", 10, FALSE }, { 'D', "A", 1, TRUE },
    { 'H', "2", 2, FALSE }, { 'H', "3", 3, FALSE }, { 'H', "4", 4, FALSE }, { 'H', "5", 5, FALSE }, { 'H', "6", 6, FALSE }, { 'H', "7", 7, FALSE }, { 'H', "8", 8, FALSE }, { 'H', "9", 9, FALSE }, { 'H', "10", 10, FALSE }, { 'H', "J", 10, FALSE }, { 'H', "Q", 10, FALSE }, { 'H', "K", 10, FALSE }, { 'H', "A", 1, TRUE },
    { 'S', "2", 2, FALSE }, { 'S', "3", 3, FALSE }, { 'S', "4", 4, FALSE }, { 'S', "5", 5, FALSE }, { 'S', "6", 6, FALSE }, { 'S', "7", 7, FALSE }, { 'S', "8", 8, FALSE }, { 'S', "9", 9, FALSE }, { 'S', "10", 10, FALSE }, { 'S', "J", 10, FALSE }, { 'S', "Q", 10, FALSE }, { 'S', "K", 10, FALSE }, { 'S', "A", 1, TRUE },
};
CARD* used_cards[DECK_SIZE] = {};
short used_cards_index = 0;

void init_term()
{
    printf("\e[?1049h"); // Enable alternate buffer
    printf("\e[2J");     // Clean the screen
    printf("\e[H");      // Move the cursor home
}

void clear_term()
{
    printf("\e[2J");     // Clean the screen
    printf("\e[H");      // Move the cursor home
}

void reset_term()
{
    clear_term();
    printf("\e[?1049l"); // Disable alternate buffer
}

void reset_term_exit(int signal)
{
    reset_term();
    exit(signal);
}

char* concat(const char* str_1, const char* str_2, const char* separator)
{
    const size_t len_1 = strlen(str_1);
    const size_t len_2 = strlen(str_2);
    const size_t len_3 = strlen(separator);

    char* result = malloc(len_1 + len_2 + len_3 + 1);

    memcpy(result, str_1, len_1);
    memcpy(result + len_1, separator, len_3);
    memcpy(result + len_1 + len_3, str_2, len_2 + 1);

    return result;
}

void pause_for_input()
{
    printf("Enter to continue. . .\n");
    getchar();
}

size_t already_used(CARD* card)
{
    for (short i = 0; i < DECK_SIZE; ++i) {
        CARD* used_card = used_cards[i];
        if (!used_card || !used_card->label || !used_card->value) break;
        if (used_card->label == card->label && used_card->suit == card->suit) return TRUE;
    }
    return FALSE;
}

CARD* get_card()
{
    CARD* card = NULL;

    do card = &cards[rand() % DECK_SIZE]; 
    while (already_used(card));

    return card;
}

void print_player_status(PLAYER* player)
{
    printf("%s\n", player->name);
    printf("\tHand:  [");

    size_t i = 0;
    while (player->cards[i]) {
        printf("%c%s", player->cards[i]->suit, player->cards[i]->label);
        if (player->cards[i+1]) printf(", ");
        ++i;
    }
    printf("]\n");
    printf("\tScore: %d", player->score);
    if (player->score == BLACKJACK) printf(" BLACKJACK!");
    if (player->score > BLACKJACK) printf(" BUST!");
    printf("\n");
}


void handle_player_cards(PLAYER* current_player)
{
    size_t player_cards_index = 0;
    while (used_cards_index < DECK_SIZE && current_player->score < BLACKJACK) {
        clear_term();
        CARD* card = get_card();

        used_cards[used_cards_index++] = card;
        current_player->score += card->value;
        current_player->cards[player_cards_index++] = card;

        print_player_status(current_player);

        if (current_player->score >= BLACKJACK) break;
        if (current_player->npc) {
            if (current_player->score >= 17) break;
            continue;
        }

        printf("Hit (ENTER) or Stand (s)? ");
        char action = getchar();
        if (action == 's') break;
    }
}

void handle_players(PLAYER players[])
{
    for (size_t i = 0; i < 2; ++i) {
        PLAYER* current_player = &players[i];

        handle_player_cards(current_player);

        printf("Final score: %d\n\n", current_player->score);

        pause_for_input();
    }
}

void print_winners(PLAYER players[])
{
    size_t blackjack_result = FALSE;
    size_t winners = 0;
    size_t closest_score = 0;
    char* winners_names = NULL;
    char* separator = ", ";

    for (size_t i = 0; i < 2; i++) {
        size_t name_len = strlen(players[i].name);

        if (players[i].score > BLACKJACK) continue;
        if (players[i].score == BLACKJACK) {
            if (closest_score) winners_names = NULL;
            blackjack_result = TRUE;
            ++winners;
            winners_names = winners_names ?
                concat(winners_names, players[i].name, separator) : players[i].name;
        }
        if (!blackjack_result && players[i].score > closest_score) {
            closest_score = players[i].score;
            winners_names = players[i].name;
            ++winners;
        }
    }
    if (winners) printf("%s %s the winner%c!\n",
                        winners_names,
                        winners > 1 ? "are" : "is",
                        winners > 1 ? 's' : '\0');
    else printf("Bust!\n");
}

void reset_players(PLAYER players[])
{
    for (size_t i = 0; i < 2; ++i) {
        memset(players[i].cards, 0, sizeof(players[i].cards));
        players[i].score = 0;
    }
}

int main()
{
    srand(time(NULL));
    init_term();
    signal(SIGINT, reset_term_exit);

    char play_again = 'y';
    PLAYER players[] = { { "Player", {}, 0, FALSE }, { "House", {}, 0, TRUE } };
    // PLAYER players[] = { { "Dealer", {}, 0, TRUE }, { "Player", {}, 0, FALSE } };

    do {
        handle_players(players);
        clear_term();

        print_winners(players);

        pause_for_input();
        reset_players(players);
        printf("Play again? (Y/n) ");
    } while (play_again = getchar() != 'n' && play_again != 'N');

    reset_term();
    return 0;
}
