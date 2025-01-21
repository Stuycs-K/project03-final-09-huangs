# Dev Log:

This document must be updated daily by EACH group member.

## Stanley Huang

### 2025-01-07 - Game works for one player and one word
Includes time taken and asks player to retype word if typed incorrectly. (20 minutes)

### 2025-01-08 - Game nearly works for one player
Works for a list of 10 randomly generated words. There is a singular bugged word. (1 hour)

### 2025-01-09 - Working game for two simultaneous players
Expanded word bank size from 100 to 1000. Uses semaphores to limit players to two. (2 hours)

### 2025-01-10 - Game is synchronized now and signals work.
Used shared memory segments so players start at the same time. When players are done, they send their times to the host. Also, signals work now during times when inputs are expected. (2 hours)

### 2025-01-13 - Players now communicate with each other
Used shared memory so players know what word the other player is at. Updates after the types in a new word. (1 hour)

### 2025-01-14 - Updated visuals during the game and multiple rounds can now be played
Added a car animation instead of plain text to display what word each player is at. Also, ./player doesn't end immediately after one round. (2 hours)

### 2025-01-15 - Nothing
Made several local commits that had working not reading input during the countdown and ability to start the second round instead of it playing immediately. However, circumstances happened and I rm -rf'd the entire folder so the progress is lost. (3 hours)

### 2025-01-16 - Reverted damages from yesterday's rm
Game now starts normally for players instead of having them newline first. (1 hour)

### 2025-01-17 - Working ignore input during countdown
Anything you type during the countdown will be ignored for the first word (2 hours)

### 2025-01-19 - Working score and setusername and added various print statements and started on sigint for players
Host and players can check the score. Score is automatically updated after each game. Players can set their usernames and it will be reflected in the score and in the game string. Host knows when a player sigints. The mechanics of the game are practically done. (7 hours)

### 2025-01-20 - Working everything else
Added player and host sighandlers to make sure shared memory segments and semaphores are removed properly. If host sigints, both players are now removed. Players now have to wait for the current game to be over to start playing. Fixed minor issue when game is started while a player is setting their username. Fixed issue where the winner is incorrectly decided if a player quits. Also uploaded demo and updated README.md. (5 hours)
