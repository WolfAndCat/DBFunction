#include "DataBaseTest.h"

#include <iostream>
#include "MySqlDB.h"
#include "mysql.h"


using std::cout;
using std::endl;

void DataBaseTest::runTest()
{
    MYSQL mysql;
    MYSQL_RES * res;
    MYSQL_ROW row;
    mysql_init(&mysql);
    mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");

    if (mysql_real_connect(&mysql, "localhost", "root", "123456", "test", 3306, NULL, 0) == NULL)
    {
        cout << "Á¬½ÓÊ§°Ü" << endl;
        system("pause");
        return;
    }

    mysql_query(&mysql, "SELECT * FROM test");

    res = mysql_store_result(&mysql);

    while (row = mysql_fetch_row(res))
    {
        cout << "id is " << row[0] << endl;
    }

    mysql_free_result(res);
    mysql_close(&mysql);

    MySqlDB msdb;
    DataBaseInfo dbi{ "test", DBTYPE_MYSQL, "localhost","root", "123456",  3306, "gbk"};
    bool bRes = msdb.Open(dbi);

    if (bRes)
    {
        msdb.Close();
    }

	system("pause");
	return ;
}
