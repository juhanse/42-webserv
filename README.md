*This project has been created as part of the 42 curriculum by ByteBusters.*

# Description

This project is a **C++ Web Server** implementation that simulates core functionalities of servers like Nginx.  
It handles HTTP requests, serves static content, manages multiple server blocks, and supports basic CGI scripts.  

Key features:

- Multi-server support on different ports  
- Multiple locations per server  
- Client body size limits  
- Automatic error pages (404, 500)  
- CGI support for `.py` and `.sh` scripts  
- Robust configuration parsing with error detection

# Instructions
Run the server by specifying a configuration file:
	
./webserv srcs/config.conf

## Compilation
The project uses a Makefile. The makefile contains the following flags, Werror Wextra Wall -std=c++98.
Compile with:

make

# References
- https://nginx.org/en/docs/

## AI was used to:
	Suggest improvements to the parser and tokenizer
	Generate edge-case configurations for testing

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