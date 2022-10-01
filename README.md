# 2048-in-c

- This is a 2048 game I made to teach a friend to program in C/C++.
- It is based on an university assignment we found.
- It's intended to be played on the terminal.
- We were starting from 0, so the code is very simple and not elegant at all.


Originally, I programmed the whole thing without using external functions or pointers as the assignment indicates.


**Controls:**

- Key **(w, a, s, d)** = (up, left, down, right)
- Key **q** = quit the game.


**Updates:**

- Rewrote some parts of the code to follow quality standards.
- Translated it all to English to follow international standards.
- Added functions to reuse code and make it more elegant.
- Add a good algorithm to search a random unused matrix cell now using pointers. For this I created a List module. This increased the speed notoriously.
- Also added a missing detail: when generating a new number, it generated a 2. Now it's corrected as the original game generates a 2 or a 4.
