#ifndef DATABASEINTERFACE_H
#define DATABASEINTERFACE_H

#include <vector>
#include "SqlString.h"

#define DBTYPE_MYSQL 0

using VecStdString = std::vector<SqlString>;
using MatrixStdString = std::vector<VecStdString>;

using VecPString = std::vector<const char*>;
using VecSqlString = std::vector<SqlString>;

//数据库信息
struct DataBaseInfo
{
    const char*  strDBName;         //数据库名
    int iDbType;                    //数据库操作类型
    const char* strLocation;        //数据库位置
    const char*  strUser;           //用户名
    const char*  strPassword;       //密码
    int iPort;                      //端口
    const char*  strEncode;         //字符编码  
};

class DataBaseInterface
{
public:
    //打开数据库
    virtual bool Open(const DataBaseInfo& sdiDataBase) = 0;
    //判读数据库是否打开
    virtual bool IsOpen() = 0;
    //读取数据
    virtual bool SelectData(MatrixStdString &mssResult, const char *strTable, const VecPString& strHeaders, const char *strCondition = "true") = 0;
    //读取数据表内所有数据
    virtual bool SelectData(MatrixStdString &mssResult, const char *strTable, const char *strCondition = "true") = 0;

    //添加
    virtual bool InsertData(const char * strTable, const VecSqlString& datas, const VecPString& strHeaders = VecPString()) = 0;
    //删除
    virtual bool DeleteData(const char * strTable, const char * strCondition) = 0;
    //修改单项
    virtual bool UpdateData(const char * strTable, const char * strHeader, const char * strValue, const char * strCondition) = 0;
    //多项更新
    virtual bool UpdateData(const char * strTable, const VecSqlString& vssValues, const VecPString& vpsHeaders, const char * strCondition) = 0;
    //关闭
    virtual void Close() = 0;

    //获取错误
    virtual const char * GetError() = 0;
};


#endif
