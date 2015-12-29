# logRecovery
EECS484 LogRecovery Coming soon...

Log Recovery as described in spec. Everything under StudentComponent is what my partner and I created.
Project 4: Logging and Recovery
Due April 17 at 11:55:00 pm
Introduction
It's a sad fact of life: computers crash. One minute everything is working just fine, and the next
minute everything that was in volatile memory is gone forever. To deal with this problem on your
personal machine, you've probably gotten into the habit of saving frequently. In this project, you
will implement an algorithm that database systems commonly use to address the same problem
without slowing down the system too much.
Some Basics of Transactions
1
A transaction is any one execution of a user program in a database management system
(DBMS). For example, suppose Ada and Bob both have accounts at the same bank. Ada logs
onto the bank's website and instructs the bank to make a payment of $100 from her account into
Bob's account. If the bank's computer runs normally, it will deduct $100 from Ada's account
balance, add $100 to Bob's account, and trigger emails to Ada and Bob confirming the transfer.
Those steps—deducting, adding, and confirming that it was done—make up one transaction.
But suppose that the moment after the bank's computer deducts the money from Ada's account
balance, it crashes. When it reboots, the instructions about that $100 that were in its memory
are gone. We would like to ensure that if this happens, the $100 has not simply vanished—it is
back in Ada's account, or it is in Bob's account. Either the whole transaction goes through, or
the part of the transaction that happened before the crash gets undone. Another way of saying
this is that we want a transaction to be atomic​.
Suppose the timing of the crash was a little different. The bank's computer read Ada's balance
into memory and modified it there, read Bob's balance into memory and modified it there, and
triggered the emails. Then, just as it was about to write the updated balances back onto disk, it
crashed. We want to make sure that if the system says a transaction completed successfully,
the changes the transaction made will persist even through a crash. We call this durability​.
(In lecture, you will also learn about two other properties that transactions should have, called
consistency​and isolation​. These have to do with concurrency and are important to
understand, but you don't need to worry about them for this project.)
To ensure atomicity and durability while minimizing the harm to performance, DBMSs use
write­ahead logging​and with a recovery algorithm, such as ARIES​. In this project, you will be
implementing a single­threaded version of ARIES.
1 Transactions will be covered in lecture soon, but if you just can't wait to learn more, check out chapter 16
of the textbook.
1
What you need to do:
Read.
Read sections 16.7 through 16.7.2 and 18.1 through 18.6 in your textbook. This is important​.
The rest of this project will not make sense until you have understood this material.
(Since we have been giving you reading assignments all semester, we assume you already own
the textbook or know that it can be checked out for two hours at a time from the Art Architecture
& Engineering library's course reserve desk on the second floor.)
Download.
Download the recovery simulator from CTools and unzip it. You will see that the eecs484p4
directory contains directories called StorageEngine, StudentComponent, output, correct, and
testcases. The section on Understanding the Simulator below explains what these pieces do.
You'll also want to spend some time familiarizing yourself with the header files.
Implement.
Implement ARIES in LogMgr.cpp.
Do not alter the other files in any way. The autograder will compile and run your LogMgr.cpp
with unaltered copies of all of the other files, so it is in your best interest to test with exactly the
same files. Please do not add any header files; if you need helper functions, you may declare
them and define them in LogMgr.cpp.
You may use the C++11 STL, except​that you may not​use anything that reads from or
writes to disk​
