# Card Crptography
A collection of Card Themed Cryptography projects (Mental Poker, Solitare Cipher) written in C, C++ and eventually Assembly (x64)

## Mental Poker
Implemented with a handcrafted implementation of Blowfish running in OFB (I may change the algorithm to TwoFish or AES if it gets more use)

The protocal (Two Players, Bob and Alice):
 - Alice generates 52 cards, each with a random string attached, and encrypts them with her key (any commutable public or symmetric algorithm will do)
 - Bob randomly selects 5, encrypts them with his key, and sends 5 additional cards that he does not encrypt back to Alice
 - Alice decrypts all 10 cards and sends the ones still encrypted with Bob's key back
 
 ## Solitare Cipher
 
 a description can be found at <https://www.schneier.com/academic/solitaire/>
