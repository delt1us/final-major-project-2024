/*
 * @Author: Armin Raad <armin3600z@gmail.com>
 * @Date: 2024-03-05 06:08:49
 * @Last Modified by: Armin Raad <armin3600z@gmail.com>
 * @Last Modified time: 2024-03-07 06:47:49
 */

#include "defs.h"
#include <WinSock2.h>
#include <iostream>
#include <minwinbase.h>
#include <minwindef.h>
#include <WS2tcpip.h>

int main() {
  std::cout << "Starting server...\n";
  // From https://learn.microsoft.com/en-us/windows/win32/api/winsock/nf-winsock-wsastartup
  WSAData wsaData;
  int result;

  // Use MAKEWORD macro declared in Windef.h
  result = WSAStartup(MAKEWORD(2, 2), &wsaData);
  if (result != 0) {
    std::cout << "WSAStartup failed with error code: " << result << "\n";
    return 1;
  }

  struct addrinfo *addressInfo = NULL, *ptr = NULL, hints;
  ZeroMemory(&hints, sizeof(hints));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_protocol = IPPROTO_TCP;
  hints.ai_flags = AI_PASSIVE;

  // Resolve local address and port to be used by the server
  result = getaddrinfo(NULL, SERVER_PORT, &hints, &addressInfo);
  if (result != 0) {
    std::cout << "getaddreinfo failed with error code: " << result << "\n";
    WSACleanup();
    return 1;
  }

  // Make socket
  int listenSocket = INVALID_SOCKET;
  listenSocket = socket(addressInfo->ai_family, addressInfo->ai_socktype, addressInfo->ai_protocol);

  // Check if socket is valid
  if (listenSocket == INVALID_SOCKET) {
    std::cout << "Created socket invalid, error: " << WSAGetLastError() << "\n";
    freeaddrinfo(addressInfo);
    WSACleanup();
    return 1;
  }

  // Bind socket
  result = bind(listenSocket, addressInfo->ai_addr, (int)addressInfo->ai_addrlen);
  freeaddrinfo(addressInfo);
  if (result == SOCKET_ERROR) {
    std::cout << "Bind failed with error: " << WSAGetLastError() << "\n";
    closesocket(listenSocket);
    WSACleanup();
    return 1;
  }

  if (listen(listenSocket, SOMAXCONN) == SOCKET_ERROR) {
    std::cout << "Listen failed with error: " << WSAGetLastError() << "\n";
    closesocket(listenSocket);
    WSACleanup();
    return 1;
  }

  // Accept a single client socket
  SOCKET clientSocket = INVALID_SOCKET;
  clientSocket = accept(listenSocket, NULL, NULL);
  if (clientSocket == INVALID_SOCKET) {
    std::cout << "Accept failed with error: " << WSAGetLastError() << "\n";
    closesocket(listenSocket);
    WSACleanup();
    return 1;
  }

  char receiveBuffer[BUFFER_SIZE];
  int sendResult;
  int receiveBufferLength = BUFFER_SIZE;
  do {
    result = recv(clientSocket, receiveBuffer, receiveBufferLength, 0);
    if (result > 0) {
      std::cout << "Bytes received: " << result << "\n";

      // Echo buffer back to sender
      sendResult = send(clientSocket, receiveBuffer, result, 0);
      if (sendResult == SOCKET_ERROR) {
        std::cout << "Send failed with error: " << WSAGetLastError() << "\n";
        closesocket(clientSocket);
        WSACleanup();
        return 1;
      }
      std::cout << "Bytes sent: " << sendResult << "\n";
    } else if (result == 0) {
      std::cout << "Connection closing...\n";
    } else {
      std::cout << "Receive failed with error: " << WSAGetLastError() << "\n";
      closesocket(clientSocket);
      WSACleanup();
      return 1;
    }
  } while (result > 0);

  // Disconnect and shut down the socket
  // https://learn.microsoft.com/en-us/windows/win32/winsock/disconnecting-the-server
  result = shutdown(clientSocket, SD_SEND);
  if (result == SOCKET_ERROR) {
    std::cout << "Shutdown failed with error: " << WSAGetLastError();
    closesocket(clientSocket);
    WSACleanup();
    return 1;
  }

  closesocket(clientSocket);
  WSACleanup();
  return 0;
}
