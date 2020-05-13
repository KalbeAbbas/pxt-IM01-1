#include "pxt.h"
#include "mbed.h"
#include "SDFileSystem.h"

namespace im01
{
	
long ptr_position = 0;
	
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
	char * _word;
	char* error_no_file = "ERROR! NO FILE";
	char* cant_read_file = "ERROR! CANT READ FILE";
	//char* path = "/sd/im01/";
	long lSize;
	size_t b_read;
	
    SDFileSystem sd(P0_21, P0_22, P0_23, P0_16, "sd");
	FILE *fp = fopen((const char *)s->getUTF8Data(), "rb");
	
	if (fp == NULL)
	{
        return mkString(error_no_file, strlen(error_no_file));
	}else{
		
	// obtain file size:
	fseek (fp , 0 , SEEK_END);
	lSize = ftell(fp);
	rewind (fp);
	
	_word = (char*) malloc (sizeof(char)*lSize);
	b_read = fread(_word, sizeof(char), lSize, fp);
	
	fclose(fp);
	}
	
	if(b_read != lSize)
	{
        return mkString(cant_read_file, strlen(cant_read_file));
	}
	
	String str = mkString(_word, strlen(_word));
	
	free(_word);
	return str;
}


//%
String _readBytes(String s, int bytes, bool cont)
{
	char * _word;
	char* error_no_file = "ERROR! NO FILE";
	char* cant_read_file = "ERROR! CANT READ FILE";
	long lSize;
	size_t b_read;
	
	const char * one_char = s->getUTF8DataAt(10);
	
	lSize = bytes;
	
    SDFileSystem sd(P0_21, P0_22, P0_23, P0_16, "sd");
	FILE *fp = fopen((const char *)s->getUTF8Data(), "rb");
	
	if(!cont)
	{
		ptr_position = 0;
	}
	
	
	if (fp == NULL)
	{
        return mkString(error_no_file, strlen(error_no_file));
	}else{
		
	fseek(fp, ptr_position, SEEK_SET);
	
	_word = (char*) malloc (sizeof(char)*lSize);
	b_read = fread(_word, sizeof(char), lSize, fp);
	
	ptr_position = ftell(fp);
	
	fclose(fp);
	}
	
	if(b_read != lSize)
	{
        return mkString(cant_read_file, strlen(cant_read_file));
	}
	
	String str = mkString(_word, strlen(_word));
	
	free(_word);
	return str;
}

//%
int _fileSize(String s)
{
	long lSize;
	
    SDFileSystem sd(P0_21, P0_22, P0_23, P0_16, "sd");
	FILE *fp = fopen((const char *)s->getUTF8Data(), "rb");
	
	if (fp == NULL)
	{
        return 0;
	}else{
		
	// obtain file size:
	fseek (fp , 0 , SEEK_END);
	lSize = ftell(fp);
	rewind(fp);
	fclose(fp);
	}
	
	return lSize;
}


} // namespace im01