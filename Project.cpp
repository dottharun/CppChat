#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <winsock2.h>
#include <ws2tcpip.h>
#include "OutputValues.h"
#include "Client.h"
#include "Server.h"
#include <limits>

#pragma comment(lib, "Ws2_32.lib")

#define MAX_CLIENTS 3
//IP test: 127.0.0.1
//Port test: 5000
//Wireshark filter: ip.addr == 127.0.0.1 or tcp.port == 5000 or udp.port == 5000 ip.src = 127.0
int main()
{
    std::string input;
    std::cout << "Start as [s]erver or [c]lient? ";
    std::cin >> input;

    if (input == "s") //Server loop
    {
        // Start server
        Server server(MAX_CLIENTS, "5000");
        try
        {
            server.run();
        }
        catch (const std::exception& ex)
        {
            std::cerr << "Error: " << ex.what() << std::endl;
            return OutputMessageType::STARTUP_ERROR;
        }
    }
    else if (input == "c") //Client loop
    {
        // Initialize Client
        Client client;
        try
        {
            // Connect to server
            client.listenForUdpBroadcast();
            // Register username
            std::string username;
            std::cout << "Enter username: ";
            std::cin >> username;
            client.registerUser(username);
        }
        catch (const std::exception& ex)
        {
            std::cerr << "Error: " << ex.what() << std::endl;
            return OutputMessageType::CONNECT_ERROR;
        }

        // Main loop
        bool quitFlag = false;
        // Start a thread to listen for incoming messages from the server
        std::thread serverListener([&]()
            {
                // Check for incoming messages from the server
                while (client.isConnected() && !quitFlag)
                {
                    try
                    {
                        std::string message = client.receiveMessage(quitFlag);
                        if (message != "")
                            std::cout << message;
                    }
                    catch (const std::exception& ex)
                    {
                        std::cerr << "Error: " << ex.what() << std::endl;
                        break;
                    }
                }
                exit(0);
                //return 0;
            });

        // Start a thread to listen for user input
        std::thread userInput([&]()
            {
                while (client.isConnected() && !quitFlag)
                {
                    std::string input;
                    std::cout << "Enter command or message: ";
                    std::getline(std::cin >> std::ws, input);
                    if (quitFlag)
                        break;

                    if (input == "$help")
                    {
                        std::string helpMessage = "Available commands:\n\n";
                        helpMessage += "$register username: Registers a new user with the specified username. Returns SV_SUCCESS if successful, or SV_FULL if the server is at capacity.\n\n";
                        helpMessage += "$getlist: Returns a list of connected users.\n\n";
                        helpMessage += "$getlog: Returns the chat log.\n\n";
                        helpMessage += "$exit: Disconnects the user from the server.\n\n";
                        helpMessage += "$chat message: Sends a message to all connected clients.\n\n";
                        helpMessage += "$help: Displays this help message.\n\n";
                        helpMessage += "Enter command or message: ";
                        std::cout << helpMessage;
                        std::getline(std::cin >> std::ws, input);
                    }
                    if (input == "$quit") //Function to simulate forced quit, not to confuse with $exit
                    {
                        quitFlag = true;
                        std::cout << "You have quitted the chat\n";
                        break;
                    }
                    else if (input.find("$chat") == 0)
                    {
                        // Send chat message to server
                        try
                        {
                            client.sendMessage(input.substr(6));
                        }
                        catch (const std::exception& ex)
                        {
                            std::cerr << "Error: " << ex.what() << std::endl;
                        }
                    }
                    else
                    {
                        // Send other command to server
                        try
                        {
                            client.executeCommand(input);
                        }
                        catch (const std::exception& ex)
                        {
                            std::cerr << "Error: " << ex.what() << std::endl;
                        }
                    }
                }
            });
        // Wait for both threads to finish
        serverListener.join();
        userInput.join();

        // Close connection
        client.closeConnection();

    }
    else
    {
        std::cout << "Invalid input." << std::endl;
        return OutputMessageType::PARAMETER_ERROR;
    }

    return OutputMessageType::SUCCESS;

}

