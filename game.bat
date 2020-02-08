echo off

REM Will listen to 7777 by default but will automatically tick the server port up if another client is listening
START "" "C:\Program Files\Epic Games\UE_4.17\Engine\Binaries\Win64\UE4Editor.exe" "C:\Users\drach\Documents\Unreal Projects\PuzzlePlatforms\PuzzlePlatforms.uproject" /Game/Lobby -game -log
