#pragma once
#ifndef DBLITE_H
#define DBLITE_H

#include <iostream>
#include <string>
#include <sqlite3.h>
#include <stdio.h>
#include <string.h>

//#include "asprintf.h"

using namespace std;

class DBLite
{
private:
    // Pointer to SQLite connection
    sqlite3 *db;

    // Save any error messages
    char *zErrMsg;

    // Save the result of opening the file
    int rc;

    // Saved SQL
    string sql;

    // Compiled SQLite Statement
    sqlite3_stmt *stmt;

    static int callback(void *NotUsed, int argc, char **argv, char **azColName);
    void checkDBErrors();

public:
    DBLite();
    DBLite(string dbName);
    void createTable(string sql);
    void insertData(const char *ID,const char *name);
    void insertData(const char *query);
    void showTable(string &tblName);
    void deleteRow(const char* ID);
    void closeDB();

};

#endif // DBLITE_H
