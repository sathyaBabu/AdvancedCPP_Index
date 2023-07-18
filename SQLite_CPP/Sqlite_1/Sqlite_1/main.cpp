#include <iostream>
#include <string>
#include <sqlite3.h>

//Undefined symbol: _sqlite3_open
/*
 Open your Xcode project file
 Go the "General" tab
 Look for the section that says "Linked Frameworks and Libraries"
 Press the "+" button
 Search for "sqlite"
 Click on "libsqlite3.dylib" and press "Add"

 */
using namespace std;

/// using raw query
/// // https://razorsql.com/articles/sqlite_mac.html
///
/// https://www.tutorialspoint.com/sqlite/sqlite_c_cpp.htm

// Create a callback function
int callback(void *NotUsed, int argc, char **argv, char **azColName){

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
  
int main() {

    // Pointer to SQLite connection
    sqlite3 *db;

    // Save any error messages
    char *zErrMsg = 0;

    // Save the result of opening the file
    int rc;

    // Save any SQL
    string sql;

    //
   // create table department(dept_no int, dept_name varchar(25));
    // Save the result of opening the file
    rc = sqlite3_open("example.db", &db);
    
    if( rc ){
        // Show an error message
        cout << "DB Error: " << sqlite3_errmsg(db) << endl;
        // Close the connection
        sqlite3_close(db);
        // Return an error
        return(1);
    }

    // insert into department values (1, 'Sales');
    
    // Save SQL to create a table
    sql = "CREATE TABLE PEOPLE ("  \
      "ID INT PRIMARY KEY     NOT NULL," \
      "NAME           TEXT    NOT NULL);";
    
    // Run the SQL (convert the string to a C-String with c_str() )
    rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);

  //  "CREATE TABLE PEOPLE (ID INT PRIMARY KEY NOT NULL,NAME TEXT NOT NULL);";
    // Save SQL insert data
    sql = "INSERT INTO PEOPLE ('ID', 'NAME') VALUES ('4','Virupaksh Sing');";
    
    // Save SQL insert data
    sql = "INSERT INTO PEOPLE ('ID', 'NAME') VALUES ('3','Shashank');";
    
    // Run the SQL (convert the string to a C-String with c_str() )
  //  rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);

    // Save SQL insert data
    sql = "INSERT INTO PEOPLE ('ID', 'NAME') VALUES ('2','Sneha');";
    
   

    // Save SQL insert data
    sql = "INSERT INTO PEOPLE ('ID', 'NAME') VALUES ('1','Sathya');";
    
    
    
    // Run the SQL (convert the string to a C-String with c_str() )
    rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);

    
    // select * from department;
    // Save SQL insert data
    sql = "SELECT * FROM 'PEOPLE';";
    
    // Run the SQL (convert the string to a C-String with c_str() )
    rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);
    
    // Close the SQL connection
    sqlite3_close(db);
    
    return 0;
}

/*
 go to that dir sqlite_1
 change into it
 compile main.cpp
 
 Sathyas-MBP-2:Sqlite_1 malsneha$ g++ main.cpp -lsqlite3
 Sathyas-MBP-2:Sqlite_1 malsneha$ ls
 a.out        main.cpp    student.db
 Sathyas-MBP-2:Sqlite_1 malsneha$ ./a.out
 
 ID: 3
 NAME: Shashank

 ID: 2
 NAME: Sneha

 ID: 1
 NAME: Sathya

 */
