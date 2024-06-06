//implement some simple algorithm with C

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>

#define MAX 256

//string copy
//CAUTION!! string copy will cover destition string
/*
first, set a character pointer,save points str1(first element address) 
second,set variable count str1 length
third,loop: copy str2 to str1,until meet '\0' end.
last, return os(it's means string str2 cover str1's)
addtional: rounite call argmunt my_strcpy(str1, str2, sizeof(str1))
such as, we operate pointer to implement string copy!
*/
char* my_strcpy(char* str1, const char* str2, size_t str1_sz)
{	
	char* os = str1;
	size_t i = 0;    //set count to compare str1 length

	while(i< str1_sz - 1 && (*str1++ = *str2++) != '\0')
		i++;
	if(i == str1_sz -1)
		*str1 = '\0';
	return os;
}

//string copy before N to destition string
//caution:n-- is loop condition(not exceed n)!NOT get out loop!
//second while loop keeps str2 length less n,str1 fill '\0'
char* my_strncpy(char* str1, const char* str2, unsigned int n)
{
    char* os = str1;
    while(n-- > 0 && (*str1++ = *str2++) != '\0')
        ;
    while(n-- > 0)      //if str2 length less n
        *str1++ = '\0';
    return os;
}

//safe copy
//key is --n > 0 and *deat=0,so cpoy size = n-1
char* safe_my_strcpy(char* dest, const char* src, int n)
{
    char* os = dest;
    if(n <= '\0')
        return os;
    while(--n > 0 &&(*dest++ = *src++) != '\0')
        ;
    *dest = '\0';    //keep destition string end is '\0'
    return os;
}

//string compare
/*
first, loop:judge str1 whether exist,and str1 whether equal str2
second, return str1 - str2(casts unsigned char)
extend: return value is int type,unsigned char type fetch value range in "0~255",
while return 0, prove str1==str2;
	    return positive means str1>str2;
      return negative means str1<str2
*/
int my_strcmp(const char* str1, const char* str2)
{
	while(*str1 && *str1 == *str2){
			str1++;
			str2++;
	}
	return (unsigned char)*str1 - (unsigned char)*str2;
}

//compare before N character from two string
int my_strncmp(const char* str1, const char* str2, unsigned int n)
{
    if(n < 0){
        printf("compare size error.\n");
        return -1;
    }
    while(n > 0 && *str1 && *str1 == *str2){
        n--;
        str1++,str2++;
    }
    if(n == 0)
        return 0;
    return (unsigned char*)str1 - (unsigned char*)str2;
} 

//string length
//if calculate total size,only needs +1
size_t my_strlen(const char* str)
{	
	const char* p = str;
	while(*p)		//euqal *p!='\0'
		p++;
	return p - str;		//amount to (tail - head)
}

//search character in string
char* my_strchr(const char* str, char c)
{
    while(*str){
        if(*str == c){
            return (char*)str;
        }
        str++;
    }
    return 0;
}

//exchange character array of number to intger
int my_atoi(const char* str)
{
    int n = 0;
    while(*str >= '0' && *str <= '9')
        n = n * 10 + *str++ - '0';      //exchange formula
    return n;
}

//memory block copy
void* my_memmove(void* dest, const void* src, size_t n)
{
    char* vad;
    const char* vas;

    vad = dest;
    vas = src;
    if(vas < vad && vas + n > vad){     //overlap
        vas += n;
        vad += n;
        while(n-- > 0)
            *--vad = *--vas;            //copy from back to front
    }else{                              //not overlap
        while(n-- > 0)
            *vad++ = *vas++;
    }
    return dest;
}

//memory compare
int my_memcmp(const void* v1, const void* v2, unsigned int n)
{
    const unsigned char *s1 = v1, *s2 = v2;

    while(n-- > 0){
        if (*s1 != *s2){
            return *s1 - *s2;
            s1++;
            s2++;
        }
    }
    return 0;
}

/*Summary:
1.string is essentially a character array,the end bit is '\0',string's 
  effective length no include '\0',but total size include '\0',
  in C, '\0' equal 0.
2.string not modify(only read) when use pointer to define,this moment string 
  in memory only read section(that string equal constant).
3.if use array or dynamic memory allocate to define, string can to modify
  beacause this moment string in stack/heap.
4.use pointer traverse string(example calculate length,copy,compare..)
  more convenient://set pointer variable save string(get begin address)
                  //pointer backward until to '\0'
5.string name is a pointer of points to string,it's string begin address.
  it's means it CAN operable sub(example "my_strlen" fuction:you could use
  local variable pointer traverse string end)! and pointer sub only sence.
Supplement:array name just is constant pointer of points to array first 
           element address,and not modify.
*/
