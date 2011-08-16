/*
  Very simple C program.

   Compile:
     gcc -o simplesqlite3 simplesqlite3.c  -Wall -W -O2 -Wl,-R/usr/local/lib -lsqlite3
  
   Note sqlite3 shared library, by default, installs in /usr/local/lib. 
   The compile command above will directly link the full path of 
   this library into this program.

*/



#include <stdio.h>
#include <stdlib.h>
#include <mysql.h>


static int callback(void *NotUsed, int argc, char **argv, char **azColName){
  int i;
  NotUsed=0;

  for(i=0; i<argc; i++){
    printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
  }
  printf("\n");
  return 0;
}

int main(int argc, char **argv){
  mysql *db;
  char *zErrMsg = 0;
  int rc;

  if( argc!=3 ){
    fprintf(stderr, "Usage: %s DATABASE SQL-STATEMENT\n", argv[0]);
    exit(1);
  }
  rc = mysql_open(argv[1], &db);
  if( rc ){
    fprintf(stderr, "Can't open database: %s\n", mysql_errmsg(db));
    mysql_close(db);
    exit(1);
  }
  rc = mysql_exec(db, argv[2], callback, 0, &zErrMsg);
  if( rc!=MYSQL_OK ){
    fprintf(stderr, "SQL error: %s\n", zErrMsg);
  }
  mysql_close(db);
  return 0;
}


