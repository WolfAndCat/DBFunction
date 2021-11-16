#pragma once
#include "DataBaseInterface.h"

class MYSQL;
class MySqlDB :
    public DataBaseInterface
{
public:
    MySqlDB();
    ~MySqlDB();

    //打开数据库
    virtual bool Open(const DataBaseInfo& sdiDataBase)override;
    //判读数据库是否打开
    virtual bool IsOpen() override;

    virtual bool SelectData(MatrixStdString &mssResult, const char *strTable, const VecPString& strHeaders, const char *strCondition = "true") override;
    //读取数据表内所有数据
    virtual bool SelectData(MatrixStdString &mssResult, const char *strTable, const char *strCondition = "true") override;
    //添加
    virtual bool InsertData(const char * strTable, const VecSqlString& datas, const VecPString& strHeaders = VecPString()) override;
    //删除
    virtual bool DeleteData(const char * strTable, const char * strCondition) override;
    //修改单项
    virtual bool UpdateData(const char * strTable, const char * strHeader, const char * strValue, const char * strCondition) override;
    //多项更新
    virtual bool UpdateData(const char * strTable, const VecSqlString& vssValues, const VecPString& vpsHeaders, const char * strCondition) override;

    //关闭
    virtual void Close()override;
    //获取错误
    virtual const char * GetError()override;

private:
    //sql语句执行
    bool Query(std::string strSQL);
    //获取语句执行结果
    bool GetResultSet(MatrixStdString &mssResult);

private:
    MYSQL* m_pMysql;
};

