#line 1 "test.cpp"
#line 1 "/usr/include/assert.h"



extern "C" {











 
 
 

 
 
 

#ident "$Revision$"









 







extern void __assert(const char *, const char *, int);
#line 49 "/usr/include/assert.h"


}


#line 2 "test.cpp"
#line 1 "/usr/include/stdio.h"



extern "C" {

#ident "$Revision$"
















 
 
 

 
 
 





 
#line 1 "/usr/include/standards.h"

















 
#ident "$Id$"





























 












 












 

#line 85 "/usr/include/standards.h"
















 
#line 111 "/usr/include/standards.h"












 












 
#line 143 "/usr/include/standards.h"







 
#line 157 "/usr/include/standards.h"


 
#line 166 "/usr/include/standards.h"








 
#line 182 "/usr/include/standards.h"









 


















 
#line 217 "/usr/include/standards.h"







 




 


#line 37 "/usr/include/stdio.h"
#line 1 "/usr/include/sgidefs.h"










 




extern "C" {


#ident "$Revision$"















 






 





 









 


		 










 



































 











 






 
#line 135 "/usr/include/sgidefs.h"

typedef int __int32_t;
typedef unsigned  __uint32_t;

#line 145 "/usr/include/sgidefs.h"



































 

	 
typedef long long __int64_t;
typedef unsigned long long  __uint64_t;

#line 215 "/usr/include/sgidefs.h"




typedef __int32_t __psint_t;
typedef __uint32_t __psunsigned_t;










 
#line 239 "/usr/include/sgidefs.h"

 
typedef __int32_t __scint_t;
typedef __uint32_t __scunsigned_t;






}


#line 38 "/usr/include/stdio.h"





typedef unsigned int 	size_t;









typedef int 	ssize_t;








typedef __int64_t	fpos_t;





 


 
typedef	__int64_t	off64_t;	 


#line 82 "/usr/include/stdio.h"
typedef __int64_t	off_t;		 










 
typedef	__int64_t	fpos64_t;





 


typedef char *va_list;













#line 123 "/usr/include/stdio.h"







#line 141 "/usr/include/stdio.h"










#line 157 "/usr/include/stdio.h"
















typedef struct	 








 
__file_s

{

	int		_cnt;	 




	unsigned char	*_ptr;	 
	unsigned char	*_base;	 





	unsigned char	_flag;	 
	unsigned char	_o_file;	 
	unsigned short	_file;	 




} FILE;

extern FILE		__iob[100];	

extern FILE		*_lastbuf;
extern unsigned char 	*_bufendtab[];
extern unsigned char	 _sibuf[], _sobuf[];


extern int	remove(const char *);
extern int	rename(const char *, const char *);
extern FILE	*tmpfile(void);
extern char	*tmpnam(char *);
extern int	fclose(FILE *);
extern int	fflush(FILE *);
extern FILE	*fopen(const char *, const char *);
extern FILE	*freopen(const char *, const char *, FILE *);
extern void	setbuf(FILE *, char *);
extern int	setvbuf(FILE *, char *, int, size_t);
 
extern int	fprintf(FILE *, const char *, ...);
 
extern int	fscanf(FILE *, const char *, ...);
 
extern int	printf(const char *, ...);
 
extern int	scanf(const char *, ...);

 
extern int	snprintf(char *, ssize_t, const char *, ...);

 
extern int	sprintf(char *, const char *, ...);
 
extern int	sscanf(const char *, const char *, ...);
extern int	vfprintf(FILE *, const char *,   char *);
extern int	vprintf(const char *,   char *);

extern int	vsnprintf(char *, ssize_t, const char *,   char *);

extern int	vsprintf(char *, const char *,   char *);


#pragma intrinsic (printf)
#pragma intrinsic (fprintf)
#pragma intrinsic (sprintf)
#pragma intrinsic (scanf)
#pragma intrinsic (fscanf)
#pragma intrinsic (sscanf)


extern int	fgetc(FILE *);
extern char	*fgets(char *, int, FILE *); 
extern int	fputc(int, FILE *);
extern int	fputs(const char *, FILE *);
extern int	getc(FILE *);
extern int	getchar(void);
extern char	*gets(char *);
extern int	putc(int, FILE *);
extern int	putchar(int);
extern int	puts(const char *);
extern int	ungetc(int, FILE *);
extern size_t	fread(void *, size_t, size_t, FILE *);
#pragma int_to_unsigned fread
extern size_t	fwrite(const void *, size_t, size_t, FILE *);
#pragma int_to_unsigned fwrite
extern int	fgetpos(FILE *, fpos_t *);
extern int	fseek(FILE *, long, int);
extern int	fsetpos(FILE *, const fpos_t *);
extern long	ftell(FILE *);
extern void	rewind(FILE *);
extern void	clearerr(FILE *);
extern int	feof(FILE *);
extern int	ferror(FILE *);
extern void	perror(const char *);

extern int	__filbuf(FILE *);	
extern int	__flsbuf(int, FILE *);	


	 
extern FILE    *fdopen(int, const char *);
extern int	fileno(FILE *);



	 
extern void	flockfile(FILE *);
extern int	ftrylockfile(FILE *);
extern void	funlockfile(FILE *);
extern int	getc_unlocked(FILE *);
extern int	putc_unlocked(int, FILE *);
extern int	getchar_unlocked(void);
extern int	putchar_unlocked(int);



extern FILE	*popen(const char *, const char *);
extern int	pclose(FILE *);


	 
#line 1 "/usr/include/getopt.h"


#ident "$Revision$"

extern "C" {



















 



extern int	getopt(int, char *const *, const char *);

extern char	*optarg;
extern int	opterr;
extern int	optind;
extern int	optopt;







 


extern int	getsubopt(char **, char *const *, char **);
extern void	getoptreset(void);



}


#line 309 "/usr/include/stdio.h"
extern char	*ctermid(char *);
extern char	*cuserid(char *);
extern char	*tempnam(const char *, const char *);
extern int	getw(FILE *);
extern int	putw(int, FILE *);




	 
extern char	*mktemp(char *);
extern int	mkstemp(char *);
extern int	setbuffer(FILE *, char *, int);
extern int	setlinebuf(FILE *);
extern int	system(const char *);



	 
extern off_t	ftello(FILE *);
extern int	fseeko(FILE *, off_t, int);



	 
extern int	fgetpos64(FILE *, fpos64_t *);
extern FILE	*fopen64(const char *, const char *);
extern FILE	*freopen64(const char *, const char *, FILE *);
extern int	fseek64(FILE *, __int64_t, int);
extern int	fseeko64(FILE *, off64_t, int);
extern int	fsetpos64(FILE *, const fpos64_t *);
extern __int64_t ftell64(FILE *);
extern off64_t	ftello64(FILE *);
extern FILE	*tmpfile64(void);



extern int	__semputc(int, FILE *);
extern int	__semgetc(FILE *);
extern int	__us_rsthread_stdio;



extern char	*ctermid_r(char *);














 

 





 




 
#line 392 "/usr/include/stdio.h"

 
#line 403 "/usr/include/stdio.h"

#line 448 "/usr/include/stdio.h"






}
#line 3 "test.cpp"
#line 1 "/usr/include/math.h"




