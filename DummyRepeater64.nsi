;NSIS Modern User Interface
;Repeater install script
;Written by Jonathan Naylor

;--------------------------------
;Include Modern UI

  !include "MUI2.nsh"

;--------------------------------
;Configuration

  ;General
  Name "DummyRepeater 20180510"
  OutFile "DummyRepeater64-20180510.exe"

  ;Folder selection page
  InstallDir "$PROGRAMFILES64\Dummy Repeater"
 
   ;Request application privileges for Windows Vista
  RequestExecutionLevel admin
 
;--------------------------------
;Interface Settings

  !define MUI_ABORTWARNING

;--------------------------------
;Pages

  !insertmacro MUI_PAGE_LICENSE "COPYING.txt"
  !insertmacro MUI_PAGE_DIRECTORY
  !insertmacro MUI_PAGE_INSTFILES
  !insertmacro MUI_UNPAGE_CONFIRM
  !insertmacro MUI_UNPAGE_INSTFILES
  
;--------------------------------
;Languages
 
  !insertmacro MUI_LANGUAGE "English"

;--------------------------------
;Installer Sections

Section "Repeater Program Files" SecProgram

  SetOutPath "$INSTDIR"

  File "x64\Release\DummyRepeater.exe"
  File "..\portaudio\build\msvc\x64\Release\portaudio_x64.dll"
  File "C:\wxWidgets-3.0.4\lib\vc_x64_dll\wxbase30u_vc_x64_custom.dll"
  File "C:\wxWidgets-3.0.4\lib\vc_x64_dll\wxmsw30u_adv_vc_x64_custom.dll"
  File "C:\wxWidgets-3.0.4\lib\vc_x64_dll\wxmsw30u_core_vc_x64_custom.dll"
  File "COPYING.txt"
  File "CHANGES.txt"

  ;Create start menu entry
  CreateDirectory "$SMPROGRAMS\Dummy Repeater"
  CreateShortCut "$SMPROGRAMS\Dummy Repeater\Dummy Repeater.lnk"           "$INSTDIR\DummyRepeater.exe"
  CreateShortCut "$SMPROGRAMS\Dummy Repeater\Licence.lnk"                  "$INSTDIR\COPYING.txt"
  CreateShortCut "$SMPROGRAMS\Dummy Repeater\Changes.lnk"                  "$INSTDIR\CHANGES.txt"
  CreateShortCut "$SMPROGRAMS\Dummy Repeater\Uninstall.lnk"                "$INSTDIR\Uninstall.exe"

  ;Create uninstaller
  WriteUninstaller "$INSTDIR\Uninstall.exe"

SectionEnd

;--------------------------------
;Uninstaller Section

Section "Uninstall"

  Delete "$INSTDIR\*.*"
  RMDir  "$INSTDIR"

  Delete "$SMPROGRAMS\Dummy Repeater\*.*"
  RMDir  "$SMPROGRAMS\Dummy Repeater"

  DeleteRegKey /ifempty HKCU "Software\G4KLX\Dummy Repeater"

SectionEnd
