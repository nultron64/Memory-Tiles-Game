#include "icons.hpp"

Texture2D icons[32];

int InitializeIcons()
{
    char imgName[100];
    for(int i=0; i<32; i++)
    {
        sprintf(imgName, "icons/%d.png", i+1);
        Image img = LoadImage(imgName);
        if (img.data==nullptr) return -1;
        icons[i] = LoadTextureFromImage(img);

        UnloadImage(img);
    }
    return 0;
}