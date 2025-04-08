#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

const char *red[] = {"R0", "R1", "R2", "R3", "R4", "R5", "R6", "R7", "R8", "R9", "R+2", "R+2", "RRev"};
const char *green[] = {"G0", "G1", "G2", "G3", "G4", "G5", "G6", "G7", "G8", "G9", "G+2", "G+2", "GRev"};
const char *blue[] = {"B0", "B1", "B2", "B3", "B4", "B5", "B6", "B7", "B8", "B9", "B+2", "B+2", "BRev"};
const char *yellow[] = {"Y0", "Y1", "Y2", "Y3", "Y4", "Y5", "Y6", "Y7", "Y8", "Y9", "Y+2", "Y+2", "YRev"};
const char *wild[] = {"+4", "+4"};

// Function to check if a player has won the game
bool determine_winner(int player_card_count, int computer_card_count) {
    if (player_card_count == 0) {
        printf("Player wins the game!\n");
        return true;
    }
    if (computer_card_count == 0) {
        printf("Computer wins the game!\n");
        return true;
    }
    return false;
}

// Function to draw a random card
const char* draw_card() {
    int color = rand() % 4;
    int index = rand() % 13;
    switch (color) {
        case 0: return red[index];
        case 1: return green[index];
        case 2: return blue[index];
        case 3: return yellow[index];
    }
    return wild[rand() % 2];
}

int main() {
    srand(time(NULL));

    const char *player_hand[100];
    const char *computer_hand[100];
    int player_card_count = 5;
    int computer_card_count = 5;
    bool skip_turn = false;

    for (int i = 0; i < player_card_count; i++) {
        player_hand[i] = draw_card();
        computer_hand[i] = draw_card();
    }

    const char *top_card = draw_card();
    printf("Starting top card: [%s]\n", top_card);

    while (true) {
        if (!skip_turn) {
            printf("\nTop card: [%s]\n", top_card);
            printf("Your hand: ");
            for (int i = 0; i < player_card_count; i++) {
                printf("[%s] ", player_hand[i]);
            }
            printf("\n");

            int choice;
            printf("Enter the index of the card to play (-1 to draw, -5 to quit): ");
            scanf("%d", &choice);

            if (choice == -5) {
                printf("Game exited.\n");
                break;
            }
            else if (choice == -1) {
                player_hand[player_card_count] = draw_card();
                printf("You drew [%s]\n", player_hand[player_card_count]);
                player_card_count++;
            } else if (choice >= 0 && choice < player_card_count) {
                if (player_hand[choice][1] == top_card[1] || player_hand[choice][0] == top_card[0]) {
                    printf("You played [%s]\n", player_hand[choice]);
                    top_card = player_hand[choice];
                    if (strstr(top_card, "+2") || strstr(top_card, "+4")) {
                        skip_turn = true;
                    }
                    for (int i = choice; i < player_card_count - 1; i++) {
                        player_hand[i] = player_hand[i + 1];
                    }
                    player_card_count--;
                } else {
                    printf("Invalid move! Card does not match the top card.\n");
                }
            } else {
                printf("Invalid choice.\n");
            }
        } else {
            printf("Your turn is skipped due to a draw card!\n");
            skip_turn = false;
        }

        if (determine_winner(player_card_count, computer_card_count)) {
            break;
        }

        printf("\nComputer's turn...\n");
        if (!skip_turn) {
            bool played = false;
            for (int i = 0; i < computer_card_count; i++) {
                if (computer_hand[i][1] == top_card[1] || computer_hand[i][0] == top_card[0]) {
                    printf("Computer played [%s]\n", computer_hand[i]);
                    top_card = computer_hand[i];
                    if (strstr(top_card, "+2") || strstr(top_card, "+4")) {
                        skip_turn = true;
                    }
                    for (int j = i; j < computer_card_count - 1; j++) {
                        computer_hand[j] = computer_hand[j + 1];
                    }
                    computer_card_count--;
                    played = true;
                    break;
                }
            }

            if (!played) {
                computer_hand[computer_card_count] = draw_card();
                printf("Computer drew a card.\n");
                computer_card_count++;
            }
        } else {
            printf("Computer's turn is skipped due to a draw card!\n");
            skip_turn = false;
        }

        if (determine_winner(player_card_count, computer_card_count)) {
            break;
        }
    }

    return 0;
}