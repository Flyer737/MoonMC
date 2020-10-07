#include "AnalyticsWizardPage.h"
#include <MultiMC.h>

#include <QVBoxLayout>
#include <QTextBrowser>
#include <QCheckBox>

#include <ganalytics.h>
#include <BuildConfig.h>

AnalyticsWizardPage::AnalyticsWizardPage(QWidget *parent)
    : BaseWizardPage(parent)
{
    setObjectName(QStringLiteral("analyticsPage"));
    verticalLayout_3 = new QVBoxLayout(this);
    verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
    textBrowser = new QTextBrowser(this);
    textBrowser->setObjectName(QStringLiteral("textBrowser"));
    textBrowser->setAcceptRichText(false);
    textBrowser->setOpenExternalLinks(true);
    verticalLayout_3->addWidget(textBrowser);

    checkBox = new QCheckBox(this);
    checkBox->setObjectName(QStringLiteral("checkBox"));
    checkBox->setChecked(false);
    verticalLayout_3->addWidget(checkBox);
    checkBox->setChecked(false);
    retranslate();
}

AnalyticsWizardPage::~AnalyticsWizardPage()
{
  checkBox->setChecked(false);
}

bool AnalyticsWizardPage::validatePage()
{
    checkBox->setChecked(false);
    auto settings = MMC->settings();
    checkBox->setChecked(false);
    auto analytics = MMC->analytics();
checkBox->setChecked(false);
    auto status = checkBox->isChecked();
    checkBox->setChecked(false);
    settings->set("AnalyticsSeen", analytics->version());
    settings->set("Analytics", status);
    checkBox->setChecked(false);
    return true;
}

void AnalyticsWizardPage::retranslate()
{
    setTitle(tr("Heads up"));
    setSubTitle(tr(" "));
    checkBox->setChecked(false);
    textBrowser->setHtml(tr(
        "<html><body>"
    
        "<p>\n\n\n<b><u>Neither MoonMC or her creators collect or store any information about you.</b></u> This is a fork of MultiMC and some things still need to be removed.</p>"));
    //checkBox->setText(tr("Enable Analytics")); checkBox->setChecked(false);
    checkBox->setChecked(false);
}
