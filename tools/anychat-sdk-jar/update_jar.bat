@echo off
@echo.

set curpath=%~dp0
set srcpath=%curpath%\..\..\..\anychatsamples\android\src2.0
copy %curpath%\bin\anychat-sdk.jar %srcpath%\HelloAnyChat\libs\.
copy %curpath%\bin\anychat-sdk.jar %srcpath%\HelloAnyChatCloud\app\src\main\jniLibs\.
copy %curpath%\bin\anychat-sdk.jar %srcpath%\AnyChatSelfRecord\libs\.
copy %curpath%\bin\anychat-sdk.jar %srcpath%\AnyChatQueuePlus\libs\.
copy %curpath%\bin\anychat-sdk.jar %srcpath%\AnyChatQueue\libs\.
copy %curpath%\bin\anychat-sdk.jar %srcpath%\AnyChatFeatures\libs\.
copy %curpath%\bin\anychat-sdk.jar %srcpath%\AnyChatCallCenter\libs\.

pause
