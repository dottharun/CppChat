# CppChat - A C++ Networking Project
CppChat is a console-based chat application that allows users to communicate with each other over TCP and UDP connections. The application is written in C++ and uses sockets to establish connections between clients. Users can send and receive text messages in real-time, as well as view their chat history. The application includes error handling and input validation to ensure a smooth user experience.


## Features
- Supports both TCP and UDP connections
- Real-time messaging
- Chat history
- Robust error handling and input validation
- Simple and intuitive user interface
## Technologies Used
- C++
- Threads
- Sockets
- TCP/UDP protocols
- Git
## Learning Outcomes
During the development of CppChat, I gained experience in the following areas:

- Project management
- Networking protocols
- Socket programming
- Error handling and input validation
- CppChat is a great showcase of my skills in C++, networking, and project management. As I continue to develop and improve the application, I look forward to exploring new features and technologies, and applying what I've learned to future projects.

## Installation
To install CppChat, follow these steps:

1. Clone the repository to your local machine:

`git clone https://github.com/dottharun/CppChat.git`

2. Navigate to the project directory:

`cd CppChat`

3. Compile the source code using your preferred C++ compiler:

`g++ -o CppChat Project.cpp`

4. Run the application:

`./CppChat`
## Usage
Once you've installed CppChat, you can use the following commands to start a chat session:

- `$register <username>`: Registers the specified username for the current client session.
- `$getlist`: Returns a list of all connected clients.
- `$getlog`: Returns the chat log for the current session.
- `$exit`: Closes the connection to the server and exits the application.
- `$chat <message>`: Sends a message to all connected clients.
- Any other message: Sends a message to all connected clients.

To simulate a force quit, enter `$quit` during a chat session.

