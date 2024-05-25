#include "allStksMgr.h"

allStksMgr::allStksMgr()
	: m_stks(new stkMap)
	, m_catStks(new catMap)
{
}

allStksMgr::~allStksMgr() 
{
	m_stks->clear();
	m_catStks->clear();
}

void allStksMgr::reset()
{
	std::lock_guard<std::mutex> lock(m_mutex);
	if (!m_stks.unique())
	{
		m_stks.reset(new stkMap());
		return;
	}
	assert(m_stks.unique());
	m_stks->clear();
}

void allStksMgr::reset(stkMap &newMap)
{
	std::lock_guard<std::mutex> lock(m_mutex);
	if (!m_stks.unique())
	{
		m_stks.reset(new stkMap(newMap));
		return;
	}
	assert(m_stks.unique());
	m_stks->clear();
	/*assign*/
	(*m_stks)= newMap;
}

void allStksMgr::reset(catMap & newMap)
{
	std::lock_guard<std::mutex> lock(m_catMutex);
	if (!m_catStks.unique())
	{
		m_catStks.reset(new catMap(newMap));
		return;
	}
	assert(m_catStks.unique());
	m_catStks->clear();
	/*assign*/
	(*m_catStks) = newMap;
}

void allStksMgr::reset(std::map<std::string, std::string> &map)
{
	std::lock_guard<std::mutex> lock(m_mutex);
	if (!m_stks.unique()) 
	{
		m_stks.reset(new stkMap()); 
	}
	else
	{
		assert(m_stks.unique());
		m_stks->clear();
	}
	/*放入bimap*/
	size_t nums = 0;
	for (auto &i : map)
	{
		m_stks->insert({ i.first, i.second });
		++nums;
		if (m_stks->size() != nums)
		{
			/*這裡補-回來，否則之後都不一樣*/
			--nums;

			//
			/*結論：目前看起來是一些，指數、概念股有重複，放不進去bimap*/
			/*(先不管她)*/
			//
		}
	}
}

std::string allStksMgr::getStkName(const std::string &stkID)
{
	std::string name = "";
	stkMapPtr allStks = getAllStks();
	stkMap::left_iterator it = allStks->left.find(stkID);
	if (it != allStks->left.end())
		name = it->get_right();
	return name;
}

bool allStksMgr::getStkName(const std::string &stkID, std::string &stkName)
{
	bool bhas = true;
	stkMapPtr allStks = getAllStks();
	stkMap::left_iterator it = allStks->left.find(stkID);
	if (it != allStks->left.end())
		stkName = it->get_right();
	else
		bhas = false;
	return bhas;
}

std::string allStksMgr::getStkID(const std::string &stkName)
{
	std::string stkID = "";
	stkMapPtr allStks = getAllStks();
	stkMap::right_iterator it = allStks->right.find(stkName);
	if (it != allStks->right.end())
		stkID = it->get_left();
	return stkID;
}

bool allStksMgr::hasStkID(const std::string &stk)
{
	bool bret = false;
	stkMapPtr allStks = getAllStks();
	stkMap::left_iterator it = allStks->left.find(stk);
	if (it != allStks->left.end())
		bret = true;
	return bret;
}

int allStksMgr::insertStk(const std::string &stk, const std::string &name)
{
	if (stk.empty() || name.empty())
		return -1;

	int iret = 0;
	//
	std::lock_guard<std::mutex> lock(m_mutex);
	if (!m_stks.unique())
	{
		m_stks.reset(new stkMap(*m_stks));
	}
	assert(m_stks.unique());
	/*先刪除*/
	stkMap::left_iterator it = m_stks->left.find(stk);
	if (it != m_stks->left.end())
		m_stks->left.erase(it);
	/*insert*/
	m_stks->insert({ stk, name });

	return 0;
}

int allStksMgr::removeStkID(const std::string &stk)
{
	int iret = 0;
	//
	std::lock_guard<std::mutex> lock(m_mutex);
	if (!m_stks.unique()) 
	{
		m_stks.reset(new stkMap(*m_stks));
	}
	assert(m_stks.unique());
	//
	stkMap::left_iterator it = m_stks->left.find(stk);
	if (it != m_stks->left.end())
		m_stks->left.erase(it);
	else
		iret = -1;
	///////////////////////////////////////////////////////////
	std::lock_guard<std::mutex> lock2(m_catMutex);
	if (!m_catStks.unique())
	{
		m_catStks.reset(new catMap(*m_catStks));
	}
	assert(m_catStks.unique());
	//
	catMap::iterator itF = m_catStks->find(stk);
	if (itF != m_catStks->end())
		m_catStks->erase(itF);
	else
		iret -= 2;

	return iret;
}

stkMapPtr allStksMgr::getAllStks()
{
	std::lock_guard<std::mutex> lock(m_mutex);
	return m_stks;
}

catMapPtr allStksMgr::getAllcatStks()
{
	std::lock_guard<std::mutex> lock(m_catMutex);
	return m_catStks;
}

char allStksMgr::getMarket(const std::string &stkName)
{
	std::string stkID = "";
	catMapPtr allStks = getAllcatStks();
	catMap::iterator it = allStks->find(stkName);
	if (it != allStks->end())
		return it->second;

	return 0x00;
}

void allStksMgr::cloneAllStks(std::map<std::string, std::string>& ret)
{
	stkMapPtr sp = getAllStks();
	for (auto& i : (*sp))
	{
		ret.emplace(i.left, i.right);
	}
}

size_t allStksMgr::getAllStksNums()
{
	stkMapPtr sp = getAllStks();
	return sp->size();
}