extern "C" {





 
 
 
 
 
 
 
 

 













 















 





 



 




typedef union _h_val {

        unsigned long i[2];




        double d;
} _h_val;


extern const _h_val __huge_val;
#line 86 "/usr/include/math.h"

#line 96 "/usr/include/math.h"




 
extern double	acos(double);

#pragma no side effects (acos)


extern float	acosf(float);

#pragma no side effects (acosf)


extern double	asin(double);

#pragma no side effects (asin)


extern float	asinf(float);

#pragma no side effects (asinf)


extern double	atan(double);

#pragma no side effects (atan)


extern float	atanf(float);

#pragma no side effects (atanf)




#pragma intrinsic (acos)
#pragma intrinsic (acosf)
#pragma intrinsic (asin)
#pragma intrinsic (asinf)
#pragma intrinsic (atan)
#pragma intrinsic (atanf)


extern double	atan2(double, double);

#pragma no side effects (atan2)


extern float	atan2f(float, float);

#pragma no side effects (atan2f)


extern double	cos(double);

#pragma no side effects (cos)


extern float	cosf(float);

#pragma no side effects (cosf)


extern double	sin(double);

#pragma no side effects (sin)


extern float	sinf(float);

#pragma no side effects (sinf)


extern double	tan(double);

#pragma no side effects (tan)


extern float	tanf(float);

#pragma no side effects (tanf)




#pragma intrinsic (cos)
#pragma intrinsic (cosf)
#pragma intrinsic (sin)
#pragma intrinsic (sinf)
#pragma intrinsic (tan)
#pragma intrinsic (tanf)


extern double	cosh(double);

#pragma no side effects (cosh)


extern float	coshf(float);

#pragma no side effects (coshf)


extern double	sinh(double);

#pragma no side effects (sinh)


extern float	sinhf(float);

#pragma no side effects (sinhf)


extern double	tanh(double);

#pragma no side effects (tanh)


extern float	tanhf(float);

#pragma no side effects (tanhf)


extern double	exp(double);

#pragma no side effects (exp)


extern float	expf(float);

#pragma no side effects (expf)




#pragma intrinsic (exp)
#pragma intrinsic (expf)


extern double	frexp(double, int *);






extern double	ldexp(double, int);






extern double	log(double);

#pragma no side effects (log)


extern float	logf(float);

#pragma no side effects (logf)


extern double	log10(double);

#pragma no side effects (log10)


extern float	log10f(float);

#pragma no side effects (log10f)




#pragma intrinsic (log)
#pragma intrinsic (logf)
#pragma intrinsic (log10)
#pragma intrinsic (log10f)


extern double	modf(double, double *);

 

extern float	modff(float, float *); 

extern double	pow(double, double);

#pragma no side effects (pow)


 
extern float	powf(float, float);

#pragma no side effects (powf)


extern double	sqrt(double);

#pragma no side effects (sqrt)


extern float	sqrtf(float);

#pragma no side effects (sqrtf)


extern double	ceil(double);

#pragma no side effects (ceil)


extern float	ceilf(float);

#pragma no side effects (ceilf)


extern double	fabs(double);

#pragma no side effects (fabs)


 

extern float	fabsf(float);

#pragma no side effects (fabsf)


extern double	floor(double);

#pragma no side effects (floor)


extern float	floorf(float);

#pragma no side effects (floorf)


extern double	fmod(double, double);

#pragma no side effects (fmod)


 

extern float	fmodf(float, float);

#pragma no side effects (fmodf)





 
 
#line 368 "/usr/include/math.h"

extern int signgam;

extern double	gamma(double);
extern double	lgamma(double);

extern int	isnan(double);

#pragma no side effects (isnan)


#line 385 "/usr/include/math.h"

extern double	erf(double);

#pragma no side effects (erf)


extern double	erfc(double);

#pragma no side effects (erfc)


extern double	hypot(double, double);

#pragma no side effects (hypot)


extern double	j0(double);

#pragma no side effects (j0)


extern double	j1(double);

#pragma no side effects (j1)


extern double	jn(int, double);

#pragma no side effects (jn)


extern double	y0(double);

#pragma no side effects (y0)


extern double	y1(double);

#pragma no side effects (y1)


extern double	yn(int, double);

#pragma no side effects (yn)













 
extern double	rint(double);

#pragma no side effects (rint)


extern double	asinh(double);

#pragma no side effects (asinh)


extern double	acosh(double);

#pragma no side effects (acosh)


extern double	atanh(double);

#pragma no side effects (atanh)


extern double	cbrt(double);

#pragma no side effects (cbrt)


extern double	log1p(double);

#pragma no side effects (log1p)


extern double	expm1(double);

#pragma no side effects (expm1)


extern double	logb(double);

#pragma no side effects (logb)


extern int	ilogb(double);

#pragma no side effects (ilogb)


extern double	nextafter(double, double);

#pragma no side effects (nextafter)


extern double	remainder(double, double);

#pragma no side effects (remainder)


extern double	scalb(double, double);

#pragma no side effects (scalb)






 

extern long double fabsl( long double );

extern long double acosl( long double );

extern long double asinl( long double );

extern long double atanl( long double );



#pragma intrinsic (acosl)
#pragma intrinsic (asinl)
#pragma intrinsic (atanl)


extern long double atan2l( long double, long double );

struct __cabsl_s { long double a,b; };

extern long double cabsl( struct __cabsl_s );

extern long double ceill( long double );

extern long double copysignl( long double, long double );

extern long double cosl( long double );



#pragma intrinsic (cosl)


extern long double coshl( long double );

extern long double erfl( long double );

extern long double erfcl( long double );

extern long double expl( long double );



#pragma intrinsic (expl)


extern int finitel( long double );

extern long double floorl( long double );

extern long double fmodl( long double, long double );

extern long double hypotl( long double, long double );

extern long double j0l( long double );

extern long double j1l( long double );

extern long double jnl( int, long double );

extern long double logl( long double );

extern long double log1pl( long double );

extern long double log10l( long double );



#pragma intrinsic (logl)
#pragma intrinsic (log10l)


extern long double logbl( long double );

extern long double powl( long double, long double );

extern long double rintl( long double );

extern long double sinl( long double );



#pragma intrinsic (sinl)


extern long double sinhl( long double );

extern long double sqrtl( long double );

extern long double tanl( long double );



#pragma intrinsic (tanl)


extern long double tanhl( long double );

extern long double truncl( long double );

extern long double y0l( long double );

extern long double y1l( long double );

extern long double ynl( int, long double );



#pragma no side effects (fabsl)
#pragma no side effects (acosl)
#pragma no side effects (asinl)
#pragma no side effects (atanl)
#pragma no side effects (atan2l)
#pragma no side effects (cabsl)
#pragma no side effects (ceill)
#pragma no side effects (copysignl)
#pragma no side effects (cosl)
#pragma no side effects (coshl)
#pragma no side effects (expl)
#pragma no side effects (erfl)
#pragma no side effects (erfcl)
#pragma no side effects (finitel)
#pragma no side effects (floorl)
#pragma no side effects (fmodl)
#pragma no side effects (hypotl)
#pragma no side effects (j0l)
#pragma no side effects (j1l)
#pragma no side effects (jnl)
#pragma no side effects (logl)
#pragma no side effects (log10l)
#pragma no side effects (logbl)
#pragma no side effects (powl)
#pragma no side effects (rintl)
#pragma no side effects (sinl)
#pragma no side effects (sinhl)
#pragma no side effects (sqrtl)
#pragma no side effects (tanl)
#pragma no side effects (tanhl)
#pragma no side effects (truncl)
#pragma no side effects (y0l)
#pragma no side effects (y1l)
#pragma no side effects (ynl)



extern	int	signgaml;






 

enum version { c_issue_4, ansi_1, strict_ansi };
extern const enum version _lib_version;

struct __cabs_s { double a,b; };

extern double	cabs(struct __cabs_s);

#pragma no side effects (cabs)


extern double	copysign(double, double);

#pragma no side effects (copysign)


extern double	drem(double, double);

#pragma no side effects (drem)


extern int	finite(double);

#pragma no side effects (finite)





 

 

extern long double frexpl( long double, int *);

extern int isnanl( long double );

extern long double ldexpl( long double, int );

extern long double modfl( long double, long double *);

extern long double nextafterl( long double, long double );

extern long double scalbl( long double, long double );



#pragma no side effects (isnanl)
#pragma no side effects (ldexpl)
#pragma no side effects (nextafterl)
#pragma no side effects (scalbl)





extern double	atof(const char *);

extern double   strtod(const char *, char **);

extern double   trunc(double);

#pragma no side effects (trunc)


extern int	rand(void);
extern void	srand(unsigned);

extern long	random(void);
extern void	srandom(unsigned);
extern char *	initstate(unsigned int, char *, size_t);
extern char *	setstate(const char *);

extern double	drand48(void);
extern double	erand48(unsigned short [3]);
extern long	lrand48(void);
extern long	nrand48(unsigned short [3]);
extern long	mrand48(void);
extern long	jrand48(unsigned short [3]);
extern void	srand48(long);
extern unsigned short * seed48(unsigned short int [3]);
extern void	lcong48(unsigned short int [7]);

 

#line 762 "/usr/include/math.h"




 











#line 813 "/usr/include/math.h"






extern long double gammal( long double );

extern long double lgammal( long double );




 








inline int abs(int x) {return x > 0 ? x : -x;}



 
extern float	fhypot(float, float);

#pragma no side effects (fhypot)


extern float	hypotf(float, float);

#pragma no side effects (hypotf)


struct __fcabs_s { float a,b; };

extern float	fcabs(struct __fcabs_s);

#pragma no side effects (fcabs)


extern float	fexpm1(float);

#pragma no side effects (fexpm1)


extern float	expm1f(float);

#pragma no side effects (expm1f)


extern float	log1pf(float);

#pragma no side effects (log1pf)


extern float	truncf(float);

#pragma no side effects (truncf)





#pragma intrinsic (hypotf)
#pragma intrinsic (fhypot)



#line 907 "/usr/include/math.h"

#line 915 "/usr/include/math.h"

#line 929 "/usr/include/math.h"

#line 937 "/usr/include/math.h"

struct math_exception {
	int type;
	char *name;
	double arg1;
	double arg2;
	double retval;
};

extern int matherr(struct math_exception *p);



#line 1 "/usr/include/svr4_math.h"
 














 

 





extern "C" {


#line 33 "/usr/include/svr4_math.h"


}


#line 951 "/usr/include/math.h"









 


#pragma intrinsic (sqrt)
#pragma intrinsic (sqrtf)

#pragma intrinsic (pow)
#pragma intrinsic (powf)


#pragma intrinsic (fabs)
#pragma intrinsic (fabsf)



}  





 

