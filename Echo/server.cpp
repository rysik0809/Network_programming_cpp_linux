#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

int main(){
    // Создаем сокет сервера
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(serverSocket < 0){
        std::cerr<<"Not create socket!"<<std::endl;
        return 1;
    }

    // Настройки адреса сервера
    struct sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET; // Используем IPv4
    server_addr.sin_port = htons(8000); // Порт 8000
    server_addr.sin_addr.s_addr = INADDR_ANY; // Принимаем соединение отовсюду

    // Привязываем сокет к адресу
    int Bind = bind(serverSocket, (sockaddr*)&server_addr, sizeof(server_addr));
    if(Bind < 0){
        std::cerr<<"Not bind socket!"<<std::endl;
        return 1;
    }

    // Начинаем слушать (ждать клиентов)
    int Listen = listen(serverSocket, 5); // максимальное число клиентов - 5
    if(Listen < 0){
        std::cerr<<"Not start listen"<<std::endl;
        return 1;
    }

    std::cout<<"Сервер запущен на порту 8000. Ожидание подключений..."<<std::endl;

    // Принимаем подключение
    struct sockaddr_in client_addr{};
    socklen_t client_size = sizeof(client_addr);
    int clientSocket = accept(serverSocket, (sockaddr*)&client_addr, &client_size);

    std::cout<<"Клиент подключился!"<<std::endl;

    // Отправляем сообщение
    const char* message = "Hello user!";
    send(clientSocket, message, strlen(message), 0);

    // Закрываем соединение
    close(clientSocket);
    close(serverSocket);

    return 0;
}