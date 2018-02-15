﻿#include "aboutdialog.h"
#include "ui_aboutdialog.h"
#include "splayer-version.h"

#include <QFile>
#include <QTextStream>

AboutDialog::AboutDialog(QString lang, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);

    ui->compilerText->setText(compilerText_HTML());
    ui->aboutText->setText(aboutText_HTML());
    ui->creditsText->setText(creditsText_HTML());
    ui->licenseText->setText(licenseText_HTML(lang));

    connect(ui->closeButton, SIGNAL(clicked()),
            this, SLOT(close()));
}

AboutDialog::~AboutDialog()
{
    delete ui;
}

void AboutDialog::about(QString lang, QWidget *parent)
{
    AboutDialog dialog(lang, parent);
    dialog.exec();
}

QString AboutDialog::compilerText_HTML()
{
#ifndef CI
    static QString text = QString::fromLatin1("<h2>%1</h2>\n<h3>%2: %3</h3>\n<h3>%4: %5</h3>\n<h3>%6: %7</h3>")
                     .arg(tr("SPlayer"))
                     .arg(tr("Version")).arg(QString::fromStdWString(SPLAYER_VERSION_STR))
                     .arg(tr("Architecture")).arg(QString::fromStdWString(SPLAYER_ARCH_STR))
                     .arg(tr("Compiler")).arg(QString::fromLatin1("MSVC ") + QString::number(_MSC_FULL_VER));
#else
    static QString text = QString::fromLatin1("<h2>%1</h2>\n<p><b>%2</b>: %3\n<b>%4</b>: %5\n<b>%6</b>: %7\n<b>%8</b>: %9\n<b>%10</b>: %11\n<b>%12</b>: %13\n<b>%14</b>: %15\n<b>%16</b>: %17</p>")
                     .arg(tr("SPlayer"))
                     .arg(tr("Version")).arg(QString::fromStdWString(SPLAYER_VERSION_STR))
                     .arg(tr("Commit ID")).arg(QString::fromStdWString(SPLAYER_COMMIT_ID_STR))
                     .arg(tr("Commit author")).arg(QString::fromStdWString(SPLAYER_COMMIT_AUTHOR_STR))
                     .arg(tr("Commit author e-mail")).arg(QString::fromStdWString(SPLAYER_COMMIT_AUTHOR_EMAIL_STR))
                     .arg(tr("Commit time")).arg(QString::fromStdWString(SPLAYER_COMMIT_TIMESTAMP_STR))
                     .arg(tr("Commit message")).arg(QString::fromStdWString(SPLAYER_COMMIT_MESSAGE_STR))
                     .arg(tr("Architecture")).arg(QString::fromStdWString(SPLAYER_ARCH_STR))
                     .arg(tr("Compiler")).arg(QString::fromLatin1("MSVC ") + QString::number(_MSC_FULL_VER));
#endif
    return text;
}

QString AboutDialog::compilerText_PlainText()
{
    return compilerText_HTML().remove(QRegExp(QStringLiteral("<[^>]*>")));
}

QString AboutDialog::aboutText_HTML()
{
    static QString text = tr("<p><b>SPlayer</b> is a multimedia player based on "
                          "<b>libmpv</b> and <b>Qt</b> for Microsoft Windows 7+.</p>\n"
                          "<p>People should know that <b>SPlayer</b> is a fork of "
                          "<a href='https://github.com/u8sand/Baka-MPlayer'><b>Baka MPlayer</b></a>. "
                          "<b>Baka MPlayer</b> is a free and open source, cross-platform, <b>libmpv</b> "
                          "based multimedia player. Its simple design reflects the idea for an uncluttered, "
                          "simple, and enjoyable environment for watching tv shows. "
                          "Thanks to the great work of <b>Baka MPlayer</b>'s original developers. "
                          "Without their hard work, there won't be <b>SPlayer</b> anymore. "
                          "I really appreciate <a href='https://github.com/u8sand'><b>u8sand</b></a> "
                          "and his team.</p>\n"
                          "<p>GitHub repository: <a href='https://github.com/wangwenx190/SPlayer'>"
                          "https://github.com/wangwenx190/SPlayer</a></p>");
    return text;
}

QString AboutDialog::aboutText_PlainText()
{
    return aboutText_HTML().remove(QRegExp(QStringLiteral("<[^>]*>")));
}