#line 997 "/usr/include/math.h"

#line 1211 "/usr/include/math.h"



#line 4 "test.cpp"
#line 1 "/usr/include/string.h"



extern "C" {

#ident "$Revision$"
















 
 
 
 

 
 
 
 





 


#line 49 "/usr/include/string.h"





#line 63 "/usr/include/string.h"



 
extern void *memcpy(void *, const void *, size_t);
extern void *memmove(void *, const void *, size_t);
extern char *strcpy(char *, const char *);
extern char *strncpy(char *, const char *, size_t);
extern char *strcat(char *, const char *);
extern char *strncat(char *, const char *, size_t);
extern void *memccpy(void *, const void *, int, size_t);
extern int memcmp(const void *, const void *, size_t);
extern int strcmp(const char *, const char *);
extern int strcoll(const char *, const char *);
extern int strncmp(const char *, const char *, size_t);
extern size_t strxfrm(char *, const char *, size_t);

extern void *memchr(const void *, int, size_t);
extern char *strchr(const char *, int);

extern size_t strcspn(const char *, const char *);
#pragma int_to_unsigned strcspn

extern char *strpbrk(const char *, const char *);
extern char *strrchr(const char *, int);

extern size_t strspn(const char *, const char *);
#pragma int_to_unsigned strspn

extern char *strstr(const char *, const char *);

extern char *strtok(char *, const char *);
extern void *memset(void *, int, size_t);
extern char *strerror(int);
extern size_t strlen(const char *);
#pragma int_to_unsigned strlen


extern int ffs(int);
 
extern int strcasecmp(const char *, const char *);
extern int strncasecmp(const char *, const char *, size_t);



extern char *strdup(const char *);



extern char *strtok_r(char *, const char *, char **);





 




#pragma intrinsic (strcpy)  
#pragma intrinsic (strcmp)  
#pragma intrinsic (strlen)  


#pragma intrinsic (memcpy)
#pragma intrinsic (memmove)
#pragma intrinsic (memset)




}


