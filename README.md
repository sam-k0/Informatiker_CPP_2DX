# Informatiker_CPP_2DX
Now with 200% more memory leaks!

# What is this?

A simple card game without card images made in C++ and GameMaker:Studio IDE

This is more a proof of concept than a real game. I just wanted to try coding a game in C++, and because C++ GUIs are really tedious, I used GM:S for that.
The whole thing could be enhanced by the actual use of card images but I am simply too lazy to put them in.

# How it works

- Game logic is coded in C++, exported as a DLL
- The "GUI" is made with GameMaker: Studio
- The Inputs are detected by the GMS runnable and sent to the DLL
- The DLL handles the inputs given from the GUI
- The DLL triggers callbacks in the GUI with necessary info about the game
- The GUI displays the received info
