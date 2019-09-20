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

   while (1) {

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

   msgctl (msgid, IPC_RMID, NULL);

   return 0;
 }

 void service1 (message &msg) {

     system (msg.cmd);

 }

 void service2 (message &msg) {

     char comm [200] = "echo \"  PFA  \" | mutt -s ";
     strcat (comm, msg.cmd);
     strcat (comm, " ");
     strcat (comm, msg.email);
     strcat (comm, " -a ");
     strcat (comm, msg.address);

     system (comm);


 }

 void service3 (message &msg) {

   char *command, cmm [104]= "vlc ";
   strcat (cmm, msg.address);
   command = cmm;
   system (command);

 }

 void service4 (message &msg) {

   char *command, cmm [105]= "atom ";
   strcat (cmm, msg.address);
   command = cmm;
   system (command);

 }
