/* Copyright 2013-2019 MultiMC Contributors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "AboutDialog.h"
#include "ui_AboutDialog.h"
#include <QIcon>
#include "MultiMC.h"
#include "BuildConfig.h"

#include <net/NetJob.h>

#include "HoeDown.h"

namespace {
// Credits
// This is a hack, but I can't think of a better way to do this easily without screwing with QTextDocument...
QString getCreditsHtml(QStringList patrons)
{
    QString patronsHeading = QObject::tr("Patrons", "About Credits");
    QString output;
    QTextStream stream(&output);
    stream << "<center>\n";
    // TODO: possibly retrieve from git history at build time?
    stream << "<h3>" << QObject::tr("MoonMC Developers", "About Credits") << "</h3>\n";
    stream << "<p>Flyer737</p>\n";
    stream << "<br />\n";

    /*stream << "<h3>" << QObject::tr("With thanks to", "About Credits") << "</h3>\n";
    stream << "<p>Orochimarufan &lt;<a href='mailto:orochimarufan.x3@gmail.com'>orochimarufan.x3@gmail.com</a>&gt;</p>\n";
    stream << "<p>TakSuyu &lt;<a href='mailto:taksuyu@gmail.com'>taksuyu@gmail.com</a>&gt;</p>\n";
    stream << "<p>Kilobyte &lt;<a href='mailto:stiepen22@gmx.de'>stiepen22@gmx.de</a>&gt;</p>\n";
    stream << "<p>Rootbear75 &lt;<a href='https://twitter.com/rootbear75'>@rootbear75</a>&gt;</p>\n";
    stream << "<p>Zeker Zhayard &lt;<a href='https://twitter.com/zeker_zhayard'>@Zeker_Zhayard</a>&gt;</p>\n";
    stream << "<br />\n";*/

    if(!patrons.isEmpty()) {
        stream << "<h3>" << QObject::tr("Patrons", "About Credits") << "</h3>\n";
        for (QString patron : patrons)
        {
            stream << "<p>" << patron << "</p>\n";
        }
    }
    stream << "</center>\n";
    return output;
}

QString getLicenseHtml()
{
    HoeDown hoedown;
    QFile dataFile(":/documents/COPYING.md");
    dataFile.open(QIODevice::ReadOnly);
    QString output = hoedown.process(dataFile.readAll());
    return output;
}

}

AboutDialog::AboutDialog(QWidget *parent) : QDialog(parent), ui(new Ui::AboutDialog)
{
    ui->setupUi(this);

    QString chtml = getCreditsHtml(QStringList());
    ui->creditsText->setHtml(chtml);

    QString lhtml = getLicenseHtml();
    ui->licenseText->setHtml(lhtml);

    ui->urlLabel->setOpenExternalLinks(true);

    ui->icon->setPixmap(MMC->getThemedIcon("logo").pixmap(64));
    ui->title->setText("MoonMC v1.1");

    ui->versionLabel->setText(tr("Version") +": 1.1");
    //ui->platformLabel->setText(tr("Platform") +": " + BuildConfig.BUILD_PLATFORM);

    if (BuildConfig.VERSION_BUILD >= 0)
        ui->buildNumLabel->setText(tr("Build Number") +": " + QString::number(BuildConfig.VERSION_BUILD));
    else
        ui->buildNumLabel->setVisible(false);

    /*if (!BuildConfig.VERSION_CHANNEL.isEmpty())
        ui->channelLabel->setText(tr("Channel") +": " + BuildConfig.VERSION_CHANNEL);
    else
        ui->channelLabel->setVisible(false);*/

    ui->redistributionText->setHtml(tr(
"<p>Thank you for downloading and trying this out!</p>"
    ));

    connect(ui->closeButton, SIGNAL(clicked()), SLOT(close()));

    connect(ui->aboutQt, &QPushButton::clicked, &QApplication::aboutQt);

    loadPatronList();
}

AboutDialog::~AboutDialog()
{
    delete ui;
}

void AboutDialog::loadPatronList()
{
    netJob.reset(new NetJob("Patreon Patron List"));
    netJob->addNetAction(Net::Download::makeByteArray(QUrl("https://files.multimc.org/patrons.txt"), &dataSink));
    connect(netJob.get(), &NetJob::succeeded, this, &AboutDialog::patronListLoaded);
    netJob->start();
}

void AboutDialog::patronListLoaded()
{
    QString patronListStr(dataSink);
    dataSink.clear();
    QString html = getCreditsHtml(patronListStr.split("\n", QString::SkipEmptyParts));
    ui->creditsText->setHtml(html);
}

