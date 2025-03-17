#include <windows.h>
#include <stdio.h>

int main() {
    HKEY hKey;
    DWORD index = 0;
    DWORD subkeyLength = 255;
    char subkeyName[255];
    if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, "SYSTEM\\CurrentControlSet\\Services", 0, KEY_READ, &hKey) == ERROR_SUCCESS) 
    {
        while (RegEnumKeyExA(hKey, index++, subkeyName, &subkeyLength, NULL, NULL, NULL, NULL) == ERROR_SUCCESS)
        {
            HKEY subkey;
            if (RegOpenKeyExA(hKey, subkeyName, 0, KEY_READ, &subkey) == ERROR_SUCCESS) 
            {
                DWORD valueSize = 255;
                char imagePath[255];

                if (RegQueryValueExA(subkey, "ImagePath", NULL, NULL, (LPBYTE)imagePath, &valueSize) == ERROR_SUCCESS) 
                {
                    printf("%s\nImagePath: %s\n\n", subkeyName, imagePath);
                }

                RegCloseKey(subkey);
            }
            subkeyLength = 255;
        }
        RegCloseKey(hKey);
    }
    else 
    {
        printf("Eroare\n");
        return 1;
    }

    return 0;
}