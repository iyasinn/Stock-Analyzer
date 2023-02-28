#include <iostream> 
#include <sqlite3.h>

using namespace std; 


static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
   int i;
   for(i = 0; i<argc; i++) {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

auto main() -> int {

    sqlite3* db; 
    char *zErrMsg = nullptr; 
    string sql;
    int rc; 

    // rc is run command
    rc = sqlite3_open("test.db", &db);

    if (rc) {
        cout << "Error\n";
        return(1);
    }
    
    cout << "Opened the data base\n";

    sql =  "CREATE TABLE COMPANY("             \
           "ID INT PRIMARY KEY     NOT NULL,"  \
           "NAME           TEXT    NOT NULL,"  \
           "AGE            INT     NOT NULL,"  \
           "ADDRESS        CHAR(50),"          \
           "SALARY         REAL );";



    string test; 

    rc = sqlite3_exec(db, sql.c_str(), callback, nullptr, &zErrMsg);


    
   sql = "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "  \
         "VALUES (1, 'Paul', 32, 'California', 20000.00 ); " \
         "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "  \
         "VALUES (2, 'Allen', 25, 'Texas', 122343000.00 ); "     \
         "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
         "VALUES (3, 'Teddy', 23, 'Norway', 0.00 );" \
         "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
         "VALUES (4, 'Mark', 25, 'Rich-Mond ', 000.00 );";

   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql.c_str(), callback, nullptr, &zErrMsg);

      if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } else {
      fprintf(stdout, "Records created successfully\n");
   }
   sqlite3_close(db);

   // So if data already exists you can tinsert it again 







    sqlite3_close(db);
   

    


}