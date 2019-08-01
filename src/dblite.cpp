#include "dblite.h"
#include "asprintf.h"


DBLite::DBLite()
{
    // Save the result of opening the file
    rc = sqlite3_open("example.db", &db);
    checkDBErrors();
}

DBLite::DBLite(string dbName)
{
    // Save the result of opening the file
    rc = sqlite3_open(dbName.c_str(), &db);
    checkDBErrors();
}

void DBLite::createTable(string sql)
{

    // Save SQL to create a table
    //sql = "CREATE TABLE PEOPLE (ID INT PRIMARY KEY NOT NULL, NAME TEXT NOT NULL);";

    // Run the SQL
    rc = sqlite3_exec(db, sql.c_str(), callback, nullptr, &zErrMsg);

    checkDBErrors();

}

void DBLite::insertData(const char *ID, const char *name)
{//demo
    char *query = nullptr;

    // Build a string using asprintf()
    asprintf(&query, "INSERT INTO PEOPLE ('ID', 'NAME') VALUES  ('%s', '%s');", ID, name);

    // Prepare the query
    sqlite3_prepare(db, query, static_cast<int>(strlen(query)), &stmt, nullptr);

    // Test it
    rc = sqlite3_step(stmt);

    // Finialize the usage
    sqlite3_finalize(stmt);

    // Free up the query space
    //free(query);

    checkDBErrors();
}

void DBLite::insertData(const char *query)
{
    //// Prepare the query
    //sqlite3_prepare(db, query, static_cast<int>(strlen(query)), &stmt, nullptr);
    //// Test it
    //rc = sqlite3_step(stmt);
    //// Finialize the usage
    //sqlite3_finalize(stmt);
    //// Free up the query space
    ////free(&query);

    int rc = sqlite3_exec(db, query, callback, nullptr, &zErrMsg);

    if (rc != SQLITE_OK) {
        std::cerr << "Error Insert :" << zErrMsg<< std::endl;
        checkDBErrors();
    }
    else
        std::cout << "Records created Successfully!" << std::endl;

    cout << "STATE OF TABLE AFTER INSERT" << endl;


}

void DBLite::showTable(string &tblName)
{
    // Save SQL insert data
    //sql = "SELECT * FROM 'PEOPLE';";
    sql = "SELECT * FROM '"  + tblName + "';";

    // Run the SQL
    rc = sqlite3_exec(db, sql.c_str(), callback, nullptr, &zErrMsg);
}

void DBLite::deleteRow(const char *ID)
{//demo
    char *query = nullptr;

    // Build a string using asprintf()
    asprintf(&query, "DELETE FROM 'PEOPLE' WHERE ID = '%s';", ID);

    // Prepare the query
    sqlite3_prepare(db, query, static_cast<int>(strlen(query)), &stmt, nullptr);

    // Test it
    rc = sqlite3_step(stmt);

    // Finialize the usage
    sqlite3_finalize(stmt);

    // Free up the query space
    free(query);
}

void DBLite::closeDB()
{
    // Close the SQL connection
    sqlite3_close(db);
}


// Create a callback function
int DBLite::callback(void *NotUsed, int argc, char **argv, char **azColName)
{
    // int argc: holds the number of results
    // (array) azColName: holds each column returned
    // (array) argv: holds each value

    for(int i = 0; i < argc; i++) {

        // Show column name, value, and newline
        cout << azColName[i] << ": " << argv[i] << endl;

    }
    // Insert a newline
    cout << endl;

    // Return successful
    return 0;
}

void DBLite::checkDBErrors()
{
    if( rc ){
        // Show an error message
        cout << "DB Error: " << sqlite3_errmsg(db) << endl;
        sqlite3_free(zErrMsg);
        closeDB();
        exit(-1);
    }
}
