*This project has been created as part of the 42 curriculum by ByteBusters.*

# 🤖 Description

This project is a **C++ Web Server** implementation that simulates core functionalities of servers like Nginx.  
It handles HTTP requests, serves static content, manages multiple server blocks, and supports basic CGI scripts.  

### Key features:

- Multi-server support on different ports  
- Multiple locations per server  
- Client body size limits  
- Automatic error pages
- CGI support for all scripts
- Robust configuration parsing with error detection

### Bonus:
- Support cookies and session management (provide simple examples)
- Handle multiple CGI types



# 🧰 Instructions
Compile with:

`make`


Run the server by specifying a configuration file:

`./webserv srcs/config.conf`

Go to the default URL `http://localhost:8080`

> You can edit the `srcs/config.conf` file to change the server configuration


## Project structure
	webserv_git/
	├── srcs/
	│	├── main.cpp
	│	├── Webserver.cpp / Webserver.hpp / Webserver_utils.cpp
	│	├── Client.cpp / Client.hpp
	│	├── config/
	│	│	├── ServerConfig.cpp / ServerConfig.hpp
	│	│	└── LocationConfig.cpp / LocationConfig.hpp
	│	├── http/
	│	│	├── HttpRequest.cpp / HttpRequest.hpp
	│	│	├── HttpResponse.cpp / HttpResponse.hpp
	│	│	└── ResponseGenerator.cpp / ResponseGenerator.hpp
	│	├── parse/
	│	│	├── ConfigParser.cpp / ConfigParser.hpp
	│	│	├── ParseListen.cpp / ParseListen.hpp
	│	│	├── ParseLocation.cpp / ParseLocation.hpp
	│	│	├── ParseMaxSize.cpp / ParseMaxSize.hpp
	│	│	├── ParseRoot.cpp / ParseRoot.hpp
	│	│	├── ParseServerName.cpp / ParseServerName.hpp
	│	│	├── ParseErrorPage.cpp / ParseErrorPage.hpp
	│	│	└── ParseIndex.cpp / ParseIndex.hpp
	│	├── session/
	│	│	└── SessionManager.cpp / SessionManager.hpp
	│	└── utils/
	│		 └── utils.cpp / utils.hpp / debugPrint.cpp / debugPrint.hpp
	├── srcs/www/
	│	├── 404.html
	│	├── index.html
	│	├── uploads/
	│	└── cgi-bin/
	├── objs/  (compiled objects)
	├── Makefile
	└── README.md


# 📚 References
- https://nginx.org/en/docs/
- https://fr.wikipedia.org/wiki/FastCGI
- https://m4nnb3ll.medium.com/webserv-building-a-non-blocking-web-server-in-c-98-a-42-project-04c7365e4ec7

### AI was used to:
- Suggest improvements to the parser and tokenizer
- Generate edge-case configurations for testing
- Explain how to implement a multi-CGI setup
- Explain the basics of how HTTP works using the GET, POST, and DELETE methods
