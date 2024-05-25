/**
* @file allStks.h�C
*
* �w�q�Ҧ��ӫ~��ƪ��޲z���O
*
* @author boris.chen@localhost
*/

#ifndef _ALL_STK_MGR_H_
#define _ALL_STK_MGR_H_

#include <atomic>
#include <string>
#include <map>
#include <mutex>
#include <boost/bimap.hpp>
#include "mtkNetDef.h"

typedef boost::bimap<std::string, std::string> stkMap;
typedef std::shared_ptr<stkMap> stkMapPtr;

typedef std::map<std::string, char> catMap;
typedef std::shared_ptr<catMap> catMapPtr;

class allStksMgr
{
public:
	/**
	* @brief �غc��
	*
	* allStksMgr()
	*
	* @param �L
	* @return �L
	*/
	allStksMgr();

	/**
	* @brief �Ѻc��
	*
	* ~allStksMgr()
	*
	* @param �L
	* @return �L
	*/
	virtual ~allStksMgr();

	/**
	* @brief ���m
	*
	* reset()
	*
	* @param �L
	* @return �L
	*/
	void reset();

	/**
	* @brief ���m
	*
	* reset()
	*
	* @param std::map<std::string, std::string> &map: �ӷ����
	* @return �L
	*/
	void reset(std::map<std::string, std::string> &map);

	/**
	* @brief ���m
	*
	* reset()
	*
	* @param stkMap &newMap: �ӷ����
	* @return �L
	*/
	void reset(stkMap &newMap);
	
	/**
	* @brief ���m
	*
	* reset()
	*
	* @param catMap &newMap: �ӷ����
	* @return �L
	*/
	void reset(catMap &newMap);

	/**
	* @brief �ΪѲ��N�����o�ѦW
	*
	* getStkName()
	*
	* @param std::string:�Ѳ��N��
	* @return std::string:�ѦW
	*/
	std::string getStkName(const std::string &stkID);

	/**
	* @brief �ΪѲ��N�����o�ѦW
	*
	* getStkName()
	*
	* @param std::string:�Ѳ��N��
	* @return bool: ���ӫ~ / �L�ӫ~
	* @return std::string:�ѦW
	*/
	bool getStkName(const std::string &stkID, std::string &stkName);

	/**
	* @brief  �ΪѦW���o�Ѳ��N��
	*
	* getStkID()
	*
	* @param std::string: �ѦW
	* @return std::string:�Ѳ��N��
	*/
	std::string getStkID(const std::string &stkName);

	/**
	* @brief  �ΪѲ��N�����o�����O
	*
	* getMarket()
	*
	* @param std::string: �Ѳ��N��
	* @return std::string:�����O
	*/
	char getMarket(const std::string &stkName);

	/**
	* @brief  �O�_���Ѳ��N��
	*
	* hasStkID()
	*
	* @param std::string:�Ѳ��N��
	* @return true: �� / false: �L
	*/
	bool hasStkID(const std::string &stk);

	/**
	* @brief  �s�W�Ѳ��N��
	*
	* insertStk()
	*
	* @param std::string:�Ѳ��N��
	* @param std::string:�Ѳ��W��
	* @return 0: ���\ / �D0: ����
	*/
	int insertStk(const std::string &stk, const std::string &name);

	/**
	* @brief  �R���Ѳ��N��
	*
	* removeStk()
	*
	* @param std::string:�Ѳ��N��
	* @return 0: ���\ / -1: stkmap���� / -2: catmap���� / -3: ������
	*/
	int removeStkID(const std::string &stk);

	/**
	* @brief  �ƻs�Ҧ��ӫ~
	*
	* cloneAllStks()
	*
	* @param sstd::map<std::string, std::string>& ret:�Ҧ��ӫ~
	* @return �L
	*/
	void cloneAllStks(std::map<std::string, std::string>& ret);

	/**
	* @brief  �Ҧ��ӫ~�ƶq
	*
	* getAllStksNums()
	*
	* @param �L
	* @return size_t:�ƶq
	*/
	size_t getAllStksNums();
private:
	stkMapPtr getAllStks();
	catMapPtr getAllcatStks();

	std::mutex m_mutex;
	stkMapPtr m_stks;				/**<�O���Ҧ��Ѳ���T*/

	std::mutex m_catMutex;
	catMapPtr m_catStks;			/**<�O���Ҧ��Ѳ�������T*/
};

#endif	// ! _ALL_STK_MGR_H_