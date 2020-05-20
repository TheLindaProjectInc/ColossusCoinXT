// Copyright (c) 2015-2018 The COLX developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "configmodel.h"
#include "util.h"

using namespace std;

ConfigModel::ConfigModel(int argc, char* argv[])
{
    // Parse command-line options. These take precedence over anything else.
    ParseParameters(argc, argv);

    //fEnableZeromint_ = GetBoolArg("-enablezeromint", false);
    fEnableZeromint_ = false;
}

ConfigModel::~ConfigModel()
{}

bool ConfigModel::isZeromintInitialized() const
{
    return fEnableZeromint_.is_initialized();
}

bool ConfigModel::isZeromintEnabled() const
{
    return fEnableZeromint_.get_value_or(false);
}

void ConfigModel::setZeromintEnabled(bool enable)
{
    //disabled
    //fEnableZeromint_ = enable;
}
