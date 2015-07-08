//
//  LogMgr.cpp
//  
//
//  Created by Raymond Borkowski on 4/14/15.
//
//

#include "LogMgr.h"
#include <string>

using namespace std;
/*
 * Find the LSN of the most recent log record for this TX.
 * If there is no previous log record for this TX, return
 * the null LSN.
 */

int getLastLSN(int txnum){
    if(tx_table.end() == tx_table.find(txnum))
        return NULL_LSN;
    return tx_table[txtnum].lastLSN;
}
    
    /*
     * Update the TX table to reflect the LSN of the most recent
     * log entry for this transaction.
     */
void setLastLSN(int txnum, int lsn){
    tx_table[txnum].lastLSN = lsn;
}
    
    /*
     * Force log records up to and including the one with the
     * maxLSN to disk. Don't forget to remove them from the
     * logtail once they're written!
     */
void flushLogTail(int maxLSN){
    //write to string
    string temp;
    //loop til getLSN matches maxLSN
    auto * i = logtail.begin();
    while( i.getLSN()!=maxLSN){
        temp += i.toString();
        logtail.erase(i);
        i = logtail.begin();
    }
    }
    se->updateLog(temp);
}

    /*
     * Run the analysis phase of ARIES.
     */
    void analyze(vector <LogRecord*> log);
    
    /*
     * Run the redo phase of ARIES.
     * If the StorageEngine stops responding, return false.
     * Else when redo phase is complete, return true.
     */
    bool redo(vector <LogRecord*> log);
    
    /*
     * If no txnum is specified, run the undo phase of ARIES.
     * If a txnum is provided, abort that transaction.
     * Hint: the logic is very similar for these two tasks!
     */
    void undo(vector <LogRecord*> log, int txnum = NULL_TX);
    vector<LogRecord*> stringToLRVector(string logstring);
    

    void abort(int txid);
    
    /*
     * Write the begin checkpoint and end checkpoint
     *
     * First, a begin_checkpoint record is
     * written to indicate when the checkpoint starts. Second, an end__checkpoint
     * record is constructed, including in it the current contents of the transaction
     * table and the dirty page table, and appended to the log. The third step is
     * carried out after the end_checkpoint record is written to stable storage:A
     * special master record containing the LSN of the begirLcheckpoint log record
     * is written to a known place on stable storage. 'Vhile the end__checkpoint 
     * record is being constructed, the DBMS continues executing transactions and 
     * writing other log records; the only guarantee we have is that the transaction table
     */
void checkpoint(){
    logtail.push_back(LogRecord(se->nextLSN(), getLastLSN(txid),txid,COMMIT));
    logtail.push_back(ChkptLogRecord(se->nextLSN(),se->nextLSN(),NULL_TX, tx_table,dirty_page_table));
    se->store_master(se->nextLSN);
    flushLogTail(se->nextLSN);
}

    /*
     * Commit the specified transaction.
     */
void commit(int txid){
    //push begin
    //status
    //flush
    //push end
    logtail.push_back(LogRecord(se->nextLSN(), getLastLSN(txid),txid,COMMIT));
    logtail.push_back(LogRecord(se->nextLSN(),se->nextLSN(),txid,END));
    //call flush
    flushLogTail(se->nextLSN);
    //end
    tx_table[txid].status = C;
}

    /*
     * A function that StorageEngine will call when it's about to
     * write a page to disk.
     * Remember, you need to implement write-ahead logging
     */
void pageFlushed(int page_id){
    
}
    
    /*
     * Recover from a crash, given the log from the disk.
     */
void recover(string log){
    //aries
    analyze(stringToLRVector(log));
    //analyze
    redo(stringToLRVector(log));
    //redue
    undo(stringToLRVector(log));
    //undo
    
}
    /*
     * Logs an update to the database and updates tables if needed.
     */
int write(int txid, int page_id, int offset, string input, string oldtext);
    
    /*
     * Sets this.se to engine.
     */
void setStorageEngine(StorageEngine* engine){
    se = engine;
}
