int turn;
boolean flag[2];
do{
    flag[i] = true;
    turn = j;
    while (flag[j] && turn == j);
    /* critical section */
    flag[i] = false;
    /* remainder section */   

}


/*P1:*/  flag[1] = true;
/*P1_gate:*/ turn = 0;
         while (flag[0] == true && turn == 0)
         {
             // busy wait
         }
         // critical section
         ...
         // end of critical section
         flag[1] = false;



/*P0:*/  flag[0] = true;
/*P0_gate:*/ turn = 1;
         while (flag[1] == true && turn == 1)
         {
             // busy wait
         }
         // critical section
         ...
         // end of critical section
         flag[0] = false;