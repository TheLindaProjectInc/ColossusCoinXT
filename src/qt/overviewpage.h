// Copyright (c) 2011-2013 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_QT_OVERVIEWPAGE_H
#define BITCOIN_QT_OVERVIEWPAGE_H

#include "amount.h"

#include <QWidget>
#include <memory>

class ClientModel;
class TransactionFilterProxy;
class TxViewDelegate;
class WalletModel;

namespace Ui
{
class OverviewPage;
}

QT_BEGIN_NAMESPACE
class QModelIndex;
class QNetworkReply;
class QNetworkAccessManager;
QT_END_NAMESPACE

/** Overview ("home") page widget */
class OverviewPage : public QWidget
{
    Q_OBJECT

public:
    explicit OverviewPage(QWidget* parent = 0);
    ~OverviewPage();

    void setClientModel(ClientModel* clientModel);
    void setWalletModel(WalletModel* walletModel);
    void showOutOfSyncWarning(bool fShow);

public slots:
    void setBalance(const CAmount& balance, const CAmount& unconfirmedBalance, const CAmount& immatureBalance, 
                    const CAmount& zerocoinBalance, const CAmount& unconfirmedZerocoinBalance, const CAmount& immatureZerocoinBalance,
                    const CAmount& watchOnlyBalance, const CAmount& watchUnconfBalance, const CAmount& watchImmatureBalance);
    void alertLinkActivated(const QString& link);

signals:
    void transactionClicked(const QModelIndex& index);

private:
    Ui::OverviewPage* ui = nullptr;
    ClientModel* clientModel = nullptr;
    WalletModel* walletModel = nullptr;
    CAmount currentBalance;
    CAmount currentUnconfirmedBalance;
    CAmount currentImmatureBalance;
    CAmount currentZerocoinBalance;
    CAmount currentUnconfirmedZerocoinBalance;
    CAmount currentimmatureZerocoinBalance;
    CAmount currentWatchOnlyBalance;
    CAmount currentWatchUnconfBalance;
    CAmount currentWatchImmatureBalance;
    QString newVersionNotification;
    int nDisplayUnit;
    void getPercentage(CAmount nTotalBalance, CAmount nZerocoinBalance, QString& sPIVPercentage, QString& szPIVPercentage);

    TxViewDelegate* txdelegate;
    TransactionFilterProxy* filter;

    QString strNewsDate;
    std::unique_ptr<QTimer> timerNews;
    std::unique_ptr<QNetworkAccessManager> network;

private slots:
    void updateDisplayUnit();
    void handleTransactionClicked(const QModelIndex& index);
    void updateAlerts(const QString& warnings);
    void updateWatchOnlyLabels(bool showWatchOnly);
    void updateNewVersionAvailability();
    void updateNewVersionDownloadProgress(const QString& msg, int nProgress);

    void downloadNewsRequest();
    void newsDownloaded(QNetworkReply *reply);
};

#endif // BITCOIN_QT_OVERVIEWPAGE_H
