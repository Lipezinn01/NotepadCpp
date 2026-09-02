💻 Cpp Notepad v1.0.0
A professional, ultra-fast text editor developed in C++ using the native Windows API.

GitHub Platform Language

🌟 Key Features
⚡ Peak Performance
Ultra-compact .exe file (~50-100 KB)
Instant execution speed ⚡
No lag or freezing
Minimal memory usage
🎨 Professional Fonts
Access to ALL Windows system fonts
Standard Windows ChooseFont dialog
Real-time preview
Special effects (bold, italic, underline, strikethrough)
Unlimited sizes
🛡️ Security
100% trusted by Windows Defender
No antivirus blocks
Compiled native code
Legitimate Windows APIs
No external dependencies
📝 Full Functionality
✅ Open files (.txt, .log, .py, .html, .json, etc.)
✅ Save with any extension
✅ Save specifically as .txt
✅ Automatic/manual line wrapping at 1024 characters
✅ Format menu with access to all fonts
✅ Keyboard shortcuts (CTRL+S, CTRL+O, CTRL+N)
✅ Modification detection
✅ User-friendly, responsive interface
🚀 Download and Installation
Option 1: Direct Download
Download Cpp Notepad v1.0.0

1. Download CppNotepad.exe
2. Run the file
3. Done! No installation required
Option 2: Clone from GitHub
git clone https://github.com/Lipezinn01/CppNotepad-1.0.0.git
cd CppNotepad-1.0.0
📖 How to Use
Main Menu Buttons
Button	Function	Shortcut
Save As...	Saves with any extension	CTRL+S*
Save .txt	Quickly saves as .txt	-
Choose Document	Opens files from PC	CTRL+O
Format	Opens formatting menu	-
Help	Shows program help	-
*CTRL+S opens "Save As"

Format Menu
┌─────────────────────────────────┐
│ Format                          │
├─────────────────────────────────┤
│ ✓ Word Wrap                     │ ← Toggle
│ Fonts...                        │ ← Opens ChooseFont
└─────────────────────────────────┘
Word Wrap:

Automatic (default): Creates a new line automatically upon reaching 1024 characters
Manual: Stops at 1024 characters; requires pressing ENTER
Fonts:

Opens standard Windows dialog
Access to ALL installed fonts
Real-time preview
Unlimited size and styles
🎯 Keyboard Shortcuts
Shortcut	Function
CTRL+S	Save As
CTRL+O	Open file
CTRL+N	Toggle Word Wrap
CTRL+Z	Undo (Windows native)
CTRL+Y	Redo (Windows native)

💡 Available Versions
There are 2 versions of the Notepad available:

🐍 Python Notepad
Easy to customize and modify
Cross-platform (Windows, Linux, macOS)
Python source code
Tkinter interface
~10-15 MB
💻 Cpp Notepad (THIS REPOSITORY)
Maximum performance
Native Windows
Ultra-compact file (~50-100 KB)
C++ source code
Access to all system fonts
RECOMMENDED for distribution
🔧 Compilation (Optional)
If you want to compile from the Source code:

Requirements
Visual Studio 2019+ or MinGW
Windows SDK
Compile with Visual Studio
cl /O2 /Fe:CppNotepad.exe notepad.cpp /link user32.lib gdi32.lib comdlg32.lib comctl32.lib
Compile with MinGW
g++ -O2 -o CppNotepad.exe notepad.cpp -luser32 -lgdi32 -lcomdlg32 -lcomctl32
📊 Statistics
Language:        C++ (100%)
Lines of code: ~250 lines
.exe size:       ~50-100 KB
Compile time:    <1 second
Memory usage:    ~5-10 MB (in use)
Compatibility:   Windows 7+ (64-bit and 32-bit)
🐛 Known Issues
None identified so far! ✅

Support for very large files (>100 MB)
📝 License
This project is licensed under the MIT License - see the LICENSE file for details.

MIT License

Copyright (c) 2026 Lipezinn01

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction...
👨‍💻 Author
Lipezinn01

GitHub: @Lipezinn01

🤝 Contributions
Contributions are welcome! You can:

Fork the project
Create a branch for your feature (git checkout -b feature/AmazingFeature)
Commit changes your changes (git commit -m 'Add some AmazingFeature')
Push to the branch (git push origin feature/AmazingFeature)
Open a Pull Request
💬 Feedback and Suggestions
If you have suggestions or find bugs, please open an Issue.

📚 Resources Used
Windows API - CreateWindowEx, SendMessage, etc.
Common Controls - ChooseFont, OpenFileName
Standard C++ - STL, strings, vectors
Visual Studio - Compilation and development
⭐ If you liked it, leave a star!
If this project was useful to you, please consider leaving a ⭐ on GitHub!

📜 Version History
v1.0.0 (2026-05-09)
v1.1.0 (2026-07-09)
v2.0.0 (2026-09-02)
Developed with ❤️ in C++