#line 206 "/usr/include/string.h"

#line 5 "test.cpp"
#line 1 "../Globals/lglobal.h"








 

enum DerivationDirection
{
	eForward,
	eBackward
};


enum
{
        eMaxIdentifierLength = 32,
        eMaxParams = 64,
        eMaxFormalModules = 32
};

typedef short int ModuleIdType;

enum mReservedModuleValues
{
	SB_id = 0,
	EB_id,
	eFirstModuleId
};








#line 6 "test.cpp"
#line 1 "../Globals/lsysintrfc.h"




class ActualParameters
{
public:
  ActualParameters();
  const char* pArg(int) const;
  void AddModuleAddr(const char*);
  int Count() const
  { return _count; }
  void Reset();
private:
  const char* _arr[eMaxFormalModules];
  int _count;
};

struct CallerData
{
  void Reset();
  ActualParameters RCntxt;
  ActualParameters Strct;
  ActualParameters LCntxt;
};


void _Add(const void*, int);

template<class T>
void Produce(T t)
{
  _Add(&t, sizeof(T));
}

typedef void (*ProdCaller)(const CallerData*);

struct ProductionModules
{
  ModuleIdType arr[eMaxFormalModules];
  int count;
};

struct ProductionPrototype
{
  ProductionModules LCntxt;
  ProductionModules Strct;
  ProductionModules RCntxt;
  ProdCaller pCaller;
};


