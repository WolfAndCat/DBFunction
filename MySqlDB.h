#pragma once
#include "DataBaseInterface.h"

class MYSQL;
class MySqlDB :
    public DataBaseInterface
{
public:
    MySqlDB();
    ~MySqlDB();

    //�����ݿ�
    virtual bool Open(const DataBaseInfo& sdiDataBase)override;
    //�ж����ݿ��Ƿ��
    virtual bool IsOpen() override;

    virtual bool SelectData(MatrixStdString &mssResult, const char *strTable, const VecPString& strHeaders, const char *strCondition = "true") override;
    //��ȡ���ݱ�����������
    virtual bool SelectData(MatrixStdString &mssResult, const char *strTable, const char *strCondition = "true") override;
    //���
    virtual bool InsertData(const char * strTable, const VecSqlString& datas, const VecPString& strHeaders = VecPString()) override;
    //ɾ��
    virtual bool DeleteData(const char * strTable, const char * strCondition) override;
    //�޸ĵ���
    virtual bool UpdateData(const char * strTable, const char * strHeader, const char * strValue, const char * strCondition) override;
    //�������
    virtual bool UpdateData(const char * strTable, const VecSqlString& vssValues, const VecPString& vpsHeaders, const char * strCondition) override;

    //�ر�
    virtual void Close()override;
    //��ȡ����
    virtual const char * GetError()override;

private:
    //sql���ִ��
    bool Query(std::string strSQL);
    //��ȡ���ִ�н��
    bool GetResultSet(MatrixStdString &mssResult);

private:
    MYSQL* m_pMysql;
};

