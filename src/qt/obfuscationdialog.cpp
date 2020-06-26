// Copyright (c) 2015-2018 The COLX developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "obfuscationdialog.h"
#include "obfuscationmodel.h"
#include "ui_interface.h"
#include "tinyformat.h"
#include "guiutil.h"

#include <QFrame>
#include <QMenu>
#include <QLabel>
#include <QCheckBox>
#include <QLineEdit>
#include <QTableView>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QModelIndex>
#include <QTextBrowser>
#include <QSortFilterProxyModel>
#include <QDebug>

static const char *stylesheet = "QPushButton {background-color: transparent;} QPushButton:hover { background-color:qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: .01 #346337, stop: .1 #38693b, stop: .95 #457c49, stop: 1 #4b814f); }";

ObfuscationDialog::ObfuscationDialog(QWidget* parent):
    QWidget(parent)
{
    memset(&ui, 0, sizeof(ui));

    setupUI();
    setupLayout();
}

ObfuscationDialog::~ObfuscationDialog()
{}

void ObfuscationDialog::setupUI()
{
    if (ui.labelTitle) // must be nullptr
        throw std::runtime_error(strprintf("%s: ui has already been initialized", __func__));

    this->setObjectName(QStringLiteral("MasternodeList")); // for CSS

    ui.labelTitle = new QLabel(this);
    ui.labelTitle->setObjectName(QStringLiteral("labelOverviewHeaderLeft")); // for CSS
    ui.labelTitle->setText(tr("OBFUSCATION"));
    ui.labelTitle->setMinimumSize(QSize(464, 60));
    QFont font;
    font.setPointSize(20);
    font.setBold(true);
    font.setWeight(75);
    ui.labelTitle->setFont(font);

    ui.labelStatus = new QLabel(this);
    ui.labelStatus->setText(tr("Status:"));

    ui.labelCompletion = new QLabel(this);
    ui.labelCompletion->setText(tr("Completion:"));

    ui.labelBalance = new QLabel(this);
    ui.labelBalance->setText(tr("Obfuscation Balance:"));

    ui.labelAmountRound = new QLabel(this);
    ui.labelAmountRound->setText(tr("Amount and Rounds:"));

    ui.labelDenom = new QLabel(this);
    ui.labelDenom->setText(tr("Submitted Denom:"));

    ui.btnStart = new QPushButton(this);
    ui.btnStart->setText(tr("Start Obfuscation"));

    ui.btnStop = new QPushButton(this);
    ui.btnStop->setText(tr("Stop Obfuscation"));

    ui.btnMix = new QPushButton(this);
    ui.btnMix->setText(tr("Try Mix"));

    ui.btnReset = new QPushButton(this);
    ui.btnReset->setText(tr("Reset"));

    connect(ui.btnStart, SIGNAL (released()), this, SLOT (onStart()));
    connect(ui.btnStop, SIGNAL (released()), this, SLOT (onStop()));
    connect(ui.btnMix, SIGNAL (released()), this, SLOT (onMix()));
    connect(ui.btnReset, SIGNAL (released()), this, SLOT (onReset()));
}

void ObfuscationDialog::setupLayout()
{
    QHBoxLayout *layoutButtons = new QHBoxLayout;
    layoutButtons->addWidget(ui.btnStart);
    layoutButtons->addWidget(ui.btnStop);
    layoutButtons->addWidget(ui.btnMix);
    layoutButtons->addWidget(ui.btnReset);
    //layoutButtons->addItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Fixed));

    QVBoxLayout *layoutTop = new QVBoxLayout;
    layoutTop->addWidget(ui.labelStatus);
    layoutTop->addWidget(ui.labelCompletion);
    layoutTop->addWidget(ui.labelBalance);
    layoutTop->addWidget(ui.labelAmountRound);
    layoutTop->addWidget(ui.labelDenom);
    layoutTop->addLayout(layoutButtons);

    // Combine all
    QVBoxLayout *layoutMain = new QVBoxLayout;
    layoutMain->setContentsMargins(30, 10, 15, 15);
    layoutMain->addWidget(ui.labelTitle);
    layoutMain->addLayout(layoutTop);
    this->setLayout(layoutMain);
}

void ObfuscationDialog::updateUI()
{}

void ObfuscationDialog::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);
    updateUI();
}

void ObfuscationDialog::setModel(ObfuscationModelPtr model)
{
    model_ = model;
    updateUI();
}

void ObfuscationDialog::onStart()
{}

void ObfuscationDialog::onStop()
{}

void ObfuscationDialog::onMix()
{}

void ObfuscationDialog::onReset()
{}
