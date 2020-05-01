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
String _read(String s)
{
	char * _word = "New file";
	long lSize;
	char* path = "/sd/im01/";
	strcat(path, s->getUTF8Data());
    SDFileSystem sd(P0_21, P0_22, P0_23, P0_16, "sd");
	FILE *fp = fopen(path, "rb");
	
	// obtain file size:
	/*fseek (fp , 0 , SEEK_END);
	lSize = ftell(fp);
	rewind (fp);*/
	//FILE *fp = fopen((const char *)p , "rb");
	if (fp == NULL)
	{
        _word = "No file";
	}else{
		_word = "Yes File";
	}
	/*_word = (char*) malloc (sizeof(char)*lSize);
	size_t b_read = fread(_word, sizeof(char), lSize, fp);*/
	fclose(fp);
	
	/*if(b_read != 10)
	{
		_word = "no count";
	}else{
		_word = "count";
	}*/
	String str = mkString(_word, strlen(_word));
	free(_word);
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