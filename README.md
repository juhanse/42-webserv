*This project has been created as part of the 42 curriculum by ade-woel, jdebrull, juhanse.*

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

Check the current connections:

`ss -tna | grep 8080` or `lsof -i:8080`

Go to the default URL `http://localhost:8080`

> You can edit the `srcs/config.conf` file to change the server configuration

## Usage
1. POST Method :
`curl -X POST -H "Content-Type: plain/text" --data "utilisateur=12345" localhost:8080`

2. DELETE Method :
`curl -X DELETE http://localhost:8080/uploads/background.png`

3. GET Method with CGI :
`curl http://localhost:8080/cgi-bin/bonus.sh`

4. POST Method with CGI :
`curl -X POST -d "user=juhanse" http://localhost:8080/cgi-bin/post.py`


# 📚 Resources
- https://nginx.org/en/docs/
- https://fr.wikipedia.org/wiki/FastCGI
- https://m4nnb3ll.medium.com/webserv-building-a-non-blocking-web-server-in-c-98-a-42-project-04c7365e4ec7

### AI was used to:
- Suggest improvements to the parser and tokenizer
- Generate edge-case configurations for testing
- Explain how to implement a multi-CGI setup
- Explain the basics of how HTTP works using the GET, POST, and DELETE methods
