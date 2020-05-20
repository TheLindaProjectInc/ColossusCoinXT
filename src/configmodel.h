// Copyright (c) 2015-2018 The COLX developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_CONFIGMODEL_H
#define BITCOIN_CONFIGMODEL_H

#include <boost/optional/optional.hpp>

/**
 * @brief The ConfigModel class is responsible for providing
 * interface to the application settings cmd/.conf.
 */
class ConfigModel
{
public:
    ConfigModel(int argc, char* argv[]);

    ~ConfigModel();

    bool isZeromintInitialized() const;

    bool isZeromintEnabled() const;

    void setZeromintEnabled(bool enable);

private:
    ConfigModel();
    ConfigModel(const ConfigModel&);
    ConfigModel& operator=(const ConfigModel&);
    friend class CContext;

private:
    boost::optional<bool> fEnableZeromint_;
};

#endif // BITCOIN_CONFIGMODEL_H
