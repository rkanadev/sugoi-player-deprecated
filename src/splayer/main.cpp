﻿#include "ui/mainwindow.h"

#include <QApplication>
#include <QString>
#include <QFileInfo>
#include <QMimeDatabase>
#include <QIcon>

#include <locale.h>

#if defined(Q_OS_WIN)
#include <Windows.h>
#endif

#include "splayer-version.h"
#include "qtsingleapplication.h"
#include "util.h"
#include "winsparkle.h"
#include "fileassoc.h"

int main(int argc, char *argv[])
{
#ifndef _DEBUG
    qInstallMessageHandler(Util::messagesOutputToFile);
#endif

#if defined(Q_OS_WIN)
    FreeConsole();
#endif

    QtSingleApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QtSingleApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);

    QtSingleApplication::setApplicationName(QString::fromStdWString(SPLAYER_APP_NAME_STR));
    QtSingleApplication::setApplicationDisplayName(QString::fromStdWString(SPLAYER_APP_DISPLAY_NAME_STR));
    QtSingleApplication::setApplicationVersion(QString::fromStdWString(SPLAYER_VERSION_STR));
    QtSingleApplication::setOrganizationName(QString::fromStdWString(SPLAYER_COMPANY_NAME_STR));
    QtSingleApplication::setOrganizationDomain(QString::fromStdWString(SPLAYER_COMPANY_URL_STR));

    QtSingleApplication instance(QString::fromStdWString(SPLAYER_APP_MUTEX_STR), argc, argv);

    bool singleInstance = true;

    QStringList cmdline = instance.arguments();
    QString filePath = QString();

    if (cmdline.count() > 1)
    {
        for (int i = 1; i <= (cmdline.count() - 1); ++i)
        {
            if (cmdline.at(i) == QString::fromLatin1("--regall"))
            {
                FileAssoc fileAssoc;
                if (!fileAssoc.registerMediaFiles(FileAssoc::reg_type::ALL))
                {
                    return -1;
                }
                return 0;
            }
            else if (cmdline.at(i) == QString::fromLatin1("--regvideo"))
            {
                FileAssoc fileAssoc;
                if (!fileAssoc.registerMediaFiles(FileAssoc::reg_type::VIDEO_ONLY))
                {
                    return -1;
                }
                return 0;
            }
            else if (cmdline.at(i) == QString::fromLatin1("--regaudio"))
            {
                FileAssoc fileAssoc;
                if (!fileAssoc.registerMediaFiles(FileAssoc::reg_type::AUDIO_ONLY))
                {
                    return -1;
                }
                return 0;
            }
            else if (cmdline.at(i) == QString::fromLatin1("--unregall"))
            {
                FileAssoc fileAssoc;
                fileAssoc.unregisterMediaFiles(FileAssoc::reg_type::ALL);
                return 0;
            }
            else if (cmdline.at(i) == QString::fromLatin1("--unregvideo"))
            {
                FileAssoc fileAssoc;
                fileAssoc.unregisterMediaFiles(FileAssoc::reg_type::VIDEO_ONLY);
                return 0;
            }
            else if (cmdline.at(i) == QString::fromLatin1("--unregaudio"))
            {
                FileAssoc fileAssoc;
                fileAssoc.unregisterMediaFiles(FileAssoc::reg_type::AUDIO_ONLY);
                return 0;
            }
            else if (cmdline.at(i) == QString::fromLatin1("--newinstance"))
            {
                singleInstance = false;
            }
            else
            {
                QFileInfo fi(cmdline.at(i));
                if (fi.exists() && fi.isFile())
                {
                    QMimeDatabase mdb;
                    if (Util::supportedMimeTypes().contains(mdb.mimeTypeForFile(fi).name()))
                    {
                        filePath = cmdline.at(i);
                        break;
                    }
                }
            }
        }
    }

    if (singleInstance)
    {
        if (instance.sendMessage(filePath))
        {
            return 0;
        }
    }

    // Qt sets the locale in the QApplication constructor, but libmpv requires
    // the LC_NUMERIC category to be set to "C", so change it back.
    setlocale(LC_NUMERIC, "C");

    MainWindow window;
    window.setWindowIcon(QIcon(":/images/splayer.svg"));
    window.show();
    window.Load(filePath);

    MainWindow *mainWindow = &window;

    instance.setActivationWindow(&window, true);
    QObject::connect(&instance, &QtSingleApplication::messageReceived,
                     [=](const QString &newFilePath)
                     {
                         mainWindow->setPauseWhenMinimized(false);
                         mainWindow->openFileFromCmd(newFilePath);
                         mainWindow->setPauseWhenMinimized(true);
                     });

    HANDLE mutexHandle = CreateMutex(NULL, FALSE
                     , reinterpret_cast<const wchar_t *>(QString::fromStdWString(SPLAYER_APP_MUTEX_STR).utf16()));

    win_sparkle_set_appcast_url("https://raw.githubusercontent.com/wangwenx190/SPlayer/master/src/splayer/appcast.xml");
    win_sparkle_set_app_details(SPLAYER_COMPANY_NAME_STR, SPLAYER_APP_NAME_STR, SPLAYER_VERSION_STR);
    win_sparkle_set_automatic_check_for_updates(1);
    win_sparkle_set_lang(window.getLang().toUtf8().constData());
    win_sparkle_init();
    win_sparkle_check_update_without_ui();

    int ret = instance.exec();

    mainWindow = nullptr;

    win_sparkle_cleanup();

    CloseHandle(mutexHandle);

    return ret;
}