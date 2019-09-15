/* Client1 of server Misty */

#include <iostream>
#include <cstdio>
#include <unistd.h>
#include <sys/msg.h>
#include <cstring>

 struct message {
   long mtype;
   char cmd [200];
   char email [100];
   char address [100];
 }msg_clear = {0, '\0', '\0', '\0'};

 int main(int argc, char const *argv[]) {

   message msg;
   int msgid, req;
   key_t key;

   key = ftok ("Misty", 'X');
   msgid = msgget (key, 0400);

   while (1) {

     msg = msg_clear;

     std::cout << "\n\n\t\t Menu \n";
     std::cout << "\t 1. Execute a program or a command" << '\n';
     std::cout << "\t 2. Email a given file to a given address" << '\n';
     std::cout << "\t 3. Play a video" << '\n';
     std::cout << "\t 4. Display contents of a given file" << '\n';
     std::cout << "\t 5. Exit" << '\n';
     std::cout << "\n\t Enter the service request number : ";
     std::cin >> req;

     switch (req) {

       case 1 : std::cout << "\n\n\t Enter command : ";
                //getline (std::cin, msg.cmd);
                std::cin.ignore ();
                std::cin.getline (msg.cmd, 200);
                msg.mtype = req;
                break;

       case 2 : {std::cout << "\n\t Enter the mail address : ";
                std::cin.ignore ();
                //std::cin >> msg.email;
                std::cin.getline (msg.email, 100);
                //fgets (msg.email, 100, stdin);
                //std::cout << msg.email << '\n';
                //char temp[100], temp2 [100];
                //strcpy (temp, msg.email);
                //std::cout << temp << '\n';
                std::cout << "\n\t Enter the mail subject : ";
                //std::cin >> msg.cmd;
                //std::cin.ignore ();
                std::cin.getline (msg.cmd, 100);
                std::cout << "\n\t Enter the file address : ";
                //std::cin >> msg.address;
                //std::cin.ignore ();
                std::cin.getline (msg.address, 100);
                //std::cout << msg.address << '\n';
                //strcpy (temp2, msg.address);
                //std::cout << temp2 << '\n';
                msg.mtype = req;
                //strcpy (msg.address, temp2);
                //strcpy (msg.email, temp);
                //std::cout << msg.email << '\n';
                //std::cout << msg.address << '\n';
                //std::cout << msg.address << '\n';
                //std::cout << msg.email << '\n';
                //strcpy (temp, "");
                //strcpy (temp2, "");
                break;}

       case 3 : std::cout << "\n\n\t Enter the address of the video : ";
                // std::cin >> msg.address;
                std::cin.ignore ();
                std::cin.getline (msg.address, 100);
                msg.mtype = req;
                break;

       case 4 : std::cout << "\n\n\t Enter the address of file : ";
                //std::cin >> msg.address;
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

     /*std::cout << "\n\t Enter the message number : ";
     std::cin >> msg.mtype;
     std::cout << "\t Enter the message : ";
     std::cin >> msg.msg;*/

     msgsnd (msgid, &msg, sizeof (message), 0);

   }

   return 0;
 }