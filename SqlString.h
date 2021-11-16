#pragma once

#include <string>

class SqlString
{
    /*enum DataType
    {
        DATATYPE_BOOL,
        DATATYPE_CHAR,
        DATATYPE_SHORT,
        DATATYPE_INT,
        DATATYPE_LONG,
        DATATYPE_FLOAT,
        DATATYPE_DOUBLE,
        DATATYPE_STRING,
    };*/

public:
    //Êý¾Ý×ª»»
    SqlString(bool bValue);
    SqlString(int iValue);
    SqlString(unsigned long nValue);
    SqlString(long lValue);
    SqlString(double dValue);
    SqlString(const char* strValue);
    SqlString(const std::string& strReslut);

    bool ToBool() const;
    int ToInt() const;
    unsigned long ToULong() const;
    long ToLong() const;
    double ToDouble() const;
    const char* ToPString() const;

private:
    std::string m_strSqlValue;
};

