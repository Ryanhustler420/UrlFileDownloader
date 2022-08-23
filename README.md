# RaisehandForAdminQt

`AppId{{E7EA394D-F9AC-4475-AA7A-2202E7AEFF98}` -> use this appId for every new release

##### Steps to follow for new release

- Make changes to the application
- Delete old release build folder form system
- Run build release of the application
- Run `windeployqt.exe .` on the release folder
- Bring all the files to `Desktop` for ease access of inno setup
- Run the executable to see if everything is working as expected
- You can use `Resource Hacker` to change the setup.exe file image [optional]
- Create Innosetup script wizard with `icon, files, folders, license, setup-23.8.2022.exe`
- Install on the local system to see if everything is working as expected
- Upload the setup to mediafire
- Upload the link of mediafire with release changelog to /release page of the site and on home page too <br />`[mention the version number during upload of new release]`
- Keep a seperate copy on the disk **[optional]**

```iss

; Application name:
; Url File Downloader

; Application version:
; 23.08.2022a

; Application publisher:
; Raisehand Software Private Limited

; Application website:
; https://www.raisehand.software/

; Application destination base folder:
; Program Files folder

; Application folder name:
; Url File Downloader
; [x] Allow user to change the application folder

; Application main executable file:
; C:\Users\Raisehand\Desktop\release\UrlFileDownloader.exe
; [x] Allow user to start the application after Setup has finished

; Select all the folders and edit the path and add DESTINATION SUBFOLDER same as choosen folder name
; Select all the files except .exe file

; [x] Associate a file type to main executable
; Application file type name:
; UrlFileDownloader File

; Application file type extension:
; .exe

; [x] Create a shortcut to the main executable in the Start Menu Programs folder
; Other shortcut to the main executable:
; [x] Allow user to create a desktop shortcut

; Application Documentation
; - [Optional]

; Install mode:
; (x) Administrative install mode (install for all users)
; ( ) Non Administrative install mode (install for current user only)
; [ ] Allow user to override the install mode via the command line
; [ ] Ask the user to choose the install mode at startup

; Setup Language
; [x] English

; Costom compiler output folder:
; C:\Users\Raisehand\Desktop\release\setup

; Compiler output base file name:
; setup-23.08.2022a

; Custom Setup icon file:
; C:\Users\Raisehand\Desktop\favicon.ico

; [x] Yes, use #define compiler directive

; Finish

; Replace AppId with above mention one. [IMPORTANT]
; Compile and Save the script to anywhere since next time we'll create new script with old AppID

```
