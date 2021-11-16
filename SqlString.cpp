#include "SqlString.h"

SqlString::SqlString(bool bValue)
{
    if (bValue)
    {
        m_strSqlValue = "1";
    }
    else
    {
        m_strSqlValue = "0";
    }
}

SqlString::SqlString(int iValue)
{
    m_strSqlValue = std::to_string(iValue);
}

SqlString::SqlString(unsigned long nValue)
{
    m_strSqlValue = std::to_string(nValue);
}

SqlString::SqlString(long lValue)
{
    m_strSqlValue = std::to_string(lValue);
}

SqlString::SqlString(double dValue)
{
    m_strSqlValue = std::to_string(dValue);
}

SqlString::SqlString(const char * strValue)
{
    m_strSqlValue.append("'");
    m_strSqlValue.append(strValue);
    m_strSqlValue.append("'");
}

SqlString::SqlString(const std::string& strReslut)
{
    m_strSqlValue = strReslut;
}

bool SqlString::ToBool() const
{
    if (strcmp(m_strSqlValue.data(), "0"))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int SqlString::ToInt() const
{
    return atoi(m_strSqlValue.c_str());
}

unsigned long SqlString::ToULong() const
{
    return stoul(m_strSqlValue);
}

long SqlString::ToLong() const
{
    return atol(m_strSqlValue.c_str());
}

double SqlString::ToDouble() const
{
    return stod(m_strSqlValue);
}

const char * SqlString::ToPString() const
{
    return m_strSqlValue.c_str();
}