struct ModuleData
{
  const char* Name;
  int size;
};

const ModuleData* GetModuleData(int);
const char* GetModuleName(int);
int NumOfModules();
int GetSizeOf(int);
int DerivationLength();
int NumOfProductions();
const ProductionPrototype& GetProductionPrototype(int);
int NumOfIProductions();
const ProductionPrototype& GetIProductionPrototype(int);
int NumOfConsidered();
ModuleIdType GetConsidered(int i);
int NumOfIgnored();
ModuleIdType GetIgnored(int i);


void Start();
void StartEach();
void EndEach();
void End();


 
extern FILE* fOut;






#line 7 "test.cpp"
#line 1 "../Generate/succstor.h"



class SuccessorStorage
{
public:
  SuccessorStorage();
  ~SuccessorStorage();
  void Clear()
  { _appendPos = 0; }
  template <class T>void Append(T t)
  { _Add(&t, sizeof(T)); }
  int Size() const
  { return _appendPos; }
  const char* Bf() const
  { return _mem; }
  void Add(const void* pX, int size)
  { _Add(pX, size); }
private:
  void _Add(const void*, int); 
  void _Grow(int);
  char* _mem;
  int _size;
  int _appendPos;
  enum
  { eInitSize = 4096 };
};





#line 8 "test.cpp"





