/**
* @file allStks.h。
*
* 定義所有商品資料的管理類別
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
	* @brief 建構式
	*
	* allStksMgr()
	*
	* @param 無
	* @return 無
	*/
	allStksMgr();

	/**
	* @brief 解構式
	*
	* ~allStksMgr()
	*
	* @param 無
	* @return 無
	*/
	virtual ~allStksMgr();

	/**
	* @brief 重置
	*
	* reset()
	*
	* @param 無
	* @return 無
	*/
	void reset();

	/**
	* @brief 重置
	*
	* reset()
	*
	* @param std::map<std::string, std::string> &map: 來源資料
	* @return 無
	*/
	void reset(std::map<std::string, std::string> &map);

	/**
	* @brief 重置
	*
	* reset()
	*
	* @param stkMap &newMap: 來源資料
	* @return 無
	*/
	void reset(stkMap &newMap);
	
	/**
	* @brief 重置
	*
	* reset()
	*
	* @param catMap &newMap: 來源資料
	* @return 無
	*/
	void reset(catMap &newMap);

	/**
	* @brief 用股票代號取得股名
	*
	* getStkName()
	*
	* @param std::string:股票代號
	* @return std::string:股名
	*/
	std::string getStkName(const std::string &stkID);

	/**
	* @brief 用股票代號取得股名
	*
	* getStkName()
	*
	* @param std::string:股票代號
	* @return bool: 有商品 / 無商品
	* @return std::string:股名
	*/
	bool getStkName(const std::string &stkID, std::string &stkName);

	/**
	* @brief  用股名取得股票代號
	*
	* getStkID()
	*
	* @param std::string: 股名
	* @return std::string:股票代號
	*/
	std::string getStkID(const std::string &stkName);

	/**
	* @brief  用股票代號取得市場別
	*
	* getMarket()
	*
	* @param std::string: 股票代號
	* @return std::string:市場別
	*/
	char getMarket(const std::string &stkName);

	/**
	* @brief  是否有股票代號
	*
	* hasStkID()
	*
	* @param std::string:股票代號
	* @return true: 有 / false: 無
	*/
	bool hasStkID(const std::string &stk);

	/**
	* @brief  新增股票代號
	*
	* insertStk()
	*
	* @param std::string:股票代號
	* @param std::string:股票名稱
	* @return 0: 成功 / 非0: 失敗
	*/
	int insertStk(const std::string &stk, const std::string &name);

	/**
	* @brief  刪除股票代號
	*
	* removeStk()
	*
	* @param std::string:股票代號
	* @return 0: 成功 / -1: stkmap失敗 / -2: catmap失敗 / -3: 都失敗
	*/
	int removeStkID(const std::string &stk);

	/**
	* @brief  複製所有商品
	*
	* cloneAllStks()
	*
	* @param sstd::map<std::string, std::string>& ret:所有商品
	* @return 無
	*/
	void cloneAllStks(std::map<std::string, std::string>& ret);

	/**
	* @brief  所有商品數量
	*
	* getAllStksNums()
	*
	* @param 無
	* @return size_t:數量
	*/
	size_t getAllStksNums();
private:
	stkMapPtr getAllStks();
	catMapPtr getAllcatStks();

	std::mutex m_mutex;
	stkMapPtr m_stks;				/**<記錄所有股票資訊*/

	std::mutex m_catMutex;
	catMapPtr m_catStks;			/**<記錄所有股票市場資訊*/
};

#endif	// ! _ALL_STK_MGR_H_