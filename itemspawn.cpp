#include <iostream>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h> 
#include <sqlite3.h>
#include "libsqlite.hpp"
#include <string.h>

using namespace std;

string sqliteFile = "databaseALL.sqlite3";
sqlite::sqlite db( sqliteFile );

auto cur = db.get_statement();
  
int itemSpawn = rand() % 100;
int itmSpwn = rand() % 100;

int itSpn = rand() % 100;
int itemTypeSpawn;

int main()
{
  sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   char *sql;
   const char* data ;  
   
   int idd_ittem;
   //cout <<"hellooooo"<< itemSpawn <<endl;
   cout<<itemSpawn<<itmSpwn<<itSpn<<endl;
   cout << "Hello  " << itSpn << endl;
  
  //itSpn=13; //...HARDCODING...HARDCODING...DELETE AFTER DEVELOPMENT...
  
  if ( itSpn <= 30 )                        // (itemSpawn <= 90 )
  {
     itemTypeSpawn = rand() % 100;
     cout<< itemTypeSpawn <<endl;
 
    //itemTypeSpawn = 55;  //...HARDCODING...HARDCODING...DELETE AFTER DEVELOPMENT...
 
    void callDatabase(int idd_ittem);
  if(itemTypeSpawn <= 50)             //if(itemTypeSpawn <= 100)
  {
      //Health potion...
      idd_ittem = 1;
      callDatabase(idd_ittem);     
  }
  else      //     > 50 ;
  {
      //Lucky Charm...
      idd_ittem = 2;
      callDatabase(idd_ittem);
      cout<<endl;
  }
}
}
 
int callDatabase(int idd_ittem)
{
  
  cout << "You have found an item" << endl;
      //cur->set_sql("SELECT * FROM Items;");
      cur->prepare();
      //cout << "You have a health potion" << endl; 
     
       while( cur->step() )  
       {         
         
       }
    
    //}
    //else  //  > 50;
    //{      
    //}

    //cout<< "hhhh : " << itSpn << endl;
    //cout<<"hihi"<<endl;
    //if (itemSpawn <= 30) 

  {
   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   char *sql;
   const char* data;

   /* Open database */
   //rc = sqlite3_open("test.db", &db);
   rc = sqlite3_open("databaseALL.sqlite3", &db); 
  
   if( rc ) 
   {
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      //return(0);
   } 
   else 
   {
      //fprintf(stderr, "Opened database successfully\n");
   }

   
    
    std::string id_item_x = to_string(idd_ittem);
   /* sql = */
   std::string sstring = "select item_name from Items where id_item = " + id_item_x; //(string *)(id_item_x);
   //cout << sstring << endl;
    
    sql = strtok( &sstring[0], ""); 
   
    //cout << sql <<endl;
    
    int callback(void *data, int argc, char **argv, char **azColName);
   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
   
   if( rc != SQLITE_OK ) 
   {
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } 
   else 
   {
      //fprintf(stdout, "Operation done successfully\n");
   }
   sqlite3_close(db);
      
   return 0;
}
  
}
  
  
int callback(void *data, int argc, char **argv, char **azColName)
{
   int i;
   //fprintf(stderr, "%s: ", (const char*)data);
   
   for(i = 0; i<argc; i++)
   {
       printf("You have found a %s",  argv[i] ? argv[i] : "NULL");
   }
   
     //printf("%s = %s\n", azColName, argv ? argv : "NULL");
     //cout<<"hhii 2 : " << azColName << argv <<endl;
     
     //printf("\n");
  
  return 0;
}
