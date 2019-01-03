#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <pthread.h>

using namespace std;

short threadCount = 0;

void *playSound(void *threadid)
{
    system("canberra-gtk-play -f laptop.ogg");
    threadCount--;
    pthread_exit(NULL);
}

void *playSound2(void *threadid)
{
    system("canberra-gtk-play -f spacebarkey.ogg");
    threadCount--;
    pthread_exit(NULL);
}

void *playSound3(void *threadid)
{
    system("canberra-gtk-play -f deletekey.ogg");
    threadCount--;
    pthread_exit(NULL);
}

int main()
{

    FILE *fin;
    char buffer[1000];
    if(!(fin = popen("echo \'5 6 7 8 9 10 11 14 15 17 18\' | xargs -P0 -n1 xinput test","r")))
        return 1;
    pthread_t threads[1000];
    while(fgets(buffer, sizeof(buffer), fin)!=NULL)
    {
        //space is 65 backspace is 22
        string str(buffer);
        if(str.find("press") != string::npos)
        {
            if(str.find("65") != string::npos)
                pthread_create(&threads[++threadCount], NULL, playSound2, NULL);
            else if(str.find("22") != string::npos)
                pthread_create(&threads[++threadCount], NULL, playSound3, NULL);
            else
                pthread_create(&threads[++threadCount], NULL, playSound, NULL);
            //cout << str << endl;
        }
        //memset(&buffer[0], 0, sizeof(buffer));
    }
    pclose(fin);
    return 0;
}
