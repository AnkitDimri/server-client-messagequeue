
#include <iostream>
#include <unistd.h>

 int min (int*, int);
 int min_of_4 (int, int, int, int);

 int main () {

   //std::vector <int> v;
   int n, val, fp, fc1, fc2, p1 [2], p2 [2], p3 [2], p4 [2], arr [100];
   int min_q, min1, min2, min3, min4, minimum;
   /* create pipes */
   pipe (p1);
   pipe (p2);
   pipe (p3);
   pipe (p4);

   /* Enter the number of elements to be compared */
   std::cin >> n;

   /* Enter the elements */
   for (int i = 0; i < n; i++) {
     std::cin >> arr [i];
     //v.push_back (val);
   }

   fp = fork ();

   if (!fp) {

     fc1 = fork ();
     fc2 = fork ();

     if (fc1 > 0 && fc2 > 0) {

       close (1);
       dup (p1 [1]);
       close (p1 [0]);
       min_q = min (arr, n/4);
       //std::cout << min_q
       write (p1 [1], &min_q, sizeof (min_q));

     }

     if (fc1 > 0 && !fc2) {

       close (1);
       dup (p2 [1]);
       close (p2 [0]);
       min_q = min (arr + n/4, n/4);
       //std::cout << min_q;
       write (p2 [1], &min_q, sizeof (min_q));

     }

     if (!fc1 && fc2 > 0) {

       close (1);
       dup (p3 [1]);
       close (p3 [0]);
       min_q = min (arr + 2*(n/4), n/4);
       //std::cout << min_q;
       write (p3 [1], &min_q, sizeof (min_q));

     }

     if (!fc1 && !fc2) {

       close (1);
       dup (p4 [1]);
       close (p4 [0]);
       min_q = min (arr + 3*(n/4), n/4 + n%4);
       //std::cout << min_q;
       write (p4 [1], &min_q, sizeof (min_q));

     }

   }

   if (fp > 0) {
     close (0);
     dup (p1 [0]);
     close (p1 [1]);
     //std::cin >> min1;
     read (p1 [0], &min1, sizeof (min1));
     close (p1 [0]);
     dup (p2 [0]);
     close (p2 [1]);
     //std::cin >> min2;
     read (p2 [0], &min2, sizeof (min2));
     close (p2 [0]);
     dup (p3 [0]);
     close (p3 [1]);
     //std::cin >> min3;
     read (p3 [0], &min3, sizeof (min3));
     close (p3 [0]);
     dup (p4 [0]);
     close (p4 [1]);
     //std::cin >> min4;
     read (p4 [0], &min4, sizeof (min4));
     close (p4 [0]);

     minimum = min_of_4 (min1, min2, min3, min4);
     std::cout << minimum << '\n';
   }
 }

 int min (int *p, int size) {

   int min = p [0];

   for (int i = 1; i < size; i++)
     if (p [i] < min)
        min = p [i];

   return min;
 }

 int min_of_4 (int m1, int m2, int m3, int m4) {
   int m;
   m = m1;
   if (m2 < m)
    m = m2;
   if (m3 < m)
    m = m3;
   if (m4 < m)
    m = m4;

   return m;
 }
