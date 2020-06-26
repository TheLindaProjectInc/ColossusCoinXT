// Copyright (c) 2015-2018 The COLX developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_OBFUSCATIONDIALOG_H
#define BITCOIN_OBFUSCATIONDIALOG_H

#include <QWidget>
#include <memory>

class QLabel;
class QCheckBox;
class QPushButton;
class QLineEdit;
class QTimer;
class QMenu;
class QTableView;
class QModelIndex;
class QSortFilterProxyModel;

class ObfuscationModel;
typedef std::shared_ptr<ObfuscationModel> ObfuscationModelPtr;

class ObfuscationDialog : public QWidget
{
    Q_OBJECT

public:
    explicit ObfuscationDialog(QWidget* parent = nullptr);

    ~ObfuscationDialog() override;

    void setModel(ObfuscationModelPtr model);

private:
    void setupUI();
    void updateUI();
    void setupLayout();
    void showEvent(QShowEvent *event) override;

private slots:
    void onStart();
    void onStop();
    void onMix();
    void onReset();

private:
    ObfuscationModelPtr model_;

    struct {
        QLabel *labelTitle = nullptr;
        QLabel *labelStatus = nullptr;
        QLabel *labelCompletion = nullptr;
        QLabel *labelBalance = nullptr;
        QLabel *labelAmountRound = nullptr;
        QLabel *labelDenom = nullptr;
        QPushButton *btnStart = nullptr;
        QPushButton *btnStop = nullptr;
        QPushButton *btnMix = nullptr;
        QPushButton *btnReset = nullptr;
    } ui;
};

#endif // BITCOIN_OBFUSCATIONDIALOG_H
