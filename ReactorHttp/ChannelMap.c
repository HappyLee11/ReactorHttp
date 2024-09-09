#include "ChannelMap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct ChannelMap* channelMapInit(int size)
{
    struct ChannelMap* map = (struct ChannelMap*)malloc(sizeof(struct ChannelMap));
    map->size = size;
    map->list = (struct Channel**)malloc(size * sizeof(struct Channel*));
    return map;
}

void ChannelMapClear(struct ChannelMap* map)
{
    if (map != NULL)
    {
        for (int i = 0; i < map->size; ++i)
        {
            if (map->list[i] != NULL)
            {
                free(map->list[i]);
            }
        }
        free(map->list);
        map->list = NULL;
    }
    map->size = 0;
}

bool makeMapRoom(struct ChannelMap* map, int newSize, int unitSize)
{
    if (map->size < newSize)
    {
        int curSize = map->size;
        // 容量每次扩大原来的一倍
        while (curSize < newSize)
        {
            curSize *= 2;
        }
        // 扩容 realloc
        struct Channel** temp = realloc(map->list, curSize * unitSize);
        if (temp == NULL)
        {
            return false;
        }
        map->list = temp;
        memset(&map->list[map->size], 0, (curSize - map->size) * unitSize);
        map->size = curSize;
    }
    return true;
}

//也就是说menset就是将指定区域内的内容设定为特定的值，这里将已有的内存后面的新分配的空间设置为0，就是将空间初始化掉；
	//扩容的思想就是先获取新的所需空间大小是多少，然后根据新空间来两倍两倍的扩充空间，直达比新空间所需容量大
	//然后再利用realloc来对已有的空间进行扩充到所需的新空间大小
	//然后对所扩充的新内存将他们初始化；然后再将之前的空间size值变为新空间大小值，然后就完成扩充


