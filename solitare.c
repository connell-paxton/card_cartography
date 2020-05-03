#include <stdio.h>
#include <stdbool.h>
#define swap(a, b) a ^= b; b = a ^ b; a ^= b;
#define swap3(a, b, c) a = a ^ b ^ c; b = a ^ b ^ c; c = a ^ b ^ c; a = a ^ b ^ c;
/* Suit Value */
#define SPADE 0x53
#define DIAMOND 0x44
#define HEART 0x48
#define CLUB 0x43

#define _CLV 0
#define _DMD 13
#define _HRT 26
#define _SPD 39
#define _JA 53
#define _JB 54



unsigned char JA_pos = 0;
unsigned char JB_pos = 0;

char* encrypt(char* plain_text, char* keystream, int len);
char* ShuffleDeck(int len);
char* process_cards(char deck[162]);
int main(int argc, char **argv) {
    char deck[162];
    char* plain_text;
    unsigned int len;
    printf("Please Input your 54 card deck: ");
    fgets(deck, 164, stdin);
    printf("Please input the length: ");
    scanf("%i\n", &len);
    printf("Please input your message (CAPS ONLY OR NO SERVICE): ");
    scanf("%s\n", plain_text);
    char* keystream = KeyGen(len);
    free(keystream);

    return 0;
}

char* process_cards(char deck[162]) {
    char new_deck[54];
    for (unsigned char i = 0, j = 0; j < 54; j++) {
        switch(deck[i]) {
            case 'J':
                switch (deck[(i*3)+1]) {
                    case 'A':
                        JA_pos = j;
                        new_deck[j] = _JA;
                    break;
                    case 'B':
                        JB_pos = j;
                        new_deck[j] = _JB;
                    break;
                }
                i += 2;
            break;
            default:
                new_deck[j] = (deck[i] == 'C')?
                        _CLV
                        : (deck[i] == 'D')? _DMD
                            : (deck[i] == 'H')? _HRT : _SPD;
                new_deck[j] += (deck[i+1] == 0x31)? 10
                                : (deck[i+1] == 'J')? 11
                                    : (deck[i+1] == 'Q')? 12
                                        : (deck[i+1] =='K')? 13
                                            : (deck[i+1] == 'A')? 1
                                                : (deck[i+1] - 0x30);
                i += (deck[i+1]==0x31)? 3 : 2;
            break;
        }
    }
    return new_deck;
}

char* ShuffleDeck(char* deck) {
    /*
    1. Find A Joker, then move it one down (swap it with the card below it)
    2. Find B Joker, then move it two down
    3. "Triple Cut" - swap the card groups outside the two jokers
    4. "Count cut"
        - Count down from the top card by the bottom card
        - Cut from there, leaving the bottom card on the bottom
    5. Find output
    */
    // Step 1
    swap(deck[JA_pos], deck[(JA_pos + 1) % 54]);
    // Step 2
    // swap3 makes a = c , b = a, c = b
    // run it again and a = b, b = c, c = a
    swap3(deck[JB_pos], deck[(JB_pos + 1) % 54],  deck[(JB_pos + 1) % 54]);
    swap3(deck[JB_pos], deck[(JB_pos + 1) % 54],  deck[(JB_pos + 1) % 54]);

    // Step 3
    char new_deck[54];
    if(JA_pos > JB_pos) {
        const unsigned char over_a = 53 - JA_pos; // number of cards after JA
        for(unsigned char i = 53; i != JA_pos; i--) {
            new_deck[53-i] = deck[i];
        }
        new_deck[over_a] = _JB;
        JB_pos =  over_a;
        for(unsigned char i = JB_pos; i < 54; i++) {

        }
    }
}

char* encrypt(char* plain_text, char* keystream, int len) {
    char cipher_text[len];
    for (unsigned char i = 0; i < len, i++) {
        for (unsigned char j = 0; j < 5; i++) {
            cipher_text[i] = ((plain_text[i] - 0x64) + keystream[i]) % 26;
        }
    }
}
