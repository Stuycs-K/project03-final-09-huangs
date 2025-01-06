# Final Project Proposal

## Group Members:

Stanley Huang

# Intentions:

A game where two players compete against each other to type a randomly generated list of a couple words the fastest. Each player will need to type in a username when they first connect and it will be displayed on a leaderboard. There will be a command to check the leaderboard and a way to reset it.

# Intended usage:

When the game is first created, the creator can reset the leaderboard. When not in the round, the creator can control when the game is started while everyone can check the leaderboard. When in the round, the same word will appear for all players and the next word will appear only after the player types in the first one and presses ENTER. Round does not stop until all players are done.

# Technical Details:

I will use semaphores to limit the players to 2. To time the players, I will use time(NULL). I will use shared memory segments so the other player will know who won (set it to the time that the other player finished) or if the other player quit (set to -1 through sighandler). I may also use it to start/end rounds and let the player know where the other player is. For the leaderboard, I will read a leaderboard.txt and use stat to determine the size of the arrays. For the game itself, a lot of fgets and stdin will be used.

# Intended pacing:

1/8 - game works for one player
1/10 - creator works and can start the game for the one player
1/13 - second player can connect and both players can decide usernames
1/17 - the game works for both players and a winner can be determined
1/18 - functioning leaderboard
1/20 - complete video
