/************************************************************************************
 *                                                                                  *
 *  @ Ankit Dimri                                                                   *
 *  A IPC server client using message queue to service the req in priority          *
 *                                                                                  *                
 ************************************************************************************/

/* Server Misty */

#include <iostream>
#include <unistd.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <cstring>

 struct message {
   long mtype;
   char cmd [200];
   char email [100];
   char address [100];
 } msg_clear = {0, '\0', '\0', '\0'};

 void service1 (message&);
 void service2 (message&);
 void service3 (message&);
 void service4 (message&);

 int main(int argc, char const *argv[]) {

   message msg;
   msqid_ds buf;
   int msgid, reqs;
   key_t key;

   key = ftok ("Misty", 'X');
   msgid = msgget (key, 0600 | IPC_CREAT);

   //if (msgrcv (msgid, &msg, sizeof (message), 1, 0) == -1 )
   //  std::cout << "\nno message" << '\n';

   while (1) {

     /*if (msgrcv (msgid, &msg, sizeof (message), 1, 0) == -1 )
      std::cout << "\nno message" << '\n';
      std::cout << msg.cmd << '\n';*/

      sleep (60);  // sleep for 10 seconds

      msgctl (msgid, IPC_STAT, &buf);
      reqs = (int)(buf.msg_qnum);

      for (int i = 0; i < reqs; i++) {

        msgrcv (msgid, &msg, sizeof (message), -4, 0);

        switch (msg.mtype) {

          case 1 : if (!fork ())
                    service1 (msg);
                   break;
          case 2 : if (!fork ())
                    service2 (msg);
                   break;
          case 3 : if (!fork ())
                    service3 (msg);
                   break;
          case 4 : if (!fork ())
                    service4 (msg);
                   break;
          default : std::cout << "\n Invalid service requested" << '\n';

        }

        msg = msg_clear;

      }

   }

   /* msgrcv (msgid, &msg, 100, 0, 0);
   std::cout << "\n\t message type : " << msg.mtype;
   std::cout << "\n\t message : " << msg.msg << std::endl; */

   msgctl (msgid, IPC_RMID, NULL);

   return 0;
 }

 void service1 (message &msg) {

     system (msg.cmd);
     //const char* c = msg.cmd;
     //std::cout << "inside it" << '\n';
     //execl (c, NULL);
     //std::cout << "Inside it" << '\n';

 }

 void service2 (message &msg) {

     char comm [200] = "echo \"  PFA  \" | mutt -s ";
     //std::cout << msg.email << '\n';
     strcat (comm, msg.cmd);
     strcat (comm, " ");
     strcat (comm, msg.email);
     strcat (comm, " -a ");
     strcat (comm, msg.address);
     //std::cout << comm << '\n';
     //std::cout << msg.address << '\n';
     system (comm);
     //execv (comm, NULL);

 }

 void service3 (message &msg) {

   char *command, cmm [104]= "vlc ";
   strcat (cmm, msg.address);
   command = cmm;
   system (command);
   //execv (command, NULL);

 }

 void service4 (message &msg) {

   char *command, cmm [105]= "atom ";
   strcat (cmm, msg.address);
   command = cmm;
   system (command);
   //execv (command, NULL);

 }
