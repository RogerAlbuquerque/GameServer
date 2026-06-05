// #include <iostream>
// // #include <cstring>
// #include <arpa/inet.h>
// #include <unistd.h>

// int main() {
//     int sock = socket(AF_INET, SOCK_DGRAM, 0);

//     sockaddr_in serverAddr{};
    
//     serverAddr.sin_family = AF_INET;
//     serverAddr.sin_port = htons(7777);
//     serverAddr.sin_addr.s_addr = INADDR_ANY;

//     bind(sock, (sockaddr*)&serverAddr, sizeof(serverAddr));

//     std::cout << "Servidor UDP rodando na porta 7777...\n";

//     char buffer[1024];
//     sockaddr_in clientAddr{};
//     socklen_t clientSize = sizeof(clientAddr);

//     while (true) {
//         int bytes = recvfrom(sock, buffer, sizeof(buffer), 0,
//                              (sockaddr*)&clientAddr, &clientSize);

//         buffer[bytes] = '\0';

//         std::cout << "Recebido: " << buffer << std::endl;

//         sendto(sock, buffer, bytes, 0,
//                (sockaddr*)&clientAddr, clientSize);
//     }

//     close(sock);
// }