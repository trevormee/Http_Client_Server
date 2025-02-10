## Overview
This is a simple HTTP server that utilizes TCP sockets for handling HTTP requests

## Project Members
Trevor Mee

## File Structure Breakdown
**Root Directory**
- httpServer.cpp (contains all source code for this project)
- Makefile
- Protocol_Document_P1.pdf
- proj1 (executable)
- README.md
- img.jpg
- index.html
- testPresence.html

**Screen_Captures Directory**

Navigate into the Screen_Captures directory to find 4 screenshots of the project working on my end.
- working_clientServer_index.png: Displays a screen shot of the client and server communicating to display 'index.html' on a web broswer.
- working_clientServer_dragon.png: Displays a screen shot of the client and server communicating to display 'img.jpg' on a web browser.
- invalid_clientServer_htmlFile.png: Displays a screen shot of the client and server communicating to display an error message for an invalid html file.
- shut_down_server.png: Displays a screen shot of the connection being broken between the client and server after the server has been shut down.

## Notes for Grader
This project was developed utilizing WSL. Please use WSL when grading this program. Note that my project does compile and run on the SSH server, but you will not be able to test the browser as a client on the SSH server. 

## Compilation and Running
1. **Ensure that port 60001 is available to be opened**

2. **Navigate into the projects root directory**

3. **Compile the program:**
```bash
    make
```

4. **Run the program**
```bash
    ./proj1
```

## Usage
Once the server is running, you can access it through a web browser or through command line commands like 'curl'.

**Example**
- Open a web browser and go to 'http://localhost:60001/index.html'

