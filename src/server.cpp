#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

#include <cstring>
#include <iostream>
#include <limits>
#include <string>

#include "Database.h"
#include "Parser.h"
#include "Tokenizer.h"

#define PORT "9987"
#define QUEUE_LENGTH 20
#define MAX_PACKET 1025

std::string getStatusOutput(bool success) {
  return (success ? "Success!" : "Failure");
}

int main() {
  int yes = 1;

  struct addrinfo hints;
  struct addrinfo *serverInfo;
  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;

  int getAddressStatus = getaddrinfo(NULL, PORT, &hints, &serverInfo);
  if (getAddressStatus != 0) {
    std::cout << "ERROR: Cannot get address information" << std::endl;
    return 1;
  }

  int sock;
  sock = socket(serverInfo->ai_family, serverInfo->ai_socktype,
                serverInfo->ai_protocol);

  if (sock == -1) {
    std::cout << "ERROR: Cannot create socket" << std::endl;
    return 1;
  }

  if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1) {
    std::cout << "ERROR: Cannot reuse socket" << std::endl;
    return 1;
  }

  if (bind(sock, serverInfo->ai_addr, serverInfo->ai_addrlen) != 0) {
    std::cout << "ERROR: Cannot bind to port" << std::endl;
    return 1;
  }

  freeaddrinfo(serverInfo);

  if (listen(sock, QUEUE_LENGTH) == -1) {
    std::cout << "ERROR: Cannot listen to port" << std::endl;
    return 1;
  }

  Database db;

  Tokenizer tokenizer;
  Parser parser;
  bool success;
  std::string message;

  int clientSock;
  int receiveSuccess;
  char incomingPacket[MAX_PACKET];

  struct sockaddr_storage clientAddress;
  socklen_t addressSize;

  const char null_data(0);

  while (true) {
    clientSock = accept(sock, (struct sockaddr *)&clientAddress, &addressSize);

    if (clientSock == -1) {
      std::cout << "ERROR: Could not accept connection" << std::endl;
      return 1;
    }

    receiveSuccess = recv(clientSock, incomingPacket, MAX_PACKET - 1, 0);

    if (receiveSuccess == 0 || receiveSuccess == -1) {
      continue;  // the client has either closed the connection or something
                 // else has gone wrong
    }

    std::stringstream input(incomingPacket);
    Tokenizer::Token token = tokenizer.tokenizeInput(input);
    Command command = parser.parse(token);

    switch (command) {
      case Command::exit:
        std::cout << std::endl << "Bye~" << std::endl;
        return 0;
      case Command::set:
        success = db.setValue(token.key, token.value);
        message = getStatusOutput(success);
        send(clientSock, message.c_str(), strlen(message.c_str()), 0);
        break;
      case Command::get:
        if (db.exists(token.key)) {
          message = db.getValue(token.key);
        } else {
          message = "ERROR: Key does not exist";
        }

        if (message == "") {
          send(clientSock, &null_data, 1, 0);
        } else {
          send(clientSock, message.c_str(), strlen(message.c_str()), 0);
        }
        break;
      case Command::exists:
        success = db.exists(token.key);
        message = getStatusOutput(success);
        send(clientSock, message.c_str(), strlen(message.c_str()), 0);
        break;
      case Command::remove:
        success = db.deleteValue(token.key);
        message = getStatusOutput(success);
        send(clientSock, message.c_str(), strlen(message.c_str()), 0);
        break;
      case Command::invalid:
        std::cout << "Invalid command" << std::endl;
        break;
    }
  }

  return 0;
}
