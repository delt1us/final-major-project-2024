/*
 * @Author: Armin Raad <armin3600z@gmail.com>
 * @Date: 2024-03-08 08:38:19
 * @Last Modified by: Armin Raad <armin3600z@gmail.com>
 * @Last Modified time: 2024-03-08 08:38:49
 */

#include <WS2tcpip.h>
#include <WinSock2.h>
#include <cstring>
#include <iostream>
#include <minwinbase.h>
#include <minwindef.h>
#include "defs.h"

int TempSocketFunction() {
  std::cout << "Starting client...\n";

  WSADATA wsaData;
  int result;
  // Initialise WinSock
  result = WSAStartup(MAKEWORD(2, 2), &wsaData);
  if (result != 0) {
    std::cout << "WSAStartup failed with error: " << result << "\n";
    return 1;
  }

  struct addrinfo *addressInfo = NULL, *ptr = NULL, hints;
  ZeroMemory(&hints, sizeof(hints));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_protocol = IPPROTO_TCP;

  result = getaddrinfo(SERVER_IP, SERVER_PORT, &hints, &addressInfo);
  if (result != 0) {
    std::cout << "getaddrinfo failed with error: " << result << "\n";
    WSACleanup();
  }

  // Make empty socket object
  SOCKET connectSocket = INVALID_SOCKET;

  // Attempt to connect to the first address returned by call to getaddrinfo
  ptr = addressInfo;

  // Create a socket for connecting to the server
  connectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
  if (connectSocket == INVALID_SOCKET) {
    std::cout << "Error at socket(): " << WSAGetLastError() << "\n";
    freeaddrinfo(addressInfo);
    WSACleanup();
    return 1;
  }

  // Connect to the server
  result = connect(connectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
  freeaddrinfo(addressInfo);
  if (result == SOCKET_ERROR) {
    closesocket(connectSocket);
    std::cout << "Unable to connect to server\n";
    WSACleanup();
    return 1;
  }

  int receiveBufferLength = BUFFER_SIZE;
  char receiveBuffer[BUFFER_SIZE];
  const char *sendBuffer = "this is a test";

  // Send initial buffer
  result = send(connectSocket, sendBuffer, (int)strlen(sendBuffer), 0);
  if (result == SOCKET_ERROR) {
    std::cout << "Send failed with error: " << WSAGetLastError() << "\n";
    closesocket(connectSocket);
    WSACleanup();
    return 1;
  }
  std::cout << "Bytes sent: " << result << "\n";

  // Shut down the connection since no more data will be sent
  // connectSocket can still be used to receive data
  result = shutdown(connectSocket, SD_SEND);
  if (result == SOCKET_ERROR) {
    std::cout << "Shutdown failed with error: " << WSAGetLastError() << "\n";
    closesocket(connectSocket);
    WSACleanup();
    return 1;
  }

  // Receive data until the server closes the connection
  do {
    result = recv(connectSocket, receiveBuffer, receiveBufferLength, 0);
    if (result > 0)
      std::cout << "Bytes received: " << result << "\n";
    else if (result == 0)
      std::cout << "Connection closed\n";
    else
      std::cout << "recv failed with error: " << WSAGetLastError() << "\n";
  } while (result > 0);

  closesocket(connectSocket);
  WSACleanup();
  return 0;
}
