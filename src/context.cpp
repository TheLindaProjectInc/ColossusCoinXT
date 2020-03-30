// Copyright (c) 2018 The COLX developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "context.h"
#include "bootstrapmodel.h"
#include "autoupdatemodel.h"
#include "timedata.h"
#include "util.h"

#include <memory>
#include <stdexcept>

using namespace std;

static unique_ptr<CContext> context_;

void CreateContext()
{
    if (context_)
        throw runtime_error("context has already been initialized, revise your code");
    else
        context_.reset(new CContext);
}

void ReleaseContext()
{
    context_.reset();
}

CContext& GetContext()
{
    if (!context_)
        throw runtime_error("context is not initialized");
    else
        return *context_;
}

CContext::CContext()
{
    nStartupTime_ = GetAdjustedTime();
    banAddrConsensus_.insert("DSesymccyAQr6LjGLCHsvHzE41uKMk86XS"); // Cryptopia
    banAddrConsensus_.insert("D5cNN2DThi3UUwS1hhedfx1UreXjMuxZPp"); // spammer
    banAddrConsensus_.insert("DJB3pXt9Xuz7UTwPg4R8YtXB75gpNmkErD"); // spammer
}

CContext::~CContext() {}

int64_t CContext::GetStartupTime() const
{
    return nStartupTime_;
}

void CContext::SetStartupTime(int64_t nTime)
{
    nStartupTime_ = nTime;
}

BootstrapModelPtr CContext::GetBootstrapModel()
{
    if (!bootstrapModel_)
        bootstrapModel_.reset(new BootstrapModel);

    return bootstrapModel_;
}

AutoUpdateModelPtr CContext::GetAutoUpdateModel()
{
    if (!autoupdateModel_)
        autoupdateModel_.reset(new AutoUpdateModel);

    return autoupdateModel_;
}

void CContext::AddAddressToBan(
        const std::vector<std::string>& mempool,
        const std::vector<std::string>& consensus)
{
    LOCK(csBanAddr_);
    banAddrMempool_.insert(mempool.begin(), mempool.end());
    banAddrConsensus_.insert(consensus.begin(), consensus.end());
}

bool CContext::MempoolBanActive() const
{
    std::set<std::string> banAddrMem = GetMempoolBanAddr();
    return !banAddrMem.empty() || ConsensusBanActive();
}

bool CContext::MempoolBanActive(const std::string& addr) const
{
    std::set<std::string> banAddrMem = GetMempoolBanAddr();
    return banAddrMem.find(addr) != banAddrMem.end() || ConsensusBanActive(addr);
}

bool CContext::ConsensusBanActive() const
{
    std::set<std::string> banAddrCons = GetConsensusBanAddr();
    return !banAddrCons.empty();
}

bool CContext::ConsensusBanActive(const std::string& addr) const
{
    std::set<std::string> banAddrCons = GetConsensusBanAddr();
    return banAddrCons.find(addr) != banAddrCons.end();
}

std::set<std::string> CContext::GetConsensusBanAddr() const
{
    LOCK(csBanAddr_);
    return banAddrConsensus_;
}

std::set<std::string> CContext::GetMempoolBanAddr() const
{
    LOCK(csBanAddr_);
    return banAddrMempool_;
}
