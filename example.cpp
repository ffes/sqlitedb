#include <windows.h>
#include <iostream>
#include <string>
#include "SqliteDB.h"

int main()
{
	try
	{
		SqliteDatabase db(L"example.sqlite");

		// Does the database have a table named "Example"?
		if (!db.TableExists("Example"))
		{
			// Create a new table and put a record in it
			db.Execute("CREATE TABLE Example (Key INT, Value TEXT);");
			db.Execute("INSERT INTO Example VALUES(1, 'Example 1');");
		}

		// Insert an extra record into the table
		SqliteStatement stmt(&db, "INSERT INTO Example VALUES(@key, @value);");
		stmt.Bind("@key", 2);
		stmt.Bind("@value", "Example 2");
		stmt.SaveRecord();
		stmt.Finalize();

		// Retrieve the records from the database.
		// Note that the Bind() below is not really needed. It is only here as an example.
		stmt.Prepare("SELECT * FROM Example WHERE Key >= @key ORDER BY Value");
		stmt.Bind("@key", 1);
		while (stmt.GetNextRecord())
		{
			std::cout << "Key = " << stmt.GetTextColumn("Key") <<  ", value = " << stmt.GetTextColumn("Value") << std::endl;
		}
		stmt.Finalize();

		db.Close();
	}
	catch (SqliteException e)
	{
		// Something went wrong
		std::cerr << "ERROR: " << e.what() << std::endl;
	}
	return 0;
}
