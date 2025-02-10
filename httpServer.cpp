/***************************************************************
  Student Name: Trevor Mee
  File Name: httpServer.cpp
  Date: 01/28/2025
  Project 1
  COP4635 - Systems & Networks 2

  @brief Simple HTTP server that uses TCP sockets to handle 
         GET requests
***************************************************************/

#include <stdio.h>          
#include <stdlib.h>         
#include <sys/socket.h>     
#include <sys/types.h>      
#include <netinet/in.h>    
#include <iostream>
#include <unistd.h>
#include <fstream>
#include <sstream>
#include <csignal>

const int PORT = 60001;

/*
    @brief handles client requests

    @param client_fd: file descriptor for the client

    @return N/A
*/
void handleClient(int client_fd)
{
    char buffer[4096] = {0};

    // read request from client
    ssize_t bytesRead = read(client_fd, buffer, sizeof(buffer));
    if(bytesRead < 0)
    {
        perror("Error reading from socket");
        return;
    }
    std::cout << "Received request: " << buffer << std::endl;

    // parse the http request
    std::istringstream request(buffer);
    std::string method, path, version;
    request >> method >> path >> version;
    std::cout << "Processing request: " << method << " " << path << " " << version << std::endl;
    
    std::string response;
    
    if(method == "GET")
    {
        std::ifstream file("." + path);
        std::cout << "Requested file path: " << path << std::endl;

        if (file) {

            std::ostringstream content;
            
            content << file.rdbuf();

            std::string contentType = "text/html"; 

            response = "HTTP/1.1 200 OK\r\nContent-Type: "+ contentType + "\r\n\r\n" + content.str();
            
        } else {
            std::string errorMsg = "404 Not Found";
            response = "HTTP/1.1 404 Not Found\r\nContent-Type: text/html\r\n\r\n" + errorMsg;
        }
    }
    else
    {
        // handle other methods
        std::cout << "Method not supported: " << method << std::endl;
        response = "HTTP/1.1 404 Not found\r\n\r\n";
    }

    // send response 
    std::cout << "Sending response: " << response << std::endl;
    write(client_fd, response.c_str(), response.size());
}

/*
    @brief handles graceful shutdown of the server

    @param signal: signal received

    @return N/A
*/
void signalHandler(int signal)
{
    std::cout << "\nReceived signal: " << signal << ", shutting server down" << std::endl;
    exit(signal);
}

/* @brief main function

    @param N/A

    @return 0 on success
*/
int main()
{
    // handle graceful shutdown (Ctrl+C)
    signal(SIGINT, signalHandler);
    
    int server_fd;
    
    // create the server socket
    if((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    std::cout << "Socket created successfully!" << std::endl;

    // define server address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // bind the socket
    if(bind(server_fd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    std::cout << "Server bound to port: " << PORT << std::endl;

    // listen for connections
    if(listen(server_fd, 5) < 0)
    {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }

    std::cout << "Server listening on port: " << PORT << std::endl;

    while(true)
    {
        int client_fd;

        // accept a connection
        if((client_fd = accept(server_fd, NULL, NULL)) < 0)
        {
            perror("accept failed");
            exit(EXIT_FAILURE);
        }
        std::cout << "Connection established with client" << std::endl;

        // handle client request
        handleClient(client_fd);

        // close the client socket
        std::cout << "Closing client connection" << std::endl;
        close(client_fd);
    }

    // close the server socket
    std::cout << "Server shutting down" << std::endl;
    close(server_fd);

    return 0;
}