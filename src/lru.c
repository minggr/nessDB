#include <stdlib.h>
#include <string.h>
#include "uthash.h"
#include "lru.h"

typedef struct cache
{
	char* k;
	char* v;
	UT_hash_handle hh;
}cache_t;

static cache_t* _cache=NULL;


char* lru_find(char* k)
{
	cache_t* item;
	HASH_FIND_STR(_cache,k,item);
	if(item)
	{
		HASH_DELETE(hh,_cache,item);
		HASH_ADD_KEYPTR(hh,_cache,item->k,strlen(item->k),item);
		return item->v;
	}

	return NULL;
}

void lru_add(char* k,char* v)
{
	cache_t* item,*tmp_item;
	item=(cache_t*)malloc(sizeof(cache_t));
	item->k=strdup(k);
	item->v=strdup(v);
	HASH_ADD_KEYPTR(hh,_cache,item->k,strlen(item->k),item);
	if(HASH_COUNT(_cache)>=MAX_CACHE_SIZE)
	{
		HASH_ITER(hh,_cache,item,tmp_item)
		{
			HASH_DELETE(hh,_cache,item);
			free(item->k);
			free(item->v);
			free(item);
			break;
		}
	}
}

