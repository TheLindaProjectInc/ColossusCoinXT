// Copyright (c) 2018 The COLX developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "context.h"
#include "bootstrapmodel.h"
#include "autoupdatemodel.h"
#include "configmodel.h"
#include "utilstrencodings.h"
#include "timedata.h"
#include "util.h"

#include <memory>
#include <stdexcept>

using namespace std;

static unique_ptr<CContext> context_;

void CreateContext(int argc, char* argv[])
{
    if (context_)
        throw runtime_error("context has already been initialized, revise your code");
    else
        context_.reset(new CContext(argc, argv));
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

CContext::CContext(int argc, char* argv[]):
    configModel_(new ConfigModel(argc, argv))
{
    nStartupTime_ = GetAdjustedTime();
    banAddrConsensus_.insert(make_pair("DSesymccyAQr6LjGLCHsvHzE41uKMk86XS", 0)); // Cryptopia
    banAddrConsensus_.insert(make_pair("D5cNN2DThi3UUwS1hhedfx1UreXjMuxZPp", 1297585)); // spammer
    banAddrConsensus_.insert(make_pair("DJB3pXt9Xuz7UTwPg4R8YtXB75gpNmkErD", 1297585)); // spammer
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

ConfigModelPtr CContext::GetConfigModel() const
{
    return configModel_;
}

void CContext::AddAddressToBan(
        const std::vector<std::string>& mempool,
        const std::vector<std::string>& consensus)
{
    LOCK(csBanAddr_);

    banAddrMempool_.insert(mempool.begin(), mempool.end());

    for (const std::string& addr : consensus)
    {
        size_t pos = addr.find(':');
        if (std::string::npos == pos)
            banAddrConsensus_[addr] = 0;
        else
            banAddrConsensus_[addr.substr(0, pos)] = atoi(addr.substr(pos + 1));
    }
}

bool CContext::MempoolBanActive() const
{
    LOCK(csBanAddr_);
    return !banAddrMempool_.empty();
}

bool CContext::MempoolBanActive(const std::string& addr) const
{
    LOCK(csBanAddr_);
    return banAddrMempool_.find(addr) != banAddrMempool_.end();
}

bool CContext::ConsensusBanActive() const
{
    LOCK(csBanAddr_);
    return !banAddrConsensus_.empty();
}

bool CContext::ConsensusBanActive(
        const std::string& addr,
        int height) const
{
    LOCK(csBanAddr_);
    auto iter = banAddrConsensus_.find(addr);
    if (iter == banAddrConsensus_.end())
        return false;
    else
        return height >= iter->second;
}
