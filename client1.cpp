/************************************************************************************
 *                                                                                  *
 *  @ Ankit Dimri                                                                   *
 *  A IPC client which sends request using message queue to service the req in      *
 *  priority                                                                        *
 *                                                                                  *
 ************************************************************************************/

/* Client1 of server Misty */

#include <iostream>
#include <cstdio>
#include <unistd.h>
#include <sys/msg.h>  // for message queues
#include <cstring>

 // message queue structure
 struct message {

   /* priority based on message type */
   long mtype; // Message type
   char cmd [200];
   char email [100];
   char address [100];

 } msg_clear = {0, '\0', '\0', '\0'};  // clear the message buffer

 int main(int argc, char const *argv[]) {

   message msg; // message
   int msgid, req;
   key_t key;  // message queue creation key

   key = ftok ("Misty", 'X');  // Genrate the key using same parmeters as in server
   msgid = msgget (key, 0400); // get the messagequeue ID and set permissions

   /* Infinite server loop */
   while (1) {

     msg = msg_clear; // clear message buffer

     /* Menu Driven; to choose the tyoe of request to the server */
     /* Priorities are the menu number and priority sequence is in decreasing */
     std::cout << "\n\n\t\t Menu \n";
     std::cout << "\t 1. Execute a program or a command" << '\n';
     std::cout << "\t 2. Email a given file to a given address" << '\n';
     std::cout << "\t 3. Play a video" << '\n';
     std::cout << "\t 4. Display contents of a given file" << '\n';
     std::cout << "\t 5. Exit" << '\n';
     std::cout << "\n\t Enter the service request number : ";
     std::cin >> req;

     /* switch to req chosen */
     switch (req) {

       case 1 : std::cout << "\n\n\t Enter command : ";
                std::cin.ignore (); // pause
                std::cin.getline (msg.cmd, 200);
                msg.mtype = req;
                break;

       case 2 : {std::cout << "\n\t Enter the mail address : ";
                std::cin.ignore ();
                std::cin.getline (msg.email, 100);
                std::cout << "\n\t Enter the mail subject : ";
                std::cin.getline (msg.cmd, 100);
                std::cout << "\n\t Enter the file address : ";
                std::cin.getline (msg.address, 100);
                msg.mtype = req;
                break;}

       case 3 : std::cout << "\n\n\t Enter the address of the video : ";
                std::cin.ignore (); // Pause
                std::cin.getline (msg.address, 100);
                msg.mtype = req;
                break;

       case 4 : std::cout << "\n\n\t Enter the address of file : ";
                std::cin.ignore ();
                std::cin.getline (msg.address, 100);
                msg.mtype = req;
                break;

       case 5 : { char ans = 'y';
                  std::cout << "\n\t Do you really wanna exit? [Y/n] ";
                  std::cin >> ans;
                  if (ans == 'y' || ans == 'Y')
                    exit (0);
                  break;
                }

       default : std::cout << "\n\n\t Invalid service request !!!";

     }

     /* send message */
     msgsnd (msgid, &msg, sizeof (message), 0);

   }

 }
