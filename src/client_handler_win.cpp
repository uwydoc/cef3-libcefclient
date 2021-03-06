// Copyright (c) 2011 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#include "client_handler_impl.h"

#include <string>
#include <windows.h>
#include <shlobj.h>

#include <include/cef_browser.h>
#include <include/cef_frame.h>

#include "client_resource.h"

void ClientHandlerImpl::SendNotification(NotificationType type)
{
    UINT id;
    switch (type) {
    case NOTIFY_CONSOLE_MESSAGE:
        id = ID_WARN_CONSOLEMESSAGE;
        break;
    case NOTIFY_DOWNLOAD_COMPLETE:
        id = ID_WARN_DOWNLOADCOMPLETE;
        break;
    case NOTIFY_DOWNLOAD_ERROR:
        id = ID_WARN_DOWNLOADERROR;
        break;
    default:
        return;
    }
    PostMessage(m_MainHwnd, WM_COMMAND, id, 0);
}

std::string ClientHandlerImpl::GetDownloadPath(const std::string& file_name)
{
    std::string path;
#ifdef OS_WIN
    TCHAR szFolderPath[MAX_PATH];
    // Save the file in the user's "My Documents" folder.
    if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_PERSONAL | CSIDL_FLAG_CREATE,
                                  NULL, 0, szFolderPath))) {
        path = CefString(szFolderPath);
        path += "\\" + file_name;
    }
#endif
    return path;
}
