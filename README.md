# Project Name
<b>SFML Calculator<b>

# Project Description
Simple Calculator made from scratch from SFML. <br>
All assets are made by me with Inkscape.

# Time Spent
It's been 3 weeks since I've starting; <br>
However, not all my time is spent on this project. <br> 
It's only for fun, even though the project idea is trivial

# How to install
- Make sure you have SFML 2.6 Installed.
- At the moment, this version only works on windows. (since of the clipboard logic).

1. Run `cmake ..` inside ./build folder.
2. Run `ninja` inside the ./build folder.
3. Run `./calculator.exe` make sure you are inside the build folder or the assets wont load.

# Usability Controls

## Keyboard Inputs:
    0-9   :   (Add a digit)     
    .     :   (Add a decimal point)    
    +     :   (Add operation)      
    -     :   (Subtract operation)
    *     :   (Multiply operation)
    /     :   (Divide operation)
    
    Enter     :   (Equate expression)
    =    :   (Equate expression)           
    CTRL + C  :   (Resets)        

## Copying to clipboard:

    - Just click on the texts (which aren't buttons) and it will be copied onto the clipboard.

## Requirements
- ✅ Numbers now use long long and double long, and now use stringstream to deal with number overflowing. (Dealing it with myself is too confusing.)
- ✅ Texts shouldn't overflow, they should have a limit.
- ✅ Notifies the user they copied something.
- ✅ Texts that can be copied glow a light purple for interactivity.
- ✅ Feature to copy either the results text, or the input text to the os clipboard, through right clicking.
- ✅ Implement key inputs for user experience. CTRL-C to clear, press numbers, periods, etc.
- ✅ Buttons darken on hover.
- ✅ UI Looks decent.. not horrible.

# Changes to be made
1. (!DONE) Clean up the main function (Encapsulate It) 
2. (!DONE) Changes to the notification sprite.
  - the position of the notification png, should be below the operator character. not left to it.
  - The design, make it more horizontal
3. (!Scrapped, I prefer the current structure) Create a base pure base class UIEntity, since currently all entities require hovering, clicking, and updating.