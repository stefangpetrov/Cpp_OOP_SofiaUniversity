#pragma once
#include "DataBase.h"



class ConsoleHandler
{
private:
	fstream f_inout;
	String f_fileName;
	String f_filePath;
	DataBase f_dataBase;

	void open(String path);
	void save();
	void saveAs(String path);
	void close();
	void exit();
	void help();


	void print(String name);

	void importFile(String path);

	void showTables();

	void exportFile(String tableName, String fileName);

	void countValuesIntable(String tableName, int searchCol, String searchValue);

	void renameTable(String oldName, String newName);

	void select(int col, String value, String tableName);

	void describe(String tableName);

	void addColumn(String tableName, String columnName, String columnType);

	void update(String tableName, int searchCol, String searchValue, int targetCol, String targetValue);

	void deleteRows(String tableName, int searchCol, String searchValue);

	void insert(Vector<String> tokens);

	void aggregate(String tableName, int searchCol, String searchValue, int targetCol, String operation);

	void innerjoin(String tableName, int Col, String tableName2, int Col2);

public:




	void handleCommand(String command);


};