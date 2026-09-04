[Setup]
AppName=Desktop Search
AppVersion=0.1.0
DefaultDirName={autopf}\Desktop Search
DefaultGroupName=Desktop Search
OutputBaseFilename=DesktopSearchSetup
ArchitecturesAllowed=x64compatible
ArchitecturesInstallIn64BitMode=x64compatible

[Files]
Source: "..\dist\DesktopSearch\*"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs

[Tasks]
Name: "desktopicon"; Description: "Create a desktop shortcut"; Flags: unchecked

[Icons]
Name: "{autoprograms}\Desktop Search"; Filename: "{app}\desktop-search-gui.exe"
Name: "{autodesktop}\Desktop Search"; Filename: "{app}\desktop-search-gui.exe"; Tasks: desktopicon

[Run]
Filename: "{app}\desktop-search-gui.exe"; Description: "Launch Desktop Search"; Flags: nowait postinstall skipifsilent

