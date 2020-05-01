#include "pxt.h"
#include "mbed.h"
#include "SDFileSystem.h"

namespace im01
{
//%
void _mkdir(String s)
{
    SDFileSystem sd(P0_21, P0_22, P0_23, P0_16, "sd");
    mkdir((const char *)s->getUTF8Data(), 0777);
}

//%
void _remove(String s)
{
    SDFileSystem sd(P0_21, P0_22, P0_23, P0_16, "sd");
    remove((const char *)s->getUTF8Data());
}

//%
bool _file(String s, String v, String x)
{
    SDFileSystem sd(P0_21, P0_22, P0_23, P0_16, "sd");
    FILE *fp = fopen((const char *)s->getUTF8Data(), (const char *)x->getUTF8Data());
    if (fp == NULL)
        return false;

    fprintf(fp, (const char *)v->getUTF8Data());
    fclose(fp);
    return true;
}

//%
String _read()
{
	char * _word = "hello";
	int len = sizeof(_word);
    SDFileSystem sd(P0_21, P0_22, P0_23, P0_16, "sd");
	//FILE *fp = fopen((const char *)s->getUTF8Data(), (const char *)x->getUTF8Data());
	//FILE *fp = fopen("/sd/im01/log.txt", "rb");
	//return mkString(_word, len);
	
	String str = mkString(_word, strlen(_word));
	return str;
}

//%
String _readFile()
{
	char * _word = "hello";
	
	String str = mkString(_word, strlen(_word));
	return str;
}

} // namespace im01