derivation length: 51 - strlen("module and produce");

module A();
module B(int,float);
module C();
module D(int,int);
module E();
module F();
module G();
module H();
module I(int);
module J();
module K();
module L();
module Plus();
module Minus();

ignore: Plus Minus;

Start:
{
   
  produce A() SB()Plus()B(1,2.0) SB()Minus()C()D(3,4)E()EB() F()G()EB() SB()H()I(5)J()EB() K()L();
}

End:
{
}


A() >  SB() B(a,b)  EB() :
{
  produce B(a,b) A();
}

A() >   SB() B(a,b) SB() C() EB() EB() :
{
  produce A() SB() B(a,b)  C() EB();
}

A() > SB() B(a,b) SB() C() EB() F() EB() :
{
  produce A() SB() C() EB() B(a,b) F();
}

A() > SB() EB()  SB() H() I(c) EB()  :
{
  produce  A() I(c) H();
}

A() > SB() B(a,b) EB() SB() H() EB() K():
{
  produce A() SB()B(a,b)EB() SB()H()EB() K() L();
}

A()K() < L():
{
  produce L()I(1);
}

A() SB() B(a,b) SB() C()   < D(c,d):
{
  produce D(c,d) I(1);
}



Plus() :
{

}

Minus() :
{

}
           
