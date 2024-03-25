// ----------------------------------------------
// Copyright (c) 2022-2024 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#include "Explorer.h"

#include <Windows.h>
#include <ShObjIdl.h>

#include <filesystem>

namespace MakeshiftEditor::Util
{

	std::string Explorer::getFilePath()
	{

        HRESULT hr = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);

        if (SUCCEEDED(hr)) {
            IFileOpenDialog* pFileDialog;
            hr = CoCreateInstance(CLSID_FileOpenDialog, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pFileDialog));

            if (SUCCEEDED(hr)) {
                // Get the current working directory using std::filesystem
                std::filesystem::path currentPath = std::filesystem::current_path();

                // Convert the current path to a wide character string
                std::wstring currentPathStr = currentPath.wstring();

                // Create an IShellItem from the current path
                IShellItem* pFolder;
                hr = SHCreateItemFromParsingName(currentPathStr.c_str(), nullptr, IID_PPV_ARGS(&pFolder));

                if (SUCCEEDED(hr)) {
                    // Set the initial directory for the file dialog to the current working directory
                    hr = pFileDialog->SetFolder(pFolder);

                    if (SUCCEEDED(hr)) {
                        // Show the File Open dialog
                        hr = pFileDialog->Show(nullptr);

                        if (SUCCEEDED(hr)) {
                            IShellItem* pItem;
                            hr = pFileDialog->GetResult(&pItem);

                            if (SUCCEEDED(hr)) {
                                PWSTR pszFilePath;
                                hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

                                if (SUCCEEDED(hr)) {
                                    // Convert the wide character string to a regular string
                                    std::wstring wstrFilePath(pszFilePath);
                                    std::string filePath(wstrFilePath.begin(), wstrFilePath.end());

                                    CoTaskMemFree(pszFilePath);

                                    pItem->Release();
                                    pFolder->Release();
                                    pFileDialog->Release();
                                    CoUninitialize();

                                    // Return the selected file path
                                    return filePath;
                                }

                                pItem->Release();
                            }
                        }
                    }

                    pFolder->Release();
                }

                pFileDialog->Release();
            }

            CoUninitialize();
        }

        return ""; // Return an empty string if an error occurs
    }

    std::string Explorer::getRelativeFilePath()
    {
        std::filesystem::path absolute = getFilePath();

        return std::filesystem::relative(absolute, std::filesystem::current_path()).string();
    }

    std::string Explorer::getCreatedFilePath() 
    {
        HRESULT hr = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);

        if (SUCCEEDED(hr)) {
            IFileSaveDialog* pFileDialog;
            hr = CoCreateInstance(CLSID_FileSaveDialog, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pFileDialog));

            if (SUCCEEDED(hr)) {
                // Get the current working directory using std::filesystem
                std::filesystem::path currentPath = std::filesystem::current_path();

                // Convert the current path to a wide character string
                std::wstring currentPathStr = currentPath.wstring();

                // Create an IShellItem from the current path
                IShellItem* pFolder;
                hr = SHCreateItemFromParsingName(currentPathStr.c_str(), nullptr, IID_PPV_ARGS(&pFolder));

                if (SUCCEEDED(hr)) {
                    // Set the initial directory for the File Save dialog to the current working directory
                    hr = pFileDialog->SetFolder(pFolder);

                    if (SUCCEEDED(hr)) {
                        // Set the default file name
                        pFileDialog->SetFileName(L"Item.json");

                        // Show the File Save dialog
                        hr = pFileDialog->Show(nullptr);

                        if (SUCCEEDED(hr)) {
                            IShellItem* pItem;
                            hr = pFileDialog->GetResult(&pItem);

                            if (SUCCEEDED(hr)) {
                                PWSTR pszFilePath;
                                hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

                                if (SUCCEEDED(hr)) {
                                    // Convert the wide character string to a regular string
                                    std::wstring wstrFilePath(pszFilePath);
                                    std::string filePath(wstrFilePath.begin(), wstrFilePath.end());

                                    CoTaskMemFree(pszFilePath);

                                    pItem->Release();
                                    pFolder->Release();
                                    pFileDialog->Release();
                                    CoUninitialize();

                                    // Return the selected file path
                                    return filePath;
                                }

                                pItem->Release();
                            }
                        }
                    }

                    pFolder->Release();
                }

                pFileDialog->Release();
            }

            CoUninitialize();
        }

        return ""; // Return an empty string if an error occurs
    }

    std::string Explorer::getRelativeCreatedFilePath()
    {
        std::filesystem::path absolute = getCreatedFilePath();

        return std::filesystem::relative(absolute, std::filesystem::current_path()).string();
    }

    std::string Explorer::getFolderPath()
    {
        return std::string();
    }

    std::string Explorer::getRelativeFolderPath() 
    {
        HRESULT hr = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);

        if (SUCCEEDED(hr)) {
            IFileOpenDialog* pFolderDialog;
            hr = CoCreateInstance(CLSID_FileOpenDialog, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pFolderDialog));

            if (SUCCEEDED(hr)) {
                // Get the current working directory using std::filesystem
                std::filesystem::path currentPath =  std::filesystem::current_path();

                // Convert the current path to a wide character string
                std::wstring currentPathStr = currentPath.wstring();

                // Create an IShellItem from the current path
                IShellItem* pFolder;
                hr = SHCreateItemFromParsingName(currentPathStr.c_str(), nullptr, IID_PPV_ARGS(&pFolder));

                if (SUCCEEDED(hr)) {
                    // Set the initial directory for the Folder dialog to the current working directory
                    hr = pFolderDialog->SetFolder(pFolder);

                    if (SUCCEEDED(hr)) {
                        // Show the Folder Open dialog and configure it to select folders
                        DWORD flags;
                        hr = pFolderDialog->GetOptions(&flags);

                        if (SUCCEEDED(hr)) {
                            hr = pFolderDialog->SetOptions(flags | FOS_PICKFOLDERS);

                            if (SUCCEEDED(hr)) {
                                hr = pFolderDialog->Show(nullptr);

                                if (SUCCEEDED(hr)) {
                                    IShellItem* pItem;
                                    hr = pFolderDialog->GetResult(&pItem);

                                    if (SUCCEEDED(hr)) {
                                        PWSTR pszFolderPath;
                                        hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFolderPath);

                                        if (SUCCEEDED(hr)) {
                                            // Convert the wide character string to a regular string
                                            std::wstring wstrFolderPath(pszFolderPath);
                                            std::string folderPath(wstrFolderPath.begin(), wstrFolderPath.end());

                                            CoTaskMemFree(pszFolderPath);

                                            pItem->Release();
                                            pFolder->Release();
                                            pFolderDialog->Release();
                                            CoUninitialize();

                                            // Return the selected folder path
                                            return folderPath;
                                        }

                                        pItem->Release();
                                    }
                                }
                            }
                        }
                    }

                    pFolder->Release();
                }

                pFolderDialog->Release();
            }

            CoUninitialize();
        }

        return ""; // Return an empty string if an error occurs
    }

}