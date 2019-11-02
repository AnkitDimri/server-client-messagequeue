/************************************************************************************
 *                                                                                  *
 *  @author: Ankit Dimri                                                                   *
 *  A IPC server client using message queue to service the req in priority          *
 *                                                                                  *
 ************************************************************************************/

/* Server Misty */

#include <iostream>
#include <unistd.h>
#include <sys/msg.h>  // for message queues
#include <sys/types.h>
#include <cstring>

 // Message queue structure
 struct message {

   /* Priority based on message type */
   long mtype;  // message type
   char cmd [200];
   char email [100];
   char address [100];

 } msg_clear = {0, '\0', '\0', '\0'}; // clear buffer

 /* services serviced by the server Misty */
 void service1 (message&);
 void service2 (message&);
 void service3 (message&);
 void service4 (message&);

 int main(int argc, char const *argv[]) {

   message msg;
   msqid_ds buf;
   int msgid, reqs;
   key_t key;  // messgae queue key

   key = ftok ("Misty", 'X');  // Generate key for message queue
   /*
    * use same parameters for key generation to send messages in queue to be
    * serviced by the Server
    */
   msgid = msgget (key, 0600 | IPC_CREAT); // create message queue

   /* Infinite server loop */
   while (1) {

      sleep (60);  // sleep for 10 seconds

      /* get queue status */
      msgctl (msgid, IPC_STAT, &buf); // message control
      reqs = (int)(buf.msg_qnum); // number of messages in queue currently

      for (int i = 0; i < reqs; i++) {

        /* Service req according to priority */
        msgrcv (msgid, &msg, sizeof (message), -4, 0); // -4 is a flag

        /* switch to req */
        switch (msg.mtype) {
        /* Parallel processing */
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

        msg = msg_clear; // clear message buffer

      }

   }

//  msgctl (msgid, IPC_RMID, NULL);

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
