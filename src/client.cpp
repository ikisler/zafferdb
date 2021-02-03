#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <cstring>
#include <iostream>
#include <limits>
#include <string>

#include "Parser.h"
#include "Tokenizer.h"

#define PORT "9987"
#define QUEUE_LENGTH 20
#define MAX_PACKET 1025

int main() {
  int yes = 1;

  struct addrinfo hints;
  struct addrinfo *serverInfo;
  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;

  int getAddressStatus = getaddrinfo("127.0.0.1", PORT, &hints, &serverInfo);
  if (getAddressStatus != 0) {
    std::cout << "ERROR: Cannot get address information" << std::endl;
    return 1;
  }

  int sock;

  std::cout << "ZafferDB" << std::endl;
  std::cout << "Created by Isabeau Kisler" << std::endl;
  std::cout << "January 2021" << std::endl;
  std::cout << std::endl;

  Tokenizer tokenizer;
  Parser parser;
  bool success;

  int clientSock;
  int receiveSuccess;
  char incomingPacket[MAX_PACKET];
  int incomingPacketLength;

  struct sockaddr_storage clientAddress;
  socklen_t addressSize;

  std::stringstream input;

  while (true) {
    std::cout << "zafferdb> ";

    std::string input;
    std::getline(std::cin, input, '\n');
    std::stringstream s;
    s << input;

    Tokenizer::Token token = tokenizer.tokenizeInput(s);
    Command command = parser.parse(token);

    switch (command) {
      case Command::exit:
        std::cout << std::endl << "Bye~" << std::endl;
        return 0;
      case Command::set:
      case Command::get:
      case Command::exists:
      case Command::remove:
        sock = socket(serverInfo->ai_family, serverInfo->ai_socktype,
                      serverInfo->ai_protocol);

        if (sock == -1) {
          std::cout << "ERROR: Cannot create socket" << std::endl;
          return 1;
        }

        if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) ==
            -1) {
          std::cout << "ERROR: Cannot reuse socket" << std::endl;
          return 1;
        }
        if (connect(sock, serverInfo->ai_addr, serverInfo->ai_addrlen) == -1) {
          std::cout << "Cannot connect to server" << std::endl;
          close(sock);
          return 1;
        }

        send(sock, input.c_str(), strlen(input.c_str()), 0);

        memset(incomingPacket, 0,
               sizeof(incomingPacket));  // clear out incomingPacket before
                                         // getting new data
        incomingPacketLength = recv(sock, incomingPacket, MAX_PACKET - 1, 0);
        close(sock);

        if (incomingPacketLength == -1) {
          return 1;
        }
        std::cout << incomingPacket << std::endl;
        break;
      case Command::invalid:
        std::cout << "Invalid command" << std::endl;
        break;
    }
  }

  freeaddrinfo(serverInfo);
  return 0;
}