QString AboutDialog::creditsText_HTML()
{
    static QString text = tr("<h2>mpv - video player based on MPlayer/mplayer2</h2>\n<h3>Contributors</h3>\n"
                             "<p>pigoz, haasn, kevmitch, rossy, wiiaboo, divVerent, giselher, lachs0r, "
                             "Kovensky, Akemi, Argon-, ChrisK2, ghedo, mathstuf, olifre, xylosper, ubitux, "
                             "atomnuker, qmega, tmm1, bjin, philipl, pavelxdd, shdown, avih, thebombzen, rr-, "
                             "dubhater, rrooij, torque, jeeb, sfan5, igv, grigorig, frau, jon-y, TimothyGu, "
                             "maniak1349, richardpl, Nyx0uf, czarkoff, Coacher, qyot27, Cloudef, linkmauve, "
                             "DanOscarsson, CounterPillow, henry0312, marcan, fhvwy, jaimeMF, SirCmpwn, xantoz, "
                             "rcombs, Nikoli, percontation, AoD314, otommod, ahodesuka, LongChair, CyberShadow, "
                             "michaelforney, sCreami, medhefgo, MadFishTheOne, rozhuk-im, shinchiro, TheAMM, "
                             "Gusar321, elenril, wrl, mixi, Themaister, lu-zero, pa4, markun, maletor, quilloss, "
                             "PombeirP, mikaoP, ricardomv, wsldankers, ion1, chneukirchen, ncopa, agiz, "
                             "viveksjain, hroncok, andre-d, Bilalh, jozzse, elevengu, MoSal, foo86, ryanmjacobs, "
                             "vitorgalvao, Shudouken, zekica, c-14, eworm-de</p>\n"
                             "<h2>Baka MPlayer</h2>\n<h3>Contributors</h3>\n"
                             "<p>u8sand, godly-devotion, amazingfate, epitron, AlfredoRamos, jbeich, rrooij, "
                             "samdx, ErikDavison, muzena, FrankHB, stryaponoff, starks, theChaosCoder, luigino, "
                             "tehcereal, redranamber, wb9688, arabuli, jqs7, Reboare, yiip87, suhr</p>\n"
                             "<h3>Material Design icons</h3>\n<p>Google</p>\n"
                             "<h3>Noto Sans fonts</h3>\n<p>Google</p>\n"
                             "<h3>Retro Cassette image</h3>\n<p>Lukas Troup</p>\n"
                             "<h3>Gesture icons</h3>\n<p>Jeff Portaro</p>\n"
                             "<h3>Download icon</h3>\n<p>Sasha Mescheryakov</p>\n"
                             "<h3>Translations</h3>\n<h4>Chinese</h4>\n<p>amazingfate, Antares95</p>\n"
                             "<h4>Croatian</h4>\n<p>gogo</p>\n<h4>Dutch</h4>\n<p>robin007bond, wb9688</p>\n"
                             "<h4>French</h4>\n<p>chapouvalpin</p>\n<h4>Georgian</h4>\n<p>arabuli</p>\n"
                             "<h4>German</h4>\n<p>yiip87</p>\n<h4>Italian</h4>\n<p>Aloysius</p>\n"
                             "<h4>Korean</h4>\n<p>godly-devotion</p>\n<h4>Portuguese</h4>\n<p>u8sand</p>\n"
                             "<h4>Russian</h4>\n<p>suhr</p>\n<h4>Spanish</h4>\n<p>Alfredo Ramos</p>\n"
                             "<h2>SPlayer</h2>\n<h3>Contributors</h3>\n<p>wangwenx190</p>\n"
                             "<h3>SPlayer icon</h3>\n<p>ninja emotion-icons <a href='https://roundicons.com/'>"
                             "roundicons</a></p>\n<h3>Translations</h3>\n<h4>Simplified Chinese</h4>\n"
                             "<p>amazingfate, Antares95, wangwenx190</p>");
    return text;
}

QString AboutDialog::creditsText_PlainText()
{
    return creditsText_HTML().remove(QRegExp(QStringLiteral("<[^>]*>")));
}

QString AboutDialog::licenseText_HTML(QString lang)
{
    static QString text;
    QString l(lang);
    if (lang == QString::fromLatin1("auto") || lang == QString::fromLatin1("en_US")
            || lang == QString::fromLatin1("en_UK") || lang == QString::fromLatin1("C"))
    {
        l = QString::fromLatin1("en");
    }
    QString filePath = QString::fromLatin1(":/licenses/gpl-3.0.") + l + QString::fromLatin1(".html");
    QFile licenseFile(filePath);
    if (licenseFile.exists())
    {
        if (licenseFile.open(QFile::ReadOnly | QFile::Text))
        {
            QTextStream ts(&licenseFile);
            text = ts.readAll();
            licenseFile.close();
            return text;
        }
    }
    return licenseText_HTML(QString::fromLatin1("en"));
}

QString AboutDialog::licenseText_PlainText()
{
    return licenseText_HTML().remove(QRegExp(QStringLiteral("<[^>]*>")));
}