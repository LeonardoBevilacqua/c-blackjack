# C Blackjack

Blackjack game done with C.

## Issues and improvements

- `getchar()` not properly handled. Pressing any other key instead of 's' will move loop.
- UI sucks, should be properly handled to look more like a game.
- Improve main loop, extract to own function.
- Allow more players/NPCs.
- Improve NPC decision.
- Add chips mechanic.
- Handle soft and hard hand.
- BUG: if house stops with score less than 21, it will mark as winner even if player has won.
