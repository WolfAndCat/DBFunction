#ifndef DATABASEINTERFACE_H
#define DATABASEINTERFACE_H

#include <vector>
#include "SqlString.h"

#define DBTYPE_MYSQL 0

using VecStdString = std::vector<SqlString>;
using MatrixStdString = std::vector<VecStdString>;

using VecPString = std::vector<const char*>;
using VecSqlString = std::vector<SqlString>;

//���ݿ���Ϣ
struct DataBaseInfo
{
    const char*  strDBName;         //���ݿ���
    int iDbType;                    //���ݿ��������
    const char* strLocation;        //���ݿ�λ��
    const char*  strUser;           //�û���
    const char*  strPassword;       //����
    int iPort;                      //�˿�
    const char*  strEncode;         //�ַ�����  
};

class DataBaseInterface
{
public:
    //�����ݿ�
    virtual bool Open(const DataBaseInfo& sdiDataBase) = 0;
    //�ж����ݿ��Ƿ��
    virtual bool IsOpen() = 0;
    //��ȡ����
    virtual bool SelectData(MatrixStdString &mssResult, const char *strTable, const VecPString& strHeaders, const char *strCondition = "true") = 0;
    //��ȡ���ݱ�����������
    virtual bool SelectData(MatrixStdString &mssResult, const char *strTable, const char *strCondition = "true") = 0;

    //���
    virtual bool InsertData(const char * strTable, const VecSqlString& datas, const VecPString& strHeaders = VecPString()) = 0;
    //ɾ��
    virtual bool DeleteData(const char * strTable, const char * strCondition) = 0;
    //�޸ĵ���
    virtual bool UpdateData(const char * strTable, const char * strHeader, const char * strValue, const char * strCondition) = 0;
    //�������
    virtual bool UpdateData(const char * strTable, const VecSqlString& vssValues, const VecPString& vpsHeaders, const char * strCondition) = 0;
    //�ر�
    virtual void Close() = 0;

    //��ȡ����
    virtual const char * GetError() = 0;
};


#endif
