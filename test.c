#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*str;
	size_t			i;

	i = 0;
	str = (unsigned char *)b;
	while (i < len)
	{
		str[i] = (unsigned char)c;
		i++;
	}
	return (str);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*adst;
	unsigned char	*asrc;
	size_t			i;

	i = 0;
	adst = (unsigned char *)dst;
	asrc = (unsigned char *)src;
	if (dst == src)
		return (dst);
	while (n > i)
	{
		adst[i] = asrc[i];
		i++;
	}
	return (dst);
}


void myfree(void * p) 
{
    int	*in;
	
	in = p;
    if (in) 
	{
        --in; 
		free(in);
    }
}

void *mymalloc(int n) 
{
    int *result;
	 
	result = malloc(n + sizeof(int));
    if (result) 
	{
		*result = n;
		++result;
		ft_memset(result,0,n);
	}
    return result;
}

int getsize(void * p) 
{
    int * in = p;
    if (in) 
	{
		--in;
		return *in;
	}
    return -1;
}


void *reallocation(void *ptr,int size) 
{
    void *newptr;
    int msize;
    msize = getsize(ptr);
    printf("msize=%d\n", msize);
    if (size <= msize)
        return ptr;
    newptr = mymalloc(size);
    ft_memcpy(newptr, ptr, msize);
    // myfree(ptr);
    return newptr;
}

int main() {
    char * aa = mymalloc(50);
    char * bb ;
    printf("aa size is %d\n",getsize(aa));
    strcpy(aa,"my cookie");
    bb = reallocation(aa,100);
    printf("bb size is %d\n",getsize(bb));
    printf("<%s>\n",bb);
    // myfree(bb);
}