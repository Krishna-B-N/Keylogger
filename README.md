# Windows Keylogger (C++ Source-Based Execution)

> ⚠️ **DISCLAIMER:**  
> This code is provided **strictly for educational and ethical research purposes**.  
> Do **NOT** use this software on any system you do not own or have explicit permission to test.  
> Unauthorized use of keyloggers is illegal and may lead to criminal prosecution.
> The code author does not take any responsibility for unethical use of this code.

---

## 📌 Overview

This is a simple Windows keylogger written in C++. It monitors keypress events using the Windows API (`GetAsyncKeyState`, `GetKeyState`, and `MapVirtualKey`) and writes the captured keystrokes to a file called `LogFile.txt`.

The compiled `.exe` file is typically flagged by Windows Defender and most antivirus programs. However, transferring the **source code** to a system and compiling it **locally** may evade AV detection.

---

## ✨ Features

- Logs:
  - Alphabetic keys with correct case based on Caps Lock and Shift
  - Special characters and symbols (e.g., `!@#$%^&*()_+`)
  - Control keys: `<Enter>`, `<Tab>`, `<Backspace>`, `<Ctrl>`, `<Alt>`, `<Arrow keys>`, etc.
  - Spacebar, numpad input
- Writes all output to `LogFile.txt` in the same directory
- Uses only native Windows API functions

---

## ⚙️ How to Use (For Educational Purposes Only)

### ✅ Requirements
- A Windows system with a working C++ compiler (e.g., MinGW or TDM-GCC)

### 🛠️ Compilation
Open a terminal or PowerShell in the folder containing the `.cpp` file and run:

```bash
g++ keylogger.cpp -o keylogger.exe
./keylogger.exe
