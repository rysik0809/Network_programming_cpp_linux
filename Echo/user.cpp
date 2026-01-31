#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

int main(){
    // Создаем сокет
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(clientSocket < 0){
        std::cerr<<"Not create socket";
    }

    // Настраиваем адресс СЕРВЕРА к которому подключаемся
    struct sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8000); // порт 8000
    inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr); // IP сурвер (localhost)

    // Подключаемся к серверу
    int Connect = connect(clientSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));
    if(Connect < 0){
        std::cerr<<"Not connect server"<<std::endl;
        return 1;
    }

    std::cout<<"Подключились к серверу!"<<std::endl;

    // Получаем сообщение от сервера
    char buff[1024];
    ssize_t bytes_received = recv(clientSocket, buff, sizeof(buff) - 1, 0);
    
    if(bytes_received > 0){
        buff[bytes_received] = '\0'; // Добавляем завершающий ноль для страницы
        std::cout<<"Получили от сервера: "<<buff<<std::endl;
    }


    // Закрываем соединение
    close(clientSocket);

    return 0;
}