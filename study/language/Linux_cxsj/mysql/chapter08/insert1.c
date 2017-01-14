#include <stdlib.h>
#include <stdio.h>

#include "mysql.h"

int main(int argc, char *argv[]) {
   MYSQL my_connection;
   int res;

   mysql_init(&my_connection);  
   if (mysql_real_connect(&my_connection, "localhost", 
                          "rick", "rick", "foo", 0, NULL, 0)) {
      printf("Connection success\n");

      res = mysql_query(&my_connection, "INSERT INTO children(fname, age) VALUES('Ann', 3)");
      res = mysql_query(&my_connection, "INSERT INTO children(fname, age) VALUES('fuck', 23)");
      res = mysql_query(&my_connection, "INSERT INTO children(fname, age) VALUES('Uue', 39)");
      res = mysql_query(&my_connection, "INSERT INTO children(fname, age) VALUES('Ann', 71)");
      res = mysql_query(&my_connection, "INSERT INTO children(fname, age) VALUES('Ann', 23)");
      res = mysql_query(&my_connection, "INSERT INTO children(fname, age) VALUES('Jone', 14)");
      res = mysql_query(&my_connection, "INSERT INTO children(fname, age) VALUES('Ann', 6)");
      if (!res) {
         printf("Inserted %lu rows\n", (unsigned long)mysql_affected_rows(&my_connection));
      } else {
         fprintf(stderr, "Insert error %d: %s\n", mysql_errno(&my_connection),
                                              mysql_error(&my_connection));
      }

      mysql_close(&my_connection);
   } else {
      fprintf(stderr, "Connection failed\n");
      if (mysql_errno(&my_connection)) {
      fprintf(stderr, "Connection error %d: %s\n",
                   mysql_errno(&my_connection), mysql_error(&my_connection));
      }
   }

   return EXIT_SUCCESS;
}

