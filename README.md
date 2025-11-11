# Internet Relay Chat (IRC) Server 💬

**A fully functional IRC server implementation in C++98 compliant with RFC 1459 specifications.**

[![C++98](https://img.shields.io/badge/C++-98-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B98)
[![RFC 1459](https://img.shields.io/badge/RFC-1459-green.svg)](https://tools.ietf.org/html/rfc1459)
[![42 School](https://img.shields.io/badge/42-School-000000.svg)](https://42.fr/)

## 🌟 Features

- ✅ **Multi-client Support**: Handle multiple simultaneous connections using `poll()`
- ✅ **Channel Management**: Create, join, and manage IRC channels
- ✅ **User Authentication**: Password-protected server access
- ✅ **Operator Commands**: Full channel operator functionality (kick, ban, topic, mode)
- ✅ **Private Messaging**: Direct user-to-user communication
- ✅ **RFC 1459 Compliant**: Standard IRC protocol implementation
- ✅ **Non-blocking I/O**: Efficient event-driven architecture
- ✅ **C++98 Standard**: No external dependencies, pure C++98

## 📋 Table of Contents

- [Quick Start](#-quick-start)
- [Architecture](#-architecture)
- [Supported Commands](#-supported-commands)
- [Usage](#-usage)
- [Project Structure](#-project-structure)
- [Technical Details](#-technical-details)

## 🚀 Quick Start

### Prerequisites

- **C++ Compiler**: g++ or clang++ with C++98 support
- **Make**: Build automation tool
- **IRC Client**: Any standard IRC client (irssi, WeeChat, HexChat, or netcat)

### Building the Server

```bash
# Clone the repository
git clone <repository-url>
cd Internet-Relay-Chat

# Compile the server
make

# The executable 'ircserv' will be created
```

### Running the Server

```bash
# Start the IRC server
./ircserv <port> <password>

# Example:
./ircserv 6667 mypassword
```

**Arguments:**
- `port`: Port number for incoming IRC connections (1024-65535 recommended)
- `password`: Server password required for client authentication

### Connecting with a Client

```bash
# Using netcat (simple test)
nc localhost 6667

# Using irssi
irssi
/connect localhost 6667 mypassword

# Using WeeChat
weechat
/server add local localhost/6667 -password=mypassword
/connect local
```

## 🏗️ Architecture

### Core Components

```
┌─────────────────────────────────────────────────────────┐
│                    IRC Server                           │
├─────────────────────────────────────────────────────────┤
│  SocketServer                                           │
│  ├─ Socket Management (poll)                           │
│  ├─ Connection Handling                                │
│  └─ Event Loop                                         │
├─────────────────────────────────────────────────────────┤
│  User Management                                        │
│  ├─ Authentication                                      │
│  ├─ Nickname Registration                              │
│  └─ User State Tracking                                │
├─────────────────────────────────────────────────────────┤
│  Channel Management                                     │
│  ├─ Channel Creation/Deletion                          │
│  ├─ User Permissions                                   │
│  ├─ Modes & Topics                                     │
│  └─ Operator Privileges                                │
├─────────────────────────────────────────────────────────┤
│  Command Parser                                         │
│  ├─ IRC Protocol Parsing                               │
│  ├─ Command Routing                                    │
│  └─ Response Generation                                │
└─────────────────────────────────────────────────────────┘
```

### Class Structure

- **`SocketServer`**: Main server class managing connections and event loop
- **`User`**: Represents connected clients with authentication state
- **`Channel`**: Manages IRC channels, members, operators, and modes
- **`Command`**: Parses and executes IRC protocol commands

## 💻 Supported Commands

### Connection Commands

| Command | Description | Usage |
|---------|-------------|-------|
| `PASS` | Authenticate with server password | `PASS <password>` |
| `NICK` | Set or change nickname | `NICK <nickname>` |
| `USER` | Specify user information | `USER <username> <hostname> <servername> <realname>` |
| `QUIT` | Disconnect from server | `QUIT [<message>]` |

### Channel Commands

| Command | Description | Usage |
|---------|-------------|-------|
| `JOIN` | Join a channel | `JOIN <channel> [<key>]` |
| `PART` | Leave a channel | `PART <channel> [<message>]` |
| `TOPIC` | View or set channel topic | `TOPIC <channel> [<topic>]` |
| `MODE` | Set channel or user modes | `MODE <channel> <modes> [<parameters>]` |
| `KICK` | Remove user from channel (op only) | `KICK <channel> <user> [<reason>]` |
| `INVITE` | Invite user to channel (op only) | `INVITE <nickname> <channel>` |

### Communication Commands

| Command | Description | Usage |
|---------|-------------|-------|
| `PRIVMSG` | Send message to user or channel | `PRIVMSG <target> :<message>` |
| `PING` | Server ping | `PING <server>` |
| `PONG` | Server pong response | `PONG <server>` |
| `WHOIS` | Get user information | `WHOIS <nickname>` |

### Channel Modes

| Mode | Description |
|------|-------------|
| `+i` | Invite-only channel |
| `+t` | Topic settable by operators only |
| `+k` | Channel password/key |
| `+o` | Grant/revoke operator privileges |
| `+l` | Set user limit |

## 🎯 Usage

### Example Session

```bash
# Terminal 1: Start server
./ircserv 6667 secret123

# Terminal 2: Connect first client
nc localhost 6667
PASS secret123
NICK alice
USER alice 0 * :Alice Wonderland
JOIN #general
PRIVMSG #general :Hello everyone!
TOPIC #general :Welcome to our IRC server

# Terminal 3: Connect second client
nc localhost 6667
PASS secret123
NICK bob
USER bob 0 * :Bob Builder
JOIN #general
PRIVMSG #general :Hi Alice!
PRIVMSG alice :Private message to Alice
```

### Testing with IRC Clients

#### irssi
```bash
irssi
/connect localhost 6667 secret123
/nick myname
/join #test
/msg #test Hello World!
```

#### WeeChat
```bash
weechat
/server add myserver localhost/6667 -password=secret123
/connect myserver
/join #test
```

#### HexChat
1. Network List → Add → Server: localhost/6667
2. Edit → Password: secret123
3. Connect
4. Join #test

## 📁 Project Structure

```
Internet-Relay-Chat/
├── main.cpp                    # Entry point
├── SocketServer.cpp/.hpp       # Core server implementation
├── User.cpp/.hpp               # User management
├── Channel.cpp/.hpp            # Channel management
├── Command.cpp/.hpp            # Command parsing
├── Server_comments.hpp         # IRC reply codes
├── Makefile                    # Build configuration
├── commands/                   # IRC command implementations
│   ├── Pass.cpp               # Password authentication
│   ├── Nick.cpp               # Nickname handling
│   ├── User.cpp               # User registration
│   ├── Join.cpp               # Channel joining
│   ├── Part.cpp               # Channel leaving
│   ├── PrivMsg.cpp            # Private messaging
│   ├── Kick.cpp               # Kick users
│   ├── Invite.cpp             # Invite users
│   ├── Topic.cpp              # Topic management
│   ├── Mode.cpp               # Mode management
│   ├── Quit.cpp               # Client disconnection
│   ├── Ping.cpp/Pong.cpp      # Keep-alive
│   ├── Whois.cpp              # User information
│   └── Cap.cpp                # Capability negotiation
├── Channel_mode_utils.cpp     # Channel mode utilities
├── Channel_op_utils.cpp       # Operator utilities
├── Channel_user_utils.cpp     # User management utilities
└── README.md                  # This file
```

## 🔧 Technical Details

### Key Implementation Features

#### Non-Blocking I/O with poll()
```cpp
// Efficient event-driven architecture
std::vector<pollfd> fds;
poll(fds.data(), fds.size(), -1);
// Handle events without blocking
```

#### C++98 Compliance
- No C++11/14/17 features
- STL containers (vector, map, string)
- Standard library only
- No Boost or external dependencies

#### Memory Management
- Proper resource cleanup
- No memory leaks
- Exception-safe code

#### Protocol Compliance
- RFC 1459 standard
- Numeric reply codes
- Proper message formatting
- Error handling

### Build Commands

```bash
make          # Compile the project
make clean    # Remove object files
make fclean   # Remove object files and executable
make re       # Rebuild from scratch
```

### Compiler Flags

```makefile
CXX = c++
FLAGS = -std=c++98 -Wall -Werror -Wextra -g3
```

## 🧪 Testing

### Manual Testing

```bash
# Test basic connection
echo -e "PASS secret123\nNICK test\nUSER test 0 * :Test User\nQUIT" | nc localhost 6667

# Test channel operations
echo -e "PASS secret123\nNICK test\nUSER test 0 * :Test\nJOIN #test\nPRIVMSG #test :Hello\nQUIT" | nc localhost 6667
```

### Common Test Scenarios

1. **Authentication**: Wrong password, no password
2. **Nickname**: Duplicate nicknames, invalid characters
3. **Channels**: Join, part, multiple channels
4. **Messages**: Private messages, channel messages
5. **Operators**: Kick, ban, mode changes
6. **Edge Cases**: Buffer overflow, malformed commands

## 📚 Resources & References

- [RFC 1459 - Internet Relay Chat Protocol](https://tools.ietf.org/html/rfc1459)
- [RFC 2812 - Internet Relay Chat: Client Protocol](https://tools.ietf.org/html/rfc2812)
- [IRC Numeric Replies](https://www.alien.net.au/irc/irc2numerics.html)
- [Modern IRC Client Protocol](https://modern.ircdocs.horse/)

## 💡 Key Learnings

- **Network Programming**: Socket programming, poll(), non-blocking I/O
- **Protocol Implementation**: Parsing and implementing RFC specifications
- **C++98 Mastery**: Working with older standards and constraints
- **Event-Driven Architecture**: Managing multiple connections efficiently
- **State Management**: Tracking user and channel states
- **Error Handling**: Robust error checking and recovery

## 🎓 42 School Project

This project is part of the 42 School curriculum, focusing on:
- Advanced C++ programming
- Network programming fundamentals
- Protocol implementation
- Multi-client server architecture
- Real-time communication systems

## 🤝 Credits

**Author**: Vlad Polojie (vpolojie)  
**School**: 42 School  
**Project**: ft_irc  
**Year**: 2024

## 📝 License

This project is part of the 42 School curriculum and follows the school's academic policies.

---

**Note**: This IRC server is designed for educational purposes and may not include all features of a production-ready IRC server. It demonstrates core concepts of network programming and protocol implementation in C++98.