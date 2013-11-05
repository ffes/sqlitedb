#include <windows.h>
#include <stdio.h>
#include "SqliteDB.h"
using namespace std;

int main()
{
	try
	{
		SqliteDatabase db(L"test.sqlite");

		if (!db.TableExists("Test"))
		{
			db.Execute("CREATE TABLE Test (Key Text, Value TEXT);");
			db.Execute("INSERT INTO TEST VALUES(1,1);");
			db.SetUserVersion(2);
		}
		printf("UserVersion = %d\n", db.GetUserVersion());

		// Retrieve some records from the database
		SqliteStatement stmt(&db, "SELECT * FROM Test WHERE Key = @key");
		stmt.Bind("@key", 1);
		while (stmt.GetNextRecord())
		{
			printf("Key = %s, value = %s\n", stmt.GetTextColumn("Key").c_str(), stmt.GetTextColumn("Value").c_str());
		}
		stmt.Finalize();

		// Save a record to database
		stmt.Prepare("INSERT INTO TEST VALUES(@key, @value);");
		stmt.Bind("@key", 2);
		stmt.Bind("@value", 2);
		stmt.SaveRecord();
		stmt.Finalize();

		db.Close();
	}
	catch(SqliteException e)
	{
		printf("ERROR: %s\n", e.what());
	}
	return 0;
}
