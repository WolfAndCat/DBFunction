#include "MySqlDB.h"
#include "mysql.h"

MySqlDB::MySqlDB()
{
    m_pMysql = new MYSQL;
}

MySqlDB::~MySqlDB()
{
    if (m_pMysql != nullptr)
    {
        delete m_pMysql;
        m_pMysql = nullptr;
    }
}

bool MySqlDB::Open(const DataBaseInfo& sdiDataBase)
{
    if (m_pMysql !=nullptr)
    {
        mysql_init(m_pMysql);
        mysql_options(m_pMysql, MYSQL_SET_CHARSET_NAME, "gbk");

        return mysql_real_connect(m_pMysql, sdiDataBase.strLocation,
            sdiDataBase.strUser, sdiDataBase.strPassword, sdiDataBase.strDBName,
            sdiDataBase.iPort, NULL, 0);
    }

    return false;
}

bool MySqlDB::IsOpen()
{
    return (!mysql_ping(m_pMysql));
}

bool MySqlDB::SelectData(MatrixStdString & mssResult, const char * strTable, const VecPString & strHeaders, const char * strCondition)
{
    //拼接字符串
    std::string strSql;
    strSql.append("select ");

    std::string strTmp;
    for (auto strHeader : strHeaders)
    {
        if (!strTmp.empty())
        {
            strTmp.append(", ");
        }

        strTmp.append(strHeader);
    }
    strSql.append(strTmp);

    strSql.append(" from ");
    strSql.append(strTable);
    strSql.append(" where ");
    strSql.append(strCondition);

    //执行
    if (Query(strSql))
    {
        GetResultSet(mssResult);
        return true;
    }
    else
    {
        return false;
    }
}

bool MySqlDB::SelectData(MatrixStdString & mssResult, const char * strTable, const char * strCondition)
{
    //拼接字符串
    std::string strSql;
    strSql.append("select * from ");
    strSql.append(strTable);
    strSql.append(" where ");
    strSql.append(strCondition);

    //执行
    if (Query(strSql))
    {
        GetResultSet(mssResult);
        return true;
    }
    else
    {
        return false;
    }
}

bool MySqlDB::InsertData(const char * strTable, const VecSqlString & datas, const VecPString & strHeaders)
{
    std::string strSql;

    if (strHeaders.size() == 0)
    {//无空数据添加
        strSql.append("insert into ");
        strSql.append(strTable);
        strSql.append(" values(");

        for (int i = 0; i < datas.size(); ++i)
        {
            if (i == 0)
            {
                strSql.append(datas.at(i).ToPString());
            }
            else
            {
                strSql.append(", ");
                strSql.append(datas.at(i).ToPString());
            }
        }
        strSql.append(");");
    }
    else
    {//选择添加对应数据
        strSql.append("insert into ");
        strSql.append(strTable);
        strSql.append("(");

        //整合添加项
        for (int i = 0; i < strHeaders.size(); ++i)
        {
            if (0 == i)
            {
                strSql.append(strHeaders.at(i));
            }
            else
            {
                strSql.append(", ");
                strSql.append(strHeaders.at(i));
            }
        }

        strSql += ") values(";
        for (int i = 0; i < datas.size(); ++i)
        {
            if (i == 0)
            {
                strSql.append(datas.at(i).ToPString());
            }
            else
            {
                strSql.append(", ");
                strSql.append(datas.at(i).ToPString());
            }
        }
        strSql += ");";
    }

    return Query(strSql);
}

bool MySqlDB::DeleteData(const char * strTable, const char * strCondition)
{
    std::string strSql;
    strSql.append("delete from ");
    strSql.append(strTable);
    strSql.append(" where ");
    strSql.append(strCondition);
    strSql.append(";");

    return Query(strSql);
}

bool MySqlDB::UpdateData(const char * strTable, const char * strHeader, const char * strValue, const char * strCondition)
{
    std::string strSql;
    strSql.append("update ");
    strSql.append(strTable);
    strSql.append(" set ");
    strSql.append(strHeader);
    strSql.append(" = ");
    strSql.append(strValue);
    strSql.append(" where ");
    strSql.append(strCondition);

    return Query(strSql);
}

bool MySqlDB::UpdateData(const char * strTable, const VecSqlString & vssValues, const VecPString & vpsHeaders, const char * strCondition)
{
    if (vpsHeaders.size() != vssValues.size())
    {
        return false;
    }

    std::string strSql;
    strSql.append("update ");
    strSql.append(strTable);
    strSql.append(" set ");

    //组合修改项
    std::string strTmp;
    for (int i = 0; i < vpsHeaders.size(); ++i)
    {
        if (!strTmp.empty())
        {
            strTmp.append(", ");
        }

        strSql.append(vpsHeaders.at(i));
        strSql.append(" = ");
        strSql.append(vssValues.at(i).ToPString());
    }

    strSql.append(" where ");
    strSql.append(strCondition);

    return Query(strSql);
}

void MySqlDB::Close()
{
    mysql_close(m_pMysql);
}

const char * MySqlDB::GetError()
{
    return mysql_error(m_pMysql);
}

bool MySqlDB::Query(std::string strSQL)
{
    if (m_pMysql == NULL) return false;

    return mysql_real_query(m_pMysql, strSQL.c_str(), strSQL.length());
}

bool MySqlDB::GetResultSet(MatrixStdString & mssResult)
{
    MYSQL_RES* res = mysql_store_result(m_pMysql);
    unsigned int colNumber = mysql_num_fields(res);
    MYSQL_ROW row;

    while (row = mysql_fetch_row(res))
    {
        VecStdString vssStr;
        for (auto i = 0; i < colNumber; i++)
        {
            if (row[i] == nullptr)
            {
                vssStr.push_back(std::string());
                continue;
            }
            std::string strValue(row[i]);
            vssStr.push_back(strValue);
        }
        mssResult.push_back(vssStr);
    }
    mysql_free_result(res);

    return true;
}
