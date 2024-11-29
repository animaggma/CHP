@echo off
:menu
cls
echo ===================================
echo       Windows Utility Menu
echo ===================================
echo 1. Display IPv4 and IPv6 addresses
echo 2. Perform Traceroute
echo 3. Get IP address from DNS name
echo 4. Encrypt text (External tool required)
echo 5. Decrypt text (External tool required)
echo 6. Encrypt file (External tool required)
echo 7. Decrypt file (External tool required)
echo 8. Compress file (External tool required)
echo 9. Decompress file (External tool required)
echo 10. Calculate hash value (MD5/SHA256)
echo 11. Calculate file size
echo 12. Count lines in file
echo 0. Exit
echo ===================================
set /p choice="Select an option: "

if "%choice%"=="1" goto get_ip
if "%choice%"=="2" goto traceroute
if "%choice%"=="3" goto resolve_dns
if "%choice%"=="4" goto encrypt_text
if "%choice%"=="5" goto decrypt_text
if "%choice%"=="6" goto encrypt_file
if "%choice%"=="7" goto decrypt_file
if "%choice%"=="8" goto compress_file
if "%choice%"=="9" goto decompress_file
if "%choice%"=="10" goto hash_value
if "%choice%"=="11" goto calculate_size
if "%choice%"=="12" goto count_lines
if "%choice%"=="0" goto exit
goto menu

:get_ip
ipconfig | findstr "IPv4" 
ipconfig | findstr "IPv6"
pause
goto menu

:traceroute
set /p target="Enter the hostname or IP address: "
tracert %target%
pause
goto menu

:resolve_dns
set /p dns_name="Enter the DNS name: "
nslookup %dns_name%
pause
goto menu

:encrypt_text
set /p text="Enter text to encrypt: "
echo Blowfish and Caesar encryption is not supported natively.
echo Use external tools or Python for implementation.
pause
goto menu

:decrypt_text
set /p text="Enter text to decrypt: "
echo Blowfish and Caesar decryption is not supported natively.
echo Use external tools or Python for implementation.
pause
goto menu

:encrypt_file
set /p file="Enter the file path to encrypt: "
echo %file%
echo File encryption requires external tools.
pause
goto menu

:decrypt_file
set /p file="Enter the file path to decrypt: "
echo File decryption requires external tools.
pause
goto menu

:compress_file
set /p file="Enter the file path to compress: "
echo LZ77 compression requires external tools or scripts.
pause
goto menu

:decompress_file
set /p file="Enter the file path to decompress: "
echo LZ77 decompression requires external tools or scripts.
pause
goto menu

:hash_value
set /p input="Enter text or file path to calculate hash: "
echo Calculate Hash Value with MD5. Result in MD5-%input% file 
certutil -hashfile %input% MD5 > MD5-%input%
echo Calculate Hash Value with SHA256. Result in SHA256-%input% file 
certutil -hashfile %input% SHA256 > SHA256-%input%
pause
goto menu

:calculate_size
set /p file="Enter the file path to calculate size: "
for %%A in (%file%) do (
    echo File size of %%A: %%~zA bytes
)
pause
goto menu

:count_lines
set /p file="Enter the file path to count lines: "
find /c /v "" %file%
pause
goto menu

:exit
echo Exiting... Goodbye!
